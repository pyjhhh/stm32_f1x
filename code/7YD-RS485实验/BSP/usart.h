#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

#define BaudRate	 9600

#define USART              		USART3
#define USART_RCC         	 	RCC_APB1Periph_USART3

#define USART_GPIO_RCC    		RCC_APB2Periph_GPIOB
#define USART_TX		        	GPIO_Pin_10	// out
#define USART_RX		        	GPIO_Pin_11	// in 
#define USART_GPIO_PORT    		GPIOB
#define USART_IPQn   		      USART3_IRQn 


#define RS485_DE_GPIO_RCC     RCC_APB2Periph_GPIOB
#define RS485_DE_GPIO_PORT    GPIOB
#define RS485_DE_GPIO_PIN     GPIO_Pin_12
#define DIR485_Receive()    	GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define DIR485_Send()       	GPIO_SetBits(GPIOB,GPIO_Pin_12)

void USART3_Config(void);
void USART3_IRQHandler(void);
void NVIC_Configuration(void);
#endif
