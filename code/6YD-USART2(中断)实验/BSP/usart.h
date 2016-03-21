#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

#define BaudRate	 9600

#define USART              	 USART2
#define USART_RCC         	 RCC_APB1Periph_USART2

#define USART_GPIO_RCC    		RCC_APB2Periph_GPIOA
#define USART_TX		        	GPIO_Pin_2	// out
#define USART_RX		        	GPIO_Pin_3	// in 
#define USART_GPIO_PORT    		GPIOA   

#define USART_IPQn   		      USART2_IRQn  


void USART2_Config(void);
void USART2_IRQHandler(void);
void NVIC_Configuration(void);

#endif
