#ifndef _ADC_H_
#define _ADC_H_

#define ADC_POWER 0x80
#define ADC_FLAG 0x10
#define ADC_START 0x08
#define ADC_SPEED 0x60        //选用AD转换最高速

void ADCInit();
unsigned int GetADCResult(unsigned char ch);

#endif

