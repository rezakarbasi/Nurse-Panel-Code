//includes
#include "stm32f1xx_hal.h"
#include "usart.h"

//defines

#define Packet_Length 10
#define START_BYTE0 0xA5
#define START_BYTE1 0x5A
#define START_BYTE2 0x00
#define START_BYTE3 0xFF
#define STOP_BYTE 0x80
#define Buffer_Size Packet_Length

#define Date_Per_100ms		800

// specific for this slave
#define Slave_Uart			huart1
#define Timeout_Timer		htim2
#define RS485_GPIO_PORT	GPIOA
#define RS485_GPIO_PIN	GPIO_PIN_11


//Types

// state of packet enumeration
typedef enum{
	WAITING_PCK,
	SENDING_HELLO,
	SENDING_AUDIO,
	GETTING_AUDIO,
}SLAVE_PROGRAM_STATE;

typedef enum {
	PCK_WAIT=0,
	PCK_Unknown =1,
	PCK_Without_Me=2 ,
	PCK_With_Me=3 ,
	PCK_REQ_ME=4
}PCK_STATE;

typedef enum{
	Normal_conv,
	Speak_req
}FUNCTION;

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
  }DIST_PCK;															// Distributed packet
	
  uint8_t ASS_PCK[Packet_Length];					// Associated  packet
}PCK_CONV;

typedef struct{
	PCK_CONV pck;
	uint8_t id;
	SLAVE_PROGRAM_STATE state;
}SLAVE_HANDLER;

// Variables
extern SLAVE_HANDLER slave;
extern PCK_CONV Send_pck;
extern PCK_CONV Received_pck;
extern PCK_CONV Req_pck;
extern uint8_t PCK_RCV;

// Functions
void Init_PCK(PCK_CONV * pck,uint8_t address,FUNCTION function,uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4);
PCK_STATE Check_PCK(uint8_t * buff);
PCK_STATE GetNewData(uint8_t data);
HAL_StatusTypeDef Send_PCK(FUNCTION function,uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4);
uint8_t Send_Audio(uint8_t * audio,int audio_size);
void Set_Address(uint8_t add);
void Slave_Init(uint8_t add);