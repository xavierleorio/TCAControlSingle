#include "CURRENT_SENSOR.h"

u16 CURRENT_SAMPLE_VALUE[10] =
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void CURRENT_SAMPLE(u8 index)
{
	CURRENT_SAMPLE_VALUE[index] = Get_Adc(ADC_Channel_2);
}
void Get_CURRENT_VALUE(ADC_Data *CURRENT_SENSOR_ADC)
{
	CURRENT_SENSOR_ADC->adc_digital = (CURRENT_SAMPLE_VALUE[0]
			+ CURRENT_SAMPLE_VALUE[1] + CURRENT_SAMPLE_VALUE[2]
			+ CURRENT_SAMPLE_VALUE[3] + CURRENT_SAMPLE_VALUE[4]
			+ CURRENT_SAMPLE_VALUE[5] + CURRENT_SAMPLE_VALUE[6]
			+ CURRENT_SAMPLE_VALUE[7] + CURRENT_SAMPLE_VALUE[8]
			+ CURRENT_SAMPLE_VALUE[9]) / 10;

	CURRENT_SENSOR_ADC->voltage = (float) CURRENT_SENSOR_ADC->adc_digital
			* (3.3 / 4096);

	CURRENT_SENSOR_ADC->data_value = 15.1 * CURRENT_SENSOR_ADC->voltage;
}