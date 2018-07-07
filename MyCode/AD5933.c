#include "AD5933.h"
#include "delay.h"
#include "MYIIC.h"
#define Delay_IIC 1
#define AD5933 1
#define AD5933_MCLK 16.776  //=536870912/MCLK;
//#define	AD5933_MCLK_USE_OUT	1	//0�ڲ�ʱ��  1�ⲿʱ��
#define AD5933_Correction 101615461.47044108



/*
void Ini_I2c( void )      //��ʼ��I2C
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_11|GPIO_Pin_12); 	//PB10,PB11 �����  

	
	

	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStructure);
	//GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
	
    return;
}


void NOPS(void) 
{
	delay_us(1);
} 
void SDA_1( void )
{
//    SDA_OUT();		//��SDA����Ϊ���ģʽ
    SDA=1;		//SDA�ܽ����Ϊ�ߵ�ƽ    
    NOPS();
    return;
}

void SDA_0 ( void )
{
//    SDA_OUT();		//��SDA����Ϊ���ģʽ
    SDA=0;	//SDA�ܽ����Ϊ�͵�ƽ    
    NOPS();
    return;
}

void SCL_1( void )
{
     		//��SCL����Ϊ���ģʽ
    SCL=1;		//SCL�ܽ����Ϊ�ߵ�ƽ    
    NOPS();
    return;
}

void SCL_0 ( void )
{
    		//��SCL����Ϊ���ģʽ
    SCL=0;	//SCL�ܽ����Ϊ�͵�ƽ    
    NOPS();
    return;
}

void GetACK(void)
{   
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	SDA=1;delay_us(Delay_IIC*1);	   
	SCL=1;delay_us(Delay_IIC*1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			STOP();
			return;
		}
	}
	SCL=0;//ʱ�����0 	
}

void SendNACK(void)
{
	SCL=0;
	SDA_OUT();
	SDA=1;
	delay_us(Delay_IIC*2);
	SCL=1;
	delay_us(Delay_IIC*2);
	SCL=0;
}
*/

void Write_Byte(char nAddr,uint nValue)//nAddr��д���ֽ�nValue
{   
	int nTemp = 0x1A;      // AD5933��Ĭ�ϵ�ַ&д����λ���ͣ�
  //START(); 
	IIC_Start();
	//SendByte(nTemp);     // ���͵�ַ	
	IIC_Send_Byte(nTemp);
	//GetACK();   
	
	//SendByte(nAddr);     // ���͵�ַ�ֽ�
	IIC_Send_Byte(nAddr);
	//GetACK();
	
	//SendByte(nValue);	// ���������ֽ�	
	IIC_Send_Byte(nValue);	
	//GetACK();
		
	//STOP();	// ֹͣ����	
	IIC_Stop();	
  return;
}

void SetPointer(char nAddr)  //   ���õ�ַָ��
{          
	int nTemp = 0x1A;      // AD5933��Ĭ�ϵ�ַ&д����λ���ͣ�
	
  //START(); 
	IIC_Start();
	//SendByte(nTemp);     // ���͵�ַ	
	IIC_Send_Byte(nTemp);
	//GetACK();     // �ȴ� ACK		

	//SendByte(0xB0);     // ����ָ������1101 0000
	IIC_Send_Byte(0xB0);
	//GetACK();

	//SendByte(nAddr);	// ���͵�ַָ��	
	IIC_Send_Byte(nAddr);
	//GetACK();	

	//STOP();	// ֹͣ����
	IIC_Stop();	
   	return;
}

int Rece_Byte(char nAddr)//��ȡnAddr�е��ֽڵ�����ֵ
{   
	int nTemp ;    
  SetPointer(nAddr);   //��ַָ��ָ��nAddr
  nTemp=0x1B;      // AD5933��Ĭ�ϵ�ַ&������λ���ߣ�
  //START(); 
	IIC_Start();
	//SendByte(nTemp);     // ���͵�ַ	
	IIC_Send_Byte(nTemp);
	//GetACK();  

	nTemp=IIC_Read_Byte(0);//ReadByte();//��һ���ֽ�����		
	//SendNACK();//����NO_ACK
	
	//STOP();	// ֹͣ����	
IIC_Stop();		
	return nTemp;
}


u16 AD5933_Tempter(void)
{
 
// unsigned char Status;  //����״̬
 unsigned int Tm;   //����ʵ�����鲿���¶�
 
 
//   //��λAD5933
//   Write_Byte(0x80,0XB1);
//   Write_Byte(0x81,0X00);
    
   //�����¶Ȳ���
   Write_Byte(0x80,0x93);
    
   //�ȴ�ת�����
//   do
//    {
// 
//     Status=Rece_Byte(0x8F);
//  
//}while(!(Status & 0x01));
   //�����¶ȣ�������Tm��
   Tm=Rece_Byte(0x92);
   Tm<<=8;
   Tm+=Rece_Byte(0x93);
   Tm<<=2;

		return Tm;
}

//float Scale_imp (uint SValue[3],uint IValue[3],uint NValue[2],uint CValue[2],float ki,int Ps);
float resistance[200];
float rads[200];
int 	AD5933_Dat_Re[200];
int 	AD5933_Dat_Im[200];
u8 Gain;


void Maopao_Paixu(float *dat, u16 leng)
{
	u16 i,j;
	float buf;
	for(j=0;j<leng-1;j++)
	for(i=0;i<leng-j-1;i++)
	if(dat[i]>dat[i+1]){
	buf=dat[i];
	dat[i]=dat[i+1];
	dat[i+1]=buf;
	}
}

float Get_resistance(u16 num)
{
	u16 i;
	float navle;
	Maopao_Paixu(resistance,num);
	navle=resistance[0];

	for(i=num/2-num/4;i<num/2+num/4;i++)
	{
		navle=(navle+resistance[i])/2;
	}
	
	return navle*AD5933_Correction;
}
void Fre_To_Hex(float fre,u8 *buf)
{
	u32 dat;
	dat=(536870912/(double)(AD5933_MCLK*1000000))*fre;
	buf[0]=dat>>16;
	buf[1]=dat>>8;
	buf[2]=dat;

}
/*Fre_Begin��ʼƵ�ʣ�Fre_UPƵ��������UP_Num��������OUTPUT_Vatage�����ѹ��Gain����ϵ����SWeep_RepɨƵΪ1�ظ�Ϊ0*/

/*
Fre_Begin 		��ʼƵ�� ��HZ��
Fre_UP				����Ƶ�ʣ�HZ��
UP_Num				��������
OUTPUT_Vatage	�����ѹ
								AD5933_OUTPUT_2V
								AD5933_OUTPUT_1V
								AD5933_OUTPUT_400mV
								AD5933_OUTPUT_200mV
								
Gain					PGA����			
							AD5933_Gain_1
							AD5933_Gain_5
SWeep_Rep			ɨ��ģʽ
							AD5933_Fre_UP 	����Ƶ��
							AD5933_Fre_Rep	�ظ�Ƶ��
*/

//AD5933_Sweep(30000,200,200,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);
float AD5933_Sweep (float Fre_Begin,float Fre_UP,u16 UP_Num,u16 OUTPUT_Vatage,u16 Gain,u16 SWeep_Rep)
{
	u8 SValue[3], IValue[3], NValue[2], CValue[2];
	u16 buf=0;
	Fre_To_Hex(Fre_Begin,SValue);
	Fre_To_Hex(Fre_UP,IValue);
	NValue[0]=UP_Num>>8;
	NValue[1]=UP_Num;
#ifdef AD5933_MCLK_USE_OUT
	buf=OUTPUT_Vatage|Gain|SWeep_Rep|AD5933_OUT_MCLK;
#else
		buf=OUTPUT_Vatage|Gain|SWeep_Rep|AD5933_IN_MCLK;
#endif
	CValue[0]=buf>>8;
	CValue[1]=buf;
	
	Scale_imp(SValue,IValue,NValue,CValue);
	return 0;
}
/*SValue[3]��ʼƵ�ʣ�IValue[3]Ƶ��������NValue[2]��������CValue[2]�����֣�ki����ϵ����PsɨƵΪ1�ظ�Ϊ0*/

float Scale_imp (u8 *SValue,u8 *IValue,u8 *NValue,u8 *CValue)
{
	int i,j,AddrTemp;
	u8 Gain=((~CValue[0])&0x01)?5:1;
	//u8 SWeep_Rep=((CValue[0]&0xF0)==(AD5933_Fre_UP>>8))?1:0;
	u8 SWeep_Rep=0;
	u8 Mode=CValue[0]&0x0f;
	long ReadTemp,realArr[3],imageArr[3];
                float magnitude;       	
//                uint start_f[3]={0X33,0X26,0X17};
//                uint inc_f[3]={0,0,0X21};
//                uint num_f[2]={0,0XC8};
//                uint control[2]={0XB1,0X00};
//								CValue[0]=Mode|AD5933_Standby;
								j=0;

               // Ini_I2c();    //��ʼ��I2C
   
                AddrTemp=0X82; //��ʼ����ʼƵ�ʼĴ���
                for(i = 0;i <3;i++)
                {
    	Write_Byte(AddrTemp,SValue[i]);
                AddrTemp++;
                }               
                AddrTemp=0X85; //��ʼ��Ƶ�������Ĵ���
                for(i = 0;i <3;i++)
                {
    	Write_Byte(AddrTemp,IValue[i]);
                AddrTemp++;
                } 
                AddrTemp=0X88; //��ʼ��Ƶ�ʵ����Ĵ���
                for(i = 0;i <2;i++)
                {
    	Write_Byte(AddrTemp,NValue[i]);
                AddrTemp++;
                } 
    //��ʼ�����ƼĴ�����1011 0001 0000 0000����ģʽ��2V��һ���Ŵ��ڲ�ʱ��                                  
                AddrTemp=0X80; 
//                for(i = 0;i <2;i++)
                {
								Write_Byte(AddrTemp,Mode|(AD5933_Standby>>8));
                AddrTemp++;
								Write_Byte(AddrTemp,CValue[1]);
                AddrTemp++;
                }
                 
                Write_Byte(0x80,Mode|(AD5933_SYS_Init>>8));//���ƼĴ���д���ʼ��Ƶ��ɨ������
								delay_ms(10);
                Write_Byte(0X80,Mode|(AD5933_Begin_Fre_Scan>>8));//���ƼĴ���д�뿪ʼƵ��ɨ������
								
while(1)
{
                while(1)
                {
                ReadTemp=Rece_Byte(0x8F);  //��ȡ״̬�Ĵ������DFT�Ƿ����
//							ReadTemp=ReadTemp&0x07;
                if (ReadTemp&0x02)
                break;
                }                  
                realArr[0]=Rece_Byte(0x94);
                realArr[1]=Rece_Byte(0x95);
                realArr[2]=realArr[0]*0x100+realArr[1];
                
                imageArr[0]=Rece_Byte(0x96);
                imageArr[1]=Rece_Byte(0x97);
                imageArr[2]=imageArr[0]*0x100+imageArr[1];      
								
								rads[j]=atan2(imageArr[2],realArr[2])-0.00143485062;

                
	if (realArr[2]>=0x8000)  //����ʵ����ԭ��(������λ�⣬ȡ����һ)
	{
                realArr[2]^=0xFFFF; 
                realArr[2]^=0x8000; 
								realArr[2]+=1;
                realArr[2]^=0x8000;
	}
	if (imageArr[2]>=0x8000)  //�����鲿��ԭ��(������λ�⣬ȡ����һ)
	{
                imageArr[2]^=0xFFFF; 
                imageArr[2]^=0x8000; 
								imageArr[2]+=1;
                imageArr[2]^=0x8000;
	}
								AD5933_Dat_Re[j]=realArr[2];
								AD5933_Dat_Im[j]=imageArr[2];
                magnitude=sqrt(realArr[2]*realArr[2]+imageArr[2]*imageArr[2]);  //ģֵ����              
                resistance[j++]=1/(magnitude*Gain);		 //�迹����
								

                ReadTemp=Rece_Byte(0x8F);  //��ȡ״̬�Ĵ������Ƶ��ɨ���Ƿ����
                if (ReadTemp&0x04)
                break;
                if (SWeep_Rep==1)
                Write_Byte(0X80,CValue[0]);	//���ƼĴ���д������Ƶ�ʣ�������һ��Ƶ�ʵ�)������
								else
								Write_Byte(0X80,CValue[0]);	//���ƼĴ���д���ظ���ǰƵ�ʵ�ɨ��	

}  
                Write_Byte(0X80,0XA1);	//�������ģʽ
return magnitude;
}


void AD5933_Init(float Freq, float Freq_Step, u16 Step_Num)
{
	int i,AddrTemp;
	u8 SValue[3], IValue[3], NValue[2];

	
	Fre_To_Hex(Freq,SValue); //��ʼƵ��
	Fre_To_Hex(Freq_Step,IValue);      //����Ƶ��
	NValue[0]=Step_Num>>8;
	NValue[1]=Step_Num;               //������

		AddrTemp=0X82; //��ʼ����ʼƵ�ʼĴ���
		for(i = 0;i <3;i++)
    {
    	Write_Byte(AddrTemp,SValue[i]);
      AddrTemp++;
     } 
								
		AddrTemp=0X85; //��ʼ��Ƶ�������Ĵ���
		for(i = 0;i <3;i++)
		{
    	Write_Byte(AddrTemp,IValue[i]);
			AddrTemp++;
		} 
								
		AddrTemp=0X88; //��ʼ��Ƶ�ʵ����Ĵ���
		for(i = 0;i <2;i++)
		{
    	Write_Byte(AddrTemp,NValue[i]);
			AddrTemp++;
		} 
		
    

		
		AddrTemp=0X80;
		Write_Byte(AddrTemp,0XB1);
		AddrTemp=0X81;
		Write_Byte(AddrTemp,0X80);//��ʼ�����ƼĴ�����1011 0001 0000 0000����ģʽ��2V��һ���Ŵ��ڲ�ʱ�� 
		
		AddrTemp=0X80;
		Write_Byte(AddrTemp,0X11);
		AddrTemp=0X81;
		Write_Byte(AddrTemp,0X80);//����ʼƵ�ʳ�ʼ������������
		
		delay_ms(10);
		AddrTemp=0X80;
		Write_Byte(AddrTemp,0X21);
		AddrTemp=0X81;
		Write_Byte(AddrTemp,0X80);//����Ƶ��ɨ��

		
}

float AD5933_GetResistance(void)
{
	float Rs,L,C;
	long ReadTemp,realArr[3],imageArr[3];
  float magnitude; 
	int j=0; 
	

		Write_Byte(0X80,0X41);
		Write_Byte(0X81,0X80);//�ظ�Ƶ��ɨ��
	
		while(1)
		{
			ReadTemp=Rece_Byte(0x8F);  //��ȡ״̬�Ĵ������DFT�Ƿ����
			if (ReadTemp&0x02)
			break;
		}  


		//��ȡ�Ĵ�����ȡʵ���鲿
		realArr[0]=Rece_Byte(0x94);
		realArr[1]=Rece_Byte(0x95);
		realArr[2]=realArr[0]*0x100+realArr[1];
                
		imageArr[0]=Rece_Byte(0x96);
		imageArr[1]=Rece_Byte(0x97);
		imageArr[2]=imageArr[0]*0x100+imageArr[1];      
								
		rads[j]=atan2(imageArr[2],realArr[2])-0.00143485062;

                
	if (realArr[2]>=0x8000)  //����ʵ����ԭ��(������λ�⣬ȡ����һ)
	{
                realArr[2]^=0xFFFF; 
                realArr[2]^=0x8000; 
								realArr[2]+=1;
                realArr[2]^=0x8000;
	}
	if (imageArr[2]>=0x8000)  //�����鲿��ԭ��(������λ�⣬ȡ����һ)
	{
                imageArr[2]^=0xFFFF; 
                imageArr[2]^=0x8000; 
								imageArr[2]+=1;
                imageArr[2]^=0x8000;
	}
		AD5933_Dat_Re[j]=realArr[2];
		AD5933_Dat_Im[j]=imageArr[2];
		magnitude=sqrt(realArr[2]*realArr[2]+imageArr[2]*imageArr[2]);  //ģֵ����              
		Rs=100000000/(magnitude);		 //�迹����
	  L=Rs*sin(rads[0])*1000/(2*3.1415926);
	
	
	return L;
}



float DA5933_Get_Rs(void)
{
	float Rs;//,re,im;
	
//	AD5933_Sweep(30000,200,2,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_Rep);
	//AD5933_Sweep(10000,1,40,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);
	AD5933_Sweep(50000,1,20,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);
	//Rs=Get_resistance(40);
	Rs=Get_resistance(20);
	//re=Rs*cos(rads[0]);
	//im=Rs*sin(rads[0]);
	return Rs;
}
float DA5933_Dat_Cap(float Fre)
{
	float pp;
//	float dat=3.1415926*2*Fre;
	float dat=1;
	pp=1000000*23.9999992/(AD5933_Dat_Re[0]*dat);
	return pp;
}

float DA5933_Get_Cap(float Fre)
{
//	float Cap,dat;
//	
//	AD5933_Sweep(30000,1,40,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);
//	Cap=DA5933_Get_Rs();
//	dat=1/(Cap*30000*2*3.1415926/100000000000000);
//	DA5933_Dat_Cap(30000);
//	
//	return Cap;
	
	//float Rs,re,im,cap;
	float Rs,im,cap;
	
//	AD5933_Sweep(30000,200,2,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_Rep);
	AD5933_Sweep(100000,1,20,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);
	Rs=Get_resistance(20);
//	re=Rs*cos(rads[0]);
	im=Rs*sin(rads[0]);
	cap=0.9442/(2*3.1415926*im/10000000);
	return cap;
	
	
}
float DA5933_Get_L(float Fre)
{
	float L;
	//float Rs,re,im;
	float Rs,im;
	
	AD5933_Sweep(100000,1,20,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);
	Rs=Get_resistance(20);
//	re=Rs*cos(rads[0]);
	im=Rs*sin(rads[0]);
	L=im*1000/(2*3.1415926);	
	return L;
}
//---------------------------------------------------------------------------------------------------------------------
// ����ԭ�Σ�void display(unsigned int re,unsigned int im)
// ������������ʾ������
// ����˵����unsigned int re,unsigned int im ,ʵ�����鲿
// ����ֵ����
//---------------------------------------------------------------------------------------------------------------------

/*
void display(signed int re,signed int im)
{
   unsigned char a[11],y=0,x=0,i=0;
   signed int  revalu=0,imvalu=0;
   float  valu=0;
   double xishu=0,regist;
   long  int ll;

   revalu=re;
   imvalu=im;  
   if(revalu&0x8000)           //�Ѵ����ŵĻ�����޷�������
   {
     revalu=(revalu-0x10000)*(-1);  
     x=1;
   }
   if(imvalu&0x8000)           //�Ѵ����ŵĻ�����޷�������
   {
     imvalu=(imvalu-0x10000)*(-1);
     y=1;
   }
   valu=sqrt(imvalu*imvalu+revalu*revalu);  //�����ֵ
   switch(j)
   {
     case 0:
            if((valu<13000)&&(valu>8000))
            {
                xishu=(1/(96.86810));            //����ϵ��
                xishu=(1/(xishu*valu))*100000+0.5;   //������ֵ
                ll=xishu-250;
                i=1;
            }
            break;
     case 1:
            if((valu<13000)&&(valu>1350))
            {
                xishu=(1/(13.33726));            //����ϵ��
                xishu=(1/(xishu*valu))*1000000+0.5;   //������ֵ
                ll=xishu-100;
                i=1;
            }
            break;
     case 3:
            if((valu<12000)&&(valu>1050))
            {
                xishu=(1/(10.398994));            //����ϵ��
                xishu=(1/(xishu*valu))*10000000+0.5;   //������ֵ
                ll=xishu;
                i=1;
            }
            break;
     case 4:
            if((valu<12000)&&(valu>1000))
            {
                xishu=(1/(96.736596));            //����ϵ��
                xishu=(1/(xishu*valu))*10000000+0.5;   //������ֵ
                ll=xishu;
                i=1;
            }
            break;
     case 5:
            if((valu<2130)&&(valu>1060))
            {
                xishu=(1/(21.006));            //����ϵ��
               xishu=(1/(xishu*valu))*100000000+0.5;   //������ֵ
               ll=xishu;
                i=1;
            }
            break;
     case 6:
            if((valu<4800)&&(valu>800))
            {
                xishu=(1/(96.527914));            //����ϵ��
                xishu=(1/(xishu*valu))*100000000+0.5;   //������ֵ
                ll=xishu;
                i=1;
            }
            break;
    default: 
            break;
   }
   if(i==1)                //������������ʾ��ֵ����λ
   {
     a[0]=ll/10000000+48;
     a[1]=ll%10000000/1000000+48;
     a[2]=ll%1000000/100000+48;
     a[3]=ll%100000/10000+48;
     a[4]=ll%10000/1000+48;
     a[5]='.';
     a[6]=ll%1000/100+48;
     a[7]=ll%100/10+48;
     a[8]=ll%100%10+48;
     a[9]='K';
     a[10]=0;
     LCD_WriteStr(4,2,a);
   
     regist=ll;
     if((y==0)&&(x==0))
     {
//���㲢��ʾ  atan2(float y, float x);  ��y/x�����ȱ�ʾ���ķ�����ֵ
       xishu=atan2(imvalu,revalu)*180/3.14+0.5;          
     }
     if((y==1)&&(x==0))
     {
        //���㲢��ʾ  atan2(float y, float x);  ��y/x�����ȱ�ʾ���ķ�����ֵ
       xishu=atan2((imvalu*(-1)),revalu)*180/3.14-0.5;         
       xishu=xishu+180;
     }
     if((y==1)&&(x==1))
     {
        //���㲢��ʾ  atan2(float y, float x);  ��y/x�����ȱ�ʾ���ķ�����ֵ
       xishu=atan2(imvalu,revalu)*180/3.14+0.5;          
       xishu=xishu+180;
     }
     if((y==0)&&(x==1)) 
     {
       xishu=atan2(imvalu,(revalu*(-1)))*180/3.14-0.5;          //���㲢��ʾ  atan2(float y, float x);  ��y/x�����ȱ�ʾ���ķ�����ֵ
       xishu=xishu+360;
     }
     if((ll<1000)&&(ll>400))                //��λ�������
       ll=xishu-89.5;
     if((ll<10000)&&(ll>=1000))
       ll=xishu-(-0.0012237*regist+91.46)+0.5;
     if((ll<100000)&&(ll>=10000))
       ll=xishu-(-0.0001515*regist+91.016)+0.5;
     if((ll<1000000)&&(ll>=100000))
       ll=xishu-(-0.0000179*regist+91.806)+0.5;
     if((ll<=2000000)&&(ll>=1000000))
       ll=xishu-(-0.000009675*regist+93.789)+0.5;
     if((ll<12000000)&&(ll>2000000))
       ll=xishu-(-0.00000256*regist+95.444)+0.5;
     if(ll<0)                     //�ж�����
     {
       ll=ll*(-1);
       a[0]='-';
       a[1]=ll/100+48;
       a[2]=ll%100/10+48;
       a[3]=ll%100%10+48;
       a[4]=0;
       LCD_WriteStr(4,3,a);
     }
     else
     {
     a[0]=' ';
     a[1]=ll/100+48;
     a[2]=ll%100/10+48;
     a[3]=ll%100%10+48;
     a[4]=0;
     LCD_WriteStr(4,3,a);
     }
   }
}

*/




