#ifndef __PORT_HANDLER_H
#define __PORT_HANDLER_H

#include "utility.h"
#include "stm32f1xx_hal.h"
#include "message_queue.h"

#define UART_RX__SZ 64
#define UART_TX__SZ 25
#define HEADER_SIZE 4
#define HEADER_MASK (uint32_t)0xFFFFFD00
#define __UART_DMA_WRITE_PTR(__handle__) ((UART_RX__SZ - (uint32_t)__handle__->hdmarx->Instance->CNDTR) & (UART_RX__SZ - 1))  
#define TRUE    1
#define FALSE	0

void UART_DMA_Init();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void UART_Transmit(uint8_t *message, uint8_t size);
uint8_t get_one_byte_from_buffer(UART_HandleTypeDef *huart);
bool rxBuffer_is_empty(UART_HandleTypeDef *huart); 
bool validate_header(uint32_t header);
uint32_t get_header(UART_HandleTypeDef *huart);
void UART_rx_transfer_to_queue(UART_HandleTypeDef *huart);


#endif /* __PORT_HANDLER_H */