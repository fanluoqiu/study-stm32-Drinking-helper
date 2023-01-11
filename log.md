

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
