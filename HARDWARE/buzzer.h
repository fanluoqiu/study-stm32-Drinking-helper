#ifndef BUZZER_H
#define BUZZER_H



#include "stm32f10x.h"


void Buzzer_conf(void);
void Buzzer_cmd(uint16_t TIM_Period,uint16_t TIM_Prescaler,FunctionalState  buzzerstate);
void bootPOST(void);
#endif
