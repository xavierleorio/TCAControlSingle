#include "sys.h"
#include "usart.h"	  

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE
{
	int handle;

};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x)
{
	x = x;
}
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
	while ((USART1->SR & 0X40) == 0)
		; //ѭ������,ֱ���������
	USART1->DR = (u8) ch;
	return ch;
}
#endif 

#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART3_RX_BUF[USART_REC_LEN];
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA = 0;       //����״̬���
u16 USART3_RX_STA = 0;

void uart_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,
			ENABLE);       //ʹ��USART1��GPIOAʱ��
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Usart1 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;	//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;	//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); //��ʼ������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //�����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE); //ʹ�ܴ���1��DMA����

}

void USART3_Init(u32 BaudRate)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//ʹ�ܴ��ڵ�RCCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��UART3����GPIOB��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	//����ʹ�õ�GPIO������
	// Configure USART3 Rx (PB.11) as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Configure USART3 Tx (PB.10) as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//���ô���
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;   //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;   //��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	// Configure USART3
	USART_Init(USART3, &USART_InitStructure);   //���ô���3

	// Enable USART1 Receive interrupts ʹ�ܴ��ڽ����ж�
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	//���ڷ����ж��ڷ�������ʱ����
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

	// Enable the USART3
	USART_Cmd(USART3, ENABLE);   //ʹ�ܴ���3

	//�����ж�����
	//Configure the NVIC Preemption Priority Bits
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;   //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res = USART_ReceiveData(USART1);  //(USART1->DR);	//��ȡ���յ�������

		if ((USART_RX_STA & 0x8000) == 0)  //����δ���
		{
			if (USART_RX_STA & 0x4000)  //���յ���0x0d
			{
				if (Res != 0x0a)
					USART_RX_STA = 0;  //���մ���,���¿�ʼ
				else
					USART_RX_STA |= 0x8000;	//��������� 			//bit31�����Ƿ���յ�0x0a(\n)
			}
			else //��û�յ�0X0D
			{
				if (Res == 0x0d)
					USART_RX_STA |= 0x4000;			//bit30�����Ƿ���յ�0x0d(\r)
				else
				{
					USART_RX_BUF[USART_RX_STA & 0X3FFF] = Res;
					USART_RX_STA++;
					if (USART_RX_STA > (USART_REC_LEN - 1))
						USART_RX_STA = 0;			//�������ݴ���,���¿�ʼ����
				}
			}
		}
	}
}

void USART3_IRQHandler(void)                	//����3�жϷ������
{
	u8 Res;
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res = USART_ReceiveData(USART3);  //(USART1->DR);	//��ȡ���յ�������

		if ((USART3_RX_STA & 0x8000) == 0)  //����δ���
		{
			if (USART3_RX_STA & 0x4000)  //���յ���0x0d
			{
				if (Res != 0x0a)
					USART3_RX_STA = 0;  //���մ���,���¿�ʼ
				else
					USART3_RX_STA |= 0x8000; //��������� 			//bit31�����Ƿ���յ�0x0a(\n)
			}
			else //��û�յ�0X0D
			{
				if (Res == 0x0d)
					USART3_RX_STA |= 0x4000;		//bit30�����Ƿ���յ�0x0d(\r)
				else
				{
					USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = Res;
					USART3_RX_STA++;
					if (USART3_RX_STA > (USART_REC_LEN - 1))
						USART3_RX_STA = 0;				//�������ݴ���,���¿�ʼ����
				}
			}
		}
	}
}
#endif	

