/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ����OLED��ʾ������ʾ�ַ����ַ��������֡������Լ�С����
 * ��汾  ��V3.5.0
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * ���Է�ʽ��J-Link-OB
********************************************************************************/


//ͷ�ļ�
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "systick.h"
#include <stdio.h>
#include "OLED.h"
#include "fonts.h"



//��������
void System_Run(void);

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
	
    OLED_DispStr(15, 0, "OLED Init OK", &tFont12);//http://vcc-gnd.taobao.com/
    OLED_DisDigital(15, 15,15161, &tFont12);//��ʾ����
    OLED_DisDecimal(15, 30,15161.0123,4, &tFont12);//��ʾС
    OLED_DispStr(15, 45, "Դ������", &tFont12);
    LED_GPIO_Config();//��ʼ��LED
    USART1_Config();
    printf("*****************************************************************\r\n");
    printf("*                                                               *\r\n");
    printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
    printf("*                                                               *\r\n");
    printf("*****************************************************************\r\n");
    while (1)
    {
			LEDXToggle(LED1);
			LEDXToggle(LED2);
			delay_ms(500);
      
    }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





