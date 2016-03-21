/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ��ͨ���δ�ʱ�Ӿ�ȷ������ʱ����������LED��(LED1->D1��LED2->D2,LED3->D4)
 * ��汾  ��V3.50
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/	

//ͷ�ļ�
#include "stm32f10x.h"
#include "usart.h"
#include "SYSTICK.h"
#include "led.h"



/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  USART1_Config();   //��ʼ������
  LED_GPIO_Config();//��ʼ��LED
  SYSTICK_Init();   //��ʼ��SYSTICK
  printf("*****************************************************************\r\n");
  printf("*                                                               *\r\n");
  printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
  printf("*                                                               *\r\n");
  printf("*****************************************************************\r\n");
  while (1)
  {
		LEDXToggle(LED1);
		LEDXToggle(LED2);
		LEDXToggle(LED3);
		delay_ms(500);
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





