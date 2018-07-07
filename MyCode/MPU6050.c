#include "MPU6050.h"

//向MPU写入一个字节数据，失败返回1，成功返回0
u8 MPUWriteReg(u8 regAddr, u8 setValue)
{
	u8 res;
	IIC_Start();                    //起始信号
	res = IIC_Send_Byte(MPU_SlaveAddress);    //发送设备地址+写信号
	res = IIC_Send_Byte(regAddr);     //发送存储单元地址，从0开始
	res = IIC_Send_Byte(setValue);       //内部寄存器数据，
	IIC_Stop();            //发送停止信号
	return res;
}

//**************************************
//从MPU读一个字节数据
//**************************************
u8 MPUReadReg(u8 regAddr, u8* readValue)
{
	u8 res;
	IIC_Start();                    //起始信号
	res = IIC_Send_Byte(MPU_SlaveAddress);    //发送设备地址+写信号
	res = IIC_Send_Byte(regAddr);     //发送存储单元地址，从0开始
	IIC_Start();                    //起始信号
	res = IIC_Send_Byte(MPU_SlaveAddress + 1);    //发送设备地址+读信号
	*readValue = IIC_Read_Byte(0);             //读数据，不应答
	IIC_Stop();            //发送停止信号
	return res;
}

//MPU 初始化
u8 InitMPU6050(void)
{
	u8 result;
	u8 id = 0;
	result = MPUReadReg(WHO_AM_I, &id);
	if (result)
		return 1;  //IIC总线错误
	else
	{
		id &= 0x7e;  //去除最高位和最低位
		id >>= 1;
		if (id != 0x34)
			return 1;    //获取的芯片ID错误
	}
	MPUWriteReg(PWR_MGMT_1, 0x00);	//解除休眠状态，设置取样时钟为陀螺x轴
	MPUWriteReg(SMPLRT_DIV, 0x07);           //陀螺仪采样率，典型值：0x07(125Hz)
	MPUWriteReg(CONFIG, 0x06);              //低通滤波频率，典型值：0x06(5Hz)
	MPUWriteReg(GYRO_CONFIG, 0x18);        //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	MPUWriteReg(ACCEL_CONFIG, 0x01);    //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
	return 0;
}

//**************************************
//合成数据,读两个字节
//**************************************
s16 MPU_ReadTwoByte(u8 REG_Address)
{
	u8 H, L;
	MPUReadReg(REG_Address, &H);
	MPUReadReg(REG_Address + 1, &L);
	return (s16) ((((u16) H) << 8) + L);     //合成数据
}

//获取测量数据
s16 MpuGetData(ACCELSTRUCT *accelStruct, GYROSTRUCT *gyroStruct)
{
	accelStruct->accelX = MPU_ReadTwoByte(ACCEL_XOUT_H);
	accelStruct->accelY = MPU_ReadTwoByte(ACCEL_YOUT_H);
	accelStruct->accelZ = MPU_ReadTwoByte(ACCEL_ZOUT_H);
	gyroStruct->gyroX = MPU_ReadTwoByte(GYRO_XOUT_H);
	gyroStruct->gyroY = MPU_ReadTwoByte(GYRO_YOUT_H);
	gyroStruct->gyroZ = MPU_ReadTwoByte(GYRO_ZOUT_H);
	return MPU_ReadTwoByte(TEMP_OUT_H);
}
