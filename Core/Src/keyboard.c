/*
 * keyboard.c
 *
 *  Created on: Nov 6, 2023
 *      Author: Juan Felipe Ordóñez
 */

#include "keyboard.h"
#include <stdio.h> // Make sure to include necessary libraries.
#include "stm32l4xx_hal.h"

// Define your GPIO pins and ports here.
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

/**
 * @brief This functions initialize the functionality of the keypad
 */
void keypad_init(void)
{
    // Set the rows high to be detected in the columns by rising interrupt
    ROW_1_GPIO_Port->BSRR = ROW_1_Pin;
    ROW_2_GPIO_Port->BSRR = ROW_2_Pin;
    ROW_3_GPIO_Port->BSRR = ROW_3_Pin;
    ROW_4_GPIO_Port->BSRR = ROW_4_Pin;
}
/**
 * @brief  This function debounces and identify keypad events.
 * @param  column_to_evaluate: the column where the event happened.
 * @retval 0xFF -> invalid key. [0x00 - 0x0F] -> valid key.
 */
uint8_t keypad_handler(uint16_t column_to_evaluate)
{
    uint8_t key_pressed = 0xFF; // Value to return

    // Debounce the key press (remove noise in the key)
    #define KEY_DEBOUNCE_MS 300 /*!> Minimum time required since the last press */
    static uint32_t last_pressed_tick = 0;
    if (HAL_GetTick() <= (last_pressed_tick + KEY_DEBOUNCE_MS))
    {
        // Less than KEY_DEBOUNCE_MS since the last press. Probably noise.
        return key_pressed; // Return 0xFF
    }
    last_pressed_tick = HAL_GetTick();

    // Check in which column the event happened
    switch (column_to_evaluate)
    {
    case COLUMN_1_Pin:
        ROW_1_GPIO_Port->BSRR = ROW_1_Pin;
        ROW_2_GPIO_Port->BRR = ROW_2_Pin;
        ROW_3_GPIO_Port->BRR = ROW_3_Pin;
        ROW_4_GPIO_Port->BRR = ROW_4_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin)
        {
            key_pressed = 0x01;
            break;
        }

        ROW_1_GPIO_Port->BRR = ROW_1_Pin;
        ROW_2_GPIO_Port->BSRR = ROW_2_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin)
        {
            key_pressed = 0x04;
            break;
        }

        ROW_2_GPIO_Port->BRR = ROW_2_Pin;
        ROW_3_GPIO_Port->BSRR = ROW_3_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin)
        {
            key_pressed = 0x07;
            break;
        }

        ROW_3_GPIO_Port->BRR = ROW_3_Pin;
        ROW_4_GPIO_Port->BSRR = ROW_4_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin)
        {
            key_pressed = 0x0E;
            break;
        }
        break;

    case COLUMN_2_Pin:
        ROW_1_GPIO_Port->BSRR = ROW_1_Pin;
        ROW_2_GPIO_Port->BRR = ROW_2_Pin;
        ROW_3_GPIO_Port->BRR = ROW_3_Pin;
        ROW_4_GPIO_Port->BRR = ROW_4_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin)
        {
            key_pressed = 0x02;
            break;
        }

        ROW_1_GPIO_Port->BRR = ROW_1_Pin;
        ROW_2_GPIO_Port->BSRR = ROW_2_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin)
        {
            key_pressed = 0x05;
            break;
        }

        ROW_2_GPIO_Port->BRR = ROW_2_Pin;
        ROW_3_GPIO_Port->BSRR = ROW_3_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin)
        {
            key_pressed = 0x08;
            break;
        }

        ROW_3_GPIO_Port->BRR = ROW_3_Pin;
        ROW_4_GPIO_Port->BSRR = ROW_4_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin)
        {
            key_pressed = 0x00;
            break;
        }
        break;

    case COLUMN_3_Pin:
        ROW_1_GPIO_Port->BSRR = ROW_1_Pin;
        ROW_2_GPIO_Port->BRR = ROW_2_Pin;
        ROW_3_GPIO_Port->BRR = ROW_3_Pin;
        ROW_4_GPIO_Port->BRR = ROW_4_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)
        {
            key_pressed = 0x03;
            break;
        }

        ROW_1_GPIO_Port->BRR = ROW_1_Pin;
        ROW_2_GPIO_Port->BSRR = ROW_2_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)
        {
            key_pressed = 0x06;
            break;
        }

        ROW_2_GPIO_Port->BRR = ROW_2_Pin;
        ROW_3_GPIO_Port->BSRR = ROW_3_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)
        {
            key_pressed = 0x09;
            break;
        }

        ROW_3_GPIO_Port->BRR = ROW_3_Pin;
        ROW_4_GPIO_Port->BSRR = ROW_4_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)
        {
            key_pressed = 0x0F;
            break;
        }
        break;

    case COLUMN_4_Pin:
        ROW_1_GPIO_Port->BSRR = ROW_1_Pin;
        ROW_2_GPIO_Port->BRR = ROW_2_Pin;
        ROW_3_GPIO_Port->BRR = ROW_3_Pin;
        ROW_4_GPIO_Port->BRR = ROW_4_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin)
        {
            key_pressed = 0x0A;
            break;
        }

        ROW_1_GPIO_Port->BRR = ROW_1_Pin;
        ROW_2_GPIO_Port->BSRR = ROW_2_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin)
        {
            key_pressed = 0x0B;
            break;
         }

        ROW_2_GPIO_Port->BRR = ROW_2_Pin;
        ROW_3_GPIO_Port->BSRR = ROW_3_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin)
        {
            key_pressed = 0x0C;
            break;
        }

        ROW_3_GPIO_Port->BRR = ROW_3_Pin;
        ROW_4_GPIO_Port->BSRR = ROW_4_Pin;
        HAL_Delay(2); // wait for voltage to establish
        if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin)
        {
            key_pressed = 0x0D;
            break;
        }
        break;

    default:
        // This should not be reached.
        printf("Unknown column: %x\r\n", column_to_evaluate);
        break;
    }

    keypad_init(); // Set the columns high again.
    return key_pressed;
}
