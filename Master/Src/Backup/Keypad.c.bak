
#include "Keypad.h"

KEY function(void)
{
	KEY kk=HICH;
	GPIO_InitTypeDef init;
	
	/* K1 => output */
  init.Pin = K1_PIN;
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(K1_PORT, &init);
	HAL_Delay(1);
	
	HAL_GPIO_WritePin(K1_PORT, K1_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	
	/* check */
	if(HAL_GPIO_ReadPin(K2_PORT, K2_PIN)){kk= M2;}
	else if(HAL_GPIO_ReadPin(K3_PORT, K3_PIN)){kk= M1;}
	else if(HAL_GPIO_ReadPin(K4_PORT, K4_PIN)){kk= M8;}
	else if(HAL_GPIO_ReadPin(K5_PORT, K5_PIN)){kk= M3;}
	else if(HAL_GPIO_ReadPin(K6_PORT, K6_PIN)){kk= M4;}
	else if(HAL_GPIO_ReadPin(K7_PORT, K7_PIN)){kk= M5;}
	else if(HAL_GPIO_ReadPin(K8_PORT, K8_PIN)){kk= M7;}
	else if(HAL_GPIO_ReadPin(K9_PORT, K9_PIN)){kk= M6;}
	
	HAL_GPIO_WritePin(K1_PORT, K1_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	
	/* K1 => input */
	init.Pin = K1_PIN;
	init.Mode = GPIO_MODE_INPUT;
  init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(K1_PORT, &init);
	HAL_Delay(1);
	
	if(kk!=HICH)return kk;
	
	
	
	/* K2 => output */
  init.Pin = K2_PIN;
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(K2_PORT, &init);
	HAL_Delay(1);
	
	HAL_GPIO_WritePin(K2_PORT, K2_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	
	/* check */
	if(HAL_GPIO_ReadPin(K1_PORT, K1_PIN)){kk= M2;}
	else if(HAL_GPIO_ReadPin(K3_PORT, K3_PIN)){kk= HICH;}
	else if(HAL_GPIO_ReadPin(K4_PORT, K4_PIN)){kk= DOWN;}
	else if(HAL_GPIO_ReadPin(K5_PORT, K5_PIN)){kk= HICH;}
	else if(HAL_GPIO_ReadPin(K6_PORT, K6_PIN)){kk= DOW;}
	else if(HAL_GPIO_ReadPin(K7_PORT, K7_PIN)){kk= PANJ;}
	else if(HAL_GPIO_ReadPin(K8_PORT, K8_PIN)){kk= HASHT;}
	else if(HAL_GPIO_ReadPin(K9_PORT, K9_PIN)){kk= SEFR;}
	
	HAL_GPIO_WritePin(K2_PORT, K2_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	
	/* K2 => input */
	init.Pin = K2_PIN;
	init.Mode = GPIO_MODE_INPUT;
  init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(K2_PORT, &init);
	HAL_Delay(1);
	
	if(kk!=HICH)return kk;

	
	
	/* K3 => output */
  init.Pin = K3_PIN;
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(K3_PORT, &init);
	HAL_Delay(1);
	
	HAL_GPIO_WritePin(K3_PORT, K3_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	
	/* check */
	if(HAL_GPIO_ReadPin(K1_PORT, K1_PIN)){kk= M1;}
	else if(HAL_GPIO_ReadPin(K2_PORT, K2_PIN)){kk= HICH;}
	else if(HAL_GPIO_ReadPin(K4_PORT, K4_PIN)){kk= UP;}
	else if(HAL_GPIO_ReadPin(K5_PORT, K5_PIN)){kk= OUT;}
	else if(HAL_GPIO_ReadPin(K6_PORT, K6_PIN)){kk= YEK;}
	else if(HAL_GPIO_ReadPin(K7_PORT, K7_PIN)){kk= CHAHAR;}
	else if(HAL_GPIO_ReadPin(K8_PORT, K8_PIN)){kk= HAFT;}
	else if(HAL_GPIO_ReadPin(K9_PORT, K9_PIN)){kk= SETAREH;}
	
	HAL_GPIO_WritePin(K3_PORT, K3_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	
	/* K3 => input */
	init.Pin = K3_PIN;
	init.Mode = GPIO_MODE_INPUT;
  init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(K3_PORT, &init);
	HAL_Delay(1);
	
	if(kk!=HICH)return kk;
	
	
	
	/* K4 => output */
  init.Pin = K4_PIN;
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(K4_PORT, &init);
	HAL_Delay(1);
	
	HAL_GPIO_WritePin(K4_PORT, K4_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	
	/* check */
	if(HAL_GPIO_ReadPin(K1_PORT, K1_PIN)){kk= M8;}
	else if(HAL_GPIO_ReadPin(K2_PORT, K2_PIN)){kk= DOWN;}
	else if(HAL_GPIO_ReadPin(K3_PORT, K3_PIN)){kk= UP;}
	else if(HAL_GPIO_ReadPin(K5_PORT, K5_PIN)){kk=DEL;}
	else if(HAL_GPIO_ReadPin(K6_PORT, K6_PIN)){kk=HOLD;}
	else if(HAL_GPIO_ReadPin(K7_PORT, K7_PIN)){kk=HF;}
	else if(HAL_GPIO_ReadPin(K8_PORT, K8_PIN)){kk=MUTE;}
	else if(HAL_GPIO_ReadPin(K9_PORT, K9_PIN)){kk=SETT;}
	
	HAL_GPIO_WritePin(K4_PORT, K4_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	
	/* K4 => input */
	init.Pin = K4_PIN;
	init.Mode = GPIO_MODE_INPUT;
  init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(K4_PORT, &init);
	HAL_Delay(1);
	
	if(kk!=HICH)return kk;
	
	
	
	/* K5 => output */
  init.Pin = K5_PIN;
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(K5_PORT, &init);
	HAL_Delay(1);
	
	HAL_GPIO_WritePin(K5_PORT, K5_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	
	/* check */
	if(HAL_GPIO_ReadPin(K1_PORT, K1_PIN)){kk=M3;}
	else if(HAL_GPIO_ReadPin(K3_PORT, K3_PIN)){kk=OUT;}
	else if(HAL_GPIO_ReadPin(K4_PORT, K4_PIN)){kk=DEL;}
	else if(HAL_GPIO_ReadPin(K6_PORT, K6_PIN)){kk=SEH;}
	else if(HAL_GPIO_ReadPin(K7_PORT, K7_PIN)){kk=SHESH;}
	else if(HAL_GPIO_ReadPin(K8_PORT, K8_PIN)){kk=NOH;}
	else if(HAL_GPIO_ReadPin(K9_PORT, K9_PIN)){kk=SHARP;}
	
	HAL_GPIO_WritePin(K5_PORT, K5_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	
	/* K5 => input */
	init.Pin = K5_PIN;
	init.Mode = GPIO_MODE_INPUT;
  init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(K5_PORT, &init);
	HAL_Delay(1);
	
	if(kk!=HICH)return kk;
	
	
	
	/* K6 => output */
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(K6_PORT, &init);
	HAL_Delay(1);
	
	HAL_GPIO_WritePin(K6_PORT, K6_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	
	/* check */
	if(HAL_GPIO_ReadPin(K1_PORT, K1_PIN)){kk= M4;}
	else if(HAL_GPIO_ReadPin(K2_PORT, K2_PIN)){kk= DOW;}
	else if(HAL_GPIO_ReadPin(K3_PORT, K3_PIN)){kk= YEK;}
	else if(HAL_GPIO_ReadPin(K4_PORT, K4_PIN)){kk= HOLD;}
	else if(HAL_GPIO_ReadPin(K5_PORT, K5_PIN)){kk= SEH;}
	else if(HAL_GPIO_ReadPin(K7_PORT, K7_PIN)){kk= RD;}
	else if(HAL_GPIO_ReadPin(K8_PORT, K8_PIN)){kk= M9;}
	else if(HAL_GPIO_ReadPin(K9_PORT, K9_PIN)){kk= BACK;}
	
	HAL_GPIO_WritePin(K6_PORT, K6_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	
	/* K6 => input */
	init.Pin = K6_PIN;
	init.Mode = GPIO_MODE_INPUT;
  init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(K6_PORT, &init);
	HAL_Delay(1);
	
	
	if(kk!=HICH)return kk;
	


	/* K7 => output */
  init.Pin = K7_PIN;
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(K7_PORT, &init);
	HAL_Delay(1);
	
	HAL_GPIO_WritePin(K7_PORT, K7_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	
	/* check */
	if(HAL_GPIO_ReadPin(K1_PORT, K1_PIN)){kk= M5;}
	else if(HAL_GPIO_ReadPin(K2_PORT, K2_PIN)){kk= PANJ;}
	else if(HAL_GPIO_ReadPin(K3_PORT, K3_PIN)){kk= CHAHAR;}
	else if(HAL_GPIO_ReadPin(K4_PORT, K4_PIN)){kk= HF;}
	else if(HAL_GPIO_ReadPin(K5_PORT, K5_PIN)){kk= SHESH;}
	else if(HAL_GPIO_ReadPin(K6_PORT, K6_PIN)){kk= RD;}
	else if(HAL_GPIO_ReadPin(K8_PORT, K8_PIN)){kk= M10;}
	else if(HAL_GPIO_ReadPin(K9_PORT, K9_PIN)){kk= KEYTONE;}
	
	HAL_GPIO_WritePin(K7_PORT, K7_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	
	/* K7 => input */
	init.Pin = K7_PIN;
	init.Mode = GPIO_MODE_INPUT;
  init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(K7_PORT, &init);
	HAL_Delay(1);
	
	if(kk!=HICH)return kk;
	


	/* K8 => output */
  init.Pin = K8_PIN;
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
	init.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(K8_PORT, &init);
	HAL_Delay(1);
	
	HAL_GPIO_WritePin(K8_PORT, K8_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	
	/* check */
	if(HAL_GPIO_ReadPin(K1_PORT, K1_PIN)){kk= M7;}
	else if(HAL_GPIO_ReadPin(K2_PORT, K2_PIN)){kk= HASHT;}
	else if(HAL_GPIO_ReadPin(K3_PORT, K3_PIN)){kk= HAFT;}
	else if(HAL_GPIO_ReadPin(K4_PORT, K4_PIN)){kk= MUTE;}
	else if(HAL_GPIO_ReadPin(K5_PORT, K5_PIN)){kk= NOH;}
	else if(HAL_GPIO_ReadPin(K6_PORT, K6_PIN)){kk= M9;}
	else if(HAL_GPIO_ReadPin(K7_PORT, K7_PIN)){kk= M10;}
	else if(HAL_GPIO_ReadPin(K9_PORT, K9_PIN)){kk= FLASHH;}
	
	HAL_GPIO_WritePin(K8_PORT, K8_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);
	
	/* K8 => input */
	init.Pin = K8_PIN;
	init.Mode = GPIO_MODE_INPUT;
  init.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(K8_PORT, &init);
	HAL_Delay(1);
	
	return kk;
}