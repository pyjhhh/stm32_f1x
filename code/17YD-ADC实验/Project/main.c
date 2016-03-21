/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：完成ADC的配置，并将ADC采样值通过串口显示在串口调试助手的窗口界面上和在OLED上显示。
 * 库版本  ：V3.50
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 调试方式：J-Link-OB
**********************************************************************************/	

//头文件
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include <stdio.h>
#include "systick.h"
#include "OLED.h"
#include "fonts.h"
#include "ADC.h"


//声明函数
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
	LED_GPIO_Config();//初始化LED
	USART1_Config();
	printf("*****************************************************************\r\n");
	printf("*                                                               *\r\n");
	printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
	printf("*                                                               *\r\n");
	printf("*****************************************************************\r\n");
	while (1)
	{
		Temp_Value = ADC_GetConversionValue(ADC1);
		ADC_Value = (3.3/4096)*Temp_Value;			 /*将AD值转换为电压值*/
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





