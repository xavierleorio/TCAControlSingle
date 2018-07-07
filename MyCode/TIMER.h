#ifndef  __TIMER_H
#define  __TIMER_H
#include "sys.h"
#include "usart.h"
#include "stm32f10x_tim.h"
#include "VOLTAGE_SENSOR.h"
#include "CURRENT_SENSOR.h"
#include "IR_sensor.h"
#include "INA226.h"
#include "X9C104.h"
#include "MAX6675.h"
#include "PWM_CAPTURE.h"
#include "MPU6050.h"
#include "PID.h"
#include <math.h>
#include "Power.h"


typedef struct
{
	float tempature;
	float distance;
	float voltage;
	float current;
	float voltage_Ny;
	float resistance;
	float count_tempature;
	float filte_temperature;
	float resistance_Ny;
	float distance_self;
	float dR1;
	float dT;
} SAMPLEtypef;

extern char control_stautes;
extern u32 times;
extern u16 sample_period;
extern SAMPLEtypef SAMPLEDATA;
extern float tempature_control;
extern float pwm_duty;
extern char system_flag;
extern char x9c104_flag;
extern char tempature_control_flag;
extern PIDtypedef tempature_PID;
extern PIDtypedef distance_PID;
extern int POWER_GUIDE;
extern float t_kp;
extern float t_ti;
extern float t_td;
extern char distance_control_flag;
extern float distance_control;
extern float d_kp;
extern float d_ti;
extern float d_td;
extern float NylonResistance;
extern float T_Resistance;
extern u8 sample_count;
extern char filter_enable;
extern u16 filter_number;
extern float Tempcontrol_c;



extern const float pi;   //定义pi的值

void TIM2_Int_Init(u16 arr, u16 psc);
void TIM1_Int_Init(u16 arr, u16 psc);

void Init_sampledata(SAMPLEtypef *sampledata);
void Get_sampledata(SAMPLEtypef *sampledata);
void Calibration(void);
void Count_tempature_control(void);

#endif
