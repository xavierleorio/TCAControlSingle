#include "PWM_CAPTURE.h"

//定时器3通道2输入捕获配置

TIM_ICInitTypeDef TIM3_ICInitStructure;

void TIM3_Cap_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //PA7 清除之前设置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //上升沿配置为下拉输入，下降沿配置为上拉输入，浮空输入需要内部上拉才能稳定
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);						 //PA7 下拉

	//初始化定时器3 TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//预分频器
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM3输入捕获参数
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC2S=01 	选择输入端 IC2映射到TI1上
	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频
	TIM3_ICInitStructure.TIM_ICFilter = 0x00;	 //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM3, &TIM3_ICInitStructure);

	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC2IE捕获中断
	TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);  //允许CC2IE捕获中断

	TIM_Cmd(TIM3, ENABLE); 	//使能定时器3

}

//定时器4通道2输入捕获配置

TIM_ICInitTypeDef TIM4_ICInitStructure;

void TIM4_Cap_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能TIM4时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOB时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  //PB7 清除之前设置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //上升沿配置为下拉输入，下降沿配置为上拉输入，浮空输入需要内部上拉才能稳定
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);						 //PB7 下拉

	//初始化定时器4 TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//预分频器
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM4输入捕获参数
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC2S=01 	选择输入端 IC2映射到TI1上
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	 //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC2, ENABLE); //允许更新中断 ,允许CC2IE捕获中断

	TIM_Cmd(TIM4, ENABLE); 	//使能定时器4

}

u8 TIM3CH2_CAPTURE_STA = 0;	//输入捕获状态
u16 TIM3CH2_CAPTURE_VAL = 0;	//输入捕获值
u16 TIM3CH2_CAPTURE_COUNT = 0;	//输入捕获计算
u8 TIM4CH2_CAPTURE_STA = 0;	//输入捕获状态
u16 TIM4CH2_CAPTURE_VAL = 0;	//输入捕获值
u16 TIM4CH2_CAPTURE_COUNT = 0;	//输入捕获计算

u8 MR_state = 0x00;	//状态
double MR_DISTANCE = 0;	//距离
long int MR_DISTANCE_count = 0;	//计数

//定时器3中断服务程序
void TIM3_IRQHandler(void)	//A相
{
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)	//捕获2发生捕获事件
	{
		if (TIM3CH2_CAPTURE_STA == 0)	//捕获到上升沿
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
			TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Falling);	//下降沿触发
		}
		else	//捕获到下降沿
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
			TIM_OC2PolarityConfig(TIM3, TIM_ICPolarity_Rising);	//上升沿触发
		}
	}
	TIM_SetCounter(TIM3, 0);
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC2 | TIM_IT_Update); //清除中断标志位
}

//定时器4中断服务程序

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET) //捕获2发生捕获事件
	{
		if (TIM4CH2_CAPTURE_STA == 0) //捕获到上升沿
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
			TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Falling); //下降沿触发
		}
		else //捕获到下降沿
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
			TIM_OC2PolarityConfig(TIM4, TIM_ICPolarity_Rising); //上升沿触发
		}
	}
	TIM_SetCounter(TIM4, 0);
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC2 | TIM_IT_Update); //清除中断标志位
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
	MR_state = 0x00; //本次状态
	MR_DISTANCE = 0;	//距离
	MR_DISTANCE_count = 0;	//计数
}
