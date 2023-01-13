#include "buzzer.h"
#include "delay.h"
#include "stm32f10x.h"
#include "musicdata.h"
#include "adctest.h"
#include "oled.h"

void Buzzer_conf(void)
{

    //配置GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);

}

//frq:输入的频率
//duty:占空比，在此处是音量的大小(0~50)
void Buzzer_playtone(const uint32_t frq,const uint16_t duty)
{
    uint32_t time;
    if(frq==1000)
        delay_us(1000);    
    else
    {
        time=10000/(uint32_t)frq;
        Buzzer_pwm(GPIOA,GPIO_Pin_2,OPEN_BUZZER);
        delay_us(time*duty);
        Buzzer_pwm(GPIOA,GPIO_Pin_2,CLOSE_BUZZER);
        delay_us(time*(100-duty));
    }
}

void Buzzer_pwm(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,BUZZERSTATE state)
{
    if(state==OPEN_BUZZER)
        GPIO_SetBits(GPIOx,GPIO_Pin);
    else
        GPIO_ResetBits(GPIOx,GPIO_Pin);
}


uint8_t Buzzer_playmusic(void)
{
	for(uint16_t i=0;i<sizeof(music)/sizeof(music[0]);i++)
    {
		for(uint16_t e=0;e<((u16)time[i])*tone[music[i]]/6;e++)
        {
			Buzzer_playtone((u32)tone[music[i]],2);
            if(datacapt[PERIPHNUMB-1]>1000)             //如果物体被拿开则停止播放
            {
                GPIO_ResetBits(GPIOA,GPIO_Pin_2);
                OLED_Clear();
                return 1;
            }
        }
    }
    return 0;
}


void bootPOST(void)
{

    for(int i=0;i<3;i++)
    {
        for(int i=1;i<50;i++)
        {
            Buzzer_playtone(850,3);
        }
        delay_ms(100);
    }
    Buzzer_pwm(GPIOA,GPIO_Pin_2,CLOSE_BUZZER);
}
