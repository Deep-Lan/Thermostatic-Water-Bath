#include<math.h>
#include "ADC.H"

double voltage(unsigned char ch)
{
	unsigned int value;
	double vol;
	value=GetADCResult(ch);
	vol=(5.0*value)/1024.0;         //value*5/1024
	return vol;
}
double temperature()
{
	double T,vol;
	vol=voltage(0x00);
	T=(6.35-1.0*vol)/(6.35+1.0*vol);
	T=log(T);
	T=1.0/(T/3495.0+1.0/298.0);//Kelvin
	T-=273.15;//摄氏
	return T;	
}
double set()
{
	double S,vol;
	vol=voltage(0x01);
	S=10.0*vol+50.0;
	return S;	
}

