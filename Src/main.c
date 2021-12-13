#include "cmsis_os.h"
#include "stm32f1xx_utility.h"
#include "stm32f1xx_port_handler.h"
#include "FreeRTOS.h"
#include "task_manager.h"
#include "device.h"

extern UART_HandleTypeDef huart1;


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
  MX_USART1_UART_Init();  
  UART_DMA_Init(&huart1);  
  initialize_self();
  osKernelInitialize();  
	
	start_tasks();
	
  if (osKernelGetState() == osKernelReady) {
    osKernelStart();                    // Start thread execution
  }
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  }
  /* USER CODE END 3 */
}
