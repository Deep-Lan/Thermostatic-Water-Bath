#include "DISPLAY.H"
#include "DATAPROS.H"

unsigned char disp[4];
unsigned char code smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


void digpros(double a)
{
	disp[3]=smgduan[(unsigned char)a/100];//百位
	disp[2]=smgduan[(unsigned char)a%100/10];//十位
	disp[1]=smgduan[(unsigned char)a%10]+0x80;//个位
	disp[0]=smgduan[(unsigned int)(a*10)%10];//十分位		
}
void DigDisplay()
{
	unsigned char i,j;
	for(i=0;i<4;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				dig1=1;dig2=1;dig3=1;dig4=0; break;//显示第1位
			case(1):
				dig1=1;dig2=1;dig3=0;dig4=1; break;//显示第2位
			case(2):
				dig1=1;dig2=0;dig3=1;dig4=1; break;//显示第3位
			case(3):
				dig1=0;dig2=1;dig3=1;dig4=1; break;//显示第4位	
		}
		P0=disp[i];//发送数据
		for(j=0;j<255;j++);	
		P0=0x00;//消隐
		dig1=1;dig2=1;dig3=1;dig4=1;//消隐
	}		
}

