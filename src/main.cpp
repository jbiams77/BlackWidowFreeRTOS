extern "C" void *_sbrk(int incr);
void dummy_sbrk_caller() __attribute__((__used__));
void dummy_sbrk_caller()
{
  _sbrk(0);
}


#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include "stm32f1xx_hal.h"
#include "utility.h"
#include "port_handler.h"
#include "packet_handler.h"


/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_SEND_TASK_PRIORITY        ( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue.  The 200ms value is converted
to ticks using the portTICK_PERIOD_MS constant. */
#define mainQUEUE_SEND_FREQUENCY_MS         ( 200 / portTICK_PERIOD_MS )

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH       ( 10 )
#define UART_RX__SZ            ( 64 )
/*-----------------------------------------------------------*/

typedef struct Message {
  uint8_t body[UART_RX__SZ];
  int count;
} Message;

uint8_t rx_buffer[UART_RX__SZ];

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvQueueReceiveTask( void *pvParameters );
static void prvQueueSendTask( void *pvParameters );

/*-----------------------------------------------------------*/

// TODO: Move these to class when working
void UART_DMA_Init();

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;
UART_HandleTypeDef huart1;
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
    /* Create the queue. */
    xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( Message ) );

    if( xQueue != NULL )
    {
        /* Start the two tasks as described in the comments at the top of this
        file. */
        // xTaskCreate(prvQueueSendTask,
        //             "TX",
        //             configMINIMAL_STACK_SIZE,
        //             NULL,
        //             mainQUEUE_SEND_TASK_PRIORITY,
        //             NULL );

        xTaskCreate( prvQueueReceiveTask,               /* The function that implements the task. */
                    "Rx",                               /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                    configMINIMAL_STACK_SIZE,           /* The size of the stack to allocate to the task. */
                    NULL,                               /* The parameter passed to the task - not used in this case. */
                    mainQUEUE_RECEIVE_TASK_PRIORITY,    /* The priority assigned to the task. */
                    NULL );                             /* The task handle is not required, so NULL is passed. */


        /* Start the tasks and timer running. */
        vTaskStartScheduler();
    }

    while (1)
    {

    }
    /* USER CODE END 3 */
}

/*-----------------------------------------------------------*/

static void prvQueueReceiveTask( void *pvParameters )
{
unsigned long ulReceivedValue;
const unsigned long ulExpectedValue = 100UL;

    /* Remove compiler warning about unused parameter. */
    ( void ) pvParameters;
    static Message rcv_msg;
    while (1)
    {
        /*  To get here something must have been received from the queue, but
        is it the expected value?  If it is, toggle the LED. */
        if(xQueueReceive(xQueue, &rcv_msg, portMAX_DELAY) == pdTRUE)
        {
          HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
        }
    }
}

void UART_DMA_Init()
{ 
  // set data direction pin is low
  HAL_GPIO_WritePin(DATA_DIR_GPIO_Port, DATA_DIR_Pin, GPIO_PIN_RESET);

  // turn on the UART RX port
  if (HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_buffer, UART_RX__SZ) != HAL_OK) {
    Error_Handler();
  }

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  Message msg;
  memcpy(msg.body, rx_buffer, UART_RX__SZ); // Copy from DMA (rx_buffer) to msg
  msg.count = 0;
  
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
  if (xQueueSendFromISR(xQueue, &msg, &xHigherPriorityTaskWoken) != pdTRUE)
  {
    Error_Handler();
  }

}