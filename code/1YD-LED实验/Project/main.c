/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    :ѭ������LED��    
 * ��汾  �� V3.50
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/	
//ͷ�ļ�
#include "stm32f10x.h"
#include "led.h"
                         
//��������
void Delay_ms( uint16_t time_ms );
/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
 int main(void)
{
  /*��ʼ��LED�˿�*/
  LED_GPIO_Config();
  while(1)
  {	   
    /*D1��D2��D4ȫ��*/
    LED1_ONOFF(Bit_SET);
    LED2_ONOFF(Bit_SET);
    LED3_ONOFF(Bit_SET);
    Delay_ms(500);
    /*D1��D2��D4ȫ��*/
    LED1_ONOFF(Bit_RESET);
    LED2_ONOFF(Bit_RESET);
    LED3_ONOFF(Bit_RESET);
    Delay_ms(500);
  }		
}


 /**
  * @file   Delay_ms������ȷ��
  * @brief  ������ʱtime_ms ms
  * @param   time_ms ��ʱʱ��
  * @retval ��
  */
void Delay_ms( uint16_t time_ms )
{
  uint16_t i,j;
  for( i=0;i<time_ms;i++ )
  {
		for( j=0;j<10309;j++ );//��Լ1ms
  }
}
