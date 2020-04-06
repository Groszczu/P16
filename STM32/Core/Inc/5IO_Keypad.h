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


// Left keypad
#define LEFT_IO_KEY_GPIO GPIOB
#define LEFT_IO_KEY_1 GPIO_PIN_15
#define LEFT_IO_KEY_2 GPIO_PIN_14
#define LEFT_IO_KEY_3 GPIO_PIN_13
#define LEFT_IO_KEY_4 GPIO_PIN_12
#define LEFT_IO_KEY_5 GPIO_PIN_11


// Right keypad
#define RIGHT_IO_KEY_GPIO GPIOD
#define RIGHT_IO_KEY_1 GPIO_PIN_6
#define RIGHT_IO_KEY_2 GPIO_PIN_3
#define RIGHT_IO_KEY_3 GPIO_PIN_2
#define RIGHT_IO_KEY_4 GPIO_PIN_1
#define RIGHT_IO_KEY_5 GPIO_PIN_0


// Test
#define IO_KEY_GPIO(side) 	(side == 'L' ? LEFT_IO_KEY_GPIO : RIGHT_IO_KEY_GPIO)
#define IO_KEY_1(side) 		(side == 'L' ? LEFT_IO_KEY_1 : RIGHT_IO_KEY_1)
#define IO_KEY_2(side) 		(side == 'L' ? LEFT_IO_KEY_2 : RIGHT_IO_KEY_2)
#define IO_KEY_3(side) 		(side == 'L' ? LEFT_IO_KEY_3 : RIGHT_IO_KEY_3)
#define IO_KEY_4(side) 		(side == 'L' ? LEFT_IO_KEY_4 : RIGHT_IO_KEY_4)
#define IO_KEY_5(side) 		(side == 'L' ? LEFT_IO_KEY_5 : RIGHT_IO_KEY_5)

#define GET_IO_KEY_1(side) HAL_GPIO_ReadPin(IO_KEY_GPIO(side), IO_KEY_1(side))
#define GET_IO_KEY_2(side) HAL_GPIO_ReadPin(IO_KEY_GPIO(side), IO_KEY_2(side))
#define GET_IO_KEY_3(side) HAL_GPIO_ReadPin(IO_KEY_GPIO(side), IO_KEY_3(side))
#define GET_IO_KEY_4(side) HAL_GPIO_ReadPin(IO_KEY_GPIO(side), IO_KEY_4(side))
#define GET_IO_KEY_5(side) HAL_GPIO_ReadPin(IO_KEY_GPIO(side), IO_KEY_5(side))

extern uint32_t KeypadScan(char side);
extern uint32_t KeypadScanLeft(void);
extern uint32_t KeypadScanRight(void);

extern void KeypadScanTest(char side);
extern void KeypadScanTestLeft(void);
extern void KeypadScanTestRight(void);


#endif
