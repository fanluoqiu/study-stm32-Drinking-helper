#ifndef BUZZER_H
#define BUZZER_H



#include "stm32f10x.h"


typedef enum {OPEN_BUZZER=1,CLOSE_BUZZER=!OPEN_BUZZER} BUZZERSTATE;


void Buzzer_conf(void);
void Buzzer_cmd(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,BUZZERSTATE state);
void Buzzer_playtone(const uint32_t frq,const uint16_t duty);
void Buzzer_playmusic(void);
void bootPOST(void);
#endif
