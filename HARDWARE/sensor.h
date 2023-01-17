#ifndef SENSOR_H
#define SENSOR_H

#include "stm32f10x.h"

void init_dma(__IO uint32_t * PeripheralBaseAddr,uint16_t * MemoryBaseAddr,uint16_t size);
void init_adc(void);

#define PERIPHNUMB 3

extern uint16_t  datacapt[PERIPHNUMB];

#endif

