#ifndef __CAN_H
#define __CAN_H

#include "stm32f10x.h"




void GPIO_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
void CAN_Configuration(void);
void CanWriteData(uint16_t ID);
#endif
