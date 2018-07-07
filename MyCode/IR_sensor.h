#ifndef  __IR_sensor_H
#define  __IR_sensor_H
#include "sys.h"
#include "delay.h"
#include "ADC.h"
#include "usart.h"

void IR_SAMPLE(u8 index);

void Get_IR_DISTANCE(ADC_Data *IR_ADC);

#endif
