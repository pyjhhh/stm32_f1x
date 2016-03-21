/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��usart.c
 * ����    ����printf�����ض���USART2�������Ϳ�����printf��������Ƭ�������ݴ�
 *           ӡ��PC�ϵĳ����ն˻򴮿ڵ������֡�     
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������: TX->PA2;RX->PA3
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/	

//ͷ�ļ�
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
  * @brief  USART2 GPIO ����,����ģʽ���á�9600-8-N-1
  * @param  ��
  * @retval ��
  */
void USART2_Config(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;	
  USART_InitTypeDef USART_InitStructure;  //���崮�ڳ�ʼ���ṹ��
  RCC_APB2PeriphClockCmd(USART_GPIO_RCC,ENABLE);	
  RCC_APB1PeriphClockCmd(USART_RCC,ENABLE);
 
  /*USART2_TX ->PA2*/			
  GPIO_InitStructure.GPIO_Pin = USART_TX;	       //ѡ�д���Ĭ������ܽ�         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�������������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ܽ�2��ģʽ  
  GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);           //���ú������ѽṹ�����������г�ʼ��		   
  /*USART2_RX ->PA3*/
  GPIO_InitStructure.GPIO_Pin = USART_RX;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);
  /*����ͨѶ��������*/
  USART_InitStructure.USART_BaudRate = BaudRate; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;		//У��λ ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//ʹ�ܽ��պͷ�������
   /*�����ϸ���ֵ�Ľṹ�����⺯��USART_Init���г�ʼ��*/
  USART_Init(USART, &USART_InitStructure); 
	USART_ITConfig(USART,USART_IT_RXNE,ENABLE);//ʹ�ܴ����жϽ���
  USART_Cmd(USART, ENABLE);//����USART2
}

 /**
  * @file   NVIC_Configuration
  * @brief  �ж���������
  * @param  ��
  * @retval ��
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
  * @brief  �жϴ�����
  * @param  ��
  * @retval ��
  */
void USART2_IRQHandler(void)
{
  u8 c;
  if(USART_GetITStatus(USART, USART_IT_RXNE) != RESET)
  { 	
    c=USART_ReceiveData(USART);
    printf("%c",c);    //�����ܵ�������ֱ�ӷ��ش�ӡ
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







