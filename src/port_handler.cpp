// #include "port_handler.h"

// extern UART_HandleTypeDef huart1;

// uint8_t rd_ptr;
// bool DMA_TRANSMIT_COMPLETE;
// bool MESSAGE_RECEIVED;

// PortHandler::PortHandler()
// { 
//   // set data direction pin is low
//   HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_RESET);

//   // turn on the UART RX port
//   if (HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, UART_RX__SZ) != HAL_OK) {
//     Error_Handler();
//   }

//   DMA_TRANSMIT_COMPLETE = false;
//   MESSAGE_RECEIVED = false;
// }

// void PortHandler::receiveMessages()
// {
//   if (MESSAGE_RECEIVED)
//   {
//     transferBufferToQueue();
//   }
// }

// void PortHandler::transferBufferToQueue()
// {

// }

// void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
// {
//   MESSAGE_RECEIVED = true;
//   UART_rx_transfer_to_queue(huart);
  
//   if (HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, UART_RX__SZ) != HAL_OK) {
//     Error_Handler();
//   }
  
// }

// void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart) {
  
//   DMA_TRANSMIT_COMPLETE = true;

// }

// void UART_Transmit(uint8_t *message, uint8_t size) {

//   DMA_TRANSMIT_COMPLETE = false;  
//   HAL_UART_Transmit_IT(&huart1, message, size);
  
// }
