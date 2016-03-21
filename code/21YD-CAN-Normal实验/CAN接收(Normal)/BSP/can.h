#ifndef __CAN_H
#define __CAN_H

#include "stm32f10x.h"

#define CANx                           CAN1
#define CANx_RCC                       RCC_APB1Periph_CAN1

#define CANx_GPIO_RCC    		           RCC_APB2Periph_GPIOB
#define CANx_TX		        	           GPIO_Pin_9	// out
#define CANx_RX		        	           GPIO_Pin_8	// in 
#define CANx_GPIO_PORT    	           GPIOB   
#define GPIO_Remap1_CANx    	           GPIO_Remap1_CAN1   


void GPIO_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
void CAN_Configuration(void);
void CanWriteData(uint16_t ID);
#endif
