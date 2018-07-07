#include "DMA.h"

u8 DMA_PRINTF_BUF[DMA_MAX_SEND_LEN];

DMA_InitTypeDef DMA_InitStructure;

u16 DMA1_MEM_LEN; //保存DMA每次数据传送的长度
//DMA1的各通道配置
//这里的传输形式是固定的,这点要根据不同的情况来修改
//从存储器->外设模式/8位数据宽度/存储器增量模式
//DMA_CHx:DMA通道CHx
//cpar:外设地址
//cmar:存储器地址
//cndtr:数据传输量
void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx, u32 cpar, u32 cmar, u16 cndtr)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输

	DMA_DeInit(DMA_CHx);   //将DMA的通道1寄存器重设为缺省值
	DMA1_MEM_LEN = cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设ADC基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器

	DMA_ITConfig(DMA_CHx, DMA_IT_TC, ENABLE);            // 开启发送DMA通道中断
}
//开启一次DMA传输
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx, u16 DMA_LEN)
{
	DMA_Cmd(DMA_CHx, DISABLE);  //关闭USART1 TX DMA1 所指示的通道
	DMA_SetCurrDataCounter(DMA1_Channel4, DMA_LEN);  //DMA通道的DMA缓存的大小
	DMA_Cmd(DMA_CHx, ENABLE);  //使能USART1 TX DMA1 所指示的通道
}

//DMA1_4中断服务函数
void DMA1_Channel4_IRQHandler(void)
{
	if (DMA_GetFlagStatus(DMA1_FLAG_TC4) != RESET)	//判断通道4传输完成
	{
		DMA_ClearFlag(DMA1_FLAG_TC4);	//清除通道4传输完成标志
		DMA_Cmd(DMA1_Channel4, DISABLE);  //关闭USART1 TX DMA1 所指示的通道
	}
}

//DMA PRINTF 函数
void DMA_printf(char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsprintf((char*) DMA_PRINTF_BUF, fmt, ap);
	va_end(ap);
	MYDMA_Enable(DMA1_Channel4, strlen((const char*) DMA_PRINTF_BUF));  //dma发送
}
