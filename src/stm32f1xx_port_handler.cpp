#include "stm32f1xx_port_handler.h"

/* Fields -------------------------------------------------------------------*/
MessageQueue *HAL_message_queue;

uint8_t rxBuffer[UART_RX__SZ];
uint8_t txBuffer[UART_TX__SZ];;
uint8_t rd_ptr;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
bool DMA_TRANSMIT_COMPLETE;
/* Methods ------------------------------------------------------------------*/

/* @brief Initializes UART and DMA port with handle allowing for UART receive to have direct
 * memory access. Receive uses idle line to trigger received event for variable HAL_message_queue
 * lenght.
 * 
 * @param void
 * @return void
 */
void UART_DMA_Init() {  
  
  HAL_message_queue = constructMessage();
  DMA_TRANSMIT_COMPLETE = false;

  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_RESET);

  if (HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuffer, UART_RX__SZ) != HAL_OK) {
    Error_Handler();
  }

  // Disable the Half-Transfer interrupt
  __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
  __HAL_DMA_DISABLE_IT(&hdma_usart1_tx, DMA_IT_HT);

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  UART_rx_transfer_to_queue(huart);
  
  if (HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuffer, UART_RX__SZ) != HAL_OK) {
    Error_Handler();
  }
  
}

void UART_Transmit(uint8_t *message, uint8_t size) {

  DMA_TRANSMIT_COMPLETE = false;  
  HAL_UART_Transmit_IT(&huart1, message, size);
  
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart) {
  
  // __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);   // enable idle line interrupt  
  DMA_TRANSMIT_COMPLETE = true;

}


/* @brief Transfers UART receive buffer to queue to enable prompt 
 * rx_buffer readines for next HAL_message_queue. Throws error if receive
 * idle event is thrown but buffer is empty.
 * 
 * @param void 
 * @return void
 */
void UART_rx_transfer_to_queue(UART_HandleTypeDef *huart) {
  volatile bool empty = false;
  volatile bool full = false;
  while(!empty && !full) {
    empty = rxBuffer_is_empty(huart);
    full = isFull(HAL_message_queue);
    enQueue(HAL_message_queue, get_one_byte_from_buffer(huart));
  }

  rd_ptr = 0;
  HAL_message_queue->messageRdy = true;
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
