#include "TIMER.h"
#include "DEFINE_GPIO.h"
#include "INA226.h"
#include "AD5933.h"
#include "ADS1115.h"
#include "Filter.h"


void TIM1_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能

	//定时器TIM1初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;  //重复计数设置
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //使能指定的TIM1中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

//	TIM_Cmd(TIM1, ENABLE);  //使能TIMx
}


//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
void TIM2_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	//定时器TIM2初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE); //使能指定的TIM2中断,允许比较中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
  //初始化TIM2 Channe4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC4
	

  TIM_SetCompare1(TIM2,1100);
  TIM_SetCompare4(TIM2,0);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
	TIM_Cmd(TIM2, DISABLE);  //使能TIMx
}

/*----------------------variable------------------------------------*/

INA226Typedef INA226_DATA;
ADS1115Typedef ADS1115data;
MAX6675_data MAX6675_TEMPAYURE;
ACCELSTRUCT ACCEL_DATA;
GYROSTRUCT GYRO_DATA;
float VOLTAGE = 0;
float VOLTAGE_REFERENCE = 0;
float CURRENT = 0;
float CURRENT_REFERENCE = 0;
float RESISTANCE = 0;
float RESISTANCE_reference = 0;
float VOLTAGE_Ny=0;

float NylonResistance_reference = 0;
float TEMPATURE = 0;
float TEMPATURE_REFERENCE = 0;
float RESISTANCE_RATE_REFERENCE = 0;


float amp=0;
s16 MPU_TEMP = 0;
char i;
u8 distance_PID_period = 10;
ADC_Data adc_1_value;
ADC_Data adc_0_value;
/*-----------------------global-------------------------------------*/
char control_stautes = 0;
u32 times = 0;  //循环次数
u16 sample_period = 50; //默认采样周期500ms
u16 filter_number;
SAMPLEtypef SAMPLEDATA;
float tempature_control = 0;
int tempctrl=0;
float pwm_duty = 0;
char system_flag = 'A';
char x9c104_flag = 0;
char tempature_control_flag = 0;
PIDtypedef tempature_PID;
PIDtypedef distance_PID;
float RESISTANCE_changerate = 0;
int POWER_GUIDE = 0;
float t_kp = 100;
float t_ti = 5000;
float t_td = 0.1;
char distance_control_flag = 0;
char filter_enable=0;
float distance_control = 0;
float d_kp = 2;
float d_ti = 9999;
float d_td = 0;
float NylonResistance = 0;
float T_Resistance=0;
u8 sample_count = 0;
float Tempcontrol_c=0;




const float pi = 3.1416;   //定义pi的值
/*-------------------------------------------------------------------*/

//定时器2中断服务程序

void TIM2_IRQHandler(void)   //TIM2中断
{
	
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)  //检查TIM2比较中断发生与否
	{
		sample_count += 1;
		//printf("%d\r\n",TIM2->CCR4);
		
		  NylonResistance = INA226GetData(&INA226_DATA,INA226_Nylon);
			VOLTAGE_Ny=0.00125 * (float) INA226_DATA.VBUS/6;
			RESISTANCE = INA226GetData(&INA226_DATA,INA226_Metal);
			Get_sampledata(&SAMPLEDATA);
			
			if (tempature_control_flag)
			{
				if (tempature_PID.setpoint < TEMPATURE_REFERENCE)
					tempature_PID.setpoint = TEMPATURE_REFERENCE; //控制温度不低于常温
				PID_set(&tempature_PID, pwm_duty, t_kp, t_ti * pwm_duty,
						t_td * pwm_duty); //float T,float Kp,float Ti,float Td
				if (t_ti == 0) //积分置零
					tempature_PID.integral = 0;
				tempature_PID.sum_error += incPIDcalc(&tempature_PID,
						SAMPLEDATA.count_tempature);
				RESISTANCE_changerate = (RESISTANCE - RESISTANCE_reference)
						/ RESISTANCE_reference;
				if (RESISTANCE_changerate < 0)
					RESISTANCE_changerate = -RESISTANCE_changerate;
				pwm_duty =tempature_PID.sum_error
						* (1 + RESISTANCE_changerate);
				if (pwm_duty < 1200) //pwm_delay=1100;
				{
					pwm_duty = 1200;
					TIM_SetCompare4(TIM2,pwm_duty);
				}
				else if (pwm_duty > 10000)
				{
					pwm_duty = 10000;
					TIM_SetCompare4(TIM2,pwm_duty);
				}
				else
				{
					TIM_SetCompare4(TIM2,pwm_duty);
				}		
		}
			else
			{
				pwm_duty = 1200;
				TIM_SetCompare4(TIM2,pwm_duty);
			}
				
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);  //清除TIMx更新中断标志
	}
		
	
		
		
}

void Init_sampledata(SAMPLEtypef *sampledata)
{
	sampledata->tempature = 0;
	sampledata->distance = 0;
	sampledata->voltage = 0;
	sampledata->current = 0;
	sampledata->resistance = 0;
	sampledata->count_tempature = 0;
	sampledata->resistance_Ny = 0;
	sampledata->distance_self = 0;
	sampledata->dR1=0;
	sampledata->dT=0;
}

void Get_sampledata(SAMPLEtypef *sampledata)
{
	float x,y;
	//float dT=0;
	float dR=0;
	float dR1=0;
	float p00=-127.4;
  float p10=-0.8885;
	float p01=1.385;
	float p20=-0.002076;
	float p11=0.006823;
	float p02=-0.3436;
	float p21=-0.0006911;
  float p12=-0.07333;
	float p03=-0.8578;

	if (0.0002 * (float) INA226_DATA.CURRENT>0.1)  //滤波
	{
		//sampledata->tempature = MAX6675_TEMPAYURE.data_value;
		sampledata->tempature = TEMPATURE_REFERENCE;
		sampledata->distance = -Get_MR_DISTANCE();

			if(((RESISTANCE-sampledata->resistance)/sampledata->resistance)<0.8&&((RESISTANCE-sampledata->resistance)/sampledata->resistance)>(-1))
			{
				sampledata->voltage = 0.00125 * (float) INA226_DATA.VBUS;
				sampledata->current = 0.0002 * (float) INA226_DATA.CURRENT;
				sampledata->resistance = RESISTANCE;
			}


		
			
	//if (RESISTANCE < RESISTANCE_reference)
		//Calibration();
		
		sampledata->count_tempature =TEMPATURE_REFERENCE
				+ (sampledata->resistance - RESISTANCE_reference)
						/ RESISTANCE_RATE_REFERENCE / RESISTANCE_reference;

	
		if (filter_enable)
		{
			if (sampledata->count_tempature<1000&&sampledata->count_tempature>0)
					//sampledata->filte_temperature=huadong(sampledata->count_tempature,filter_number);
			    //sampledata->filte_temperature=LowPass(sampledata->count_tempature,0.1);
			    //sampledata->filte_temperature=LowPass2nd(sampledata->count_tempature, 1, 1);
			sampledata->filte_temperature=LowPassID(sampledata->count_tempature,0);
					else
		sampledata->filte_temperature=sampledata->count_tempature;
		}
		else
		sampledata->filte_temperature=sampledata->count_tempature;
		

	   //sampledata->resistance_Ny=LowPass(NylonResistance,1);
		sampledata->resistance_Ny=NylonResistance;

		sampledata->dT=sampledata->count_tempature-TEMPATURE_REFERENCE;
		//dT=sampledata->count_tempature-TEMPATURE_REFERENCE;
		
		dR=sampledata->resistance_Ny-NylonResistance_reference;
		dR1=dR-0.0025*sampledata->dT*NylonResistance_reference;
		sampledata->dR1=dR1;
		//x=sampledata->filte_temperature;
		x=sampledata->dT;
		y=dR1;
		//y=sampledata->resistance_Ny;
		//sampledata->distance_self=p00+p10*x+p01*y+p20*x*x+p11*x*y;
		//sampledata->distance_self=y/(0.2455-0.0003019*x);
		sampledata->distance_self=3.5*y;

	}
}

void Calibration(void)
{
	MR_DISTANCE_calibration();

	//TEMPATURE_REFERENCE = 36.53+MpuGetData(&ACCEL_DATA,&GYRO_DATA)/340-5;
	TEMPATURE_REFERENCE =25;
	RESISTANCE_RATE_REFERENCE =
	0.1252/ (0.1252 * TEMPATURE_REFERENCE + 22.583);//0.0039
	RESISTANCE_reference = RESISTANCE;
	SAMPLEDATA.resistance=RESISTANCE;

	NylonResistance_reference=NylonResistance;
	LowPassID(TEMPATURE_REFERENCE,1);
	

}



//定时器1中断服务程序
void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		times += 1;

		if (times % sample_period == 0) //sampling
		{
			//Get_MAX6675_TEMPRATURE(&MAX6675_TEMPAYURE);
			//DMA_printf();
			
			printf("%dms,", (times-sample_period) * 10);
			printf(
					"%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%d,%.3f\r\n",
					SAMPLEDATA.count_tempature,SAMPLEDATA.filte_temperature,SAMPLEDATA.distance,SAMPLEDATA.distance_self
					,SAMPLEDATA.resistance, SAMPLEDATA.resistance_Ny,SAMPLEDATA.dR1,SAMPLEDATA.dT,tempature_PID.sum_error,pwm_duty,TIM2->CCR4);
			
			if (filter_number>200&&filter_number<900)
			{
				tempature_control = sin(2*(times %(1000*(filter_number-200))) * pi /(1000*(filter_number-200)))*Tempcontrol_c+Tempcontrol_c+30;
			}
			
					if(filter_number==999)
			{
				if(times%20==0)
				{				srand(sample_count);
        tempature_control=30+rand()%130;				
				}

			}
			
			
		}
		
		if (times % distance_PID_period == 0) //distance PID period
		{
			if (distance_control_flag)
			{
				PID_set(&distance_PID, distance_PID_period, d_kp,
						d_ti * distance_PID_period, d_td * distance_PID_period); //float T,float Kp,float Ti,float Td
				if (d_ti == 0) //积分置零
					distance_PID.integral = 0;
				distance_PID.sum_error += incPIDcalc(&distance_PID,
						SAMPLEDATA.distance_self);
				tempature_control += distance_PID.sum_error;
				//if((tempature_control<SAMPLEDATA.count_tempature)&&(times<300))
				//	tempature_control=SAMPLEDATA.count_tempature;
				if (tempature_control > 180)
				{
					tempature_control = 180;
				}
			}
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
