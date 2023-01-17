#ifndef _DMATEST_H
#define _DMATEST_H
#include "adctest.h"

#include "stm32f10x.h"

void init_dma(__IO uint32_t * PeripheralBaseAddr,uint16_t * MemoryBaseAddr,uint16_t size);
#endif
