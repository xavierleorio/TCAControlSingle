#include "main.h"



int main(void)
{
	u8 i;
	u8 len;
	u8 Fan=0;

	char sample_enable = 0; //默认采样不使能
	char sample_doing = 0; //sampling


	sysinit();
 

	while (1)
	{


		if (USART_RX_STA & 0x8000)
		{
			len = USART_RX_STA & 0x3fff; //得到数据长度，一个字符为一个长度,数据以回车结束，回车不计入字符
			//计算控制时间
			if (len == 44)
			{
				system_flag = USART_RX_BUF[0];
				sample_enable = USART_RX_BUF[1] - 48;
				filter_enable = USART_RX_BUF[2] - 48;
				tempature_control_flag = USART_RX_BUF[3] - 48;
				distance_control_flag = USART_RX_BUF[4] - 48;
				Fan = USART_RX_BUF[43] - 48;
				sample_period = 0;
				filter_number=0;
				tempature_control = 0;
				distance_control = 0;
				t_kp = 0;
				t_ti = 0;
				t_td = 0;
				d_kp = 0;
				d_ti = 0;
				d_td = 0;
				for (i = 0; i < 3; i++)
				{
					sample_period = 10 * sample_period
							+ (USART_RX_BUF[i + 5] - 48);
					filter_number=10 * filter_number
							+ (USART_RX_BUF[i + 8] - 48);
				}
				for (i = 0; i < 4; i++)
				{
										
					tempature_control = 10 * tempature_control
							+ (USART_RX_BUF[i + 11] - 48);
					Tempcontrol_c=tempature_control;
					distance_control = 10 * distance_control
							+ (USART_RX_BUF[i + 15] - 48);
					t_kp = 10 * t_kp + (USART_RX_BUF[i + 19] - 48);	//100,
					t_ti = 10 * t_ti + (USART_RX_BUF[i + 23] - 48);	//5000,
					t_td = 10 * t_td + (USART_RX_BUF[i + 27] - 48);	//100,
					d_kp = 10 * d_kp + (USART_RX_BUF[i + 31] - 48);	//2,
					d_ti = 10 * d_ti + (USART_RX_BUF[i + 35] - 48);	//5000,
					d_td = 10 * d_td + (USART_RX_BUF[i + 39] - 48);	//0,
				}
				t_td = t_td / 100;	//0.1
				d_td = d_td / 100;	//0
				d_kp=d_kp/100;
				
				if (Fan)
				Fan_ON();
				else
				Fan_OFF();
						

				if (sample_doing)
				{	printf("%dms,", (times-sample_period) * 10);
			printf("%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f",
					SAMPLEDATA.count_tempature,SAMPLEDATA.filte_temperature,SAMPLEDATA.distance,SAMPLEDATA.distance_self
		     ,SAMPLEDATA.resistance, SAMPLEDATA.resistance_Ny, SAMPLEDATA.dR1);}
				
				else
					printf("Time,Temp,Tempf,Dis,Dis_s,Res_M,Res_N,dR1,dT");
				printf("\r\n");
			}
			//RESET RECEIVE FLAG
			USART_RX_STA = 0;
			//SYSTEM
			switch (system_flag)
			{
			case 'C':	//CALIBRATION
			{
				Calibration();
			}
				break;
			
			default:
				;
			}
			//FLAG

			if (sample_enable)
			{
				if (sample_doing == 0)
				{
					Power_u(100);
					delay_ms(10);	//wait
					Power_i(300);
					delay_ms(10);	//wait
					Power_on();
					times = 0;
					//Init_sampledata(&SAMPLEDATA);
					TIM_Cmd(TIM2, ENABLE);  //打开TIMX
					TIM_Cmd(TIM1, ENABLE);  //打开TIMX
					//printf("0,0,0,0,0,0,0");
					//printf("mpu6050	%d,", InitMPU6050());
					//printf("ina226	%d,", InitINA226());
					//printf("SAMPLING PERIOD:%dms\r\n", times * 10);
				}
			}
			else
			{
				Power_off();
				MOS_OFF();
				delay_ms(10);	//wait
				Power_u(100);
				printf("%dms,", (times-sample_period) * 10);
			printf(
					"%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f",
					SAMPLEDATA.count_tempature,SAMPLEDATA.filte_temperature,SAMPLEDATA.distance,SAMPLEDATA.distance_self
					,SAMPLEDATA.resistance, SAMPLEDATA.resistance_Ny,SAMPLEDATA.dR1);
				printf("DISABLE SAMPLE\r\n");
				sample_enable = 0;
				sample_period = 50;
				sample_doing = 0;
				times = 0;
				TIM_SetCompare4(TIM2,0);
				TIM_Cmd(TIM2, DISABLE);  //关闭TIMx
				TIM_Cmd(TIM1, DISABLE);  //关闭TIMx
				control_stautes = 0;
			}
		}
		else
		{
			if (sample_enable)
			{

				if (tempature_control_flag)
				{
					if ((tempature_control - tempature_PID.setpoint) > 5
							|| (tempature_PID.setpoint - tempature_control) > 5)
					{
						incPIDinit(&tempature_PID);
						PID_setpoint(&tempature_PID, tempature_control);
						control_stautes = 0;
						if (tempature_control == 180)
							POWER_GUIDE = 300;
						else
							POWER_GUIDE = 4 * tempature_control; //调压上限
						if (POWER_GUIDE < 100)
							POWER_GUIDE = 100;
					}

				}
				if (SAMPLEDATA.count_tempature > 190) //限温保护
				{
					MOS_OFF();
					tempature_control_flag = 0;

					distance_control_flag = 0;
				}
				if (tempature_control_flag == 0 
						&& distance_control_flag == 0)
				{
					MOS_OFF();
					Power_u(100);
					POWER_GUIDE = 100;
					incPIDinit(&tempature_PID);
					control_stautes = 0;
					pwm_duty = 1200;

					system_flag = 'A';
				}
				Power_u(POWER_GUIDE);
				sample_doing = 1;
			}  //采样周期结束
			
		}  //menu
	}  //while
}  //main
