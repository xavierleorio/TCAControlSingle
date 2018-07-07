#include "IR_sensor.h"

u16 IR_SAMPLE_VALUE[10] =
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void IR_SAMPLE(u8 index)
{
	IR_SAMPLE_VALUE[index] = Get_Adc(ADC_Channel_0);
}

void Get_IR_DISTANCE(ADC_Data *IR_ADC)
{
	IR_ADC->adc_digital = (IR_SAMPLE_VALUE[0] + IR_SAMPLE_VALUE[1]
			+ IR_SAMPLE_VALUE[2] + IR_SAMPLE_VALUE[3] + IR_SAMPLE_VALUE[4]
			+ IR_SAMPLE_VALUE[5] + IR_SAMPLE_VALUE[6] + IR_SAMPLE_VALUE[7]
			+ IR_SAMPLE_VALUE[8] + IR_SAMPLE_VALUE[9]) / 10;

	IR_ADC->voltage = (float) IR_ADC->adc_digital * (3.3 / 4096);

	//¡y y = 1.9953x6 - 22.631x5 + 103.69x4 - 246.91x3 + 327.55x2 - 240.87x + 90.192
	//	y= 12.08x6 - 109.44x5 + 401.97x4 - 767.45x3 + 809.79x2 - 461.74x + 126.44
	/*
	 IR_ADC->data_value =  +12.08*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage
	 -109.44*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage
	 +401.97*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage
	 -767.45*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage
	 +809.79*IR_ADC->voltage*IR_ADC->voltage
	 -461.74*IR_ADC->voltage
	 +126.44;
	 */
	// y = 6.0124x6 - 53.315x5 + 190.15x4 - 350.49x3 + 357.19x2 - 199.64x + 55.696
	// y = -5.4132x5 + 37.532x4 - 102.75x3 + 140.87x2 - 101.58x + 36.195
	/*
	 IR_ADC->data_value = 	-5.4132*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage
	 +37.532*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage
	 -102.75*IR_ADC->voltage*IR_ADC->voltage*IR_ADC->voltage
	 +140.87*IR_ADC->voltage*IR_ADC->voltage
	 -101.58*IR_ADC->voltage
	 +36.195;
	 */
	IR_ADC->data_value = 15.714 * IR_ADC->voltage;
}
