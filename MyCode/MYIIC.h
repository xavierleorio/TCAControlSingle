#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

//IO方向设置
#define SDA_IN()  {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=8<<4;}
#define SDA_OUT() {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=3<<4;}

//IO操作函数
#define IIC_SCL    PBout(0) //SCL
#define IIC_SDA    PBout(1) //SDA	 
#define READ_SDA   PBin(1)  //输入SDA 

//IIC所有操作函数
extern void IIC_Init(void);                //初始化IIC的IO口
extern void IIC_Start(void);				//发送IIC开始信号
extern void IIC_Stop(void);	  			//发送IIC停止信号
extern u8 IIC_Send_Byte(u8 txd);			//IIC发送一个字节
extern u8 IIC_Read_Byte(unsigned char ack);			//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr, u8 addr, u8 data);
u8 IIC_Read_One_Byte(u8 daddr, u8 addr);

#endif
