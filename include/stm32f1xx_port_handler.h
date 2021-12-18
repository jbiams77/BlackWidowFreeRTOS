#ifndef __STM32F1xx_PORT_HANDLER_H
#define __STM32F1xx_PORT_HANDLER_H

#include "stm32f1xx_utility.h"
#include "stm32f1xx_hal.h"

#define UART_RX__SZ 64
#define UART_TX__SZ 64
#define HEADER_SIZE 4
#define HEADER_MASK (uint32_t)0xFFFFFD00
#define __UART_DMA_WRITE_PTR(__handle__) ((UART_RX__SZ - __handle__.hdmarx->Instance->CNDTR) & (UART_RX__SZ - 1))  
#define TRUE    1
#define FALSE	0
#define SIZE   256

/* the HEAD of the MessageQueue, hold the amount of node's that are in the queue*/
typedef struct MessageQueue { 
    uint8_t message[SIZE];
    int front; 
    int rear;     
} MessageQueue;

// PORT MANAGEMENT
void UART_DMA_Init(UART_HandleTypeDef huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
uint8_t get_one_byte_from_buffer(UART_HandleTypeDef huart);
bool rxBuffer_is_empty(UART_HandleTypeDef huart); 
bool validate_header(uint32_t header);
uint32_t get_header(UART_HandleTypeDef huart);
void UART_rx_transfer_to_queue(UART_HandleTypeDef huart);

// FIFO MANAGMENT
MessageQueue* constructMessage();
int enQueue(MessageQueue*, uint8_t);
uint8_t deQueue(MessageQueue*);
int isEmpty(MessageQueue*);
int isFull(MessageQueue*);
uint8_t peek(MessageQueue*);
int nextRear(MessageQueue*);
int nextFront(MessageQueue*);

#endif /* __STM32F1xx_PORT_HANDLER_H */