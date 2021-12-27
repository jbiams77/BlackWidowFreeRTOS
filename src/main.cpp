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
#define mainQUEUE_LENGTH                    ( 10 )

/*-----------------------------------------------------------*/
typedef struct Message {
  char body[20];
  int count;
} Message;

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvQueueReceiveTask( void *pvParameters );
static void prvQueueSendTask( void *pvParameters );

/*-----------------------------------------------------------*/


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

    /* Create the queue. */
    xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( Message ) );

    if( xQueue != NULL )
    {
        /* Start the two tasks as described in the comments at the top of this
        file. */
        xTaskCreate(prvQueueSendTask,
                    "TX",
                    configMINIMAL_STACK_SIZE,
                    NULL,
                    mainQUEUE_SEND_TASK_PRIORITY,
                    NULL );

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
static void prvQueueSendTask( void *pvParameters )
{
TickType_t xNextWakeTime;
const unsigned long ulValueToSend = 100UL;

    /* Remove compiler warning about unused parameter. */
    ( void ) pvParameters;
    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();
    Message msg;
    msg.count = 0;
    while (1)
    {
        /* Place this task in the blocked state until it is time to run again. */
        vTaskDelayUntil( &xNextWakeTime, mainQUEUE_SEND_FREQUENCY_MS );
        
        strcpy(msg.body, "Hello-World");
        msg.count += 1;
        /* Send to the queue - causing the queue receive task to unblock and
        toggle the LED.  0 is used as the block time so the sending operation
        will not block - it shouldn't need to block as the queue should always
        be empty at this point in the code. */
        if (xQueueSend( xQueue, &msg, 10) != pdTRUE)
        {
          Error_Handler();
        }
    }
}

/*-----------------------------------------------------------*/

static void prvQueueReceiveTask( void *pvParameters )
{
unsigned long ulReceivedValue;
const unsigned long ulExpectedValue = 100UL;

    /* Remove compiler warning about unused parameter. */
    ( void ) pvParameters;
    Message rcv_msg;
    volatile int x = 0;
    volatile char *body;
    while (1)
    {
        /*  To get here something must have been received from the queue, but
        is it the expected value?  If it is, toggle the LED. */
        if(xQueueReceive(xQueue, &rcv_msg, 1) == pdTRUE)
        {
          HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
        }
    }
}