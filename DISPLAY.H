#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include<STC15F2K60S2.H>

sbit dig1=P2^0;			 //dig1是第四位
sbit dig2=P2^1;
sbit dig3=P2^2;
sbit dig4=P2^3;			 //dig4是第一位


void DigDisplay();
void digpros(double a);

#endif

