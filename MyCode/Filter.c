#include "Filter.h"

double Y[3]={0};
double X[2]={0};


float LowPass(float input, float freq)
{
	static float a=1;
	static float Output[2]={0,0};
	
	a=freq*0.1;
	//a=freq;
	
	Output[0]=a*input+(1-a)*Output[1];
	Output[1]=Output[0];
	
	return Output[0];
}




float LowPass2nd(float input, float freq, float Q)
{
	static float Omega=0;
	static float Yn[3]={0};
	static float Xn[3]={0};
	float b0,b1,b2,a1,a2;
	
	Omega=2*pi*freq*0.1;
	
	/*
	b0=0.00060985471871729939;
	b1=0.0012197094374345988 ;
	b2=0.00060985471871729939;
	a1=-1.9289422632520334   ;
  a2=  0.93138168212690264  ;
	*/
	b0=(1-cos(Omega))/2;
	b1=2*b0;
	b2=b0;
	a1=-2*cos(Omega);
	a2=1-sin(Omega)/(2*Q);

	
	Xn[2]=Xn[1];
	Xn[1]=Xn[0];
	Xn[0]=input;
	Yn[2]=Yn[1];
	Yn[1]=Yn[0];
	Yn[0]=b0*Xn[0]+b1*Xn[1]+b2*Xn[2]+a1*Yn[1]+a2*Yn[2];

	return Yn[0];
}

float LowPassID(float Input, u8 Cali)
{
	const float T=0.02;

	
	double a0=0;
	double a1=0;
	double a2=0;
	double b1=0;
	double b2=0;
	double b3=0;


 
 a0=0.07999;
 a1=-0.07814;
 b1=1.84345;
 b2=-0.8453;


	/*
 a0=0.04396;
 a1=-0.04389;
 b1=1.94933;
 b2=-0.9494;
*/
 /*
 a0=0.01509;
 a1=-0.01375;
 b1=1.92996;
 b2=-0.9313;
*/
/*
 a0=0.06289;
 a1=-0.04654;
 b1=1.70855;
 b2=-0.7249;
*/
	X[1]=X[0];
	X[0]=Input;
	Y[2]=Y[1];
	Y[1]=Y[0];
	//Y[0]=((a1/T+a2)*X[0]-a1/T*X[1]-b1/T/T*Y[2]+(2*b1/T/T+b2/T)*Y[1])/(b1/T/T+b2/T+b3);
	Y[0]=b1*Y[1]+b2*Y[2]+a1*X[1]+a0*X[0];
	
		
	if (Cali)
	{
    X[0]=Input;
		X[1]=Input;
	  Y[0]=Input;
		Y[1]=Input;
		Y[2]=Input;
	}

	return Y[0];
	
}


float huadong(float input, int n)
{

static float Input_temp[200]={0};
static float Input_sum=0;


	int j;
		j=sample_count%n;
	  Input_sum-=Input_temp[j];
		Input_temp[j]=input;
		Input_sum+=Input_temp[j];
	  
	
    return Input_sum/n;
}


