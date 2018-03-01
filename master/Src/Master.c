#include "Master.h"

//variables
PCK_CONV Send_pck;
PCK_CONV User_state[USER_NUMBER];
PCK_CONV Req_pck;
uint8_t PCK_RCV;
MASTER_HANDLER master;

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

PCK_STATE GetNewData(uint8_t data,uint8_t id){
	
	switch(PCK_RCV)
	{
	
	case 0:
		if (data == START_BYTE0)
		{
			PCK_RCV++;
			User_state[id].ASS_PCK[PCK_RCV]=data;
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
			User_state[id].ASS_PCK[PCK_RCV]=data;
		}
		else
		{
			PCK_RCV = 0;
			return PCK_Unknown;
		}
		break;
	
	case 2:
		User_state[id].ASS_PCK[PCK_RCV] = data;
		User_state[id].DIST_PCK.cksum = data;
		PCK_RCV++;
		break;
	
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		User_state[id].ASS_PCK[PCK_RCV] = data;
		User_state[id].DIST_PCK.cksum+= data;
		PCK_RCV++;
		break;
		
	case 8:
		if((User_state[id].DIST_PCK.cksum-data) == 0) PCK_RCV++;
		else {
			PCK_RCV = 0;
			return PCK_Unknown;
		}
		break;
	
	case 9:
		PCK_RCV=0;
		if (data == STOP_BYTE && User_state[id].DIST_PCK.addr == id){
			User_state[id].DIST_PCK.timeout=0;
			if(User_state[id].DIST_PCK.func==Normal_conv)return PCK_Data;
			if(User_state[id].DIST_PCK.func==Speak_req)return PCK_DATA_PLUS_SPEAK_REQ;
			if(User_state[id].DIST_PCK.func==end_speak)return PCK_END_SPEAK;
		}
		return PCK_Unknown;
	}
	return PCK_Wait;
}

HAL_StatusTypeDef Send_PCK(uint8_t address,FUNCTION function,uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t * buffer){
	Init_PCK(&Send_pck,address,function,data1,data2,data3,data4);
		
	Enable_RS485_Line;
	
	HAL_UART_Abort(&huart2);
	uint8_t out= HAL_UART_Transmit_DMA(&huart2,Send_pck.ASS_PCK,Packet_Length);
	HAL_UART_Receive_DMA(&huart2,buffer,Packet_Length);
	
	TimeOut_Timer.Instance->CNT=0;
	HAL_TIM_Base_Stop_IT(&TimeOut_Timer);
	HAL_TIM_Base_Start_IT(&TimeOut_Timer);
	
	return out;
}

uint8_t Send_Audio(uint8_t address,uint8_t * audio_send,uint8_t * audio_receive,int audio_size){
	Init_PCK(&Send_pck,address,Speak_req,0,0,0,0);
		
	Enable_RS485_Line;
	uint8_t out1= HAL_UART_Transmit(&huart2,Send_pck.ASS_PCK,Packet_Length,1);

	HAL_UART_Abort(&huart2);
	uint8_t out2= HAL_UART_Transmit_DMA(&huart2,audio_send,audio_size);
	HAL_UART_Receive_DMA(&huart2,audio_receive,audio_size);
	
	Increase_Buffer_Pointer(& (master.tx_p));
	Increase_Buffer_Pointer(& (master.rx_p));
	
	return ((out1<<1)+out2);
}

void Master_Init(void){
	master.state=WAITING;
	master.hello_id=0;
	master.call_id=0;
	master.call_flag=FLAG_DISABLE;
	master.hello_counter=0;
	master.audio_adc_cplt_flag=FLAG_DISABLE;
	master.audio_uart_cplt_flag=FLAG_DISABLE;
	master.save_2_SD_flag=FLAG_DISABLE;
	master.save_2_SD_enable_flag=FLAG_DISABLE;
	master.refresh_LCD_flag=FLAG_DISABLE;
	//master.update_keypad_flag=FLAG_DISABLE;
	master.rx_p=0;
	master.adc_p=0;
	master.tx_p=0;
	master.rec_rx_p=0;
	master.rec_adc_p=0;
	master.start_of_call_flag=FLAG_DISABLE;

	HAL_TIM_Base_Stop(&htim8);
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_1);
	
	PCK_RCV=0;
}

void Make_Call(uint8_t add,uint16_t * ADC_Buff,uint16_t min,uint16_t hour, uint16_t day,uint16_t month){
	master.rx_p=0;
	master.adc_p=0;
	master.tx_p=0;
	master.rec_rx_p=0;
	master.rec_adc_p=0;
	master.audio_adc_cplt_flag=FLAG_DISABLE;
	master.audio_uart_cplt_flag=FLAG_DISABLE;
	master.save_2_SD_flag=FLAG_DISABLE;
	//master.save_2_SD_enable_flag=FLAG_ENABLE;
	master.save_2_SD_enable_flag=FLAG_DISABLE;
	master.call_id=add;
	master.call_flag=FLAG_ENABLE;
	master.start_of_call_flag=FLAG_ENABLE;
	
	master.temp= Start_Recording(min,hour,day,month);
	//if(master.temp!=0)master.save_2_SD_enable_flag=FLAG_DISABLE;
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
	
	HAL_TIM_Base_Start(&htim8);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Buff,Date_Per_100ms);
//	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(uint32_t *)UART_Buff,Date_Per_100ms*audio_buffer_size,DAC_ALIGN_8B_R);
}

void Append_Record(char* buffer){
	int cc;
	
	f_lseek(&audio_file.fil,f_size(&audio_file.fil));
	f_write(&audio_file.fil,(uint8_t *)buffer,Date_Per_100ms,(unsigned int *)&cc);
	
	audio_file.counter++;
	Increase_Buffer_Pointer(&(audio_file.buffer_counter));
}

void End_Call(void){
	int cc;
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
	
	HAL_TIM_Base_Stop(&htim8);
	HAL_ADC_Stop_DMA(&hadc1);
	HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_1);
	
	f_close(&audio_file.fil);
	f_mount(&audio_file.fs,"",1);
						
	f_open(&audio_file.fil,audio_file.path,FA_WRITE | FA_OPEN_ALWAYS);
	WavaRecorderHeaderInit((uint8_t *)SD_buff,audio_file.counter*Date_Per_100ms);
	f_write(&audio_file.fil,(uint8_t *)SD_buff,44,(unsigned int *)&cc);
	f_close(&audio_file.fil);
	
	master.rx_p=0;
	master.adc_p=0;
	master.tx_p=0;
	master.rec_rx_p=0;
	master.rec_adc_p=0;
	master.audio_adc_cplt_flag=FLAG_DISABLE;
	master.audio_uart_cplt_flag=FLAG_DISABLE;
	master.save_2_SD_flag=FLAG_DISABLE;
	//master.save_2_SD_enable_flag=FLAG_ENABLE;
	master.save_2_SD_enable_flag=FLAG_DISABLE;
	master.call_id=0;
	master.call_flag=FLAG_DISABLE;
	master.start_of_call_flag=FLAG_DISABLE;
	
}

void Increase_Buffer_Pointer(int * p){
	(*p)++;
	if((*p)==audio_buffer_size)(*p)=0;
}

