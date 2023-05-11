/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t RxBuffer[20];
uint8_t TxBuffer[500];
int freq_value = 0;
int LEDStatus = 1;
int lala = 0;
enum  {
		 MainMenu,
		 LEDControl,
		 ButtonStatus
}state = MainMenu;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void DummyTask();
void UARTInterruptConfig();
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
//  uint8_t text[] = "HELLO FIBO";
//  HAL_UART_Transmit(&huart2, text , 11, 10);
  UARTInterruptConfig();
  sprintf((char*)TxBuffer,"=======================================================\r\n"
		  "Welcome to LED and Button Control System\r\n"
		  "\r\n"
  							"Please Select these functions for selecting modes \r\n"
		  "\r\n"
  							"Press 0: LED Control mode \r\n"
  							"Press 1: Button status mode \r\n"
		  	  	  	  	  	"======================================================\r\n"
  							"\r\n");
  		HAL_UART_Transmit(&huart2, TxBuffer, strlen((char*)TxBuffer),300);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (LEDStatus == 1){
		  DummyTask();
	  }
	  if (LEDStatus == 0){
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
	  }

	  HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_0);

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 14400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 LD2_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) /*ถู�?เรีย�?เมื่อ Interrupt ถู�?ทำงาน ถ้าไม่เรีย�?ใช้ที่นี่จะไปทำงานใน Library �?ทน*/
{
	if(GPIO_Pin == GPIO_PIN_13){

		if(state == ButtonStatus && (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)) == 0)
		{
		sprintf((char*)TxBuffer,"----------------------------------------\r\n"
				"\r\n"
				"Status: Button is pressed \r\n"
				"\r\n"
				"----------------------------------------\r\n"
				"\r\n");
		HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
		}
		if(state == ButtonStatus && (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)) == 1)
		{
		sprintf((char*)TxBuffer,"----------------------------------------\r\n"
				"\r\n"
				"Status: Button is not pressed \r\n"
				"\r\n"
				"----------------------------------------\r\n"
				"\r\n");

		HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
		}
	}
}
void UARTInterruptConfig(){

	//start UART in interrupt mode
	HAL_UART_Receive_IT(&huart2, RxBuffer, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//	enum  {
//			 MainMenu,
//			 LEDControl,
//			 ButtonStatus
//	}state = MainMenu;
	if(huart == &huart2){

		// (for only string) Add String stop symbol \0 to end string
		RxBuffer[1] = '\0';
		//return receive char
		switch (state) {
		   case MainMenu:
				if(RxBuffer[0] == '0')
				{
					sprintf((char*)TxBuffer, "----------------------------------------\r\n"
							"\r\n"
							"Welcome to LED Control mode \r\n"
							"\r\n"
							"Please Select the function(s) \r\n"
							"\r\n"
							"Press a: Speed Up +1Hz \r\n"
							"Press s: Speed Down -1Hz \r\n"
							"Press d: On/Off \r\n"
							"Press x: back to the main menu \r\n"
							"\r\n"
							"----------------------------------------\r\n"
							" \r\n");
					HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
					state = LEDControl;
				}
				if(RxBuffer[0] == '1')
				{
					sprintf((char*)TxBuffer,"----------------------------------------\r\n"
							"\r\n"
							"Welcome to Button status mode \r\n"
							"\r\n"
							"Please Select the function(s) \r\n"
							"\r\n"
							"Press x: back to the main menu \r\n"
							"\r\n"
							"----------------------------------------\r\n"
							" \r\n");
					HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
					state = ButtonStatus;
				}
				if(RxBuffer[0] != '0' && RxBuffer[0] != '1'){
					sprintf((char*)TxBuffer, "****************************************\r\n"
							"\r\n"
							"Error! This function button is unavailable! \r\n"
							"Please check your input before enter. \r\n"
							"\r\n"
							"****************************************\r\n"
							"\r\n");

					HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
				}
					break;
		   case LEDControl:
		  				if(RxBuffer[0] == 'a')
		  				{
		  					freq_value = freq_value + 1;
		  					if (LEDStatus == 0){
		  						sprintf((char*)TxBuffer,"****************************************\r\n"
		  								"\r\n"
		  								"LED is off, Please turn on the LED! \r\n"
		  								"\r\n"
										"****************************************\r\n"
										"\r\n")	;
		  						HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
		  					}
		  					if (LEDStatus == 1){
		  					sprintf((char*)TxBuffer,"----------------------------------------\r\n"
		  							"\r\n"
		  							"a was pressed: Speed Up +1= %d Hz \r\n"
		  							"\r\n"
		  							"----------------------------------------\r\n"
		  							"\r\n", freq_value);
		  					HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
		  					}
		  				}
		  				if(RxBuffer[0] == 's')
		  				{
		  					freq_value = freq_value - 1;
		  					if (LEDStatus == 0){
		  						sprintf((char*)TxBuffer,"****************************************\r\n"
		  								"\r\n"
		  								"LED is off, Please turn on the LED! \r\n"
		  								"\r\n"
		  								"****************************************\r\n");
		  						HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
		  					}
		  					if (LEDStatus == 1){
								if (freq_value < 0 ){
									sprintf((char*)TxBuffer,"****************************************\r\n"
											"\r\n"
											"Invalid! The LED frequency must not less than 0 Hz \r\n"
											"****************************************\r\n"
											"\r\n");

									HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
									freq_value = 0;
								}
								else{
									sprintf((char*)TxBuffer,"----------------------------------------\r\n"
											"\r\n"
											"s was pressed: Speed Down -1= %d Hz \r\n"
											"\r\n"
											"----------------------------------------\r\n"
											"\r\n", freq_value);
									HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
								}
		  					}
		  				}
			  			if(RxBuffer[0] == 'd'){

			  					if (LEDStatus == 1)
			  				{
			  						LEDStatus = 0;
			  						lala = 1;
				  				sprintf((char*)TxBuffer,"----------------------------------------\r\n"
				  						"\r\n"
				  						"d was pressed: LED is off! \r\n"
				  						"\r\n"
				  						"----------------------------------------\r\n"
				  						"\r\n");
				  				HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
			  				}
			  					else {
						  			LEDStatus = 1;
						  			lala = 2;
						  		sprintf((char*)TxBuffer,"----------------------------------------\r\n"
						  				"\r\n"
						  				"d was pressed: LED is on! \r\n"
						  				"\r\n"
						  				"----------------------------------------\r\n"
						  				"\r\n");
						  		HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
						  					}
			  				}
				  		if(RxBuffer[0] == 'x'){
								sprintf((char*)TxBuffer,"=========================================================\r\n"
										"\r\n"
										"Welcome to LED and Button Control System \r\n"
										"\r\n"
			  							"Please Select these functions for selecting modes \r\n"
										"\r\n"
			  							"Press 0: LED Control mode \r\n"
			  							"Press 1: Button status mode \r\n"
										"\r\n"
										"=========================================================\r\n"
			  							"\r\n");
				  				HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
				  				state = MainMenu;
			  				}
				  		if(RxBuffer[0] != 'x' && RxBuffer[0] != 'a' && RxBuffer[0] != 'd' && RxBuffer[0] != 's'){
				  					sprintf((char*)TxBuffer,"****************************************\r\n"
				  							"\r\n"
				  							"Error! This function button is unavailable! \r\n"
				  							"Please check your input before enter. \r\n"
				  							"\r\n"
				  							"****************************************\r\n"
				  							"\r\n");
				  					HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
				  					}
			  			break;
		   case ButtonStatus:
		  				if(RxBuffer[0] == 'x')
		  				{
		  					sprintf((char*)TxBuffer,"=========================================================\r\n"
		  							"\r\n"
		  							"Welcome to LED and Button Control System \r\n"
		  							"Please Select these functions for selecting modes \r\n"
		  							"\r\n"
		  							"Press 0: LED Control mode \r\n"
		  							"Press 1: Button status mode \r\n"
		  							"\r\n"
		  							"=========================================================\r\n"
		  							"\r\n");
		  					HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
		  				}
					  	if(RxBuffer[0] != 'x'){
					  		sprintf((char*)TxBuffer,"****************************************\r\n"
					  				"\r\n"
					  				"Error! This function button is unavailable! \r\n"
					  				"Please check your input before enter. \r\n"
					  				"\r\n"
					  				"****************************************\r\n"
					  				"\r\n");
					  		HAL_UART_Transmit_IT(&huart2, TxBuffer, strlen((char*)TxBuffer));
					  					}
		  					RxBuffer[0] = 0;
		  					state = MainMenu;
		  					break;
		  				}

			}

		HAL_UART_Receive_IT(&huart2, RxBuffer, 1);
		//recall Receive
	}


void DummyTask(){
	static uint32_t timestamp = 0;
	if (HAL_GetTick()>=timestamp){
		timestamp = HAL_GetTick() + (1000/(freq_value * 2)); // divide 2 because it's a toggle
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
