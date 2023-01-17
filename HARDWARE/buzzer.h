#ifndef BUZZER_H
#define BUZZER_H



#include "stm32f10x.h"


typedef enum {OPEN_BUZZER=1,CLOSE_BUZZER=!OPEN_BUZZER} BUZZERSTATE;

extern uint32_t delaytime;

//basic
void Buzzer_conf(void);

void Buzzer_pwm(const uint32_t frq,const uint16_t duty);



//function
void bootPOST(void);
uint8_t Buzzer_playmusic(void);
void Buzzer_delayplayconf(uint8_t hour,uint8_t min);
void Buzzer_delayplaycmd(BUZZERSTATE state);
#endif
