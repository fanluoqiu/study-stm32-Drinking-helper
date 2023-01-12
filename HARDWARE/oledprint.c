
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



void OLEDmaininterf(void)
{
	toptitle("ADC&&DMA#TEST",0);
	OLED_ShowString(0,20,"addSrc:",8,1);	
	OLED_ShowString(0,30,"DRvalue:",8,1);		
	OLED_ShowString(0,40,"addMem:",8,1);	
	OLED_ShowString(0,50,"capt:",8,1);
	OLED_Refresh();
}


//打印开机界面和主界面
void  OLEDintset(void)
{
	OLEDloding(0,0,128,64,BMP1,1,500);
	OLEDmaininterf();
}




