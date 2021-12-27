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
//         void rx();

// };

// #endif /* __PORT_HANDLER_H */