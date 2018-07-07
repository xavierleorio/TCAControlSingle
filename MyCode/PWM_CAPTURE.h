#ifndef  __PWM_CAPTURE_H
#define  __PWM_CAPTURE_H
#include "sys.h"
#include "usart.h"
#include "stm32f10x_tim.h"

void TIM3_Cap_Init(u16 arr, u16 psc); //PA7,CH2
void TIM4_Cap_Init(u16 arr, u16 psc); //PB7,CH2

double Get_MR_DISTANCE(void);
void MR_DISTANCE_calibration(void);

#endif
