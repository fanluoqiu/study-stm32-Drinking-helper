
#include "buzzer.h"
#include "delay.h"
#include "stm32f10x.h"
#include "musicdata.h"
#include "sensor.h"
#include "oled.h"

 
uint32_t delaytime;

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

//此处通过推挽输出模式输出PWM波形
//frq:输入的频率
//duty:占空比
void Buzzer_pwm(const uint32_t frq,const uint16_t duty)
{
    uint32_t time;
    if(frq==1000)
        delay_us(1000);    
    else
    {
        time=10000/(uint32_t)frq;
        GPIO_SetBits(GPIOA,GPIO_Pin_2);
        delay_us(time*duty);
        GPIO_ResetBits(GPIOA,GPIO_Pin_2);
        delay_us(time*(100-duty));
    }
}

uint8_t Buzzer_playmusic(void)
{
	for(uint16_t i=0;i<sizeof(music)/sizeof(music[0]);i++)
    {
		for(uint16_t e=0;e<((u16)time[i])*tone[music[i]]/6;e++)
        {
			Buzzer_pwm((u32)tone[music[i]],1);
            if(datacapt[PERIPHNUMB-1]>900)             //如果物体被拿开则停止播放
            {
                GPIO_ResetBits(GPIOA,GPIO_Pin_2);
                return 1;
            }
        }
    }
    return 0;
}

void bootPOST(void)
{

    for(int i=0;i<2;i++)
    {
        for(int i=1;i<35;i++)
        {
            Buzzer_pwm(700,2);
        }
        delay_ms(100);
    }
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}


void Buzzer_delayplayconf(uint8_t hour,uint8_t min)
{
    delaytime=hour*60+min;
    //使用TIM1定时
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

    //72Mhz/7200/50000=0.2,T=1/0.2=5s,5x12=1min
    TIM_InternalClockConfig(TIM1);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period=50000-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;          
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter=12;
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
    TIM_ClearFlag(TIM1,TIM_IT_Update);
    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel=TIM1_UP_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM1,DISABLE);
}

void Buzzer_delayplaycmd(BUZZERSTATE state)
{
    if(state==OPEN_BUZZER)
        TIM_Cmd(TIM1,ENABLE);
    else 
        TIM_Cmd(TIM1,DISABLE);
}


void Buzzer_getdelaytime(void)
{
    if(delaytime==0)
    {
        OLED_Clear();
        OLED_ShowString(0,30,"please drink water:)",8,0);
        OLED_Refresh();
    }
    else if(Buzzer_playmusic()==1)   //播放被中断
    {
        Buzzer_delayplaycmd(CLOSE_BUZZER);
        once=1;
        OLED_Clear();				
    }
    else
        ;
}
