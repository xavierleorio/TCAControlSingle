#include "X9C104.h"

void X9C104_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(X9C104_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = CS_PIN | UD_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(X9C104_GPIO_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(X9C104_GPIO_PORT, CS_PIN | UD_PIN);

	RCC_APB2PeriphClockCmd(X9C104_INC_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = INC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(X9C104_INC_GPIO_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(X9C104_INC_GPIO_PORT, INC_PIN);

	INC_ON();
	CS_ON();
}

void X9C104_DOWN(void)
{
	CS_OFF();
	UD_OFF();
	INC_OFF();
	delay_us(2);
	INC_ON();
	CS_ON();
}

void X9C104_UP(void)
{
	CS_OFF();
	UD_ON();
	INC_OFF();
	delay_us(2);
	INC_ON();
	CS_ON();
}
