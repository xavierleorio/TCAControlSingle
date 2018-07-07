#include "MPU6050.h"

//��MPUд��һ���ֽ����ݣ�ʧ�ܷ���1���ɹ�����0
u8 MPUWriteReg(u8 regAddr, u8 setValue)
{
	u8 res;
	IIC_Start();                    //��ʼ�ź�
	res = IIC_Send_Byte(MPU_SlaveAddress);    //�����豸��ַ+д�ź�
	res = IIC_Send_Byte(regAddr);     //���ʹ洢��Ԫ��ַ����0��ʼ
	res = IIC_Send_Byte(setValue);       //�ڲ��Ĵ������ݣ�
	IIC_Stop();            //����ֹͣ�ź�
	return res;
}

//**************************************
//��MPU��һ���ֽ�����
//**************************************
u8 MPUReadReg(u8 regAddr, u8* readValue)
{
	u8 res;
	IIC_Start();                    //��ʼ�ź�
	res = IIC_Send_Byte(MPU_SlaveAddress);    //�����豸��ַ+д�ź�
	res = IIC_Send_Byte(regAddr);     //���ʹ洢��Ԫ��ַ����0��ʼ
	IIC_Start();                    //��ʼ�ź�
	res = IIC_Send_Byte(MPU_SlaveAddress + 1);    //�����豸��ַ+���ź�
	*readValue = IIC_Read_Byte(0);             //�����ݣ���Ӧ��
	IIC_Stop();            //����ֹͣ�ź�
	return res;
}

//MPU ��ʼ��
u8 InitMPU6050(void)
{
	u8 result;
	u8 id = 0;
	result = MPUReadReg(WHO_AM_I, &id);
	if (result)
		return 1;  //IIC���ߴ���
	else
	{
		id &= 0x7e;  //ȥ�����λ�����λ
		id >>= 1;
		if (id != 0x34)
			return 1;    //��ȡ��оƬID����
	}
	MPUWriteReg(PWR_MGMT_1, 0x00);	//�������״̬������ȡ��ʱ��Ϊ����x��
	MPUWriteReg(SMPLRT_DIV, 0x07);           //�����ǲ����ʣ�����ֵ��0x07(125Hz)
	MPUWriteReg(CONFIG, 0x06);              //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
	MPUWriteReg(GYRO_CONFIG, 0x18);        //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
	MPUWriteReg(ACCEL_CONFIG, 0x01);    //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
	return 0;
}

//**************************************
//�ϳ�����,�������ֽ�
//**************************************
s16 MPU_ReadTwoByte(u8 REG_Address)
{
	u8 H, L;
	MPUReadReg(REG_Address, &H);
	MPUReadReg(REG_Address + 1, &L);
	return (s16) ((((u16) H) << 8) + L);     //�ϳ�����
}

//��ȡ��������
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
