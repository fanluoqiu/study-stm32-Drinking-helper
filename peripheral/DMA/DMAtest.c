#include "DMAtest.h"


uint16_t dma_size;


//初始化DMA
void init_dma(__IO uint32_t * PeripheralBaseAddr,uint16_t * MemoryBaseAddr,uint16_t size)
{
    dma_size=size;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_BufferSize=size;
    DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)MemoryBaseAddr;
    DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;
    DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)PeripheralBaseAddr;
    DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority=DMA_Priority_VeryHigh;
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);
    
    DMA_Cmd(DMA1_Channel1,ENABLE);
}
