//	includes
#include "stm32f1xx_hal.h"
#include "SD_functions.h"
#include "stdio.h"
#include "stdlib.h"
//#include "adc.h"
#include "dma.h"

// Defines
#define BitsPerSample		8
#define NumChannels			1
#define SampleRate 			8000

#define NumSampleGiri			100
#define Date_Per_100ms		800

#define	FF_FileName			"mishe.wav"

//	Variables
extern FRESULT fr;
extern FATFS fs;
extern FIL fil;

//extern int SD_t;
//extern int ADC_t;
//extern int Mount_t;
//extern int Open_t;
//extern int Seek_t;
//extern int Write_t;
//extern int Close_t;

//extern uint8_t play_audio[2][audio_size];

extern int flag;
//extern int junk;

//extern uint16_t ADC_buff[Date_Per_100ms];
extern uint16_t SD_buff[Date_Per_100ms];

//	Functions
uint8_t WavaRecorderHeaderInit(uint8_t* pHeadBuf,int NumSamples);//,uint8_t* audio)
//void SD_buffer_Transfered(DMA_HandleTypeDef *DmaHandle);
