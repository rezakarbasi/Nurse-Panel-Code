#ifndef AUDIO_H
#define AUDIO_H

//	includes
#include "stm32f1xx_hal.h"
#include "SD_functions.h"
//#include "stdio.h"
//#include "stdlib.h"
//#include "dma.h"

// Defines
#define BitsPerSample		8
#define NumChannels			1
#define SampleRate 			8000

#define Date_Per_100ms		800

//types
typedef struct{
	FRESULT fres;
	FATFS fs;
	FIL fil;
	char path[20];
	uint16_t counter;
	int buffer_counter;
}AUDIO_FILE_HANDLER;

//	Variables
extern AUDIO_FILE_HANDLER audio_file;
extern char SD_buff[Date_Per_100ms];
//	Functions
uint8_t WavaRecorderHeaderInit(uint8_t* pHeadBuf,int NumSamples);//,uint8_t* audio)
FRESULT Start_Recording(uint16_t min,uint16_t hour, uint16_t day,uint16_t month);
//void SD_buffer_Transfered(DMA_HandleTypeDef *DmaHandle);
#endif
