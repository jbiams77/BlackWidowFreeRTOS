// #ifndef __PORT_HANDLER_H
// #define __PORT_HANDLER_H

// #include "utility.h"
// #include <queue.h>
// #include "stm32f1xx_hal.h"

// #define __UART_DMA_WRITE_PTR(__handle__) ((UART_RX__SZ - (uint32_t)__handle__->hdmarx->Instance->CNDTR) & (UART_RX__SZ - 1))

// #define UART_RX__SZ (64)
// uint8_t rx_buffer[UART_RX__SZ];
// extern UART_HandleTypeDef huart1;

// class PortHandler
// {
//     private:

//     public:
//         /**
//          * @brief Construct a new Port Handler object. Initializes UART and DMA port with 
//          * handle allowing for UART receive to have direct memory access. Receive uses idle 
//          * line to trigger received event for variable HAL_message_queue length.
//          * 
//          */
//         PortHandler();

//         /**
//          * @brief process messages in xQueue
//          * 
//          */
//         void receiveMessages();

//         /**
//          * @brief transfer received messages from DMA to xQueue
//          * 
//          */
//         void transferBufferToQueue();
        

// };

// void UART_DMA_Init();
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
// void UART_Transmit(uint8_t *message, uint8_t size);
// uint8_t get_one_byte_from_buffer(UART_HandleTypeDef *huart);
// bool rxBuffer_is_empty(UART_HandleTypeDef *huart); 
// bool validate_header(uint32_t header);
// uint32_t get_header(UART_HandleTypeDef *huart);
// void UART_rx_transfer_to_queue(UART_HandleTypeDef *huart);


// #endif /* __PORT_HANDLER_H */