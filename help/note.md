#喝水提醒助手
## 0 引言
最近看江科大的stm32教程，学到了DMA，想把之前学过的东西整合起来，恰好我经常忘记喝水，那就做个提醒喝水小助手把。

## 1 系统分析
###1.1 场景模拟
场景模拟比较简单，当检测到物体时，启动定时器开始计时，并在屏幕上显示倒计时时间，倒计时结束时，蜂鸣器播放音乐，直到物体被拿开。

<div align=center><img src="%E6%9C%AA%E5%91%BD%E5%90%8D%E7%BB%98%E5%9B%BE.png"></div>

### 1.2 硬件准备
检测物体是否存在原则上用压敏电阻最为合适，但是手头恰好有超声波模块，于是用超声波AD引脚采集传感器距离。
<div align=center><img src="IMG_20230119_151631_edit_18052021559743.jpg"，lenth=200></div>

<center> US-016超声波传感器模块</center>

</p>

>由于要做DMA+ADC的实验，所以额外加了两个其他传感器，采集数据并与超声波模块的采集数据一起打印到屏幕上。

### 1.3 代码实现

首先，显示界面有三个状态。通过switch选择各个界面。
```c
//主界面模式获取
tp_maininterfmode MainInterfMode(void)
{
	tp_maininterfmode mode;
	if(datacapt[PERIPHNUMB-1]>800)	mode=normal;  //默认模式
	else if(datacapt[PERIPHNUMB-1]<400)	
	{
		mode=Timekeeping;                          //计时模式
		if(delaytime==0)	mode=Timeout;          //提醒喝水模式
	}
	return mode;
}
````


<center >
<img src="IMG_20230119_162845.jpg" width=250/>
<img src="IMG_20230119_162926.jpg" width=250/>
<img src="IMG_20230119_163016.jpg" width=250/>
</center>

>默认模式（左），计时模式（中），提醒喝水模式（右）。

</p>
</p>
各模式的具体操作如下
```c
switch (MainInterfMode())
		{
			case normal:
				OLED_Clearrow(2);   //清空黄屏
				title="ADC&&DMA#TEST";  //修改标题
				resettime();    //重置倒计时到设定的时间
				once=1;
				Buzzer_delayplaycmd(CLOSE_BUZZER);  //关闭蜂鸣器
				break;
			case Timekeeping:
				if(once)    //若没有回到默认模式（normal）,则重置一次时间
				{
					resettime();
					once=!once;
				}
				title="En_TIM:";
				Buzzer_delayplaycmd(OPEN_BUZZER);    //开始计时
				OLED_Clearrow(2);
				OLED_Showtime(60,0,time_h_m_s());   //显示时间
				break;
			case Timeout:   //时间到，打印提醒界面并启动蜂鸣器
				OLED_Clear();
				OLED_ShowString(0,30,"please drink water:)",8,0);
				OLED_Refresh();
				Buzzer_playmusic();
				break;
			default:
				break;
		}
		OLEDmaininterf(title);  //将修改的标题传给界面答应函数
````

其中`time_h_m_s()`将当前倒计时（单位秒）转换为`tp_time`结构体并返回该类型的结构体。通过`OLED_Showtime()`函数在屏幕上输出`xx:xx:xx`格式的当前倒计时。

```c
typedef struct 
{
    u8 hour;
    u8 min;
    u8 sec;
} tp_time;

//倒计时初始值的定义
tp_time init_delaytime={.hour=0,.min=0,.sec=10};
//当前倒计时的定义
uint64_t delaytime;
````

