#include "stm32f1xx_port_handler.h"

/* Fields -------------------------------------------------------------------*/
MessageQueue *HAL_message_queue;

uint8_t rxBuffer[UART_RX__SZ];
uint8_t txBuffer[UART_TX__SZ];;
uint8_t rd_ptr;
extern UART_HandleTypeDef huart1;
bool DMA_TRANSMIT_COMPLETE;
/* Methods ------------------------------------------------------------------*/

/* @brief Initializes UART and DMA port with handle allowing for UART receive to have direct
 * memory access. Receive uses idle line to trigger received event for variable HAL_message_queue
 * lenght.
 * 
 * @param void
 * @return void
 */
void UART_DMA_Init(UART_HandleTypeDef *huart) {  
  
  HAL_message_queue = constructMessage();
  DMA_TRANSMIT_COMPLETE = false;
  // set direction to receive
  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_RESET);

  // initialize UART Receive
  if (HAL_UART_Receive_DMA(huart, rxBuffer, UART_RX__SZ) != HAL_OK) {
    Error_Handler();
  }

  __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);   // enable idle line interrupt  
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  UART_rx_transfer_to_queue(huart);
  __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);   // enable idle line interrupt  
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  DMA_TRANSMIT_COMPLETE = true;
	// HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_RESET);
	// volatile int x = 1;
	// x++;
}

void UART_Transmit(char *message, uint8_t size){
	
  // set direction pin to transmit
	HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_SET);	
  DMA_TRANSMIT_COMPLETE = false;
  HAL_UART_Transmit_DMA(&huart1, message, size);
  //HAL_UART_Transmit(&huart1, message, size, 100);	
	//HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_RESET);
	//volatile int x = 1;
}

/* @brief Transfers UART receive buffer to queue to enable prompt 
 * rx_buffer readines for next HAL_message_queue. Throws error if receive
 * idle event is thrown but buffer is empty.
 * 
 * @param void 
 * @return void
 */
void UART_rx_transfer_to_queue(UART_HandleTypeDef *huart) {

  while(!rxBuffer_is_empty(huart) && !isFull(HAL_message_queue)) {
    enQueue(HAL_message_queue, get_one_byte_from_buffer(huart));
  }
}

uint32_t get_header(UART_HandleTypeDef *huart) {
  int i;
  uint32_t header = 0;
  for (i=0; i<4; i++) {
    header += (get_one_byte_from_buffer(huart) << i);
  }
  return header;
}


/* @brief Determines receive buffer is empty.
 * 
 * @param void
 * @return true if buffer is empty
 */
bool rxBuffer_is_empty(UART_HandleTypeDef *huart) {
  uint16_t dma_ptr = __UART_DMA_WRITE_PTR(&huart);
	if(rd_ptr == dma_ptr) {
		return true;
	}
	return false;
}

/* @brief Grabs 1 byte of receive buffer.
 * 
 * @param void
 * @return 1 byte from receive buffer
 */
uint8_t get_one_byte_from_buffer(UART_HandleTypeDef *huart) {
	uint8_t message_byte = 0;
  uint16_t dma_ptr = __UART_DMA_WRITE_PTR(&huart);
	if(rd_ptr != dma_ptr) {
		message_byte = rxBuffer[rd_ptr++];
		rd_ptr &= (UART_RX__SZ - 1);
	}
	return message_byte;
}

