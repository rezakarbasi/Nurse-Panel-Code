/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
//includes
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

#include "Audio.h"

#include "Master.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t Buff_get[Packet_Length];

char lcd_buff[20];
int cc=0;

uint8_t Tx_buff[Date_Per_100ms];
uint8_t Rx_buff[Date_Per_100ms];

uint16_t adcBuff[2][Date_Per_100ms];
uint8_t dacBuff[2][Date_Per_100ms];

char Adc_p=0;
char Dac_p=0;

uint8_t temp=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac1);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_DMA_Init();
  MX_DAC_Init();
  MX_ADC1_Init();
  MX_SPI3_Init();
  MX_SPI2_Init();
  MX_TIM8_Init();
  MX_USART2_UART_Init();
  MX_TIM7_Init();
  MX_TIM5_Init();

  /* USER CODE BEGIN 2 */
	ILI9341_Init();//initial driver setup to drive ili9341
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	ILI9341_Fill_Screen(WHITE);
	ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	ILI9341_Draw_Text("Debug", 32, 0, RED, 4, WHITE);
	
	Master_Init();
	
	HAL_TIM_Base_Start_IT(&htim7);
	
	HAL_Delay(2);
	
	HAL_TIM_Base_Start(&htim8);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adcBuff[Adc_p],Date_Per_100ms);
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(uint32_t *)dacBuff[Dac_p],Date_Per_100ms,DAC_ALIGN_8B_R);
	
	while (1)
  {
		switch(master.state){
			case SENDING_HELLO:
				master.hello_id++;
				if(master.hello_id>USER_NUMBER)master.hello_id=0;
				
				if(User_state[master.hello_id].DIST_PCK.timeout<MAX_TIMEOUT){
					
					master.hello_counter++;
					if(master.hello_counter==HELLO_COUNTER_PER_CYCLE){
						master.hello_counter=0;
						if(master.call_flag==FLAG_ENABLE)master.state=SENDING_AUDIO;
						else master.state=WAITING;
						
						break;
					}
					Send_PCK(master.hello_id,Normal_conv,0,1,255,0,Buff_get);
					master.state=WAITING_FOR_SENDING_HELLO;
				}
				break;
			
				case WAITING_FOR_SENDING_HELLO:
				case WAITING_FOR_RECEIVING_HELLO:
					if(master.audio_rx_cplt_flag==FLAG_ENABLE){
						master.audio_rx_cplt_flag=FLAG_DISABLE;
					
						char jj=0;
						if(Dac_p==0)jj=1;
						for(int f=0;f<Date_Per_100ms;f++)dacBuff[jj][f]=Rx_buff[f];
					
						break;
					}
				
					if(master.audio_tx_cplt_flag==FLAG_ENABLE){
						master.audio_tx_cplt_flag=FLAG_DISABLE;
					
						char j=0;
						if(Adc_p==0)j=1;
						for(int f=0;f<Date_Per_100ms;f++)Tx_buff[f]=adcBuff[j][f]>>4;
						
						break;
					}
					break;
			
			case SENDING_AUDIO:
				Send_Audio(master.call_id,Tx_buff,Rx_buff,Date_Per_100ms);
				master.state=WAITING_FOR_SENDING_AUDIO;
				break;
			
			case WAITING_FOR_RECEIVING_AUDIO:
			case WAITING_FOR_SENDING_AUDIO:
			case WAITING:
				// SD			LCD			Keypad
				if(master.audio_rx_cplt_flag==FLAG_ENABLE){
					master.audio_rx_cplt_flag=FLAG_DISABLE;
					
					char jj=0;
					if(Dac_p==0)jj=1;
					for(int f=0;f<Date_Per_100ms;f++)dacBuff[jj][f]=Rx_buff[f];
					
					break;
				}
				
				if(master.audio_tx_cplt_flag==FLAG_ENABLE){
					master.audio_tx_cplt_flag=FLAG_DISABLE;
					
					char j=0;
					if(Adc_p==0)j=1;
					for(int f=0;f<Date_Per_100ms;f++)Tx_buff[f]=adcBuff[j][f]>>4;
					
					break;
				}
				
				if(master.save_2_SD_flag==FLAG_ENABLE){
					master.save_2_SD_flag=FLAG_DISABLE;
					break;
				}
				
				if(master.refresh_LCD_flag==FLAG_ENABLE){
					master.refresh_LCD_flag=FLAG_DISABLE;
					break;
				}
				
				if(master.update_keypad_flag==FLAG_ENABLE){
					master.update_keypad_flag=FLAG_DISABLE;
					break;
				}
				
				sprintf(lcd_buff,"received pck : %d",cc);
				ILI9341_Draw_Text(lcd_buff,20,60,BLACK,2,WHITE);
				break;
		}
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV8;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
	if(master.state==WAITING_FOR_SENDING_AUDIO){		
		master.audio_tx_cplt_flag=FLAG_ENABLE;
		master.state=WAITING_FOR_RECEIVING_AUDIO;
	}
	else if(master.state==WAITING_FOR_SENDING_HELLO)master.state=WAITING_FOR_RECEIVING_HELLO;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(master.state==WAITING_FOR_RECEIVING_AUDIO){
		HAL_UART_Abort(&huart2);
		master.state=WAITING;
		master.audio_rx_cplt_flag=FLAG_ENABLE;
	}
	else if(master.state==WAITING_FOR_RECEIVING_HELLO){
		HAL_UART_Abort(&huart2);
		master.state=SENDING_HELLO;
		HAL_TIM_Base_Stop_IT(&htim5);
		
		for(uint8_t ii=0;ii<Packet_Length;ii++){
			if(GetNewData(Buff_get[ii],master.hello_id)==PCK_Unknown){
				User_state[master.hello_id].DIST_PCK.timeout++;
				cc++;
				break;
			}
		}
	}
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac1){
	if(Dac_p==0)Dac_p=1;
	else Dac_p=0;
	
	HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_1);
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(uint32_t *)dacBuff[Dac_p],Date_Per_100ms,DAC_ALIGN_8B_R);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	if(Adc_p==0)Adc_p=1;
	else Adc_p=0;
	
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adcBuff[Adc_p],Date_Per_100ms);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance==TIM7){
		if(master.state==WAITING_FOR_RECEIVING_AUDIO)cc++;
		HAL_UART_Abort(&huart2);
		master.state=SENDING_HELLO;
	}
	else if(htim->Instance==TIM5){
		temp++;
		if(temp%2==0){
			master.state=SENDING_HELLO;
			HAL_UART_Abort(&huart2);
			User_state[master.hello_id].DIST_PCK.timeout++;
			HAL_TIM_Base_Stop_IT(&htim5);
		}
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
