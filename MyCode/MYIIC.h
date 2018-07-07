#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

//IO��������
#define SDA_IN()  {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=8<<4;}
#define SDA_OUT() {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=3<<4;}

//IO��������
#define IIC_SCL    PBout(0) //SCL
#define IIC_SDA    PBout(1) //SDA	 
#define READ_SDA   PBin(1)  //����SDA 

//IIC���в�������
extern void IIC_Init(void);                //��ʼ��IIC��IO��
extern void IIC_Start(void);				//����IIC��ʼ�ź�
extern void IIC_Stop(void);	  			//����IICֹͣ�ź�
extern u8 IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
extern u8 IIC_Read_Byte(unsigned char ack);			//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr, u8 addr, u8 data);
u8 IIC_Read_One_Byte(u8 daddr, u8 addr);

#endif
