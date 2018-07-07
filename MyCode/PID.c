#include "PID.h"

void incPIDinit(PIDtypedef *PIDx)                //initialize PID
{
	PIDx->setpoint = 0;                //target
	PIDx->sum_error = 0;                //sum of error
	PIDx->proportion = 0;                //P parameter
	PIDx->integral = 0;                //I parameter
	PIDx->derivative = 0;                //D parameter
	PIDx->last_error = 0;                //e[-1]
	PIDx->prev_error = 0;                //e[-2]
}

void PID_setpoint(PIDtypedef*PIDx, float setvalue)  //SET TARGET
{
	PIDx->setpoint = setvalue;
}

void PID_set(PIDtypedef *PIDx, float T, float Kp, float Ti, float Td) //SET PID  kp ki kd
{
	PIDx->proportion = Kp;  //P parameter P = Pmax(*60~70%)
	PIDx->integral = Kp * (T / Ti);  //I parameter
	PIDx->derivative = Kp * (Td / T);  //D parameter
}

// Ultimaker
//#define  DEFAULT_Kp 22.2
//#define  DEFAULT_Ki 1.08
//#define  DEFAULT_Kd 114

// MakerGear
//#define  DEFAULT_Kp 7.0
//#define  DEFAULT_Ki 0.1
//#define  DEFAULT_Kd 12

// Mendel Parts V9 on 12V
//#define  DEFAULT_Kp 63.0
//#define  DEFAULT_Ki 2.25
//#define  DEFAULT_Kd 440

float incPIDcalc(PIDtypedef *PIDx, float nextpoint)
{
	float iError, iincpid;
	iError = PIDx->setpoint - nextpoint;  //count e[k]
	/*iincpid=                                               //count increment
	 PIDx->proportion*iError                //e[k]
	 -PIDx->integral*PIDx->last_error          //e[k-1]
	 +PIDx->derivative*PIDx->prev_error;//e[k-2]
	 */
	iincpid =                                                 //count increment
			PIDx->proportion * (iError - PIDx->last_error)
					+ PIDx->integral * iError
					+ PIDx->derivative
							* (iError - 2 * PIDx->last_error + PIDx->prev_error);

	PIDx->prev_error = PIDx->last_error; //save error for next cacualte
	PIDx->last_error = iError;
	return (iincpid);
}
