#include "INA226.h"
#include "ADS1115.h"

//向ADS1115写入2个字节数据，失败返回1，成功返回0
u8 ADSWriteReg(u8 regAddr, u16 setValue,u8 ADS1115_ADDRESS)
{
	u8 res;
	IIC_Start();                    //起始信号
	res = IIC_Send_Byte(ADS1115_ADDRESS);    //发送设备地址+写信号
	res = IIC_Send_Byte(regAddr);     //发送存储单元地址，从0开始
	res = IIC_Send_Byte(setValue >> 8);
	res = IIC_Send_Byte(setValue);
	IIC_Stop();            //发送停止信号
	return res;
}

//**************************************
//从ADS1115读2字节数据
//**************************************
s16 ADSReadReg(u8 regAddr,u8 ADS1115_ADDRESS)
{
	u8 res, H, L;
	IIC_Start();                    //起始信号
	res = IIC_Send_Byte(ADS1115_ADDRESS);    //发送设备地址+写信号	//0.04ms
	res = IIC_Send_Byte(regAddr);     //发送存储单元地址，从0开始  //0.04ms
	IIC_Start();                    //起始信号
	res = IIC_Send_Byte(ADS1115_ADDRESS + 1);    //发送设备地址+读信号	//0.04ms
	H = IIC_Read_Byte(1);             //读数据,应答    //0.04ms
	L = IIC_Read_Byte(0);             //读数据，不应答   //0.04ms
	IIC_Stop();            //发送停止信号
	return (s16) ((((u16) H) << 8) + L);     //合成数据
}


//初始化ADS1115


s16 InitADS1115(void)
{
	
	ADSWriteReg(ADS1115_conf,0x42e0,ADS1115_adds);//量程±4.096，采样率860sps,测量A0-GND

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
*函数名称:  ADS1115Config
*描    述： 设置ADS1115包括通道配置，采样时间等等
*参    数： HCMD ：命令字高8位(通道，量程，转换模式)
   LCMD : 命令字低8位(采样率设置 比较模式 有效电平 信号输出锁存)
*返    回； 无
********************************************************************/
/*
void ADS1115Config()//配置寄存器
{
 I2CStart();
    I2CWriteByte(WR_REG);  // 地址0x90  器件ADR接地 写寄存器
 delay(50);
 I2CWriteByte(CONF_REG);// 地址0x01  指向配置寄存器
 delay(50);
 I2CWriteByte(0xd2);  //设置配置寄存器的高八位1101 0010，即AINp=AIN1,AINn=GND;满量程FS=+-4.096；连续转换模式  
 delay(50); 
 I2CWriteByte(0xe3); //设置配置寄存器的低八位1100 0101 
 delay(50);
 I2CStop();
}

//配置指针寄存器
void PointRegister (void) 
 {      
      I2CStart();                   
      I2CWriteByte(0x90);//写    
      delay(50);
      I2CWriteByte(0x00);//指针指向转换寄存器      
      delay(50);
      I2CStop();          // Send I2C Stop Transfer
 } 
*/
 