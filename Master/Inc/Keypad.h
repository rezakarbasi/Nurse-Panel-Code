#ifndef KEYPAD_H
#define KEYPAD_H

// includes
#include "gpio.h"
#include "stm32f1xx_hal.h"
#include "tim.h"

//defines
#define K2_PORT GPIOC
#define K2_PIN GPIO_PIN_10

#define K1_PORT GPIOA
#define K1_PIN GPIO_PIN_12

#define K4_PORT GPIOA
#define K4_PIN GPIO_PIN_11

#define K3_PORT GPIOA
#define K3_PIN GPIO_PIN_10

#define K6_PORT GPIOA
#define K6_PIN GPIO_PIN_9

#define K5_PORT GPIOA
#define K5_PIN GPIO_PIN_8

#define K8_PORT GPIOC
#define K8_PIN GPIO_PIN_9

#define K7_PORT GPIOC
#define K7_PIN GPIO_PIN_8

#define K9_PORT GPIOC
#define K9_PIN GPIO_PIN_6


#define Keypad_HAL_Timer	htim4
#define Keypad_Timer 			TIM4


//types
typedef enum {
	SEFR= 17,
	YEK= 23,
	DOW= 14,
	SEH = 41,
	CHAHAR = 24,
	PANJ = 15,
	SHESH = 42,
	HAFT = 25,
	HASHT = 16,
	NOH = 43,
	SETAREH = 26,
	SHARP = 44,
	M1 = 2,
	M2 = 1,
	M3 = 4,
	M4 = 5,
	M5 = 6,
	M6 = 8,
	M7 = 7,
	M8 = 3,
	M9 = 52,
	M10 = 61,
	UP = 21,
	DOWN = 12,
	OUT = 22,
	DEL = 31,
	SETT = 35,
	BACK = 53,
	MUTE = 34,
	FLASHH= 71,
	KEYTONE = 62,
	HOLD = 32,
	RD = 51,
	HF = 33,
	HICH = 100
}KEY;

typedef enum{
	CONTINUE=0,
	WAIT=1,
}KEYPAD_FLAG;

typedef enum{
	MAKE_OUTPUT=0,
	SET_1=1,
	CHECK=2,
	SET_0=3,
	MAKE_INPUT=4,
	END_OF_CYCLE=5
}KEY_STATE;

typedef struct{
	GPIO_TypeDef * port;
	uint16_t pin;
}KEY_GPIO;

typedef struct{
	KEY Key;
	uint8_t output_number;
	KEY_STATE state;
	KEY_GPIO k_pin[9];
	KEYPAD_FLAG flag;
}KEYPAD_HANDLER;

//functions
void Keypad_Update(KEYPAD_HANDLER * key);
void Keypad_Init(KEYPAD_HANDLER * key);

//variables
//extern KEY kk;

#endif
