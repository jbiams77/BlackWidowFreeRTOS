
#include "stm32f1xx_utility.h"
#include "cmsis_os.h"
#include "task_manager.h"
#include "task.h"
#include "stm32f1xx_port_handler.h"
#include "semphr.h"
#include "message_traffic.h"

osThreadId_t rx_message_task_id;
osThreadId_t tx_message_task_id;
osThreadId_t blink_onboard_id;
osThreadId_t blink_offboard_id;

SemaphoreHandle_t task_lock = NULL;


void start_tasks(void) {
  task_lock = xSemaphoreCreateMutex();
  rx_message_task_id = osThreadNew(rx_message_task, NULL, NULL);
  tx_message_task_id = osThreadNew(tx_message_task, NULL, NULL);
  blink_onboard_id = osThreadNew(BLINK_ONBOARD_TASK, NULL, NULL);
  blink_offboard_id = osThreadNew(BLINK_OFFBOARD_TASK, NULL, NULL);  

}

void rx_message_task(void *argument) {
  for(;;) {
    processes_received_messages_task();
  }		
}

void tx_message_task(void *argument) {  
  for(;;) {
    processes_transmit_messages_task();
  }
}

void BLINK_ONBOARD_TASK(void *argument) {
  for(;;) {
  HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
  osDelay(100);
  }		
}

void BLINK_OFFBOARD_TASK(void *argument) {
  for(;;) {
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  osDelay(1000);
  }		
}
