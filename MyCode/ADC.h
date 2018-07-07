#ifndef  __ADC_H
#define  __ADC_H
#include "sys.h"
#include "delay.h"
#include "stm32f10x_adc.h"

#define ADC_PIN_0 GPIO_Pin_0	//PA0
#define ADC_PIN_1 GPIO_Pin_1	//PA1
#define ADC_PIN_2 GPIO_Pin_2	//PA2

typedef struct 
{
	u16 adc_digital;
	float voltage;
	float data_value;
} ADC_Data;

void Adc_Init(void);
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch, u8 times);

#endif
