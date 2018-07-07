#ifndef __Filter_h
#define __Filter_h
#include "sys.h"
#include "timer.h"

float LowPass(float input, float freq);
float LowPass2nd(float input, float freq, float Q);
float huadong(float input,int n);
float LowPassID(float Input, u8 Cali);

extern double Y[3];
extern double X[2];

#endif
