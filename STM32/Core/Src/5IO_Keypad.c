#include <stdio.h>
#include "5IO_Keypad.h"

typedef enum{
	GND_START = 0,
	GND_DETECTION = 1,
	GND_OVER = 2,

	LINE1_START = 3,
	LINE1_DETECTION = 4,
	LINE1_OVER = 5,

	LINE2_START = 6,
	LINE2_DETECTION = 7,
	LINE2_OVER = 8,

	LINE3_START = 9,
	LINE3_DETECTION = 10,
	LINE3_OVER = 11,

	LINE4_START = 12,
	LINE4_DETECTION = 13,
	LINE4_OVER = 14
}Key_State;

Key_State CurrentKeyStateLeft = GND_START;
Key_State CurrentKeyStateRight = GND_START;

void ConfigurationGnd(char side);
void ConfigurationLine1(char side);
void ConfigurationLine2(char side);
void ConfigurationLine3(char side);
void ConfigurationLine4(char side);

void GndScanStart(char side);
uint32_t GndScanDetection(char side);
void GndScanOver(char side);

void Line1ScanStart(char side);
uint32_t Line1ScanDetection(char side);
void Line1ScanOver(char side);

void Line2ScanStart(char side);
uint32_t Line2ScanDetection(char side);
void Line2ScanOver(char side);

void Line3ScanStart(char side);
uint32_t Line3ScanDetection(char side);
void Line3ScanOver(char side);

void Line4ScanStart(char side);
uint32_t Line4ScanDetection(char side);
void Line4ScanOver(char side);

uint32_t KeypadScan(char side)
{
	uint32_t ReValue;
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	switch(*CurrentKeyState)
	{
		case GND_START: ReValue = KEY_VALUE_NULL; GndScanStart(side); break;
		case GND_DETECTION: ReValue = GndScanDetection(side); break;
		case GND_OVER: ReValue = KEY_VALUE_NULL; GndScanOver(side); break;

		case LINE1_START: ReValue = KEY_VALUE_NULL; Line1ScanStart(side); break;
		case LINE1_DETECTION: ReValue = Line1ScanDetection(side); break;
		case LINE1_OVER: ReValue = KEY_VALUE_NULL; Line1ScanOver(side); break;
		
		case LINE2_START: ReValue = KEY_VALUE_NULL; Line2ScanStart(side); break;
		case LINE2_DETECTION: ReValue = Line2ScanDetection(side); break;
		case LINE2_OVER: ReValue = KEY_VALUE_NULL; Line2ScanOver(side); break;
		
		case LINE3_START: ReValue = KEY_VALUE_NULL; Line3ScanStart(side); break;
		case LINE3_DETECTION: ReValue = Line3ScanDetection(side); break;
		case LINE3_OVER: ReValue = KEY_VALUE_NULL; Line3ScanOver(side); break;

		case LINE4_START: ReValue = KEY_VALUE_NULL; Line4ScanStart(side); break;
		case LINE4_DETECTION: ReValue = Line4ScanDetection(side); break;
		case LINE4_OVER: ReValue = KEY_VALUE_NULL; Line4ScanOver(side); break;
	}

	return ReValue;
}


void KeypadScanTest(char side)
{
	uint32_t TempKeyValue;

	TempKeyValue = KeypadScan(side);

	if(TempKeyValue != 0)
	{
		printf("KeyValue is : ");

		switch(TempKeyValue)
		{
			case 1: printf("-Left.\r\n"); break;
			case 2: printf("-Up.\r\n"); break;
			case 3: printf("-Press.\r\n"); break;
			case 4: printf("-Down.\r\n"); break;
			case 5: printf("-Right.\r\n"); break;
			case 6:	printf("-K1.\r\n"); break;
			case 7:	printf("-K2.\r\n"); break;
			case 8:	printf("-K3.\r\n"); break;
			case 9:	printf("-K4.\r\n"); break;
			case 10:	printf("-K5.\r\n"); break;
			case 11:	printf("-K6.\r\n"); break;
			case 12:	printf("-K7.\r\n"); break;				 
			case 13:	printf("-K8.\r\n"); break;
			case 14:	printf("-K9.\r\n"); break;
			case 15:	printf("-K10.\r\n"); break;
		}
	}
}


void ConfigurationGnd(char side)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();


  GPIO_InitStructure.Pin = IO_KEY_1(side) | IO_KEY_2(side) | IO_KEY_3(side) | IO_KEY_4(side) | IO_KEY_5(side);
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(IO_KEY_GPIO(side), &GPIO_InitStructure); //GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);
}

void ConfigurationLine1(char side)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE(); //RCC_APB2PeriphClockCmd(RCC_KEY_GPIO, ENABLE);
	__HAL_RCC_GPIOD_CLK_ENABLE();


  GPIO_InitStructure.Pin = IO_KEY_1(side);
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(IO_KEY_GPIO(side), &GPIO_InitStructure);

  GPIO_InitStructure.Pin = IO_KEY_2(side) | IO_KEY_3(side) | IO_KEY_4(side) | IO_KEY_5(side);
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IO_KEY_GPIO(side), &GPIO_InitStructure);

  HAL_GPIO_WritePin(IO_KEY_GPIO(side), IO_KEY_1(side), GPIO_PIN_SET); //GPIO_SetBits(IO_KEY_GPIO, IO_KEY_1);
}

void ConfigurationLine2(char side)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE(); //RCC_APB2PeriphClockCmd(RCC_KEY_GPIO, ENABLE);
	__HAL_RCC_GPIOD_CLK_ENABLE();


  GPIO_InitStructure.Pin = IO_KEY_1(side) | IO_KEY_2(side);
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(IO_KEY_GPIO(side), &GPIO_InitStructure);

  GPIO_InitStructure.Pin = IO_KEY_3(side) | IO_KEY_4(side) | IO_KEY_5(side);
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IO_KEY_GPIO(side), &GPIO_InitStructure);

	HAL_GPIO_WritePin(IO_KEY_GPIO(side), IO_KEY_2(side), GPIO_PIN_SET); 	//GPIO_SetBits(IO_KEY_GPIO, IO_KEY_2);
	HAL_GPIO_WritePin(IO_KEY_GPIO(side), IO_KEY_1(side), GPIO_PIN_RESET); 	//GPIO_ResetBits(IO_KEY_GPIO, IO_KEY_1);
}

void ConfigurationLine3(char side)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE(); //RCC_APB2PeriphClockCmd(RCC_KEY_GPIO, ENABLE);
	__HAL_RCC_GPIOD_CLK_ENABLE();


  GPIO_InitStructure.Pin = IO_KEY_1(side) | IO_KEY_2(side) | IO_KEY_3(side);
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(IO_KEY_GPIO(side), &GPIO_InitStructure);

  GPIO_InitStructure.Pin = IO_KEY_4(side) | IO_KEY_5(side);
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IO_KEY_GPIO(side), &GPIO_InitStructure);

	HAL_GPIO_WritePin(IO_KEY_GPIO(side), IO_KEY_1(side) | IO_KEY_2(side), GPIO_PIN_RESET);	//GPIO_ResetBits(IO_KEY_GPIO, IO_KEY_1 | IO_KEY_2);
	HAL_GPIO_WritePin(IO_KEY_GPIO(side), IO_KEY_3(side), GPIO_PIN_SET); 				//GPIO_SetBits(IO_KEY_GPIO, IO_KEY_3);
}

void ConfigurationLine4(char side)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE(); //RCC_APB2PeriphClockCmd(RCC_KEY_GPIO, ENABLE);
	__HAL_RCC_GPIOD_CLK_ENABLE();


  GPIO_InitStructure.Pin = IO_KEY_1(side) | IO_KEY_2(side) | IO_KEY_3(side) | IO_KEY_4(side);
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(IO_KEY_GPIO(side), &GPIO_InitStructure);

  GPIO_InitStructure.Pin = IO_KEY_5(side);
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IO_KEY_GPIO(side), &GPIO_InitStructure);

  HAL_GPIO_WritePin(IO_KEY_GPIO(side), IO_KEY_1(side) | IO_KEY_2(side) | IO_KEY_3(side), GPIO_PIN_RESET); 	//GPIO_ResetBits(IO_KEY_GPIO, IO_KEY_1 | IO_KEY_2 | IO_KEY_3);
  HAL_GPIO_WritePin(IO_KEY_GPIO(side), IO_KEY_4(side), GPIO_PIN_SET); 							//GPIO_SetBits(IO_KEY_GPIO, IO_KEY_4);

}

void GndScanStart(char side)
{
	ConfigurationGnd(side);
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if((GET_IO_KEY_1(side) == 0)||(GET_IO_KEY_2(side) == 0)||(GET_IO_KEY_3(side) == 0)||(GET_IO_KEY_4(side) == 0)||(GET_IO_KEY_5(side) == 0))
	{
		*CurrentKeyState = GND_DETECTION;
	}
	else
	{
		*CurrentKeyState = LINE1_START;
	}
}

uint32_t GndScanDetection(char side)
{
	uint32_t ReValue;
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if((GET_IO_KEY_1(side) == 0)||(GET_IO_KEY_2(side) == 0)||(GET_IO_KEY_3(side) == 0)||(GET_IO_KEY_4(side) == 0)||(GET_IO_KEY_5(side) == 0))
	{
		if(GET_IO_KEY_1(side) == 0)
		{
			ReValue = (side == 'L' ? KEY_VALUE_REVERSED_LEFT : KEY_VALUE_LEFT);
		}
		else if((GET_IO_KEY_2(side) == 0))
		{
			ReValue = (side == 'L' ? KEY_VALUE_REVERSED_UP : KEY_VALUE_UP);
		}
		else if((GET_IO_KEY_3(side) == 0))
		{
			ReValue = KEY_VALUE_PRESS;
		}
		else if((GET_IO_KEY_4(side) == 0))
		{
			ReValue = (side == 'L' ? KEY_VALUE_REVERSED_DOWN : KEY_VALUE_DOWN);
		}
		else if((GET_IO_KEY_5(side) == 0))
		{
			ReValue = (side == 'L' ? KEY_VALUE_REVERSED_RIGHT : KEY_VALUE_RIGHT);
		}	

		*CurrentKeyState = GND_OVER;
	}
	else
	{
		*CurrentKeyState = LINE1_START;
		ReValue = KEY_VALUE_NULL;
	}

	return ReValue;
}	
	
void GndScanOver(char side)
{
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if(((GET_IO_KEY_1(side) == 0)||(GET_IO_KEY_2(side) == 0)||(GET_IO_KEY_3(side) == 0)||(GET_IO_KEY_4(side) == 0)||(GET_IO_KEY_5(side) == 0)))
	{
		*CurrentKeyState = GND_OVER;
	}
	else
	{
		*CurrentKeyState = LINE1_START;
	}
}
/* Scan line 1 */
void Line1ScanStart(char side)
{
	ConfigurationLine1(side);
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if(((GET_IO_KEY_2(side) == 1)||(GET_IO_KEY_3(side) == 1)||(GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1)))
	{
		*CurrentKeyState = LINE1_DETECTION;
	}
	else if((!((GET_IO_KEY_2(side) == 1)||(GET_IO_KEY_3(side) == 1)||(GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1))))
	{
		*CurrentKeyState = LINE2_START;
	}		
}

uint32_t Line1ScanDetection(char side)
{
	uint32_t ReValue;
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if(((GET_IO_KEY_2(side) == 1)||(GET_IO_KEY_3(side) == 1)||(GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1)))
	{
		if(GET_IO_KEY_2(side) == 1)
		{
			ReValue = KEY_VALUE_ONE;	
		}
		else if(GET_IO_KEY_3(side) == 1)
		{
			ReValue = KEY_VALUE_TWO;
		}
		else if(GET_IO_KEY_4(side) == 1)
		{
			ReValue = KEY_VALUE_THREE;
		}
		else if(GET_IO_KEY_5(side) == 1)
		{
			ReValue = KEY_VALUE_FOUR;
		}

		*CurrentKeyState = LINE1_OVER;
	}
	else
	{
		*CurrentKeyState = LINE2_START;
		ReValue = KEY_VALUE_NULL;
	}	

	return ReValue;
}

void Line1ScanOver(char side)
{
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if((GET_IO_KEY_2(side) == 1)||(GET_IO_KEY_3(side) == 1)||(GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1))
	{
		*CurrentKeyState = LINE1_OVER;
	}
	else
	{
		*CurrentKeyState = LINE2_START;
	}
}
/* Scan line 2 */
void Line2ScanStart(char side)
{
	ConfigurationLine2(side);
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if((GET_IO_KEY_3(side) == 1)||(GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1))
	{
		*CurrentKeyState = LINE2_DETECTION;
	}
	else
	{
		*CurrentKeyState = LINE3_START;
	}		
}

uint32_t Line2ScanDetection(char side)
{
	uint32_t ReValue;
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if((GET_IO_KEY_3(side) == 1)||(GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1))
	{
		if(GET_IO_KEY_3(side) == 1)
		{
			ReValue = KEY_VALUE_FIVE;	
		}
		else if(GET_IO_KEY_4(side) == 1)
		{
			ReValue = KEY_VALUE_SIX;
		}
		else if(GET_IO_KEY_5(side) == 1)
		{
			ReValue = KEY_VALUE_SEVEN;
		}

		*CurrentKeyState = LINE2_OVER;
	}
	else
	{
		*CurrentKeyState = LINE3_START;
		ReValue = KEY_VALUE_NULL;
	}	

	return ReValue;
}

void Line2ScanOver(char side)
{
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if((GET_IO_KEY_3(side) == 1)||(GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1))
	{
		*CurrentKeyState = LINE2_OVER;
	}
	else
	{
		*CurrentKeyState = LINE3_START;
	}
}
/* Scan line 3 */
void Line3ScanStart(char side)
{
	ConfigurationLine3(side);
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if((GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1))
	{
		*CurrentKeyState = LINE3_DETECTION;
	}
	else
	{
		*CurrentKeyState = LINE4_START;
	}		
}

uint32_t Line3ScanDetection(char side)
{
	uint32_t ReValue;
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if((GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1))
	{
		if(GET_IO_KEY_4(side) == 1)
		{
			ReValue = KEY_VALUE_EIGHT;	
		}
		else if(GET_IO_KEY_5(side) == 1)
		{
			ReValue = KEY_VALUE_NINE;
		}

		*CurrentKeyState = LINE3_OVER;
	}
	else
	{
		*CurrentKeyState = LINE4_START;
		ReValue = KEY_VALUE_NULL;
	}	

	return ReValue;
}

void Line3ScanOver(char side)
{
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if((GET_IO_KEY_4(side) == 1)||(GET_IO_KEY_5(side) == 1))
	{
		*CurrentKeyState = LINE3_OVER;
	}
	else
	{
		*CurrentKeyState = LINE4_START;
	}
}
/* Scan line 4 */
void Line4ScanStart(char side)
{
	ConfigurationLine4(side);
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if(GET_IO_KEY_5(side) == 1)
	{
		*CurrentKeyState = LINE4_DETECTION;
	}
	else
	{
		*CurrentKeyState = GND_START;
	}		
}

uint32_t Line4ScanDetection(char side)
{
	uint32_t ReValue;
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if(GET_IO_KEY_5(side) == 1)
	{
		ReValue = KEY_VALUE_TEN;	

		*CurrentKeyState = LINE4_OVER;
	}
	else
	{
		*CurrentKeyState = GND_START;
		ReValue = KEY_VALUE_NULL;
	}	

	return ReValue;
}

void Line4ScanOver(char side)
{
	Key_State* CurrentKeyState = (side == 'L' ? &CurrentKeyStateLeft : &CurrentKeyStateRight);

	if(GET_IO_KEY_5(side) == 1)
	{
		*CurrentKeyState = LINE4_OVER;
	}
	else
	{
		*CurrentKeyState = GND_START;
	}
}
