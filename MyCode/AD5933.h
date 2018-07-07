#ifndef _AD5933_h_
#define _AD5933_h_

#include "sys.h"
#include "delay.h"

#include <math.h>
#define uint unsigned int



//IO��������
//#define SDA_IN()  {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=8<<16;}
//#define SDA_OUT() {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=3<<16;}
/*
#define SDA_IN()  {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=8<<4;}
#define SDA_OUT() {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=3<<4;}
*/

//IO��������	 
//#define SCL    PCout(11) //SCL
//#define SDA    PCout(12) //SDA
//#define READ_SDA   PCin(12)  //����SDA

/*
#define SCL    PBout(0) //SCL
#define SDA    PBout(1) //SDA	 
#define READ_SDA   PBin(1)  //����SDA 
*/


#define AD5933_SYS_Init					(1)<<12
#define AD5933_Begin_Fre_Scan		(2)<<12
#define AD5933_Fre_UP						(3)<<12
#define AD5933_Fre_Rep					(4)<<12
#define AD5933_Get_Temp					(9)<<12
#define AD5933_Sleep						(10)<<12
#define AD5933_Standby					(11)<<12

#define AD5933_OUTPUT_2V				(0)<<9
#define AD5933_OUTPUT_1V				(3)<<9
#define AD5933_OUTPUT_400mV			(2)<<9
#define AD5933_OUTPUT_200mV			(1)<<9

#define AD5933_Gain_1						(1)<<8
#define AD5933_Gain_5						(0)<<8

#define AD5933_IN_MCLK					(0)<<3
#define AD5933_OUT_MCLK					(1)<<3

#define AD5933_Reset						(1)<<4

//���庯��
/*
void Ini_I2c(void);
void SDA_1(void);
void SDA_0 (void);
void SCL_1(void);
void SCL_0 (void);
void GetACK(void);
void SendNACK(void);
void START(void);
void STOP(void);
void SendByte(u8 txd);	// ����һ���ֽ������Ӻ���
u8 ReadByte(void);  //��һ���ֽ�����
*/
void Write_Byte(char nAddr,uint nValue);
void SetPointer(char nAddr);
int Rece_Byte(char nAddr);
void Delay_ms(unsigned long nValue);
float Scale_imp (u8 *SValue,u8 *IValue,u8 *NValue,u8 *CValue);
u16 AD5933_Tempter(void);
float Get_resistance(u16 num);
float AD5933_Sweep (float Fre_Begin,float Fre_UP,u16 UP_Num,u16 OUTPUT_Vatage,u16 Gain,u16 SWeep_Rep);
float DA5933_Get_Rs(void);
float DA5933_Get_Cap(float Fre);
float DA5933_Get_L(float Fre);
void AD5933_Init(float Freq, float Freq_Step, u16 Step_Num);
float AD5933_GetResistance(void);
#endif

