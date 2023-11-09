/*
 * keyboard.h
 *
 *  Created on: Nov 6, 2023
 *      Author: Juan Felipe Ordóñez
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include <stdint.h>
#include "stm32l4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void Error_Handler(void);

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define COLUMN_1_Pin GPIO_PIN_10
#define COLUMN_1_GPIO_Port GPIOB
#define COLUMN_1_EXTI_IRQn EXTI15_10_IRQn
#define COLUMN_4_Pin GPIO_PIN_7
#define COLUMN_4_GPIO_Port GPIOC
#define COLUMN_4_EXTI_IRQn EXTI9_5_IRQn
#define COLUMN_2_Pin GPIO_PIN_8
#define COLUMN_2_GPIO_Port GPIOA
#define COLUMN_2_EXTI_IRQn EXTI9_5_IRQn
#define COLUMN_3_Pin GPIO_PIN_9
#define COLUMN_3_GPIO_Port GPIOA
#define COLUMN_3_EXTI_IRQn EXTI9_5_IRQn
#define ROW_1_Pin GPIO_PIN_10
#define ROW_1_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ROW_2_Pin GPIO_PIN_3
#define ROW_2_GPIO_Port GPIOB
#define ROW_4_Pin GPIO_PIN_4
#define ROW_4_GPIO_Port GPIOB
#define ROW_3_Pin GPIO_PIN_5
#define ROW_3_GPIO_Port GPIOB

void keypad_init(void);
uint8_t keypad_handler(uint16_t column_to_evaluate);

#ifdef __cplusplus
}
#endif

#endif /* INC_KEYBOARD_H_ */
