/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ������S1��S2��S3���������жϺ�������ת��Ӧled�Ƶ�״̬��������/��������      
 * ��汾  ��V3.50
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/	

//ͷ�ļ�
#include "stm32f10x.h"
#include "led.h"
#include "exti.h"
#include "key.h"


/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  Exti_Config();//��ʼ���ж�����	
  Nvic_Config();//��ʼ���ж�����
  KEY_GPIO_Config();//������������
  LED_GPIO_Config();//��ʼ��LED�˿�
  while(1)
  {
  }		
}




