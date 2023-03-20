#ifndef __UTILITY_H
#define __UTILITY_H

#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

#define GREEN_LED_Pin GPIO_PIN_13
#define GREEN_LED_GPIO_Port GPIOC
#define FAN_Pin GPIO_PIN_2
#define FAN_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOA
#define M2_Pin GPIO_PIN_13
#define M2_GPIO_Port GPIOB
#define M1_Pin GPIO_PIN_14
#define M1_GPIO_Port GPIOB
#define M0_Pin GPIO_PIN_15
#define M0_GPIO_Port GPIOB
#define STEP_Pin GPIO_PIN_8
#define STEP_GPIO_Port GPIOA
#define ENABLE_Pin GPIO_PIN_9
#define ENABLE_GPIO_Port GPIOA
#define STEP_DIR_Pin GPIO_PIN_10
#define STEP_DIR_GPIO_Port GPIOA
#define DATA_DIR_Pin GPIO_PIN_5
#define DATA_DIR_GPIO_Port GPIOB
#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET
#define UART_RX__SZ            ( 64 )
#define OFF GPIO_PIN_RESET
#define ON GPIO_PIN_SET


void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_I2C2_Init(void);
void MX_USART1_UART_Init(UART_HandleTypeDef *huart);
void Error_Handler(void);
void UART_Transmit(uint8_t *message, uint8_t size);

#endif /* __UTILITY_H */