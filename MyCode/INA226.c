#include "INA226.h"

//��INA226д��2���ֽ����ݣ�ʧ�ܷ���1���ɹ�����0
u8 INAWriteReg(u8 regAddr, u16 setValue,u8 INA226_ADDRESS)
{
	u8 res;
	IIC_Start();                    //��ʼ�ź�
	res = IIC_Send_Byte(INA226_ADDRESS);    //�����豸��ַ+д�ź�
	res = IIC_Send_Byte(regAddr);     //���ʹ洢��Ԫ��ַ����0��ʼ
	res = IIC_Send_Byte(setValue >> 8);
	res = IIC_Send_Byte(setValue);
	IIC_Stop();            //����ֹͣ�ź�
	return res;
}

//**************************************
//��INA226��2�ֽ�����
//**************************************
s16 INAReadReg(u8 regAddr,u8 INA226_ADDRESS)
{
	u8 H, L;
	IIC_Start();                    //��ʼ�ź�
	IIC_Send_Byte(INA226_ADDRESS);    //�����豸��ַ+д�ź�	//0.04ms
	IIC_Send_Byte(regAddr);     //���ʹ洢��Ԫ��ַ����0��ʼ  //0.04ms
	IIC_Start();                    //��ʼ�ź�
	IIC_Send_Byte(INA226_ADDRESS + 1);    //�����豸��ַ+���ź�	//0.04ms
	H = IIC_Read_Byte(1);             //������,Ӧ��    //0.04ms
	L = IIC_Read_Byte(0);             //�����ݣ���Ӧ��   //0.04ms
	IIC_Stop();            //����ֹͣ�ź�
	return (s16) ((((u16) H) << 8) + L);     //�ϳ�����
}

//��ʼ��INA226


s16 InitINA226(void)
{
	s16 result_Nylon = 0;
	s16 result_Metal = 0;
	result_Metal= INAReadReg(INA226_DIE_ID,0x80);     //��ȡ ID
	INAWriteReg(INA226_CONFIG,
			INA226_AVG_16 | INA226_VBUS_140uS | INA226_VSH_140uS
					| INA226_MODE_CONT_SHUNT_AND_BUS,0x80);     //��������
	INAWriteReg(INA226_CALIB, INA226_CALIB_VAL,0x80);
	
	result_Nylon= INAReadReg(INA226_DIE_ID,0x82);     //��ȡ ID
		INAWriteReg(INA226_CONFIG,
			INA226_AVG_16 | INA226_VBUS_1100uS | INA226_VSH_140uS
					| INA226_MODE_CONT_SHUNT_AND_BUS,0x82);     //��������
	INAWriteReg(INA226_CALIB, INA226_CALIB_VAL,0x82);
	return result_Metal+result_Nylon;
}


//��ȡ��������
float INA226GetData(INA226Typedef *ina226data,u8 INA226_ADDRESS)
{
	float resistance = 0;
	float R=1.08*.02;
	ina226data->VBUS = INAReadReg(INA226_BUSV,INA226_ADDRESS); //0.2ms
	ina226data->VSH = INAReadReg(INA226_SHUNTV,INA226_ADDRESS);
	ina226data->CURRENT = INAReadReg(INA226_CURRENT,INA226_ADDRESS);
	ina226data->POWER = INAReadReg(INA226_POWER,INA226_ADDRESS);
	
	switch(INA226_ADDRESS)
	{
		case 0x80:
		{		
			R=1.08*0.01;
		resistance = R * (0.00125 * ((float) ina226data->VBUS))
			/ (0.0000025 * (float) ina226data->VSH);
		}
		break;

		case 0x82:
		{		
			R=270;
		resistance = R * (0.00125 * ((float) ina226data->VBUS/6))
			/ (3.3-0.00125 * (float) ina226data->VBUS/6);
		}
		break;

	}
		

	if (resistance > 0)
		return resistance;
	else
		return -1;
}
