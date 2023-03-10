#ifndef BUZZER_H
#define BUZZER_H



#include "stm32f10x.h"
#include "main.h"

typedef enum {OPEN_BUZZER=1,CLOSE_BUZZER=!OPEN_BUZZER} BUZZERSTATE;

extern uint64_t delaytime;

//basic
void Buzzer_conf(void);

void Buzzer_pwm(const uint32_t frq,const uint16_t duty);



//function
void bootPOST(void);
uint8_t Buzzer_playmusic(void);
void Buzzer_delayplayconf(void);
void Buzzer_delayplaycmd(BUZZERSTATE state);
#endif
