/******************** (C) COPYRIGHT  Ô´µØ¹¤×÷ÊÒ ********************************
 * ÎÄ¼þÃû  £ºusart.c
 * ÃèÊö    £º½«printfº¯ÊýÖØ¶¨Ïòµ½USART3¡£ÕâÑù¾Í¿ÉÒÔÓÃprintfº¯Êý½«µ¥Æ¬»úµÄÊý¾Ý´ò
 *           Ó¡µ½PCÉÏµÄ³¬¼¶ÖÕ¶Ë»ò´®¿Úµ÷ÊÔÖúÊÖ¡£     
 * ×÷Õß    £ºzhuoyingxingyu
 * ÌÔ±¦    £ºÔ´µØ¹¤×÷ÊÒhttp://vcc-gnd.taobao.com/
 * ÂÛÌ³µØÖ·£º¼«¿ÍÔ°µØ-Ç¶ÈëÊ½¿ª·¢ÂÛÌ³http://vcc-gnd.com/
 * °æ±¾¸üÐÂ: 2015-10-20
 * Ó²¼þÁ¬½Ó: TX->PB10;RX->PB11
 * µ÷ÊÔ·½Ê½£ºJ-Link-OB
**********************************************************************************/	

//Í·ÎÄ¼þ
#include "usart.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

 

 /**
  * @file   USART3_Config
  * @brief  USART3 GPIO ÅäÖÃ,¹¤×÷Ä£Ê½ÅäÖÃ¡£9600-8-N-1
  * @param  ÎÞ
  * @retval ÎÞ
  */
void USART3_Config(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;	
  USART_InitTypeDef USART_InitStructure;  //¶¨Òå´®¿Ú³õÊ¼»¯½á¹¹Ìå
  RCC_APB2PeriphClockCmd( USART_GPIO_RCC|RS485_DE_GPIO_RCC , ENABLE);
  RCC_APB1PeriphClockCmd( USART_RCC , ENABLE);
  /*DE*/
  GPIO_InitStructure.GPIO_Pin = RS485_DE_GPIO_PIN;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(RS485_DE_GPIO_PORT, &GPIO_InitStructure);	
  /*USART3_TX ->PB10*/			
  GPIO_InitStructure.GPIO_Pin = USART_TX;	       //Ñ¡ÖÐ´®¿ÚÄ¬ÈÏÊä³ö¹Ü½Å         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¶¨ÒåÊä³ö×î´óËÙÂÊ 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//¶¨Òå¹Ü½Å9µÄÄ£Ê½  
  GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);           //µ÷ÓÃº¯Êý£¬°Ñ½á¹¹Ìå²ÎÊýÊäÈë½øÐÐ³õÊ¼»¯		   
  /*USART3_RX ->PB11*/
  GPIO_InitStructure.GPIO_Pin = USART_RX;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);
  /*´®¿ÚÍ¨Ñ¶²ÎÊýÉèÖÃ*/
  USART_InitStructure.USART_BaudRate = BaudRate; //²¨ÌØÂÊ
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //Êý¾ÝÎ»8Î»
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//Í£Ö¹Î»1Î»
  USART_InitStructure.USART_Parity = USART_Parity_No;		//Ð£ÑéÎ» ÎÞ
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ÎÞÁ÷¿ØÖÆ
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//Ê¹ÄÜ½ÓÊÕºÍ·¢ËÍÒý½Å
  //½«ÒÔÉÏ¸³ÍêÖµµÄ½á¹¹Ìå´øÈë¿âº¯ÊýUSART_Init½øÐÐ³õÊ¼»¯
  USART_Init(USART, &USART_InitStructure); 
  USART_ITConfig(USART, USART_IT_RXNE, ENABLE);
  USART_ClearFlag(USART,USART_FLAG_TC);
  //USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//Ê¹ÄÜ´®¿ÚÖÐ¶Ï½ÓÊÕ
  USART_Cmd(USART, ENABLE);//¿ªÆôUSART3
}

 /**
  * @file   NVIC_Configuration
  * @brief  ÖÐ¶ÏÏòÁ¿ÅäÖÃ
  * @param  ÎÞ
  * @retval ÎÞ
  */
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART_IPQn;	 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @file   USART3_IRQHandler
  * @brief  ÖÐ¶Ï´¦Àíº¯Êý
  * @param  ÎÞ
  * @retval ÎÞ
  */
void USART3_IRQHandler(void)
{
    u8 c;
    if(USART_GetITStatus(USART, USART_IT_RXNE) != RESET)
    { 	
     c=USART_ReceiveData(USART);
      printf("%c",c);    //½«½ÓÊÜµ½µÄÊý¾ÝÖ±½Ó·µ»Ø´òÓ
    } 
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
	 DIR485_Send();
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART, (uint8_t) ch);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART, USART_FLAG_TC) == RESET)
  {
  }
  DIR485_Receive();
  return ch;
}







	




