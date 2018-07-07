#include "delay.h"
#include "sys.h"

static u8 fac_uus = 0; //uus��ʱ������
static u8 fac_us = 0; //us��ʱ������
static u16 fac_ms = 0; //ms��ʱ������

//��ʼ���ӳٺ���
//��ʹ��ucos��ʱ��,�˺������ʼ��ucos��ʱ�ӽ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us = SystemCoreClock / 8000000;	//Ϊϵͳʱ�ӵ�1/8  ,systemcoreclock=72000000, fac_us=9;
	fac_uus = fac_us / 9;	//fac_us/9 ,1/9us
	fac_ms = (u16) fac_us * 1000;	//��ucos��,����ÿ��ms��Ҫ��systickʱ����   
}

//��ʱnuus,uus=us/9
//nuusΪҪ��ʱ��uus��.		    								   
void delay_uus(u32 nuus)
{
	u32 temp;
	SysTick->LOAD = nuus * fac_uus; //ʱ�����	  		 
	SysTick->VAL = 0x00;        //��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //��ʼ����	 
	do
	{
		temp = SysTick->CTRL;
	} while (temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��			//bit16��һ˵��ʱ�䵽������ѭ��   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL = 0X00;       //��ռ�����	 
}

//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD = nus * fac_us; //ʱ�����	  		 
	SysTick->VAL = 0x00;        //��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //��ʼ����	 
	do
	{
		temp = SysTick->CTRL;
	} while (temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��			//bit16��һ˵��ʱ�䵽������ѭ��   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL = 0X00;       //��ռ�����	 
}
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD = (u32) nms * fac_ms;       //ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL = 0x00;           //��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //��ʼ����  
	do
	{
		temp = SysTick->CTRL;
	} while (temp & 0x01 && !(temp & (1 << 16)));          //�ȴ�ʱ�䵽��   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL = 0X00;       //��ռ�����	  	    
}

//����ʱ����

void delay_s(float seconds)
{
	int s, i;
	float ms;
	s = seconds / 0.5;
	ms = s * 0.5;
	ms = seconds - ms;
	ms = ms * 1000;
	if (s != 0)
	{
		for (i = 0; i < s; i++)
		{
			delay_ms(500);
		}
	}
	if (ms != 0)
	{
		delay_ms((int) (ms));
	}
}

