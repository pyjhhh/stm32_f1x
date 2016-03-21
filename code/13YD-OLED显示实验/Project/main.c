/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：在OLED显示屏上显示字符，字符串，汉字、整数以及小数等
 * 库版本  ：V3.5.0
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 调试方式：J-Link-OB
********************************************************************************/


//头文件
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "systick.h"
#include <stdio.h>
#include "OLED.h"
#include "fonts.h"



//函数声明
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
    OLED_DisDigital(15, 15,15161, &tFont12);//显示整数
    OLED_DisDecimal(15, 30,15161.0123,4, &tFont12);//显示小
    OLED_DispStr(15, 45, "源地仪器", &tFont12);
    LED_GPIO_Config();//初始化LED
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





