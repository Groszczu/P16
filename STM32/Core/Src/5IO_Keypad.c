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

static Key_State CurrentKeyState = GND_START;

static void ConfigurationGnd(void);
static void ConfigurationLine1(void);
static void ConfigurationLine2(void);
static void ConfigurationLine3(void);
static void ConfigurationLine4(void);

static void GndScanStart(void);
static uint32_t GndScanDetection(void);
static void GndScanOver(void);

static void Line1ScanStart(void);
static uint32_t Line1ScanDetection(void);
static void Line1ScanOver(void);

static void Line2ScanStart(void);
static uint32_t Line2ScanDetection(void);
static void Line2ScanOver(void);

static void Line3ScanStart(void);
static uint32_t Line3ScanDetection(void);
static void Line3ScanOver(void);

static void Line4ScanStart(void);
static uint32_t Line4ScanDetection(void);
static void Line4ScanOver(void);

uint32_t KeypadScan(void)
{
	uint32_t ReValue;

	switch(CurrentKeyState)
	{
		case GND_START: ReValue = KEY_VALUE_NULL; GndScanStart(); break; 
		case GND_DETECTION: ReValue = GndScanDetection(); break;
		case GND_OVER: ReValue = KEY_VALUE_NULL; GndScanOver(); break; 

		case LINE1_START: ReValue = KEY_VALUE_NULL; Line1ScanStart(); break; 
		case LINE1_DETECTION: ReValue = Line1ScanDetection(); break;
		case LINE1_OVER: ReValue = KEY_VALUE_NULL; Line1ScanOver(); break;
		
		case LINE2_START: ReValue = KEY_VALUE_NULL; Line2ScanStart(); break; 
		case LINE2_DETECTION: ReValue = Line2ScanDetection(); break;
		case LINE2_OVER: ReValue = KEY_VALUE_NULL; Line2ScanOver(); break;
		
		case LINE3_START: ReValue = KEY_VALUE_NULL; Line3ScanStart(); break; 
		case LINE3_DETECTION: ReValue = Line3ScanDetection(); break;
		case LINE3_OVER: ReValue = KEY_VALUE_NULL; Line3ScanOver(); break;

		case LINE4_START: ReValue = KEY_VALUE_NULL; Line4ScanStart(); break; 
		case LINE4_DETECTION: ReValue = Line4ScanDetection(); break;
		case LINE4_OVER: ReValue = KEY_VALUE_NULL; Line4ScanOver(); break;		  
	}

	return ReValue;
}

void KeypadScanTest(void)
{
	uint32_t TempKeyValue;

	TempKeyValue = KeypadScan();

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

static void ConfigurationGnd(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();// RCC_APB2PeriphClockCmd(RCC_KEY_GPIO, ENABLE);


  /* Configure PC.0, PC.01, PC.02, PC.03, PC.04 */
  GPIO_InitStructure.Pin = IO_KEY_1 | IO_KEY_2 | IO_KEY_3 | IO_KEY_4 | IO_KEY_5;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure); //GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);
}

static void ConfigurationLine1(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE(); //RCC_APB2PeriphClockCmd(RCC_KEY_GPIO, ENABLE);

  GPIO_InitStructure.Pin = IO_KEY_1;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.Pin = IO_KEY_2 | IO_KEY_3 | IO_KEY_4 | IO_KEY_5;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);

  HAL_GPIO_WritePin(IO_KEY_GPIO, IO_KEY_1, GPIO_PIN_SET); //GPIO_SetBits(IO_KEY_GPIO, IO_KEY_1);
}

static void ConfigurationLine2(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE(); //RCC_APB2PeriphClockCmd(RCC_KEY_GPIO, ENABLE);

  GPIO_InitStructure.Pin = IO_KEY_1 | IO_KEY_2;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.Pin = IO_KEY_3 | IO_KEY_4 | IO_KEY_5;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);

	HAL_GPIO_WritePin(IO_KEY_GPIO, IO_KEY_2, GPIO_PIN_SET); 	//GPIO_SetBits(IO_KEY_GPIO, IO_KEY_2);
	HAL_GPIO_WritePin(IO_KEY_GPIO, IO_KEY_1, GPIO_PIN_RESET); 	//GPIO_ResetBits(IO_KEY_GPIO, IO_KEY_1);
}

static void ConfigurationLine3(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE(); //RCC_APB2PeriphClockCmd(RCC_KEY_GPIO, ENABLE);

  GPIO_InitStructure.Pin = IO_KEY_1 | IO_KEY_2 | IO_KEY_3;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.Pin = IO_KEY_4 | IO_KEY_5;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);

	HAL_GPIO_WritePin(IO_KEY_GPIO, IO_KEY_1 | IO_KEY_2, GPIO_PIN_RESET);	//GPIO_ResetBits(IO_KEY_GPIO, IO_KEY_1 | IO_KEY_2);
	HAL_GPIO_WritePin(IO_KEY_GPIO, IO_KEY_3, GPIO_PIN_SET); 				//GPIO_SetBits(IO_KEY_GPIO, IO_KEY_3);
}

static void ConfigurationLine4(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  /* GPIOC and GPIOD Periph clock enable */
	__HAL_RCC_GPIOB_CLK_ENABLE(); //RCC_APB2PeriphClockCmd(RCC_KEY_GPIO, ENABLE);

  GPIO_InitStructure.Pin = IO_KEY_1 | IO_KEY_2 | IO_KEY_3 | IO_KEY_4;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.Pin = IO_KEY_5;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IO_KEY_GPIO, &GPIO_InitStructure);

  HAL_GPIO_WritePin(IO_KEY_GPIO, IO_KEY_1 | IO_KEY_2 | IO_KEY_3, GPIO_PIN_RESET); 	//GPIO_ResetBits(IO_KEY_GPIO, IO_KEY_1 | IO_KEY_2 | IO_KEY_3);
  HAL_GPIO_WritePin(IO_KEY_GPIO, IO_KEY_4, GPIO_PIN_SET); 							//GPIO_SetBits(IO_KEY_GPIO, IO_KEY_4);

}

static void GndScanStart(void)
{
	ConfigurationGnd();

	if((GET_IO_KEY_1 == 0)||(GET_IO_KEY_2 == 0)||(GET_IO_KEY_3 == 0)||(GET_IO_KEY_4 == 0)||(GET_IO_KEY_5 == 0))
	{
		CurrentKeyState = GND_DETECTION;
	}
	else
	{
		CurrentKeyState = LINE1_START;
	}
}

static uint32_t GndScanDetection(void)
{
	uint32_t ReValue;

	if((GET_IO_KEY_1 == 0)||(GET_IO_KEY_2 == 0)||(GET_IO_KEY_3 == 0)||(GET_IO_KEY_4 == 0)||(GET_IO_KEY_5 == 0))
	{
		if(GET_IO_KEY_1 == 0)
		{
			ReValue = KEY_VALUE_UP;	
		}
		else if((GET_IO_KEY_2 == 0))
		{
			ReValue = KEY_VALUE_DOWN;
		}
		else if((GET_IO_KEY_3 == 0))
		{
			ReValue = KEY_VALUE_LEFT;
		}
		else if((GET_IO_KEY_4 == 0))
		{
			ReValue = KEY_VALUE_RIGHT;
		}
		else if((GET_IO_KEY_5 == 0))
		{
			ReValue = KEY_VALUE_PRESS;
		}	

		CurrentKeyState = GND_OVER;
	}
	else
	{
		CurrentKeyState = LINE1_START;
		ReValue = KEY_VALUE_NULL;
	}

	return ReValue;
}	
	
static void GndScanOver(void)
{
	if(((GET_IO_KEY_1 == 0)||(GET_IO_KEY_2 == 0)||(GET_IO_KEY_3 == 0)||(GET_IO_KEY_4 == 0)||(GET_IO_KEY_5 == 0)))
	{
		CurrentKeyState = GND_OVER;	
	}
	else
	{
		CurrentKeyState = LINE1_START;
	}
}
/* Scan line 1 */
static void Line1ScanStart(void)
{
	ConfigurationLine1();

	if(((GET_IO_KEY_2 == 1)||(GET_IO_KEY_3 == 1)||(GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1)))
	{
		CurrentKeyState = LINE1_DETECTION;	
	}
	else if((!((GET_IO_KEY_2 == 1)||(GET_IO_KEY_3 == 1)||(GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1))))
	{
		CurrentKeyState = LINE2_START;
	}		
}

static uint32_t Line1ScanDetection(void)
{
	uint32_t ReValue;

	if(((GET_IO_KEY_2 == 1)||(GET_IO_KEY_3 == 1)||(GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1)))
	{
		if(GET_IO_KEY_2 == 1)
		{
			ReValue = KEY_VALUE_ONE;	
		}
		else if(GET_IO_KEY_3 == 1)
		{
			ReValue = KEY_VALUE_TWO;
		}
		else if(GET_IO_KEY_4 == 1)
		{
			ReValue = KEY_VALUE_THREE;
		}
		else if(GET_IO_KEY_5 == 1)
		{
			ReValue = KEY_VALUE_FOUR;
		}

		CurrentKeyState = LINE1_OVER;
	}
	else
	{
		CurrentKeyState = LINE2_START;
		ReValue = KEY_VALUE_NULL;
	}	

	return ReValue;
}

static void Line1ScanOver(void)
{
	if((GET_IO_KEY_2 == 1)||(GET_IO_KEY_3 == 1)||(GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1))
	{
		CurrentKeyState = LINE1_OVER;	
	}
	else
	{
		CurrentKeyState = LINE2_START;
	}
}
/* Scan line 2 */
static void Line2ScanStart(void)
{
	ConfigurationLine2();

	if((GET_IO_KEY_3 == 1)||(GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1))
	{
		CurrentKeyState = LINE2_DETECTION;	
	}
	else
	{
		CurrentKeyState = LINE3_START;
	}		
}

static uint32_t Line2ScanDetection(void)
{
	uint32_t ReValue;

	if((GET_IO_KEY_3 == 1)||(GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1))
	{
		if(GET_IO_KEY_3 == 1)
		{
			ReValue = KEY_VALUE_FIVE;	
		}
		else if(GET_IO_KEY_4 == 1)
		{
			ReValue = KEY_VALUE_SIX;
		}
		else if(GET_IO_KEY_5 == 1)
		{
			ReValue = KEY_VALUE_SEVEN;
		}

		CurrentKeyState = LINE2_OVER;
	}
	else
	{
		CurrentKeyState = LINE3_START;
		ReValue = KEY_VALUE_NULL;
	}	

	return ReValue;
}

static void Line2ScanOver(void)
{
	if((GET_IO_KEY_3 == 1)||(GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1))
	{
		CurrentKeyState = LINE2_OVER;	
	}
	else
	{
		CurrentKeyState = LINE3_START;
	}
}
/* Scan line 3 */
static void Line3ScanStart(void)
{
	ConfigurationLine3();

	if((GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1))
	{
		CurrentKeyState = LINE3_DETECTION;	
	}
	else
	{
		CurrentKeyState = LINE4_START;
	}		
}

static uint32_t Line3ScanDetection(void)
{
	uint32_t ReValue;

	if((GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1))
	{
		if(GET_IO_KEY_4 == 1)
		{
			ReValue = KEY_VALUE_EIGHT;	
		}
		else if(GET_IO_KEY_5 == 1)
		{
			ReValue = KEY_VALUE_NINE;
		}

		CurrentKeyState = LINE3_OVER;
	}
	else
	{
		CurrentKeyState = LINE4_START;
		ReValue = KEY_VALUE_NULL;
	}	

	return ReValue;
}

static void Line3ScanOver(void)
{
	if((GET_IO_KEY_4 == 1)||(GET_IO_KEY_5 == 1))
	{
		CurrentKeyState = LINE3_OVER;	
	}
	else
	{
		CurrentKeyState = LINE4_START;
	}
}
/* Scan line 4 */
static void Line4ScanStart(void)
{
	ConfigurationLine4();

	if(GET_IO_KEY_5 == 1)
	{
		CurrentKeyState = LINE4_DETECTION;	
	}
	else
	{
		CurrentKeyState = GND_START;
	}		
}

static uint32_t Line4ScanDetection(void)
{
	uint32_t ReValue;

	if(GET_IO_KEY_5 == 1)
	{
		ReValue = KEY_VALUE_TEN;	

		CurrentKeyState = LINE4_OVER;
	}
	else
	{
		CurrentKeyState = GND_START;
		ReValue = KEY_VALUE_NULL;
	}	

	return ReValue;
}

static void Line4ScanOver(void)
{
	if(GET_IO_KEY_5 == 1)
	{
		CurrentKeyState = LINE4_OVER;	
	}
	else
	{
		CurrentKeyState = GND_START;
	}
}
