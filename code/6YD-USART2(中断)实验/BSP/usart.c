/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：usart.c
 * 描述    ：将printf函数重定向到USART2。这样就可以用printf函数将单片机的数据打
 *           印到PC上的超级终端或串口调试助手。     
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 硬件连接: TX->PA2;RX->PA3
 * 调试方式：J-Link-OB
**********************************************************************************/	

//头文件
#include "usart.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


 /**
  * @file   USART2_Config
  * @brief  USART2 GPIO 配置,工作模式配置。9600-8-N-1
  * @param  无
  * @retval 无
  */
void USART2_Config(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;	
  USART_InitTypeDef USART_InitStructure;  //定义串口初始化结构体
  RCC_APB2PeriphClockCmd(USART_GPIO_RCC,ENABLE);	
  RCC_APB1PeriphClockCmd(USART_RCC,ENABLE);
 
  /*USART2_TX ->PA2*/			
  GPIO_InitStructure.GPIO_Pin = USART_TX;	       //选中串口默认输出管脚         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //定义输出最大速率 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//定义管脚2的模式  
  GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);           //调用函数，把结构体参数输入进行初始化		   
  /*USART2_RX ->PA3*/
  GPIO_InitStructure.GPIO_Pin = USART_RX;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);
  /*串口通讯参数设置*/
  USART_InitStructure.USART_BaudRate = BaudRate; //波特率
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//停止位1位
  USART_InitStructure.USART_Parity = USART_Parity_No;		//校验位 无
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无流控制
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//使能接收和发送引脚
   /*将以上赋完值的结构体带入库函数USART_Init进行初始化*/
  USART_Init(USART, &USART_InitStructure); 
	USART_ITConfig(USART,USART_IT_RXNE,ENABLE);//使能串口中断接收
  USART_Cmd(USART, ENABLE);//开启USART2
}

 /**
  * @file   NVIC_Configuration
  * @brief  中断向量配置
  * @param  无
  * @retval 无
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART_IPQn;	 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @file   USART2_IRQHandler
  * @brief  中断处理函数
  * @param  无
  * @retval 无
  */
void USART2_IRQHandler(void)
{
  u8 c;
  if(USART_GetITStatus(USART, USART_IT_RXNE) != RESET)
  { 	
    c=USART_ReceiveData(USART);
    printf("%c",c);    //将接受到的数据直接返回打印
  } 
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART, (uint8_t) ch);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART, USART_FLAG_TC) == RESET)
  {}
  return ch;
}







