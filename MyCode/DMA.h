#ifndef __DMA_H
#define	__DMA_H
#include "sys.h"
#include "stm32f10x_dma.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define DMA_MAX_SEND_LEN     200                 //����ͻ����ֽ���

extern u8 DMA_PRINTF_BUF[DMA_MAX_SEND_LEN];      	//���ͻ�����

void MYDMA_Config(DMA_Channel_TypeDef*DMA_CHx, u32 cpar, u32 cmar, u16 cndtr); //����DMA1_CHx

void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx, u16 DMA_LEN);      	//ʹ��DMA1_CHx

extern void DMA_printf(char* fmt, ...);      	//DMA PRINTF

#endif
