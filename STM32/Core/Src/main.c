/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_customhid.h"
#include "5IO_Keypad.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SEND_BUFFER_SIZE 6
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern USBD_HandleTypeDef hUsbDeviceFS;

struct GamepadReport_t {
	uint16_t buttons;
	int8_t left_x;
	int8_t left_y;
	int8_t right_x;
	int8_t right_y;
};
typedef struct GamepadReport_t GamepadReport_t;

uint8_t dataSendBuffer[SEND_BUFFER_SIZE];
// global flag for detecting user input
uint8_t CHANGED = 0;
uint8_t SEND = 0;
GamepadReport_t gamepadReport;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */


void ResetGamepadReport() {
	gamepadReport.buttons = 0;
	gamepadReport.left_x = 0;
	gamepadReport.left_y = 0;
	gamepadReport.right_x = 0;
	gamepadReport.right_y = 0;
}

void PrepareSendBuffer(uint8_t *buffer, GamepadReport_t *gamepadReport) {
	buffer[0] = (uint8_t) (gamepadReport->buttons & 0x00FF);
	buffer[1] = (uint8_t) (gamepadReport->buttons >> 8);
	buffer[2] = gamepadReport->left_x;
	buffer[3] = gamepadReport->left_y;
	buffer[4] = gamepadReport->right_x;
	buffer[5] = gamepadReport->right_y;
}

void GetUserInput() {
	const uint8_t JOYSTICK_VALUE = 64;

	uint32_t leftKeypadValue = KeypadScan(LEFT);
	uint32_t rightKeypadValue = KeypadScan(RIGHT);
	if (leftKeypadValue == 0 && rightKeypadValue == 0) {
		if (CHANGED == 1) {
			ResetGamepadReport();
			PrepareSendBuffer(dataSendBuffer, &gamepadReport);

			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataSendBuffer, SEND_BUFFER_SIZE);
			CHANGED = 0;
		}
		return;
	}

	switch(leftKeypadValue) {
		case 1: gamepadReport.left_x = -JOYSTICK_VALUE; break; // LEFT
		case 2: gamepadReport.left_y = -JOYSTICK_VALUE; break;  // UP
		case 3: break; // PRESS
		case 4: gamepadReport.left_y = JOYSTICK_VALUE; break; // DOWN
		case 5: gamepadReport.left_x = JOYSTICK_VALUE; break;  // RIGHT
		case 6: break;
		case 7: gamepadReport.buttons |= 1U << 7; break;
		case 8: gamepadReport.buttons |= 1U << 6; break;
		case 9: gamepadReport.buttons |= 1U << 5; break;
		case 10: gamepadReport.buttons |= 1U << 4; break;
		case 11: break;
		case 12: gamepadReport.buttons |= 1U << 3; break;
		case 13: gamepadReport.buttons |= 1U << 2; break;
		case 14: gamepadReport.buttons |= 1U << 1; break;
		case 15: gamepadReport.buttons |= 1U << 0; break;
	}

	switch(rightKeypadValue) {
		case 1: gamepadReport.right_x = -JOYSTICK_VALUE; break; // LEFT
		case 2: gamepadReport.right_y = -JOYSTICK_VALUE; break;  // UP
		case 3: break; // PRESS
		case 4: gamepadReport.right_y = JOYSTICK_VALUE; break; // DOWN
		case 5: gamepadReport.right_x = JOYSTICK_VALUE; break;  // RIGHT
		case 6: break; // K1
		case 7: gamepadReport.buttons |= 1U << 8; break; // K2
		case 8: gamepadReport.buttons |= 1U << 9; break; // K3
		case 9: gamepadReport.buttons |= 1U << 10; break; // K4
		case 10: gamepadReport.buttons |= 1U << 11; break; // K5
		case 11: break; // K6
		case 12: gamepadReport.buttons |= 1U << 12; break; // K7
		case 13: gamepadReport.buttons |= 1U << 13; break; // K8
		case 14: gamepadReport.buttons |= 1U << 14; break; // K9
		case 15: gamepadReport.buttons |= 1U << 15; break; // K10
	}

	CHANGED = 1;
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
  ResetGamepadReport();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  GetUserInput();

	  if (CHANGED == 1) {
		  PrepareSendBuffer(dataSendBuffer, &gamepadReport);

	  	  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, dataSendBuffer, SEND_BUFFER_SIZE);
	  	  ResetGamepadReport();

	  	HAL_Delay(50);
	 }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB11 PB12 PB13 PB14 
                           PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 PD2 PD3 
                           PD6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
