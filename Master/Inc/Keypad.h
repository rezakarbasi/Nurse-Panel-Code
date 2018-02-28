#ifndef KEYPAD_H
#define KEYPAD_H

// includes
#include "gpio.h"

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

//types
typedef enum {
	SEFR = 0,
	YEK = 1,
	DOW = 2,
	SEH = 3,
	CHAHAR = 4,
	PANJ = 5,
	SHESH = 6,
	HAFT = 7,
	HASHT = 8,
	NOH = 9,
	SETAREH = 10,
	SHARP = 11,
	M1 = 12,
	M2 = 13,
	M3 = 14,
	M4 = 15,
	M5 = 16,
	M6 = 17,
	M7 = 18,
	M8 = 19,
	M9 = 20,
	M10 = 21,
	UP = 22,
	DOWN = 23,
	OUT = 24,
	DEL = 25,
	SETT = 26,
	BACK = 27,
	MUTE = 28,
	FLASHH	 = 29,
	KEYTONE = 30,
	HOLD = 31,
	RD = 32,
	HF = 33,
	HICH = 34
}KEY;

//functions
KEY function(void);

//variables
//extern KEY kk;

#endif
