extern "C" void* _sbrk(int incr);
void dummy_sbrk_caller() __attribute__((__used__));
void dummy_sbrk_caller()
{
    _sbrk(0);
}

#include "control_table.h"
#include "packet_handler.h"
#include "port_handler.h"
#include "stm32f1xx_hal.h"
#include "utility.h"
#include "as5600.h"
#include <FreeRTOS.h>
#include <cstdio>
#include <queue.h>
#include <stdio.h>
#include <string.h>
#include <task.h>

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define mainQUEUE_SEND_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

/* The rate at which data is sent to the queue.  The 200ms value is converted
to ticks using the portTICK_PERIOD_MS constant. */
#define mainQUEUE_SEND_FREQUENCY_MS (200 / portTICK_PERIOD_MS)

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH (10)

/*-----------------------------------------------------------*/

uint8_t rx_buffer[UART_RX__SZ];

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvQueueCommunicationTask( void *pvParameters );
static void prvAngleMeasureTask( void *pvParameters );

/*-----------------------------------------------------------*/

void UART_DMA_Init();
void resetUARTtoReceive();

/* The queue used by both tasks. */
static QueueHandle_t rxBufferQueue = NULL;
// static QueueHandle_t txBufferQueue = NULL;

UART_HandleTypeDef huart1;

bool DMA_TRANSMIT_COMPLETE;
/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_I2C2_Init();
    MX_USART1_UART_Init(&huart1);

    UART_DMA_Init();

    // ControlTable::initialize_eeprom();
    // ControlTable::flash();
    // ControlTable::load_memory();

    /* Create the queue. */
    rxBufferQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( rx_buffer ) );

    if( rxBufferQueue != NULL )
    {
        /* Start Magnetic Encoder read tasks.*/
        xTaskCreate(prvAngleMeasureTask,
                    "ANGLE_MEAS",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    mainQUEUE_SEND_TASK_PRIORITY,
                    NULL );

        /* Start the communications tasks.*/
        xTaskCreate(prvQueueCommunicationTask,
                    "COMMUNICATIONS",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    mainQUEUE_RECEIVE_TASK_PRIORITY,
                    NULL);

        /* Start the tasks and timer running. */
        vTaskStartScheduler();
    }

    while (1) {
    }
    /* USER CODE END 3 */
}

/*-----------------------------------------------------------*/
static void prvAngleMeasureTask(void* pvParameters)
{
    volatile uint32_t angle;
    volatile uint32_t previous_angle;
    while (1)
    {
        angle = MagneticEncoder::GetAngle();
        ControlTable::set(CT::PresentPosition, angle);
        HAL_Delay(100);
        previous_angle = ControlTable::get(CT::PresentPosition);
    }
}


static void prvQueueCommunicationTask(void* pvParameters)
{

    /* Remove compiler warning about unused parameter. */
    (void)pvParameters;
    uint8_t rx_packet[UART_RX__SZ];

    while (1)
    {
        /*  To get here something must have been received from the queue, but
        is it the expected value?  If it is, toggle the LED. */
        if (xQueueReceive(rxBufferQueue, &rx_packet, portMAX_DELAY) == pdTRUE)
        {
            HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
            if (PacketHandler::rxPacket(rx_packet) == COMM_SUCCESS)
            {
                PacketHandler::txPacket(rx_packet);
            }
            else
            {
                resetUARTtoReceive();
            }
        }
    }
}

void UART_DMA_Init()
{ 
    DMA_TRANSMIT_COMPLETE = false;
    // set data direction pin is low
    HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_RESET);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    // turn on the UART RX port
    if (HAL_UART_Receive_DMA(&huart1, rx_buffer, UART_RX__SZ) != HAL_OK) {
        Error_Handler();
    }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    uint8_t packet[UART_RX__SZ];
    memcpy(packet, rx_buffer, UART_RX__SZ); // Copy from DMA (rx_buffer) to msg
    
    /* xQueueSendFromISR() will set *pxHigherPriorityTaskWoken to pdTRUE if sending
    to the queue caused a task to unblock, and the unblocked task has a priority higher
    than the currently running task. If xQueueSendFromISR() sets this value to pdTRUE
    then a context switch should be requested before the interrupt is exited. */
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken =pdFALSE;
    /* Send to the queue - causing the queue receive task to unblock and
    toggle the LED.  0 is used as the block time so the sending operation
    will not block - it shouldn't need to block as the queue should always
    be empty at this point in the code. */
    if (xQueueSendFromISR(rxBufferQueue, &packet, &xHigherPriorityTaskWoken) != pdTRUE)
    {
        Error_Handler();
    }

}

void UART_Transmit(uint8_t *message, uint8_t size)
{

    HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_SET);
    if(HAL_UART_Transmit(&huart1, message, size, 1000) != HAL_OK) {
        Error_Handler();
    }
    HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_RESET);
    resetUARTtoReceive();
}

void resetUARTtoReceive()
{
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    while (HAL_UART_Receive_DMA(&huart1, rx_buffer, UART_RX__SZ) != HAL_BUSY) {}
}
