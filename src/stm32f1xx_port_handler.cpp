#include "stm32f1xx_port_handler.h"
#include "stm32f1xx_hal_gpio.h"

/* Fields -------------------------------------------------------------------*/
MessageQueue *message;

uint8_t rxBuffer[UART_RX__SZ];
uint8_t txBuffer[UART_TX__SZ];
uint8_t rd_ptr;

/* Methods ------------------------------------------------------------------*/

/* @brief Initializes UART and DMA port with handle allowing for UART receive to have direct
 * memory access. Receive uses idle line to trigger received event for variable message
 * lenght.
 * 
 * @param void
 * @return void
 */
void UART_DMA_Init(UART_HandleTypeDef huart) {
  // track position of circular dma buffer
  rd_ptr = 0;  
  message = constructMessage();
  
  // set direction to receive
  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_SET);

  if (HAL_UART_Receive_DMA(&huart, rxBuffer, UART_RX__SZ) != HAL_OK) {
    Error_Handler();
  }
  __HAL_UART_ENABLE_IT(&huart, UART_IT_IDLE);   // enable idle line interrupt  
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  UART_rx_transfer_to_queue(*huart);
  __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);   // enable idle line interrupt  
}

/* @brief Transfers UART receive buffer to queue to enable prompt 
 * rx_buffer readines for next message. Throws error if receive
 * idle event is thrown but buffer is empty.
 * 
 * @param void 
 * @return void
 */
void UART_rx_transfer_to_queue(UART_HandleTypeDef huart) {

  while(!rxBuffer_is_empty(huart) && !isFull(message)) {
    enQueue(message, get_one_byte_from_buffer(huart));
  }
}

uint32_t get_header(UART_HandleTypeDef huart) {
  int i;
  uint32_t header = 0;
  for (i=0; i<4; i++) {
    header += (get_one_byte_from_buffer(huart) << i);
  }
  return header;
}

bool validate_header(uint32_t header) {
  bool flag = ((header & HEADER_MASK) == HEADER_MASK);
  return flag;
}

/* @brief Determines receive buffer is empty.
 * 
 * @param void
 * @return true if buffer is empty
 */
bool rxBuffer_is_empty(UART_HandleTypeDef huart) {
  uint16_t dma_ptr = __UART_DMA_WRITE_PTR(huart);
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
uint8_t get_one_byte_from_buffer(UART_HandleTypeDef huart) {
	uint8_t message_byte = 0;
  uint16_t dma_ptr = __UART_DMA_WRITE_PTR(huart);
	if(rd_ptr != dma_ptr) {
		message_byte = rxBuffer[rd_ptr++];
		rd_ptr &= (UART_RX__SZ - 1);
	}
	return message_byte;
}

MessageQueue* constructMessage(){
    MessageQueue *queue = (MessageQueue*) malloc(sizeof (MessageQueue)); 
    int i;
    queue->front = -1;
    queue->rear = 0;
    for (i=0; i<SIZE; i++){
        queue->message[i] = 0;    
    }
    return queue;
}


int enQueue(MessageQueue *queue, uint8_t data){
    if(isFull(queue)){
        return FALSE;
    } else if(isEmpty(queue)){
        queue->front = queue->rear;
        queue->message[queue->rear] = data;
        return TRUE;
    } else {
        queue->rear = nextRear(queue);
        queue->message[queue->rear] = data;
        return TRUE;
    }
}


uint8_t deQueue(MessageQueue *queue){
    if(isEmpty(queue)){
        return 0;
    } else if (queue->front == queue->rear) {
        uint8_t temp = queue->message[queue->front];
        queue->front = -1;
        return temp;
    } else {
        uint8_t temp = queue->message[queue->front];
        queue->front = nextFront(queue);
        return temp;
    }
}

uint8_t peek(MessageQueue *queue){
    return queue->message[queue->front];
}

int isEmpty(MessageQueue *queue){
    if(queue->front == -1){
        return TRUE;    
    }
    return FALSE;
}

int isFull(MessageQueue *queue){
    if(nextRear(queue)==queue->front){
        return TRUE;
    }
    return FALSE;
}

int nextRear(MessageQueue *queue){
    return (queue->rear + 1) % SIZE;
}

int nextFront(MessageQueue *queue){
    return (queue->front + 1) % SIZE;
}
