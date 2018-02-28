#include "Slave.h"

//variables
PCK_CONV Send_pck;
PCK_CONV Received_pck;
PCK_CONV Req_pck;
uint8_t PCK_RCV;
SLAVE_HANDLER slave;

// functions
void Init_PCK(PCK_CONV * pck,uint8_t address,FUNCTION function,uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4){
	pck->DIST_PCK.ST0=START_BYTE0;
	pck->DIST_PCK.ST1=START_BYTE1;
	pck->DIST_PCK.func=function;
	pck->DIST_PCK.addr=address;
	pck->DIST_PCK.data1=data1;
	pck->DIST_PCK.data2=data2;
	pck->DIST_PCK.data3=data3;
	pck->DIST_PCK.data4=data4;
	
	int a=function+address+data1+data2+data3+data4;
	
	pck->DIST_PCK.cksum=a%256;
	pck->DIST_PCK.stp=STOP_BYTE;
}

PCK_STATE GetNewData(uint8_t data){
	
	switch(PCK_RCV)
	{
	
	case 0:
		if (data == START_BYTE0)
		{
			PCK_RCV++;
			Received_pck.ASS_PCK[PCK_RCV]=data;
		}
		else {
			PCK_RCV=0;
			return PCK_Unknown;
		}
		break;
	
	case 1:
		if (data == START_BYTE1)
		{
			PCK_RCV++;
			Received_pck.ASS_PCK[PCK_RCV]=data;
		}
		else
		{
			PCK_RCV = 0;
			return PCK_Unknown;
		}
		break;
	
	case 2:
		Received_pck.ASS_PCK[PCK_RCV] = data;
		Received_pck.DIST_PCK.cksum = data;
		PCK_RCV++;
		break;
	
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		Received_pck.ASS_PCK[PCK_RCV] = data;
		Received_pck.DIST_PCK.cksum+= data;
		PCK_RCV++;
		break;
		
	case 8:
		if((Received_pck.DIST_PCK.cksum-data) == 0) PCK_RCV++;
		else {
			PCK_RCV = 0;
			return PCK_Unknown;
		}
		break;
	
	case 9:
		PCK_RCV=0;
		if (data == STOP_BYTE) return Check_PCK(Received_pck.ASS_PCK);
		return PCK_Unknown;
	}
	return PCK_WAIT;
}

PCK_STATE Check_PCK(uint8_t * buff){
	
	if(buff[2]==slave.id){
		if(buff[3]==Normal_conv) return PCK_With_Me;
		else if(buff[3]==Speak_req)return PCK_REQ_SP_ME;
		else if(buff[3]==end_speak)return PCK_END_SP;
	}
	else return PCK_Without_Me;
	
	return PCK_Unknown;
}

HAL_StatusTypeDef Send_PCK(FUNCTION function,uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4){//,int timeout){
	Init_PCK(&Send_pck,slave.id,function,data1,data2,data3,data4);
		
	HAL_GPIO_WritePin(RS485_GPIO_PORT,RS485_GPIO_PIN,GPIO_PIN_SET);
	uint8_t out= HAL_UART_Transmit_DMA(&Slave_Uart,Send_pck.ASS_PCK,Packet_Length);

	return out;
}

uint8_t Send_Audio(uint8_t * audio,int audio_size){//,int timeout){
	
	HAL_GPIO_WritePin(RS485_GPIO_PORT,RS485_GPIO_PIN,GPIO_PIN_SET);
	uint8_t out= HAL_UART_Transmit_DMA(&Slave_Uart,audio,audio_size);

	return out;
}

void Set_Address(uint8_t add){
	slave.id=add;
}

void Slave_Init(uint8_t add){
	slave.id=add;
	slave.state=WAITING_PCK;
	Init_PCK(&slave.pck,add,Normal_conv,0,0,0,0);
	PCK_RCV=0;
	
	slave.rx_p=0;
	slave.adc_p=0;
	slave.tx_p=0;
	slave.call_flag=FLAG_DISABLE;
}

void Make_Call(uint16_t * ADC_Buffer,uint8_t * UART_Buffer){
	slave.rx_p=0;
	slave.adc_p=0;
	slave.tx_p=0;
	
	slave.call_flag=FLAG_ENABLE;
	
	HAL_TIM_Base_Start(&htim8);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Buffer,Date_Per_100ms);
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(uint32_t *)UART_Buffer,Date_Per_100ms*audio_buffer_size,DAC_ALIGN_8B_R);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
}

void End_Call(){
	slave.call_flag=FLAG_DISABLE;
	
	HAL_TIM_Base_Stop(&htim8);
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_2);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
}

void Increase_Buffer_Pointer(uint8_t * p){
	(*p)++;
	if((*p)==audio_buffer_size)(*p)=0;
}
