#include "delay.h"
#include "sys.h"

static u8 fac_uus = 0; //uus延时倍乘数
static u8 fac_us = 0; //us延时倍乘数
static u16 fac_ms = 0; //ms延时倍乘数

//初始化延迟函数
//当使用ucos的时候,此函数会初始化ucos的时钟节拍
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us = SystemCoreClock / 8000000;	//为系统时钟的1/8  ,systemcoreclock=72000000, fac_us=9;
	fac_uus = fac_us / 9;	//fac_us/9 ,1/9us
	fac_ms = (u16) fac_us * 1000;	//非ucos下,代表每个ms需要的systick时钟数   
}

//延时nuus,uus=us/9
//nuus为要延时的uus数.		    								   
void delay_uus(u32 nuus)
{
	u32 temp;
	SysTick->LOAD = nuus * fac_uus; //时间加载	  		 
	SysTick->VAL = 0x00;        //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //开始倒数	 
	do
	{
		temp = SysTick->CTRL;
	} while (temp & 0x01 && !(temp & (1 << 16))); //等待时间到达			//bit16置一说明时间到，跳出循环   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL = 0X00;       //清空计数器	 
}

//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD = nus * fac_us; //时间加载	  		 
	SysTick->VAL = 0x00;        //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //开始倒数	 
	do
	{
		temp = SysTick->CTRL;
	} while (temp & 0x01 && !(temp & (1 << 16))); //等待时间到达			//bit16置一说明时间到，跳出循环   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL = 0X00;       //清空计数器	 
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD = (u32) nms * fac_ms;       //时间加载(SysTick->LOAD为24bit)
	SysTick->VAL = 0x00;           //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //开始倒数  
	do
	{
		temp = SysTick->CTRL;
	} while (temp & 0x01 && !(temp & (1 << 16)));          //等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL = 0X00;       //清空计数器	  	    
}

//秒延时函数

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

