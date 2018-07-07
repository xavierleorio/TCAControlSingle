#ifndef  __HC05_H
#define  __HC05_H

#include "sys.h"
#include "delay.h"

//**********************************************************************************
#define RCC_STATE   RCC_APB2Periph_GPIOA
#define RCC_EN      RCC_APB2Periph_GPIOA
#define STATE_Pin 	GPIO_Pin_11
#define EN_Pin 		GPIO_Pin_8
//**********************************************************************************

#define HC05_EN         PAout(8)    //蓝牙控制EN信号
#define HC05_STATE      PAin(11)     //蓝牙连接状态信号

u8 HC05_Init(void);
u8 HC05_Set_Cmd(char* atstr);
u8 HC05_Get_Role(void);

#endif
