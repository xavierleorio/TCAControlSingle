#ifndef  __VOLTAGE_SENSOR_H
#define  __VOLTAGE_SENSOR_H
#include "sys.h"
#include "delay.h"
#include "ADC.h"
#include "usart.h"

void VOLTAGE_SAMPLE(u8 index);
void Get_VOLTAGE_VALUE(ADC_Data *VOLTAGE_SENSOR_ADC,ADC_Data *VOLTAGE_SENSOR_ADC1);

#endif
