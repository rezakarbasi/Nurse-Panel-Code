//includes
#include "stm32f1xx_hal.h"
#include "usart.h"

//defines
#define ADDRESS		1

#define Packet_Length 10
#define START_BYTE0 0xA5
#define START_BYTE1 0x5A
#define START_BYTE2 0x00
#define START_BYTE3 0xFF
#define STOP_BYTE 0x80
#define Buffer_Size Packet_Length
#define USER_NUMBER	10

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
	GETTING_HELLO,
	SENDING_AUDIO,
	GETTING_AUDIO,
	WAITING,
	REFRESHING_LCD,
	TRANSFERRING_SD
}MASTER_PROGRAM_STATE;

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
extern PCK_CONV Received_pck[USER_NUMBER];
extern PCK_CONV Req_pck;
extern uint8_t PCK_RCV;

// Functions
void Init_PCK(PCK_CONV * pck,uint8_t address,FUNCTION function,uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4);
//PCK_STATE Check_PCK(uint8_t * buff);
PCK_STATE GetNewData(uint8_t data,uint8_t id);
HAL_StatusTypeDef Send_PCK(uint8_t address,FUNCTION function,uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,int timeout);
uint8_t Send_Audio(uint8_t address,uint8_t * audio,int audio_size,int timeout);