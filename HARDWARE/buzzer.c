#include "buzzer.h"
#include "delay.h"

uint16_t Period=0,Prescaler=0;

void Buzzer_conf(void)
{

    //配置GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //使用TIM2输出PWM

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV4;    //18Mhz
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period=Period;
    TIM_TimeBaseInitStructure.TIM_Prescaler=Prescaler;               //18M/1800
    //TIM_TimeBaseInitStructure.TIM_RepetitionCounter=;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse=10;
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OC3Init(TIM2,&TIM_OCInitStructure);

    TIM_Cmd(TIM2,DISABLE);
}

void Buzzer_cmd(uint16_t TIM_Period,uint16_t TIM_Prescaler,FunctionalState  buzzerstate)
{
    Period=TIM_Period;
    Prescaler=TIM_Prescaler; 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_Period=Period;
    TIM_TimeBaseInitStructure.TIM_Prescaler=Prescaler;  
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    TIM_Cmd(TIM2,buzzerstate);
}


void bootPOST(void)
{
    for(int i=0;i<3;i++)
	{
		Buzzer_cmd(200-1,180-1,ENABLE);
		delay_ms(50);
		TIM_Cmd(TIM2,DISABLE);
		delay_ms(50);
	}
}
