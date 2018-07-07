#include "Power.h"

char setu[3] = ":wu";
char seti[3] = ":wi";
char setend[2] = "\r\n";
char setnum[4] = "0000";
char ii = 0;

void Power_on(void)
{
	char seto[6] = ":wo1\r\n";
	for (ii = 0; ii < 6; ii++)
	{
		USART_SendData(USART3, seto[ii]); //SEND
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
			; //WAIT
	}
}

void Power_off(void)
{
#ifdef use_old_power
	for(ii=0; ii<100; ii++) X9C104_DOWN();
#else
	char seto[6] = ":wo0\r\n";
	for (ii = 0; ii < 6; ii++)
	{
		USART_SendData(USART3, seto[ii]); //SEND
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
			; //WAIT
	}
#endif
}

void Power_u(int u) //100*num
{
	int num = u;
	setnum[0] = (num / 1000) + 48;
	setnum[1] = (num % 1000) / 100 + 48;
	setnum[2] = (num % 100) / 10 + 48;
	setnum[3] = num % 10 + 48;
	for (ii = 0; ii < 3; ii++)
	{
		USART_SendData(USART3, setu[ii]); //SEND
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
			; //WAIT
	}
	for (ii = 0; ii < 4; ii++)
	{
		USART_SendData(USART3, setnum[ii]); //SEND
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
			; //WAIT
	}
	for (ii = 0; ii < 2; ii++)
	{
		USART_SendData(USART3, setend[ii]); //SEND
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
			; //WAIT
	}
}

void Power_i(int i) //100*num
{
	int num = i;
	setnum[0] = (num / 1000) + 48;
	setnum[1] = (num % 1000) / 100 + 48;
	setnum[2] = (num % 100) / 10 + 48;
	setnum[3] = num % 10 + 48;
	for (ii = 0; ii < 3; ii++)
	{
		USART_SendData(USART3, seti[ii]); //SEND
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
			; //WAIT
	}
	for (ii = 0; ii < 4; ii++)
	{
		USART_SendData(USART3, setnum[ii]); //SEND
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
			; //WAIT
	}
	for (ii = 0; ii < 2; ii++)
	{
		USART_SendData(USART3, setend[ii]); //SEND
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
			; //WAIT
	}
}
