#ifndef __5IO_KEYPAD_H
#define __5IO_KEYPAD_H

#include "stm32f4xx_hal.h"
/* Define key value */


#define KEY_VALUE_NULL ((uint32_t)0) 
#define KEY_VALUE_LEFT ((uint32_t)1)
#define KEY_VALUE_UP ((uint32_t)2)
#define KEY_VALUE_PRESS ((uint32_t)3)
#define KEY_VALUE_DOWN ((uint32_t)4)
#define KEY_VALUE_RIGHT ((uint32_t)5)
#define KEY_VALUE_ONE ((uint32_t)6)
#define KEY_VALUE_TWO ((uint32_t)7)
#define KEY_VALUE_THREE ((uint32_t)8)
#define KEY_VALUE_FOUR ((uint32_t)9)
#define KEY_VALUE_FIVE ((uint32_t)10)
#define KEY_VALUE_SIX ((uint32_t)11)
#define KEY_VALUE_SEVEN ((uint32_t)12)
#define KEY_VALUE_EIGHT ((uint32_t)13)
#define KEY_VALUE_NINE ((uint32_t)14)
#define KEY_VALUE_TEN ((uint32_t)15)

// define reversed key values (one of the keypads is going to be placed upside down)
#define KEY_VALUE_REVERSED_UP KEY_VALUE_DOWN
#define KEY_VALUE_REVERSED_DOWN KEY_VALUE_UP
#define KEY_VALUE_REVERSED_LEFT KEY_VALUE_RIGHT
#define KEY_VALUE_REVERSED_RIGHT KEY_VALUE_LEFT

#define IO_KEY_GPIO GPIOB
//#define RCC_KEY_GPIO RCC_APB2Periph_GPIOC RCC->APB2PERIPH_BASE
#define IO_KEY_1 GPIO_PIN_15
#define IO_KEY_2 GPIO_PIN_14
#define IO_KEY_3 GPIO_PIN_13
#define IO_KEY_4 GPIO_PIN_12
#define IO_KEY_5 GPIO_PIN_11

#define GET_IO_KEY_1 HAL_GPIO_ReadPin(IO_KEY_GPIO, IO_KEY_1)
#define GET_IO_KEY_2 HAL_GPIO_ReadPin(IO_KEY_GPIO, IO_KEY_2)
#define GET_IO_KEY_3 HAL_GPIO_ReadPin(IO_KEY_GPIO, IO_KEY_3)
#define GET_IO_KEY_4 HAL_GPIO_ReadPin(IO_KEY_GPIO, IO_KEY_4)
#define GET_IO_KEY_5 HAL_GPIO_ReadPin(IO_KEY_GPIO, IO_KEY_5)

extern uint32_t KeypadScan(void);
extern void KeypadScanTest(void);

#endif
