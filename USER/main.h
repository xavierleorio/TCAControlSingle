#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "delay.h"
#include "DEFINE_GPIO.h"
#include "SPI.h"
#include "HC05.h"
#include "usart.h"
#include "DMA.h"
#include "ADC.h"
#include "IR_sensor.h"
#include "MAX6675.h"
#include "VOLTAGE_SENSOR.h"
#include "CURRENT_SENSOR.h"
#include "PWM_CAPTURE.h"
#include "X9C104.h"
#include "TIMER.h"
#include "MYIIC.h"
#include "MPU6050.h"
#include "INA226.h"
#include "PID.h"
#include "Power.h"


void sysinit(void)
{
	char i;
	SystemInit(); //系统时钟72M
	delay_init();
	NVIC_Configuration(); //设置NVIC中断分组2:2位抢占优先级00，2位响应优先级00; 4组抢占优先级4组响应优先级
	uart_init(1382400); 	 //波特率9600
	USART3_Init(9600);
	MYDMA_Config(DMA1_Channel4, (u32) &USART1->DR, (u32) DMA_PRINTF_BUF,
	DMA_MAX_SEND_LEN); 	 //DMA1通道4,外设为串口1
	HC05_Init();
	Adc_Init();
	SPI_MAX6675_Init();
	Init_GPIOpin();
	X9C104_INIT();
	TIM3_Cap_Init(0XFFFF, 72 - 1);	//以1Mhz的频率计数
	TIM4_Cap_Init(0XFFFF, 72 - 1);	//以1Mhz的频率计数
	TIM2_Int_Init(10000, 720 - 1);	//以100khz的频率计数 ,100ms
	TIM1_Int_Init(1000, 720 - 1);	//以100khz的频率计数 ,10ms
	IIC_Init();
	delay_ms(50);
	printf("mpu6050	%d\r\n", InitMPU6050());
	printf("INA226	%d\r\n", InitINA226());
  //printf("ADS1115	%d\r\n",InitADS1115());
	//AD5933_Init(100000,0,0);


	for (i = 0; i < 100; i++)
		X9C104_DOWN();
	delay_ms(100);
	Power_off();
	delay_ms(100);
	Power_u(100);

}

#endif
