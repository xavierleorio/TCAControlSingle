#include "MYIIC.h"
#include "delay.h"

#define iic_delay delay_uus(1)

//��ʼ��IIC
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1); 						 //�����

	IIC_SCL = 1; 						 //��ʼ����Ϊ����״̬
	IIC_SDA = 1;

}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT()
	;     //sda�����
	IIC_SDA = 1;
	IIC_SCL = 1;
	iic_delay;
	IIC_SDA = 0;     //START:when CLK is high,DATA change form high to low
	iic_delay;
	IIC_SCL = 0;     //ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT()
	;     //sda�����
	IIC_SDA = 0;     //STOP:when CLK is high DATA change form low to high
	IIC_SCL = 1;
	iic_delay;
	IIC_SDA = 1;     //����I2C���߽����ź�
	iic_delay;
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	SDA_OUT()
	;     //sda out
	IIC_SDA = 1;
	iic_delay;
	SDA_IN()
	;      //SDA����Ϊ����
	IIC_SCL = 1;
	iic_delay;
	while (READ_SDA)
	{
		ucErrTime++;
		iic_delay;
		if (ucErrTime > 200)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL = 0;      //ʱ�����0
	return 0;
}
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL = 0;
	SDA_OUT()
	;
	IIC_SDA = 0;
	iic_delay;
	IIC_SCL = 1;
	iic_delay;
	IIC_SCL = 0;
	iic_delay;
}
//������ACKӦ��
void IIC_NAck(void)
{
	IIC_SCL = 0;
	SDA_OUT()
	;
	IIC_SDA = 1;
	iic_delay;
	IIC_SCL = 1;
	iic_delay;
	IIC_SCL = 0;
	iic_delay;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//0����Ӧ��
//1����Ӧ��
u8 IIC_Send_Byte(u8 txd)
{
	u8 t;
	SDA_OUT()
	;
	IIC_SCL = 0;      //����ʱ�ӿ�ʼ���ݴ���
	for (t = 0; t < 8; t++)
	{
		IIC_SDA = (txd & 0x80) >> 7;
		txd <<= 1;
		IIC_SCL = 1;
		iic_delay;
		IIC_SCL = 0;
		iic_delay;
	}
	return IIC_Wait_Ack();
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	SDA_IN()
	;      //SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		IIC_SCL = 1;
		iic_delay;
		receive <<= 1;
		if (READ_SDA)
			receive++;
		IIC_SCL = 0;
		iic_delay;
	}
	if (!ack)
		IIC_NAck();      //����nACK
	else
		IIC_Ack(); //����ACK
	return receive;
}
