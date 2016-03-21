#ifndef __EEPROM_H
#define __EEPROM_H			 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"


void I2C_Test(void);
FunctionalState I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress);
FunctionalState I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress);
#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
