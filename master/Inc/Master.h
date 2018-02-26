//includes
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "tim.h"

//defines

#define Packet_Length 10

#define START_BYTE0 0xA5
#define START_BYTE1 0x5A
#define START_BYTE2 0x00
#define START_BYTE3 0xFF
#define STOP_BYTE 0x80

#define USER_NUMBER	120

#define HELLO_TIMEOUT	1

#define HELLO_COUNTER_PER_CYCLE	12

#define MAX_TIMEOUT	10

//Types

// state of packet enumeration
typedef enum {
	PCK_Wait,
	PCK_Unknown ,
	PCK_Data ,
	PCK_Audio
}PCK_STATE;

typedef enum{
	Normal_conv,
	Speak_req
}FUNCTION;

typedef enum{
	SENDING_HELLO,
	SENDING_AUDIO,
	WAITING_FOR_SENDING_AUDIO,
	WAITING_FOR_RECEIVING_AUDIO,
	WAITING_FOR_SENDING_HELLO,
	WAITING_FOR_RECEIVING_HELLO,
	WAITING,
}MASTER_PROGRAM_STATE;

typedef enum{
	FLAG_ENABLE=1,
	FLAG_DISABLE=0,
}FLAG;

typedef struct{
	MASTER_PROGRAM_STATE state;
	FLAG call_flag;
	uint8_t call_id;
	uint8_t hello_id;
	uint8_t hello_counter;
	FLAG audio_adc_cplt_flag;
	FLAG audio_uart_cplt_flag;	
	FLAG save_2_SD_flag;
	FLAG refresh_LCD_flag;
	FLAG update_keypad_flag;
	FLAG fflag;
}MASTER_HANDLER;

//conversation packet struct and union
typedef union
{
	struct DATA_CONV
  {
    uint8_t ST0;
    uint8_t ST1;
    uint8_t addr;
    uint8_t func;
		uint8_t data1;
		uint8_t data2;
		uint8_t data3;
		uint8_t data4;
		uint8_t cksum;
		uint8_t stp;
		uint8_t timeout;
  }DIST_PCK;															// Distributed packet
	
  uint8_t ASS_PCK[Packet_Length+1];					// Associated  packet
}PCK_CONV;

// Variables
extern PCK_CONV Send_pck;
extern PCK_CONV User_state[USER_NUMBER];
extern uint8_t PCK_RCV;
extern MASTER_HANDLER master;

// Functions
void Init_PCK(PCK_CONV * pck,uint8_t address,FUNCTION function,uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4);
//PCK_STATE Check_PCK(uint8_t * buff);
PCK_STATE GetNewData(uint8_t data,uint8_t id);
HAL_StatusTypeDef Send_PCK(uint8_t address,FUNCTION function,uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t * buffer);
uint8_t Send_Audio(uint8_t address,uint8_t * audio_send,uint8_t * audio_receive,int audio_size);
void Master_Init(void);