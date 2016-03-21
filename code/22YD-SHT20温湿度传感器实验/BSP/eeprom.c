/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��eeprom.c
 * ����    ����ʼ��IIC��һЩ�����Ĳ��� 
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������: PB6-I2C1_SCL��PB7-I2C1_SDA
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/

//ͷ�ļ�
#include "eeprom.h"
#include "usart.h"
#include "i2c.h"
/**
  * @file   I2C_WriteByte
  * @brief  дһ�ֽ�����
  * @param  
	*          - SendByte: ��д������
	*          - WriteAddress: ��д���ַ
  * @retval ����Ϊ:=1�ɹ�д��,=0ʧ��
  */
FunctionalState I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress)
{		
    if(!I2C_Start())return DISABLE;
    I2C_SendByte((((WriteAddress & 0x0700) >>7) | 0xA0) & 0xFFFE); /*���ø���ʼ��ַ+������ַ */
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte((uint8_t)(WriteAddress & 0x00FF));   /* ���õ���ʼ��ַ */      
    I2C_WaitAck();	
    I2C_SendByte(SendByte);
    I2C_WaitAck();   
    I2C_Stop(); 
    return ENABLE;
}									 

 /**
  * @file   I2C_ReadByte
  * @brief  ��ȡһ������
  * @param  
	*					- pBuffer: ��Ŷ�������
	*     	  - length: ����������
	*         - ReadAddress: ��������ַ
	*         - DeviceAddress: ��������(24c16��SD2403)
  * @retval ����Ϊ:=1�ɹ�����,=0ʧ��
  */
FunctionalState I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress)
{		
    if(!I2C_Start())return DISABLE;
    I2C_SendByte((((ReadAddress & 0x0700) >>7) | 0xA0) & 0xFFFE); /* ���ø���ʼ��ַ+������ַ */ 
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte((uint8_t)(ReadAddress & 0x00FF));   /* ���õ���ʼ��ַ */      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(((ReadAddress & 0x0700) >>7) | 0xA0 | 0x0001);
    I2C_WaitAck();
    while(length)
    {
      *pBuffer = I2C_ReceiveByte();
      if(length == 1)I2C_NoAck();
      else I2C_Ack(); 
      pBuffer++;
      length--;
    }
    I2C_Stop();
    return ENABLE;
}

/**
  * @file   I2C_Test
  * @brief  I2C(AT24C08)��д���ԡ�
  * @param  ��
  * @retval ��
  */
void I2C_Test(void)
{
		uint16_t Addr;
		uint8_t WriteBuffer[256],ReadBuffer[256];
		for(Addr=0; Addr<256; Addr++)
	  {
			WriteBuffer[Addr]=Addr;	 /* ���WriteBuffer */
			printf("0x%02x ",WriteBuffer[Addr]);
				if(Addr%16 == 15)    
		printf("\n\r");
		
    }
		/* ��ʼ��EEPROMд���� */
		printf("\r\n EEPROM 24C08 Write Test \r\n");
		for(Addr=0; Addr<256; Addr++)
		while( !I2C_WriteByte(WriteBuffer[Addr], Addr) );
		printf("\r\n EEPROM Write Test OK \r\n");

		/* EEPROM������ */
		printf("\r\n EEPROM 24C08 Read Test \r\n");
		I2C_ReadByte(ReadBuffer, sizeof(WriteBuffer),0);
    for(Addr=0; Addr<256; Addr++)
		{
		   printf("0x%02x ",ReadBuffer[Addr]);
				if(Addr%16 == 15)    
		printf("\n\r");
		}

		if(  memcmp(WriteBuffer,ReadBuffer,sizeof(WriteBuffer)) == 0 ) /* ƥ������ */
		printf("\r\n EEPROM 24C08 Read Test OK\r\n");
		else
		printf("\r\n EEPROM 24C08 Read Test False\r\n");
}
 


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
