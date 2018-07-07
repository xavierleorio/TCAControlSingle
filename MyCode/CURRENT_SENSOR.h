#ifndef  __CURRENT_SENSOR_H
#define  __CURRENT_SENSOR_H
#include "sys.h"
#include "delay.h"
#include "ADC.h"
#include "usart.h"

void CURRENT_SAMPLE(u8 index);
void Get_CURRENT_VALUE(ADC_Data *CURRENT_SENSOR_ADC);

#endif
