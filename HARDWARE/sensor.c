#include "sensor.h"

uint16_t  datacapt[PERIPHNUMB];
uint16_t dma_size;
//配置GPIO
void GPIO_conf(void)
{   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

//配置ADC
void ADC_conf(void)
{
    //配置ADC转换时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    //配置转换序列
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  
    ADC_RegularChannelConfig(ADC1,ADC_Channel_4,1,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_5,2,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_6,3,ADC_SampleTime_55Cycles5);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;
    ADC_InitStructure.ADC_ScanConvMode=ENABLE;
    ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
    ADC_InitStructure.ADC_NbrOfChannel=PERIPHNUMB;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1,ENABLE);    //ADC转换使能

    //复位ADC校准寄存器。
    ADC_ResetCalibration(ADC1); //重置校准
    while(ADC_GetResetCalibrationStatus(ADC1)); //等待重置完成
    ADC_StartCalibration(ADC1);  //开始校准
    while(ADC_GetCalibrationStatus(ADC1));  //等待校准完成
    ADC_SoftwareStartConvCmd(ADC1,ENABLE); //开始转换
}

void init_adc(void)
{
    GPIO_conf();
    ADC_conf();
    
    //初始化DMA
    init_dma(&ADC1->DR,datacapt,PERIPHNUMB); 
    ADC_DMACmd(ADC1,ENABLE);//开始adc触发dma转运
}

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
