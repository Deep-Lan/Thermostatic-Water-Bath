#include <STC15F2K60S2.H>			 //此文件中定义了单片机的一些特殊功能寄存器
#include <string.h>
#include "ATCOMMOND.H"
#include "DISPLAY.H"

xdata char rec[1792]={'\0'};
int count=0;

void UartInit(void)		//115200bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR = 0x40;		//定时器1时钟为Fosc,即1T。串口1选择定时器1为波特率发生器.Timer0为12T
	AUXR1 =0x80;			 //串口1放在P16-RXD，P17-TXD
	TMOD = 0x00;		//设定定时器1和0为16位自动重装方式。
	EA=1;                //总中断开
	ES=1;				  //串口中断开
	TL1 = 0xE8;		//设定定时初值
	TH1 = 0xFF;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void SendAT(char *p)
{
	while(*p!=NULL)
	{
		SBUF=*p++;
		while(!TI);			 //等待发送数据完成
		TI=0;				 //清除发送完成标志位
	}								
}

void ReadAT() interrupt 4
{
	if(RI)
	{
		rec[count++]=SBUF;  //出去接收到的数据
		RI = 0;            //清除接收中断标志位
	}
}

void Rec_Rst()			 //缓冲数组清零
{
	while(0!=count)
	{	
		--count;
		rec[count]=0;
	}
}


void CLD_START()				   //云启动
{
	Rec_Rst();
	SendAT("AT+CLDSTART\r\n");
	while(NULL==strstr(rec,"+CSTATE:[CLOUD_CONNECTED]"));
	Rec_Rst();
}

void CLD_SEND_TEMP(double T)
{
	char a[8];
	SendAT("AT+CLDSENDRAW=5\r\n");
	while(NULL==strchr(rec,'>'));
	a[0]=(unsigned int)T/100+'0';
	a[1]=(unsigned int)T%100/10+'0';
	a[2]=(unsigned int)T%10+'0';
	a[3]='.';
	a[4]=(unsigned int)(T*10)%10+'0';
	a[5]='\r';
	a[6]='\n';
	a[7]='\0';
	SendAT(a);
	Rec_Rst();		
}


