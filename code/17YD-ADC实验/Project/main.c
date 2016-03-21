/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    �����ADC�����ã�����ADC����ֵͨ��������ʾ�ڴ��ڵ������ֵĴ��ڽ����Ϻ���OLED����ʾ��
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
#include "led.h"
#include <stdio.h>
#include "systick.h"
#include "OLED.h"
#include "fonts.h"
#include "ADC.h"


//��������
void LED_RUN(u16 delay_time);
/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	uint16_t Temp_Value;
	float ADC_Value=0.00;
	OLED_Init();  
	SYSTICK_Init();
	OLED_DispStr(0, 1, "The adc value is:", &tFont12);
	ADC_Configuration();
	LED_GPIO_Config();//��ʼ��LED
	USART1_Config();
	printf("*****************************************************************\r\n");
	printf("*                                                               *\r\n");
	printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
	printf("*                                                               *\r\n");
	printf("*****************************************************************\r\n");
	while (1)
	{
		Temp_Value = ADC_GetConversionValue(ADC1);
		ADC_Value = (3.3/4096)*Temp_Value;			 /*��ADֵת��Ϊ��ѹֵ*/
		printf("\r\n The Temp_Value is %d \r\n",Temp_Value);
		printf("\r\n The Value is %f \r\n",ADC_Value);
		OLED_DisDecimal(10, 15, ADC_Value,4, &tFont12);
	  LEDXToggle(LED1);
		delay_ms(500);
    
	}
}




/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





