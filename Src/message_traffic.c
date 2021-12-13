#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "message_traffic.h"


// HAL_message_queue 
extern MessageQueue *HAL_message_queue;
extern SemaphoreHandle_t task_lock;
extern DSelf self;
extern bool DMA_TRANSMIT_COMPLETE;

const uint8_t header_size = 4;
const uint8_t length_size = 2;
const uint8_t id_size = 1;
const uint8_t instruction_size = 1;
const uint8_t crc_size = 2;

bool TRANSMIT_READY = false;
uint8_t ping[PING_SIZE] = {0xFF, 0xFF, 0xFD, 0x00, 0x01, 0x07, 0x00, STATUS, NONE, 0xBB, 0xBB, 0x01, 0x00, 0x00};


void processes_received_messages_task(void) {  

  // loop over HAL messages 
  while(HAL_message_queue->messageRdy) {
		xSemaphoreTake(task_lock, 100);
		
    // TODO: Revie byte stuffing as defined in Dynamixel Protocol 2.0
    volatile int header = grab_number_of_bytes_B(HAL_message_queue, header_size); 
		volatile int packet_id = grab_number_of_bytes_B(HAL_message_queue, id_size);
    volatile int length = grab_number_of_bytes_L(HAL_message_queue, length_size);
    volatile uint8_t param_size = length - instruction_size - crc_size;
    volatile uint8_t instruction = (uint8_t)grab_number_of_bytes_L(HAL_message_queue, instruction_size);
     // TODO: Determine if this is little endian or big endian
    volatile int parameters = grab_number_of_bytes_B(HAL_message_queue, param_size);
    volatile int crc = grab_number_of_bytes_B(HAL_message_queue, crc_size);


    flush(HAL_message_queue);
    HAL_message_queue->messageRdy = false;

    xSemaphoreGive(task_lock);
    if (packet_id == self.id) {
      respond(instruction, parameters);
    }
  }

}

void respond(uint8_t instruction, int parameters)  {  
  
  switch (instruction) {
  case PING:  
    transmit_message(ping, PING_SIZE);
    break;
  
  default:
    break;
  }
}

void transmit_message(uint8_t *message, uint8_t size) {

  //xSemaphoreTake(task_lock, 100);
  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_SET);	
  UART_Transmit(message, size);
  while(DMA_TRANSMIT_COMPLETE != true){};
  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_RESET);	
  //xSemaphoreGive(task_lock);

}

// uint8_t* ping_respond(uint8_t*ping) {  

  
//   return ping;
// }

// uint8_t* read_respond(void) {

// }

// uint8_t* write_respond(void) {

// }

// uint8_t* reg_write_respond(void) {

// }

// uint8_t* action_respond(void) {

// }

// uint8_t* factory_reset_respond(void) {

// }

// uint8_t* reboot_respond(void) {

// }

// uint8_t* clear_respond(void) {

// }

// uint8_t* control_table_backup_respond(void) {

// }

// uint8_t* sync_read_respond(void) {

// }

// uint8_t* sync_write_respond(void) {

// }

// uint8_t* fast_sync_read_respond(void) {

// }

// uint8_t* bulk_read_respond(void) {

// }

// uint8_t* bulk_write_repsond(void) {

// }

// uint8_t* fast_bulk_read_respond(void) {

// }




/* @brief Retrieves number of bytes from a MessageQueue in little endian. 
 *  If queue contains: 0xABCDEF
 *  than this returns: 0xEFCDAB
 * @param queue:  MessageQueue from HAL
 * @param number: Number of bytes to return 
 * @return the packet of bytes requested
 */
int grab_number_of_bytes_L(MessageQueue* queue, uint8_t number) {  
    
  int retval = 0;
	uint8_t i;
  for ( i=0; i<number; i++) {
    uint8_t byte = 0;
    if (deQueue(queue, &byte)) {
      retval += (byte << (i*8));			
    }
  }

  return retval;
}

/* @brief Retrieves number of bytes from a MessageQueue in big endian. 
 *  If queue contains: 0xABCDEF
 *  than this returns: 0xABCDEF
 * @param queue:  MessageQueue from HAL
 * @param number: Number of bytes to return 
 * @return the packet of bytes requested
 */
int grab_number_of_bytes_B(MessageQueue* queue, uint8_t number) {  
    
  volatile int retval = 0;
	volatile int i;  
  for ( i=number-1; i>=0; i--) {
    uint8_t byte = 0;
    if (deQueue(queue, &byte)) {
      retval += (int)(byte << ((uint8_t)i*8));			
    }
  }

  return retval;
}

