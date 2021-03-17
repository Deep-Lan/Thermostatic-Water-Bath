#include <STC15F2K60S2.H>			 //此文件中定义了单片机的一些特殊功能寄存器
#include <string.h>
#include "DISPLAY.H"
#include "DATAPROS.H"
#include "ATCOMMOND.H"
#include "ADC.H"
#include "TIMER0.H"	

sbit switchH=P2^7;
sbit switchM=P2^6;
sbit switchL=P2^5;

void switch0(s,T)
{
			if(s>T)				//设定温度大于测定温度，低档开启
				switchL=1;
			else
				switchL=0;
			if(s>T+2)		 	//设定温度大于测定温度2℃，中档开启
				switchM=1;
			else
				switchM=0;
			if(s>T+5)			//设定温度大于测定温度5℃，高档开启
				switchH=1;
			else
				switchH=0;
}

void main()
{
	bit flag_power=0;
	bit flag_app=0;
	char *p;
	unsigned char i;
	double S_hua,s_hua,S_app,s_app,T;
	S_app=0.0;
	s_app=0.0;
	S_hua=0.0;
	s_hua=0.0;
	P2M1=0x00;
	P2M0=0xe0;   //P27、P26、P25配置为强推挽输出以驱动继电器，其他口为准双向弱上拉。
	UartInit();//串口初始化
	Timer0Init();//定时器0初始化
	ADCInit();	//ADC初始化
	CLD_START();//串口发送"AT+CLDSTART"			
	while(1)
	{					  
		p=strstr(rec,"+CRAW,");
		if(NULL!=p)
		{
			if((NULL!=strstr(rec,"on"))||(NULL!=strstr(rec,"off")))
			{
				if(NULL!=strstr(rec,"on"))
					flag_power=1;
				if(NULL!=strstr(rec,"off"))
					flag_power=0;	
			}
			else
			{
				if(*(p+6)=='3')			
					S_app=1.0*((*(p+8)-'0')*100+(*(p+9)-'0')*10+(*(p+10)-'0'));
				if(*(p+6)=='2')
					S_app=1.0*((*(p+8)-'0')*10+(*(p+9)-'0'));
				if(*(p+6)=='1')
					S_app=1.0*((*(p+8)-'0'));
			}	
			Rec_Rst();
		}
		if(flag_power)
		{
			S_hua=set();
			T=temperature();
			if(flag_10s)
				CLD_SEND_TEMP(T);	  //向手机APP发送当前温度值
			if(((S_hua-s_hua)>=2.0)||((s_hua-S_hua)>=2.0))
			{
				flag_app=0;
				s_hua=S_hua;									  
				digpros(s_hua);
				for(i=0;i<255;i++)
					DigDisplay();
			}
			else
			{
				if(S_app!=s_app)
				{
					flag_app=1;
					s_app=S_app;
					digpros(s_app);
					for(i=0;i<255;i++)
						DigDisplay();
				}
				else
				{
					if(flag_app)
						switch0(s_app,T);
					else
						switch0(s_hua,T);
					digpros(T);	 //数据处理函数
					DigDisplay();	
				}
			}
	               		   
		}
		else
		{
			switchH=0;
			switchM=0;
			switchL=0;
		}
	}										   
}


