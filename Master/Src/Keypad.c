
#include "Keypad.h"

void Keypad_Init(KEYPAD_HANDLER * key){
	key->Key=HICH;
	key->output_turn=0;
	key->reading_state=MAKE_OUTPUT;
	key->Number=0;
	
	key->k_pin[0].pin=K1_PIN;
	key->k_pin[0].port=K1_PORT;
	
	key->k_pin[1].pin=K2_PIN;
	key->k_pin[1].port=K2_PORT;
	
	key->k_pin[2].pin=K3_PIN;
	key->k_pin[2].port=K3_PORT;
	
	key->k_pin[3].pin=K4_PIN;
	key->k_pin[3].port=K4_PORT;
	
	key->k_pin[4].pin=K5_PIN;
	key->k_pin[4].port=K5_PORT;
	
	key->k_pin[5].pin=K6_PIN;
	key->k_pin[5].port=K6_PORT;
	
	key->k_pin[6].pin=K7_PIN;
	key->k_pin[6].port=K7_PORT;
	
	key->k_pin[7].pin=K8_PIN;
	key->k_pin[7].port=K8_PORT;
	
	key->k_pin[8].pin=K9_PIN;
	key->k_pin[8].port=K9_PORT;
}

void Keypad_Update(KEYPAD_HANDLER * key){
	if(key->reading_state==END_OF_CYCLE);
	else if(key->reading_state==MAKE_OUTPUT){
		
		GPIO_InitTypeDef init;
		
		init.Pin = key->k_pin[key->output_turn].pin;
		init.Mode = GPIO_MODE_OUTPUT_PP;
		init.Pull = GPIO_NOPULL;
		init.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(key->k_pin[key->output_turn].port, &init);
					
		key->reading_state=SET_1;
	}	
	else if(key->reading_state==SET_1){
		HAL_GPIO_WritePin(key->k_pin[key->output_turn].port,key->k_pin[key->output_turn].pin, GPIO_PIN_SET);
		
		key->reading_state=CHECK;
	}
	else if(key->reading_state==CHECK){
		for(uint8_t ii=0;ii<9;ii++){
			if(HAL_GPIO_ReadPin(key->k_pin[ii].port,key->k_pin[ii].pin)){
				if(key->output_turn>ii){
					key->Key=ii*9+key->output_turn;
					break;
				}
				else if(key->output_turn<ii){
					key->Key=ii+key->output_turn*9;
					break;
				}
			}
		}
		key->reading_state=SET_0;
	}
	else if(key->reading_state==SET_0){
		HAL_GPIO_WritePin(key->k_pin[key->output_turn].port,key->k_pin[key->output_turn].pin, GPIO_PIN_RESET);
		key->reading_state=MAKE_INPUT;
	}
	else if(key->reading_state==MAKE_INPUT){
		GPIO_InitTypeDef init;
		
		init.Pin = key->k_pin[key->output_turn].pin;
		init.Mode = GPIO_MODE_INPUT;
		init.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(key->k_pin[key->output_turn].port, &init);
		
		key->output_turn++;
		if(key->output_turn==9)key->output_turn=0;
		
		if((key->Key==HICH) && (key->output_turn!=0))	key->reading_state=MAKE_OUTPUT;
		else	key->reading_state=END_OF_CYCLE;
	}
}

void Keypad_Restart(KEYPAD_HANDLER * key){
	key->number_state=START_OF_NUM;
	if(key->Pre_Key==HICH && key->Key!=HICH){
		switch(key->Key){
			case SEFR:
				key->Number=key->Number*10+0;
				break;
			
			case YEK:
				key->Number=key->Number*10+1;
				break;
			
			case DOW:
				key->Number=key->Number*10+2;
				break;
			
			case SEH:
				key->Number=key->Number*10+3;
				break;
			
			case CHAHAR:
				key->Number=key->Number*10+4;
				break;
			
			case PANJ:
				key->Number=key->Number*10+5;
				break;
			
			case SHESH:
				key->Number=key->Number*10+6;
				break;
			
			case HAFT:
				key->Number=key->Number*10+7;
				break;
			
			case HASHT:
				key->Number=key->Number*10+8;
				break;
			
			case NOH:
				key->Number=key->Number*10+9;
				break;
			
			case HF:
				key->number_state=END_OF_NUM;
				break;
			
			case DEL:
				key->Number/=10;
				break;
			
			default:
				key->Number=key->Number;
		}
	}
	key->reading_state=MAKE_OUTPUT;
	key->Pre_Key=key->Key;
	key->Key=HICH;
	key->output_turn=0;
	
	if(key->Number==0)key->number_state=START_OF_NUM;
	else if(key->number_state==END_OF_NUM);
	else key->number_state=MIDDLE_OF_NUM;
}
