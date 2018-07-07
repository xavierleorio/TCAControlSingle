#include "DEFINE_GPIO.h"
#include "delay.h"

void Init_GPIOpin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//RELAY
	RCC_APB2PeriphClockCmd(RELAY_CLK, ENABLE);	 //clk
	GPIO_InitStructure.GPIO_Pin = RELAY1_PIN | RELAY2_PIN | RELAY3_PIN
			| RELAY4_PIN;				 //pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //mode
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //50MHz
	GPIO_Init(RELAY_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(RELAY_GPIO_PORT,
	RELAY1_PIN | RELAY2_PIN | RELAY3_PIN | RELAY4_PIN);			//set

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //clk
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 // pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_0|GPIO_Pin_3);					//set
}
