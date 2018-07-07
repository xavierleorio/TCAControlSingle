#ifndef  __PID_H
#define  __PID_H

#include "sys.h"


typedef struct
{
	float setpoint; //target
	float sum_error; //sum of error
	float proportion; //P parameter
	float integral; //I parameter
	float derivative; //D parameter
	float last_error; //e[-1]
	float prev_error; //e[-2]
} PIDtypedef;

void incPIDinit(PIDtypedef *PIDx);                //initialize PID
float incPIDcalc(PIDtypedef*PIDx, float nextpoint);           //CACULATE PID
void PID_setpoint(PIDtypedef*PIDx, float setvalue);  //SET TARGET
void PID_set(PIDtypedef *PIDx, float T, float Kp, float Ti, float Td); //SET PID  kp ki kd

#endif
