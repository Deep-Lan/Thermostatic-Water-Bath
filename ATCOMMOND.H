#ifndef _ATCOMMOND_H
#define _ATCOMMOND_H

extern xdata char rec[];
extern int count;

#ifndef NULL
#define NULL 0
#endif

void UartInit();
void CLD_START();
void CLD_SEND_TEMP(double T);
void Rec_Rst();

#endif

