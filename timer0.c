#include <STC15F2K60S2.H>

int count_timer0=0;
bit flag_10s=0;

void Timer0Init(void)		//50毫秒@11.0592MHz
{
	ET0 = 1;		 //定时器0中断开
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x4C;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void timer0() interrupt 1
{
	count_timer0++;
	if(count_timer0>=200)
	{
		flag_10s=1;
		count_timer0=0;	
	}
	else
		flag_10s=0;		
}

