#include "PWM_CAPTURE.h"

//��ʱ��3ͨ��2���벶������

TIM_ICInitTypeDef TIM3_ICInitStructure;

void TIM3_Cap_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ��TIM3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //PA7 ���֮ǰ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //����������Ϊ�������룬�½�������Ϊ�������룬����������Ҫ�ڲ����������ȶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);						 //PA7 ����

	//��ʼ����ʱ��3 TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//Ԥ��Ƶ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM3���벶�����
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC2S=01 	ѡ������� IC2ӳ�䵽TI1��
	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ
	TIM3_ICInitStructure.TIM_ICFilter = 0x00;	 //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);

	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC2IE�����ж�
	TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);  //����CC2IE�����ж�

	TIM_Cmd(TIM3, ENABLE); 	//ʹ�ܶ�ʱ��3

}

//��ʱ��4ͨ��2���벶������

TIM_ICInitTypeDef TIM4_ICInitStructure;

void TIM4_Cap_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM4ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //PB7 ���֮ǰ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //����������Ϊ�������룬�½�������Ϊ�������룬����������Ҫ�ڲ����������ȶ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);						 //PB7 ����

	//��ʼ����ʱ��4 TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//Ԥ��Ƶ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM4���벶�����
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC2S=01 	ѡ������� IC2ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	 //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC2, ENABLE); //��������ж� ,����CC2IE�����ж�

	TIM_Cmd(TIM4, ENABLE); 	//ʹ�ܶ�ʱ��4

}

u8 TIM3CH2_CAPTURE_STA = 0;	//���벶��״̬
u16 TIM3CH2_CAPTURE_VAL = 0;	//���벶��ֵ
u16 TIM3CH2_CAPTURE_COUNT = 0;	//���벶�����
u8 TIM4CH2_CAPTURE_STA = 0;	//���벶��״̬
u16 TIM4CH2_CAPTURE_VAL = 0;	//���벶��ֵ
u16 TIM4CH2_CAPTURE_COUNT = 0;	//���벶�����

u8 MR_state = 0x00;	//״̬
double MR_DISTANCE = 0;	//����
long int MR_DISTANCE_count = 0;	//����

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)	//A��
{
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)	//����2���������¼�
	{
		if (TIM3CH2_CAPTURE_STA == 0)	//����������
		{
			if (PBin(7))	//11
			{
				if (MR_state == 2)	//10
					MR_DISTANCE_count += 1;
				if (MR_state == 1)	//01
					MR_DISTANCE_count -= 1;
				MR_state = 3;
			}
			else	//10
			{
				if (MR_state == 0)	//00
					MR_DISTANCE_count += 1;
				if (MR_state == 3)	//11
					MR_DISTANCE_count -= 1;
				MR_state = 2;
			}
			TIM3CH2_CAPTURE_STA = 1;
			TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Falling);	//�½��ش���
		}
		else	//�����½���
		{
			if (PBin(7))	//01
			{
				if (MR_state == 3)	//11
					MR_DISTANCE_count += 1;
				if (MR_state == 0)	//00
					MR_DISTANCE_count -= 1;
				MR_state = 1;
			}
			else	//00
			{
				if (MR_state == 1)	//01
					MR_DISTANCE_count += 1;
				if (MR_state == 2)	//10
					MR_DISTANCE_count -= 1;
				MR_state = 0;
			}
			TIM3CH2_CAPTURE_STA = 0;
			TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Rising);	//�����ش���
		}
	}
	TIM_SetCounter(TIM3, 0);
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC2 | TIM_IT_Update); //����жϱ�־λ
}

//��ʱ��4�жϷ������

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET) //����2���������¼�
	{
		if (TIM4CH2_CAPTURE_STA == 0) //����������
		{
			if (PAin(7)) //11
			{
				if (MR_state == 2) //10
					MR_DISTANCE_count += 1;
				if (MR_state == 1) //01
					MR_DISTANCE_count -= 1;
				MR_state = 3;
			}
			else //01
			{
				if (MR_state == 3) //11
					MR_DISTANCE_count += 1;
				if (MR_state == 0) //00
					MR_DISTANCE_count -= 1;
				MR_state = 1;
			}
			TIM4CH2_CAPTURE_STA = 1;
			TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Falling); //�½��ش���
		}
		else //�����½���
		{
			if (PAin(7)) //10
			{
				if (MR_state == 0) //00
					MR_DISTANCE_count += 1;
				if (MR_state == 3) //11
					MR_DISTANCE_count -= 1;
				MR_state = 2;
			}
			else //00
			{
				if (MR_state == 1) //01
					MR_DISTANCE_count += 1;
				if (MR_state == 2) //10
					MR_DISTANCE_count -= 1;
				MR_state = 0;
			}
			TIM4CH2_CAPTURE_STA = 0;
			TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Rising); //�����ش���
		}
	}
	TIM_SetCounter(TIM4, 0);
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC2 | TIM_IT_Update); //����жϱ�־λ
}

double Get_MR_DISTANCE(void)
{
//	printf("\r\n1,%d,%d,%d\r\n",(int)TIM3CH2_CAPTURE_VAL,(int)TIM3CH2_CAPTURE_COUNT,(int)MR_DISTANCE);
	MR_DISTANCE = (double) MR_DISTANCE_count / 1000;
	//MR_DISTANCE=MR_DISTANCE*1.2;
	return MR_DISTANCE;
}

void MR_DISTANCE_calibration(void)
{
	MR_state = 0x00; //����״̬
	MR_DISTANCE = 0;	//����
	MR_DISTANCE_count = 0;	//����
}
