/*
 * trasmitter.c
 *
 * Created: 2017/04/12 11:08:05 ق.ظ
 *  Author: Milad
 */ 

#include "trasmitter.h"
//#include "initialize.h"
uint8_t PCK_RCV = 0, PCK_Size = 0, PCK_SND = 0;
uint16_t PCK_TIMEOUT=0;
uint8_t data_write_index=0,data_read_index=0,Packet_Next_Start=0;
uint16_t PCK_Speed,PCK_Reset=0;
uint8_t Circular_Buffer[Buffer_Size];

uint8_t newPck_R=0,newPck_S=0;


PCK pck_r_tmp,pck_t,pck_t_tmp,pck_r;

void GetNewData(uint8_t data)
{
	switch(PCK_RCV)
	{
	case 0:
		if (data == START_BYTE0)
		{
			PCK_RCV++;
		}
		break;
	case 1:
		if (data == START_BYTE1)
		{
			PCK_RCV++;
		}
		else
		{
			PCK_RCV = 0;
		}
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
//	case 8:
//	case 9:
//	case 10:
//	case 11:
//	case 12:
//	case 13:
//	case 14:
//	case 15:
//	case 16:
//	case 17:
//	case 18:
//	case 19:
//	case 20:
//	case 21:
		pck_r_tmp.pck[PCK_RCV] = data;
		pck_r_tmp.CTRL.cksum += data;
		PCK_RCV++;
		break;
		
	case 8:
		pck_r_tmp.CTRL.cksum -= data;
		PCK_RCV++;
		break;
	case 9:
		if (data == STOP_BYTE)// && pck_r_tmp.Data.chksum == 0)
		{
			pck_r = pck_r_tmp;
			//BUZ_PORT.OUTTGL=BUZ_PIN_bm;
			newPck_R = 1;
		}
		PCK_RCV=0;
		break;
	}
}

