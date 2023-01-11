#ifndef _ADCTEST_H
#define _ADCTEST_H
#include "stm32f10x.h"
#include "DMAtest.h"
void init_adc(void);
#define PERIPHNUMB 3

extern uint16_t  datacapt[PERIPHNUMB];
#endif

