/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：通过串口对RTC实时时钟进行设置并在OLED和串口调试窗口上显示当前时间
 * 库版本  ：V3.50
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 调试方式：J-Link-OB
**********************************************************************************/	
//头文件
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





