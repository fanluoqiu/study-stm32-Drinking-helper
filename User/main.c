/***
* ADC+DMA(连续扫描，循环模式)
*
* ********oled********
* SCL:PIN_B8
* SDA:PNIN_B9
* ********oled********
*
* ********sensor********
* 红外传感器1：PIN_A4
* 红外传感器2：PIN_A5
* 超声波模块：PIN_A6
* 无源蜂鸣器模块：PIN_A2
* ********sensor********
*
*
*********TIM********
*	none
*********TIM********
*/
#include "stm32f10x.h"
#include "delay.h"
#include "Oledprint.h"
#include "adctest.h"
#include "buzzer.h"

int main(void)
{
	delay_init();
	Buzzer_conf();
	OLEDintset();	
	init_adc();
	bootPOST();
	delay_ms(2000);
	while (1)
	{
		if(datacapt[PERIPHNUMB-1]>900)   //判断物体是否放置
		{
			OLEDmaininterf();
			print_p(42,20,(uint32_t)&ADC1->DR);
			OLED_ShowNum(48,30,ADC1->DR,5,8,1);
			print_p(42,40,(uint32_t)&datacapt);
			OLED_ShowNum(30,50,datacapt[0],5,8,1);
			OLED_ShowNum(62,50,datacapt[1],5,8,1);
			OLED_ShowNum(94,50,datacapt[2],5,8,1);
			OLED_Refresh();
			delay_ms(20);
		}
		else if(datacapt[PERIPHNUMB-1]<500)
		{
			OLED_Clear();
			OLED_ShowString(0,30,"please drink water:)",8,0);
			OLED_Refresh();
			Buzzer_playmusic();
		}
		else
		;
	}
}
