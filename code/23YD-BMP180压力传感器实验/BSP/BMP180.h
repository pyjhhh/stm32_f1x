#ifndef __BMP180_H
#define __BMP180_H			 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"


void BMP180_TEST(void);
FunctionalState BMP180_IIC_WriteByte(uint8_t WriteAddress,uint8_t SendByte);
FunctionalState BMP180_IIC_ReadByte( uint8_t ReadAddress, uint16_t length  ,uint8_t* pBuffer);
u32 BMP180_Calc(void);
void BMP180_Init(void);
#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
