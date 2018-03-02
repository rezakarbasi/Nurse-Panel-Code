
#include "LCD.h"

void LCD_Init(){
	ILI9341_Init();//initial driver setup to drive ili9341
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	ILI9341_Fill_Screen(WHITE);
	ILI9341_Set_Rotation(SCREEN_HORIZONTAL_1);
}