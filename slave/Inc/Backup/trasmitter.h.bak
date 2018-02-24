/*
 * trasmitter.h
 *
 * Created: 2017/04/12 11:08:20 ق.ظ
 *  Author: Milad
 */ 


#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

//#include <asf.h>

#include "stm32f1xx_hal.h"

#define Max_Packet_Lenght 10
#define START_BYTE0 0xA5
#define START_BYTE1 0x5A
#define STOP_BYTE 0x80
#define Buffer_Size Max_Packet_Lenght
///////////////////////mode
#define MODE_ON (1<<0)
#define MODE_INIT (1<<1)
#define MODE_OFF (1<<2)
#define MODE_FAN (1<<3)
////////////////////////////
///////////////////////ctrl
#define CTRL_RESET (1<<0)
#define CTRL_LOCK_PANEL (1<<1)
#define CTRL_LOCK_DEVICE_TIME (1<<2)
#define CTRL_LOCK_DEVICE_BAT (1<<3)
////////////////////////////

//////////////////////////////////////////////////////////////////////////UI
//#define UI_IDLE 0
#define UI_TIME 0
#define UI_LAST_T 1
#define UI_TOTAL_M 3
#define UI_TOTAL_H 2
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////REQUEST
#define REQ_UI (1<<0)
#define REQ_TIME (1<<1)
#define REQ_MODE (1<<2)
#define REQ_UNLOCK_DEVICE_TMP (1<<3)
#define REQ_UNLOCK_DEVICE_MAIN (1<<4)
#define REQ_VIB (1<<5)
#define REQ_SPD (1<<6)


///////////////////////SPEED
#define FAN1 (1<<0)
#define FAN2 (1<<1)
#define VIB  (1<<2)

#define SPEED1 255
////////////////////////////
//////////////////////time
#define TIME1 8*60
#define TIME2 10*60
#define TIME3 12*60
//////////////////////////

#define PACKET(_A_,_B_) (newPck_S)?(_B_|_A_):_B_

typedef union PCK_c
{
  struct Data_c
  {
    uint8_t st0;
    uint8_t st1;
	
    uint8_t address; //ADDRESS
	//	uint8_t data_type; //CTRL OR DATA FOR VOICE
    uint8_t function; //ERROR or FUNCTION TABLE
	uint8_t data1;
	uint8_t data2;
	uint8_t data3;
	uint8_t data4;
	uint8_t cksum;
	uint8_t stp;
		//uint8_t OTHER[Max_Packet_Lenght-10];
	
  }CTRL;
//	struct Data_v
//  {
//    uint8_t st0;
//    uint8_t st1;
//	
//    uint8_t address; //ADDRESS
//		uint8_t data_type; //CTRL OR DATA FOR VOICE
//		uint8_t tmp1; //ERROR or FUNCTION TABLE
//		uint8_t tmp2;
//		uint16_t cksumcrc;
//		uint16_t tmp3;
//		uint8_t dataV[Max_Packet_Lenght-12];
//		uint16_t stp;
//	
//  }VOICE;
//  
  uint8_t pck[Max_Packet_Lenght];//max 1000BYTEs
}PCK;
extern PCK pck_r_tmp,pck_t,pck_t_tmp,pck_r;
extern uint8_t PCK_RCV, PCK_Size, PCK_SND;
extern uint16_t PCK_TIMEOUT;
extern uint8_t data_write_index,data_read_index,Packet_Next_Start;
extern uint16_t PCK_Speed,PCK_Reset;
extern uint8_t Circular_Buffer[Buffer_Size];

extern  uint8_t newPck_R,newPck_S;
void GetNewData(uint8_t data);

// ADDRESS: 0-> broadcast 1->250 SLAVE ADDRESS
// FUNCTION: MASTER: 
#endif /* TRANSMITTER_H_ */
