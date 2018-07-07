#include "INA226.h"

//向INA226写入2个字节数据，失败返回1，成功返回0
u8 INAWriteReg(u8 regAddr, u16 setValue,u8 INA226_ADDRESS)
{
	u8 res;
	IIC_Start();                    //起始信号
	res = IIC_Send_Byte(INA226_ADDRESS);    //发送设备地址+写信号
	res = IIC_Send_Byte(regAddr);     //发送存储单元地址，从0开始
	res = IIC_Send_Byte(setValue >> 8);
	res = IIC_Send_Byte(setValue);
	IIC_Stop();            //发送停止信号
	return res;
}

//**************************************
//从INA226读2字节数据
//**************************************
s16 INAReadReg(u8 regAddr,u8 INA226_ADDRESS)
{
	u8 H, L;
	IIC_Start();                    //起始信号
	IIC_Send_Byte(INA226_ADDRESS);    //发送设备地址+写信号	//0.04ms
	IIC_Send_Byte(regAddr);     //发送存储单元地址，从0开始  //0.04ms
	IIC_Start();                    //起始信号
	IIC_Send_Byte(INA226_ADDRESS + 1);    //发送设备地址+读信号	//0.04ms
	H = IIC_Read_Byte(1);             //读数据,应答    //0.04ms
	L = IIC_Read_Byte(0);             //读数据，不应答   //0.04ms
	IIC_Stop();            //发送停止信号
	return (s16) ((((u16) H) << 8) + L);     //合成数据
}

//初始化INA226


s16 InitINA226(void)
{
	s16 result_Nylon = 0;
	s16 result_Metal = 0;
	result_Metal= INAReadReg(INA226_DIE_ID,0x80);     //获取 ID
	INAWriteReg(INA226_CONFIG,
			INA226_AVG_16 | INA226_VBUS_140uS | INA226_VSH_140uS
					| INA226_MODE_CONT_SHUNT_AND_BUS,0x80);     //配置设置
	INAWriteReg(INA226_CALIB, INA226_CALIB_VAL,0x80);
	
	result_Nylon= INAReadReg(INA226_DIE_ID,0x82);     //获取 ID
		INAWriteReg(INA226_CONFIG,
			INA226_AVG_16 | INA226_VBUS_1100uS | INA226_VSH_140uS
					| INA226_MODE_CONT_SHUNT_AND_BUS,0x82);     //配置设置
	INAWriteReg(INA226_CALIB, INA226_CALIB_VAL,0x82);
	return result_Metal+result_Nylon;
}


//获取测量数据
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
