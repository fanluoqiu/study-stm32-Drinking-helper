/***
* ADC+DMA(连续扫描，循环模式)&&定时喝水提醒
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
#include "main.h"

u8 * title;
tp_maininterfmode mode;
tp_time init_delaytime={.hour=0,.min=0,.sec=10};
int main(void)
{
	delay_init();
	Buzzer_delayplayconf();
	Buzzer_conf();
	OLEDintset();	
	init_adc();
	bootPOST();
	delay_ms(2000);
	_Bool once=1;
	while (1)
	{
		
		switch (MainInterfMode())
		{
			case normal:
				OLED_Clearrow(2);
				title="ADC&&DMA#TEST";
				resettime();
				once=1;
				Buzzer_delayplaycmd(CLOSE_BUZZER);
				break;
			case Timekeeping:
				if(once)
				{
					resettime();
					once=!once;
				}
				title="En_TIM:";
				Buzzer_delayplaycmd(OPEN_BUZZER);    //开始计时
				OLED_Clearrow(2);
				OLED_Showtime(60,0,time_h_m_s());
				break;
			case Timeout:
				OLED_Clear();
				OLED_ShowString(0,30,"please drink water:)",8,0);
				OLED_Refresh();
				Buzzer_playmusic();
				break;
			default:
				break;
		}
		OLEDmaininterf(title);
	}
}

void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET&&delaytime!=0)
		delaytime--;
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
}


tp_maininterfmode MainInterfMode(void)
{
	tp_maininterfmode mode;
	if(datacapt[PERIPHNUMB-1]>800)	mode=normal;
	else if(datacapt[PERIPHNUMB-1]<400)	
	{
		mode=Timekeeping;
		if(delaytime==0)	mode=Timeout;
	}
	return mode;
}


void resettime(void)
{
	delaytime=init_delaytime.hour*3600+init_delaytime.min*60+init_delaytime.sec;
}


tp_time time_h_m_s(void)
{
	uint64_t temp=delaytime;
	tp_time time;

	time.hour=temp/3600;			//提取小时
	temp=temp%3600;

	time.min=temp/60;				//提取分钟
	temp=temp%60;

	time.sec=temp;					//提取秒
	return time;
}

