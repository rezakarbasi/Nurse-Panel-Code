
#include "Keypad.h"

void Keypad_Init(KEYPAD_HANDLER * key){
	key->Key=HICH;
	key->output_number=0;
	key->state=MAKE_OUTPUT;
	
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
	if(key->state==MAKE_OUTPUT){
		
		GPIO_InitTypeDef init;
		
		init.Pin = key->k_pin[key->output_number].pin;
		init.Mode = GPIO_MODE_OUTPUT_PP;
		init.Pull = GPIO_NOPULL;
		init.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(key->k_pin[key->output_number].port, &init);
					
		key->state=SET_1;
	}	
	else if(key->state==SET_1){
		HAL_GPIO_WritePin(key->k_pin[key->output_number].port,key->k_pin[key->output_number].pin, GPIO_PIN_SET);
		
		key->state=CHECK;
	}
	else if(key->state==CHECK){
		for(uint8_t ii=0;ii<9;ii++){
			if(HAL_GPIO_ReadPin(key->k_pin[ii].port,key->k_pin[ii].pin)){
				if(key->output_number>ii){
					key->Key=ii*9+key->output_number;
					break;
				}
				else if(key->output_number<ii){
					key->Key=ii+key->output_number*9;
					break;
				}
			}
		}
		key->state=SET_0;
	}
	else if(key->state==SET_0){
		HAL_GPIO_WritePin(key->k_pin[key->output_number].port,key->k_pin[key->output_number].pin, GPIO_PIN_RESET);
		key->state=MAKE_INPUT;
	}
	else if(key->state==MAKE_INPUT){
		GPIO_InitTypeDef init;
		
		init.Pin = key->k_pin[key->output_number].pin;
		init.Mode = GPIO_MODE_INPUT;
		init.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(key->k_pin[key->output_number].port, &init);
		
		key->output_number++;
		if(key->output_number==9)key->output_number=0;
		
		if((key->Key==HICH) && (key->output_number!=0))	key->state=MAKE_OUTPUT;
		else	key->state=END_OF_CYCLE;
	}
}

void Keypad_Start(KEYPAD_HANDLER * key){
	key->state=MAKE_OUTPUT;
	key->Key=HICH;
	key->output_number=0;
}
