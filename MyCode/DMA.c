#include "DMA.h"

u8 DMA_PRINTF_BUF[DMA_MAX_SEND_LEN];

DMA_InitTypeDef DMA_InitStructure;

u16 DMA1_MEM_LEN; //����DMAÿ�����ݴ��͵ĳ���
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx
//cpar:�����ַ
//cmar:�洢����ַ
//cndtr:���ݴ�����
void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx, u32 cpar, u32 cmar, u16 cndtr)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����

	DMA_DeInit(DMA_CHx);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA1_MEM_LEN = cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA����ADC����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���

	DMA_ITConfig(DMA_CHx, DMA_IT_TC, ENABLE);            // ��������DMAͨ���ж�
}
//����һ��DMA����
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx, u16 DMA_LEN)
{
	DMA_Cmd(DMA_CHx, DISABLE);  //�ر�USART1 TX DMA1 ��ָʾ��ͨ��
	DMA_SetCurrDataCounter(DMA1_Channel4, DMA_LEN);  //DMAͨ����DMA����Ĵ�С
	DMA_Cmd(DMA_CHx, ENABLE);  //ʹ��USART1 TX DMA1 ��ָʾ��ͨ��
}

//DMA1_4�жϷ�����
void DMA1_Channel4_IRQHandler(void)
{
	if (DMA_GetFlagStatus(DMA1_FLAG_TC4) != RESET)	//�ж�ͨ��4�������
	{
		DMA_ClearFlag(DMA1_FLAG_TC4);	//���ͨ��4������ɱ�־
		DMA_Cmd(DMA1_Channel4, DISABLE);  //�ر�USART1 TX DMA1 ��ָʾ��ͨ��
	}
}

//DMA PRINTF ����
void DMA_printf(char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsprintf((char*) DMA_PRINTF_BUF, fmt, ap);
	va_end(ap);
	MYDMA_Enable(DMA1_Channel4, strlen((const char*) DMA_PRINTF_BUF));  //dma����
}
