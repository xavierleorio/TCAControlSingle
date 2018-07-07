#include "INA226.h"
#include "ADS1115.h"

//��ADS1115д��2���ֽ����ݣ�ʧ�ܷ���1���ɹ�����0
u8 ADSWriteReg(u8 regAddr, u16 setValue,u8 ADS1115_ADDRESS)
{
	u8 res;
	IIC_Start();                    //��ʼ�ź�
	res = IIC_Send_Byte(ADS1115_ADDRESS);    //�����豸��ַ+д�ź�
	res = IIC_Send_Byte(regAddr);     //���ʹ洢��Ԫ��ַ����0��ʼ
	res = IIC_Send_Byte(setValue >> 8);
	res = IIC_Send_Byte(setValue);
	IIC_Stop();            //����ֹͣ�ź�
	return res;
}

//**************************************
//��ADS1115��2�ֽ�����
//**************************************
s16 ADSReadReg(u8 regAddr,u8 ADS1115_ADDRESS)
{
	u8 res, H, L;
	IIC_Start();                    //��ʼ�ź�
	res = IIC_Send_Byte(ADS1115_ADDRESS);    //�����豸��ַ+д�ź�	//0.04ms
	res = IIC_Send_Byte(regAddr);     //���ʹ洢��Ԫ��ַ����0��ʼ  //0.04ms
	IIC_Start();                    //��ʼ�ź�
	res = IIC_Send_Byte(ADS1115_ADDRESS + 1);    //�����豸��ַ+���ź�	//0.04ms
	H = IIC_Read_Byte(1);             //������,Ӧ��    //0.04ms
	L = IIC_Read_Byte(0);             //�����ݣ���Ӧ��   //0.04ms
	IIC_Stop();            //����ֹͣ�ź�
	return (s16) ((((u16) H) << 8) + L);     //�ϳ�����
}


//��ʼ��ADS1115


s16 InitADS1115(void)
{
	
	ADSWriteReg(ADS1115_conf,0x42e0,ADS1115_adds);//���̡�4.096��������860sps,����A0-GND

	return(ADSReadReg(ADS1115_conf,ADS1115_adds));
}


float ADS1115_Getdata(ADS1115Typedef *ads1115data)
{
	s16 Temp=0;
	s16 index[10];
	u8 i=0;
	float resistance;
	/*
	for(i=0;i<10;i++)
	{
		Temp=0;
		index[i]=ADSReadReg(ADS1115_conv,ADS1115_adds);
		Temp+=index[i];
	}
	Temp=Temp/10;
	*/
	Temp=ADSReadReg(ADS1115_conv,ADS1115_adds);
	if (Temp>0x7fff)
		Temp=~Temp+1;
	ads1115data->V0=4.096*Temp/32767;
	ads1115data->V1=0;
	ads1115data->V2=0;
	ads1115data->V3=0;
	resistance=47000*ads1115data->V0/(3.3-ads1115data->V0);
	return (resistance);
}






/*********************************************************************
*��������:  ADS1115Config
*��    ���� ����ADS1115����ͨ�����ã�����ʱ��ȵ�
*��    ���� HCMD �������ָ�8λ(ͨ�������̣�ת��ģʽ)
   LCMD : �����ֵ�8λ(���������� �Ƚ�ģʽ ��Ч��ƽ �ź��������)
*��    �أ� ��
********************************************************************/
/*
void ADS1115Config()//���üĴ���
{
 I2CStart();
    I2CWriteByte(WR_REG);  // ��ַ0x90  ����ADR�ӵ� д�Ĵ���
 delay(50);
 I2CWriteByte(CONF_REG);// ��ַ0x01  ָ�����üĴ���
 delay(50);
 I2CWriteByte(0xd2);  //�������üĴ����ĸ߰�λ1101 0010����AINp=AIN1,AINn=GND;������FS=+-4.096������ת��ģʽ  
 delay(50); 
 I2CWriteByte(0xe3); //�������üĴ����ĵͰ�λ1100 0101 
 delay(50);
 I2CStop();
}

//����ָ��Ĵ���
void PointRegister (void) 
 {      
      I2CStart();                   
      I2CWriteByte(0x90);//д    
      delay(50);
      I2CWriteByte(0x00);//ָ��ָ��ת���Ĵ���      
      delay(50);
      I2CStop();          // Send I2C Stop Transfer
 } 
*/
 