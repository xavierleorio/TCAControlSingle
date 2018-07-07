#ifndef __MAX6675_H
#define __MAX6675_H

#include "sys.h"
#include "stm32f10x_spi.h"
#include "usart.h"

//**********************************************************************************
#define 	MAX6675_CS	 		GPIO_Pin_4
#define 	MAX6675_CSL()		GPIOA->BRR = MAX6675_CS;
#define 	MAX6675_CSH()		GPIOA->BSRR = MAX6675_CS;
//**********************************************************************************

typedef struct MAX6675_data
{
	u16 adc_digital;
	float data_value;
} MAX6675_data;

void SPI_MAX6675_Init(void);
void Get_MAX6675_TEMPRATURE(MAX6675_data *MAX6675_TEMPAYURE);

#endif

