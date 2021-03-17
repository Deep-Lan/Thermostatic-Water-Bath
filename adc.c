#include<STC15F2K60S2.H>
#include"ADC.H"
void ADCInit()
{
	P1ASF=0x03;		  //P10和p11口设为ADC模式
	CLK_DIV=0x00;      //ADRJ=0//高8位放在ADC_RES,低2位放在ADC_RESL；
	EADC=0;         // 禁止ADC中断，采用查询方式
}

unsigned int GetADCResult(unsigned char ch)
{
	unsigned int value=0; 
	ADC_CONTR=(ADC_POWER|ADC_SPEED|ADC_START|ch);
	while(!(ADC_CONTR&ADC_FLAG));
	ADC_CONTR=0x00;
	value=ADC_RES;
	value=(value<<2)|ADC_RESL;
	return value;		
}


