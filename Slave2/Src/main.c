/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "Slave.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint8_t state_pck;
uint8_t temp_TIM2=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac11);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
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
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  MX_DAC_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	Slave_Init(10);
	while (1)
  {
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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	switch(slave.state){
		case WAITING_PCK:
			state_pck= GetNewData(buff_1byte);
			
			if(state_pck==PCK_With_Me){
				Send_PCK(slave.pck.DIST_PCK.func,slave.pck.DIST_PCK.data1,
				slave.pck.DIST_PCK.data2,slave.pck.DIST_PCK.data3,slave.pck.DIST_PCK.data4);
				slave.pck.DIST_PCK.func=Normal_conv;
				slave.state=SENDING_HELLO;
			}
			else if(state_pck==PCK_REQ_SP_ME){
				if(slave.call_flag==FLAG_DISABLE)Make_Call(adcBuff,uart_audio_buff);
				
				//timer start
				HAL_TIM_Base_Stop_IT(&Timeout_Timer);
				HAL_TIM_Base_Start_IT(&Timeout_Timer);
				Timeout_Timer.Instance->CNT=0;
				
				HAL_UART_Receive_DMA(&Slave_Uart,uart_audio_buff+Date_Per_100ms*slave.rx_p,Date_Per_100ms);
				
				slave.state=GETTING_AUDIO;
			}
			else{
				HAL_UART_Abort(&Slave_Uart);
				HAL_UART_Receive_IT(&Slave_Uart,&buff_1byte,1);
			}
			break;
		
		case GETTING_AUDIO:
		
			// timer end
			HAL_TIM_Base_Stop_IT(&Timeout_Timer);
			Timeout_Timer.Instance->CNT=0;
			
			uint8_t jj=0;
			if(slave.adc_p==0)jj=1;
		
			Send_Audio(adc_audio_buff+Date_Per_100ms*jj,Date_Per_100ms);
			slave.rx_flag=FLAG_ENABLE;
		
			slave.state=SENDING_AUDIO;
			break;
		
		default :
			HAL_UART_Abort(&Slave_Uart);
			HAL_UART_Receive_IT(&Slave_Uart,&buff_1byte,1);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	HAL_GPIO_WritePin(RS485_GPIO_PORT,RS485_GPIO_PIN,GPIO_PIN_RESET);
	slave.state=WAITING_PCK;
	HAL_UART_Abort(&Slave_Uart);
	HAL_UART_Receive_IT(&Slave_Uart,&buff_1byte,1);	
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance==TIM2 && temp_TIM2!=0){
		HAL_TIM_Base_Stop_IT(&Timeout_Timer);
		Timeout_Timer.Instance->CNT=0;
		
		slave.rx_flag=FLAG_ENABLE;
		
		uint8_t jj=0;
		if(slave.adc_p==0)jj=1;
		
		Send_Audio(adc_audio_buff+Date_Per_100ms*jj,Date_Per_100ms);
		
		slave.state=SENDING_AUDIO;
	}
	else if(temp_TIM2==0)temp_TIM2=1;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)(adcBuff),Date_Per_100ms);
	
	uint8_t jj=slave.adc_p;
	if(slave.adc_p==0)slave.adc_p=1;
	else slave.adc_p=0;
	
	for(int ii=0;ii<Date_Per_100ms;ii++)adc_audio_buff[jj*Date_Per_100ms+ii]=adcBuff[ii]>>4;
	
	// check every 100 ms bejaye timer 100ms
	if(slave.call_flag==FLAG_ENABLE && slave.rx_flag==FLAG_ENABLE && slave.start_call_flag==FLAG_ENABLE){
		slave.start_call_flag=FLAG_DISABLE;
		
		uint8_t jj=0;
		if(slave.rx_p==0)jj=1;
		
		HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(uint32_t *)uart_audio_buff+jj*Date_Per_100ms,Date_Per_100ms,DAC_ALIGN_8B_R);
	}
	else if(slave.call_flag==FLAG_DISABLE)HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_2);
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac11){
	HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_2);
	
	uint8_t jj=0;
	if(slave.rx_p==0)jj=1;
		
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(uint32_t *)uart_audio_buff+jj*Date_Per_100ms,Date_Per_100ms,DAC_ALIGN_8B_R);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
