
/* 
pinset:
SCL:	PB8
SDA:	PB9
 */

#include "oledprint.h"
#include "delay.h"
//开机界面
//x,y：起点坐标
//sizex,sizey：图片长宽
//BMP[]：要写入的图片数组
//mode：0，反色显示，1正常显示
void OLEDloding(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode,uint64_t delayms)
{
	delay_init();
	OLED_Init();
	OLED_ColorTurn(0);
	OLED_DisplayTurn(0);
	

	OLED_Clear();
	OLED_ShowPicture(x,y,sizex,sizey,BMP,mode);  
	OLED_Refresh();	delay_ms(delayms);
	OLED_Clear();
}

//str：字符串
//mode：0，反色显示，1正常显示
void toptitle(u8 str[],u8 mode)
{
	
	OLED_ShowString(0,0,str,16,mode);
}



void print_p(u8 x,u8 y, uint32_t  addr)
{
	OLED_ShowHEXNum(x,y,addr,8,8,1);
	OLED_Refresh();
}



void OLEDmaininterf(u8 * title)
{
	toptitle(title,0);
	OLED_ShowString(0,20,"adsdSrc:",8,1);	
	OLED_ShowString(0,30,"DRvalue:",8,1);		
	OLED_ShowString(0,40,"addMem:",8,1);	
	OLED_ShowString(0,50,"capt:",8,1);

	print_p(42,20,(uint32_t)&ADC1->DR);
	OLED_ShowNum(48,30,ADC1->DR,5,8,1);
	print_p(42,40,(uint32_t)&datacapt);
	OLED_ShowNum(30,50,datacapt[0],5,8,1);
	OLED_ShowNum(62,50,datacapt[1],5,8,1);
	OLED_ShowNum(94,50,datacapt[2],5,8,1);
	OLED_Refresh();
//	delay_ms(20);
}


//打印开机界面和主界面
void  OLEDintset(void)
{
	OLEDloding(0,0,128,64,BMP1,1,500);
	OLEDmaininterf("ADC&&DMA#TEST");
}




