/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ����Ҫ����ɶ�bmp180��ѹ��������д�����Ͷ����������������ǰ����ѹ�����ʹ�ӡ����
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
#include "SYSTICK.h"
#include "usart.h"
#include "i2c.h"
#include "BMP180.h"
#include <stdio.h>

/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    SYSTICK_Init();
    USART1_Config();
    LED_GPIO_Config();
    I2C_Configuration();
    BMP180_Init();

    while (1)
    {
      LEDXToggle(LED1);
      LEDXToggle(LED2);
      LEDXToggle(LED3);
      delay_ms(1000);
      BMP180_TEST();

    }
    
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





