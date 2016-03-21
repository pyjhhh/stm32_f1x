/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：eeprom.c
 * 描述    ：初始化IIC及一些基本的操作 
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 硬件连接: PB6-I2C1_SCL、PB7-I2C1_SDA
 * 调试方式：J-Link-OB
**********************************************************************************/

//头文件
#include "eeprom.h"
#include "usart.h"
#include "i2c.h"
/**
  * @file   I2C_WriteByte
  * @brief  写一字节数据
  * @param  
	*          - SendByte: 待写入数据
	*          - WriteAddress: 待写入地址
  * @retval 返回为:=1成功写入,=0失败
  */
FunctionalState I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress)
{		
    if(!I2C_Start())return DISABLE;
    I2C_SendByte((((WriteAddress & 0x0700) >>7) | 0xA0) & 0xFFFE); /*设置高起始地址+器件地址 */
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte((uint8_t)(WriteAddress & 0x00FF));   /* 设置低起始地址 */      
    I2C_WaitAck();	
    I2C_SendByte(SendByte);
    I2C_WaitAck();   
    I2C_Stop(); 
    return ENABLE;
}									 

 /**
  * @file   I2C_ReadByte
  * @brief  读取一串数据
  * @param  
	*					- pBuffer: 存放读出数据
	*     	  - length: 待读出长度
	*         - ReadAddress: 待读出地址
	*         - DeviceAddress: 器件类型(24c16或SD2403)
  * @retval 返回为:=1成功读入,=0失败
  */
FunctionalState I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress)
{		
    if(!I2C_Start())return DISABLE;
    I2C_SendByte((((ReadAddress & 0x0700) >>7) | 0xA0) & 0xFFFE); /* 设置高起始地址+器件地址 */ 
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte((uint8_t)(ReadAddress & 0x00FF));   /* 设置低起始地址 */      
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
  * @brief  I2C(AT24C08)读写测试。
  * @param  无
  * @retval 无
  */
void I2C_Test(void)
{
		uint16_t Addr;
		uint8_t WriteBuffer[256],ReadBuffer[256];
		for(Addr=0; Addr<256; Addr++)
	  {
			WriteBuffer[Addr]=Addr;	 /* 填充WriteBuffer */
			printf("0x%02x ",WriteBuffer[Addr]);
				if(Addr%16 == 15)    
		printf("\n\r");
		
    }
		/* 开始向EEPROM写数据 */
		printf("\r\n EEPROM 24C08 Write Test \r\n");
		for(Addr=0; Addr<256; Addr++)
		while( !I2C_WriteByte(WriteBuffer[Addr], Addr) );
		printf("\r\n EEPROM Write Test OK \r\n");

		/* EEPROM读数据 */
		printf("\r\n EEPROM 24C08 Read Test \r\n");
		I2C_ReadByte(ReadBuffer, sizeof(WriteBuffer),0);
    for(Addr=0; Addr<256; Addr++)
		{
		   printf("0x%02x ",ReadBuffer[Addr]);
				if(Addr%16 == 15)    
		printf("\n\r");
		}

		if(  memcmp(WriteBuffer,ReadBuffer,sizeof(WriteBuffer)) == 0 ) /* 匹配数据 */
		printf("\r\n EEPROM 24C08 Read Test OK\r\n");
		else
		printf("\r\n EEPROM 24C08 Read Test False\r\n");
}
 


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
