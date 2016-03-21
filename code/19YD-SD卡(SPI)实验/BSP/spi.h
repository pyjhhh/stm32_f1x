#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"
 	  
/**
  * @brief  SD SPI Interface pins
  */
#define SD_SPI                           SPI1
#define SD_SPI_RCC                     RCC_APB2Periph_SPI1

#define SD_SPI_SCK_PIN                   GPIO_Pin_5                /* PA.05 */
#define SD_SPI_SCK_GPIO_PORT             GPIOA                       /* GPIOA */
#define SD_SPI_SCK_GPIO_RCC              RCC_APB2Periph_GPIOA



#define SD_SPI_MISO_PIN                 GPIO_Pin_6                  /* PA.06 */
#define SD_SPI_MISO_GPIO_PORT           GPIOA                      /* GPIOA */
#define SD_SPI_MISO_GPIO_RCC            RCC_APB2Periph_GPIOA


#define SD_SPI_MOSI_PIN                  GPIO_Pin_7                 /* PA.07 */
#define SD_SPI_MOSI_GPIO_PORT            GPIOA                     /* GPIOA */
#define SD_SPI_MOSI_GPIO_RCC             RCC_APB2Periph_GPIOA


 
 				  	    													  
void SPIx_Init(void);			 //初始化SPI口
void SPIx_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPIx_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
		 
#endif

