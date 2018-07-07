#include "MAX6675.h"

void SPI_MAX6675_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	/* ʹ�� SPI1 ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

	/* ---------ͨ��I/O��ʼ��----------------
	 * PA5-SPI1-SCK :MAX6675_SCK
	 * PA6-SPI1-MISO:MAX6675_SO
	 * PA7-SPI1-MOSI:MAX6675_SI
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// �������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* ---------����I/O��ʼ��----------------*/
	/* PA4-SPI1-NSS:MAX6675_CS */							// Ƭѡ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// �������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);						// �Ȱ�Ƭѡ���ߣ������õ�ʱ��������

	/* SPI1 ���� */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);

	/* ʹ�� SPI1  */
	SPI_Cmd(SPI1, ENABLE);
}

unsigned char MAX6675_ReadByte(void)
{

	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
		;

	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI1, 0xff);

	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
		;

	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI1);
}

void Get_MAX6675_TEMPRATURE(MAX6675_data *MAX6675_TEMPAYURE)
{
	unsigned int t, i;
	unsigned char c;
	unsigned char flag;

	MAX6675_CSL()
	;
	c = MAX6675_ReadByte();
	i = c;
	i = i << 8;
	c = MAX6675_ReadByte();
	MAX6675_CSH()
	;

	i = i | ((unsigned int) c);			//i�Ƕ�������ԭʼ����
	flag = i & 0x04;						//flag�������ȵ�ż������״̬
	t = i << 1;
	t = t >> 4;
	MAX6675_TEMPAYURE->adc_digital = i;
	MAX6675_TEMPAYURE->data_value = t * 0.25;
	if (i != 0)							//max6675�����ݷ���
	{
		if (flag == 0)						//�ȵ�ż������
		{
//				printf("raw data is\t%04X,tempature is\t%4.2f\r\n",TEMPATURE->adc_digital,TEMPATURE->data_value);
		}
		else							//�ȵ�ż����
		{
			printf("\r\nNO device, plese check\r\n");
		}

	}
	else								//max6675û�����ݷ���
	{
		printf("\r\nNo data was found from max6675\r\n");
	}
}
