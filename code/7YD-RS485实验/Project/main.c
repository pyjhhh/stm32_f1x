/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ��ͨ������3��ӡ����Լ�������ַ�������������ϢΪ��9600��N,8��1��  
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


/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    USART3_Config();//���ڲ������ó�ʼ��
    NVIC_Configuration();//�ж��������ó�ʼ��
    printf("*************************************************************\r\n");
    printf("*                                                           *\r\n");
    printf("* Thank you for using The Development Board Of YuanDi ! ^_^ *\r\n");
    printf("*                                                           *\r\n");
    printf("*************************************************************\r\n");
    while (1)
		{
		
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





