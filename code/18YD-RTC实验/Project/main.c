/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ��ͨ�����ڶ�RTCʵʱʱ�ӽ������ò���OLED�ʹ��ڵ��Դ�������ʾ��ǰʱ��
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
#include "systick.h"
#include "usart.h"
#include "rtc.h"
#include "OLED.h"

/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
      SYSTICK_Init();
      OLED_Init(); 
      OLED_DispStr(15, 10, " Real Time", &tFont12);
      DateTimeDis_Init();
      USART1_Config();
      LED_GPIO_Config();
      RTC_Init();
    while (1)
    {
    }
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





