/*
 * Power.h
 *
 *  Created on: 2017Äê10ÔÂ16ÈÕ
 *      Author: lk287
 */
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "X9C104.h"

#ifndef POWER_H_
#define POWER_H_

//#define use_old_power

void Power_on(void);
void Power_off(void);
void Power_u(int u);
void Power_i(int i);

#endif /* MYCODE_POWER_H_ */
