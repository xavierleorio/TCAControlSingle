#ifndef __DMA_H
#define	__DMA_H
#include "sys.h"
#include "stm32f10x_dma.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define DMA_MAX_SEND_LEN     200                 //最大发送缓冲字节数

extern u8 DMA_PRINTF_BUF[DMA_MAX_SEND_LEN];      	//发送缓冲区

void MYDMA_Config(DMA_Channel_TypeDef*DMA_CHx, u32 cpar, u32 cmar, u16 cndtr); //配置DMA1_CHx

void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx, u16 DMA_LEN);      	//使能DMA1_CHx

extern void DMA_printf(char* fmt, ...);      	//DMA PRINTF

#endif
