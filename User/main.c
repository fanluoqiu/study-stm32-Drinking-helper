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
#include "sensor.h"
#include "buzzer.h"

u8 * title;
int main(void)
{
	delay_init();
	Buzzer_delayplayconf(0,3);
	Buzzer_conf();
	OLEDintset();	
	init_adc();
	bootPOST();
	delay_ms(2000);
	while (1)
	{
		if(datacapt[PERIPHNUMB-1]>800)   //判断物体是否放置
		{
			title="ADC&&DMA#TEST";
		}
		else if(datacapt[PERIPHNUMB-1]<400)
		{
			Buzzer_delayplaycmd(OPEN_BUZZER);//开始计时
			OLED_Clearrow(2);
		}
		else
			;
		OLEDmaininterf(title);	
	}
}

void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET&&delaytime!=0)
		delaytime--;
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
}
