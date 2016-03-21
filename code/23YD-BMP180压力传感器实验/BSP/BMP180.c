/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��BMP180.c
 * ����    ����ʼ��BMP180��һЩ�����Ĳ��� 
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������: PB6-I2C1_SCL��PB7-I2C1_SDA
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/

//ͷ�ļ�
#include "BMP180.h"
#include "usart.h"
#include "math.h"
#include "i2c.h"

u32 Air_pressure=0;

 /**
  * @file   Delay_us(����ȷ)
  * @brief  ΢����ʱ time_ms ms
  * @param  time_us ��ʱʱ��
  * @retval NO
  */
static void delay_us( uint16_t time_us )
{
  uint16_t i,j;
  for( i=0;i<time_us;i++ )
  {
		for( j=0;j<11;j++ );//1us
  }
}
 /**
  * @file   Delay_Ms(����ȷ)
  * @brief  ������ʱ time_ms ms
  * @param  time_ms ��ʱʱ��
  * @retval NO
  */
static void delay_ms(uint16_t time_ms)
{
	 uint16_t i;
  for( i=0;i<time_ms;i++ )
  {
		delay_us(11000);
  }
	
}
/**
  * @file   BMP180_IIC_WriteByte
  * @brief  ��BMP180дһ�ֽ�����
  * @param  
	*          - SendByte: ��д������
	*          - WriteAddress: ��д���ַ
  * @retval ����Ϊ:=1�ɹ�д��,=0ʧ��
  */
FunctionalState BMP180_IIC_WriteByte(uint8_t WriteAddress,uint8_t SendByte)
{		
    if(!I2C_Start())return DISABLE;
    I2C_SendByte(0xee); 
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte(WriteAddress);   /* ���õ���ʼ��ַ */      
    I2C_WaitAck();	
    I2C_SendByte(SendByte);
    I2C_WaitAck();   
    I2C_Stop(); 
    return ENABLE;
}	
 /**
  * @file   BMP180_IIC_ReadByte
  * @brief  ��BMP180��ȡһ������
  * @param  
	*					- pBuffer: ��Ŷ�������
	*     	  - length: ����������
	*         - ReadAddress: ��������ַ
	*         - DeviceAddress: ��������(24c16��SD2403)
  * @retval ����Ϊ:=1�ɹ�����,=0ʧ��
  */
FunctionalState BMP180_IIC_ReadByte( uint8_t ReadAddress, uint16_t length  ,uint8_t* pBuffer)
{		

    if(!I2C_Start())return DISABLE;
    I2C_SendByte(0xee); /* ���ø���ʼ��ַ+������ַ */ 
    if(!I2C_WaitAck())
		{I2C_Stop(); return DISABLE;}
    I2C_SendByte(ReadAddress);   /* ���õ���ʼ��ַ */      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(0xef);
    I2C_WaitAck();
    while(length)
    {
      *pBuffer = I2C_ReceiveByte();
      if(length == 1)
				I2C_NoAck();
      else I2C_Ack(); 
      pBuffer++;
      length--;
    }
    I2C_Stop();
    return ENABLE;
}
/**
  * @file   BMP180_Init
  * @brief  BMP180��ʼ��
  * @param  ��
  * @retval ��
  */
void BMP180_Init(void)
{
		u8 data[1]={0};		
		BMP180_IIC_ReadByte (0xd0,1,data);
		if(data[0]==0x55)
		printf("BMP180ok\r\n\n");
		else
		printf("BMP180error\r\n\n");	
}

/**
  * @file   BMP180_Calc
  * @brief  BMP180�����ѹ����
  * @param  ��
  * @retval ��ѹ����
  */
u32 BMP180_Calc(void)
{
  vu16 x=0,y=0,z=0;
	double angle=0;
	u8 data[22]={0};	
	short AC1=0,AC2=0,AC3=0,B1=0,B2=2,MB=0,MC=0,MD=0;
	unsigned short AC4=0,AC5=0,AC6=0;
  u8 dataUT[2]={0};
	long UT=0;
	long UP=0;  
	u8 dataUP[3]={0};
	long X1=0,X2=0,B5=0,temp=0;
	long B6=0,X3=0,B3=0,p=0;
	unsigned long B4=0,B7=0;



  BMP180_IIC_ReadByte (0xaa,22,data);
	AC1=((data[0]<<8)+data[1]);
	AC2=((data[2]<<8)+data[3]);
	AC3=((data[4]<<8)+data[5]);
	AC4=((data[6]<<8)+data[7]);
	AC5=((data[8]<<8)+data[9]);
	AC6=((data[10]<<8)+data[11]);
	B1=((data[12]<<8)+data[13]);
	B2=((data[14]<<8)+data[15]);
	MB=((data[16]<<8)+data[17]);		 
	MC=((data[18]<<8)+data[19]);
	MD=((data[20]<<8)+data[21]);
  BMP180_IIC_WriteByte(0xf4,0x2e);
	delay_ms(10);
	BMP180_IIC_ReadByte (0xf6,2,dataUT);
	UT=((((u32)dataUT[0])<<8)|(u32)dataUT[1]);	
	BMP180_IIC_WriteByte(0xf4,0x34);
	delay_ms(5);
	BMP180_IIC_ReadByte (0xf6,2,dataUP);
	UP=((((u32)dataUP[0])<<16)+((u32)dataUP[1]<<8)+(u32)dataUP[0])>>8;	
	X1=((UT-AC6)*AC5)>>15;
	X2=(MC<<11)/(X1+MD);
	B5=X1+X2;
	temp=(B5+8)>>4;
	
	//printf("%ld\r\n",temp);//����¶�

  B6=B5-4000;
	X1=(B2*((B6*B6)>>12))>>11;
	X2=(AC2*B6)>>11;
	X3=X1+X2;
	B3=(((AC1*4+X3)<<0)+2)/4;
	X1=(AC3*B6)>>13;
	X2=(B1*((B6*B6)>>12))>>16;
	X3=((X1+X2)+2)>>2;
	B4=(AC4*(unsigned long)(X3+32768))>>15;
	B7=((unsigned long)UP-B3)*(50000>>0);
	if(B7<0x80000000){p=(B7*2)/B4;}
	else
	{p=(B7/B4)*2;}
	X1=(p>>8)*(p>>8);
	X1=(X1*3038)>>16;
	X2=(-7357*p)>>16;
	Air_pressure=p+((X1+X2+3791)>>4);
	
	return Air_pressure;
}
/**
  * @file   BMP180_TEST
  * @brief  BMP180������ѹ�������ѹ����
  * @param  ��
  * @retval ��
  */
void BMP180_TEST(void)
{
		BMP180_Calc();
		printf("Air_pressure=%ld\r\n",Air_pressure);//�����ѹ	

}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
