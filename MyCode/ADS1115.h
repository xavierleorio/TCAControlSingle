#ifndef __ADS1115_H
#define __ADS1115_H
#include "sys.h"
#include "MYIIC.h"
#include "usart.h"

#define ADS1115_adds 0X90
#define ADS1115_conf 0x01
#define ADS1115_conv 0x00





typedef struct ADS1115
{
	float V0;
	float V1;
	float V2;
	float V3;
} ADS1115Typedef;

s16 InitADS1115(void);

float ADS1115_Getdata(ADS1115Typedef *ads1115data);

#endif
