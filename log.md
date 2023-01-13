

###2023.1.11 19：30
- 上传了源文件
- 未解决蜂鸣器的问题
    ```c
    //#####BUG1
    //此处加上delay函数后，蜂鸣器无法关闭
    //TIM_cmd无法失能

    //	for(int i=0;i<3;i++)
    //	{
		Buzzer_cmd(200-1,180-1,ENABLE);
		delay_ms(1000);
		TIM_Cmd(TIM2,DISABLE);
    //	}
	    OLEDintset();	
	    init_adc();
    ```
2023.1.12 16：48
- 解决了蜂鸣器问题
- 取消了pwm模式输出方波，改用delay()通过推完输出模式驱动蜂鸣器
- 实现了音乐播放功能

2023.1.13 12:46
- 实现了物件摆放时蜂鸣器播放，物件撤离时停止
- 未完成延时播放功能
```c
//buzzer.c
void Buzzer_delayplay(uint8_t hour,uint8_t min)
{
    
}
````