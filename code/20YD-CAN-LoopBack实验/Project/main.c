/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：CAN_Loopback模式测试
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
#include "can.h"
#include "systick.h"

/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	  int TestRx;
    LED_GPIO_Config();//初始化LED
	  CAN_Configuration(); 
	  NVIC_Configuration();
    USART1_Config();
    SYSTICK_Init();
		printf("\r\n");
		printf("*****************************************************************\r\n");
		printf("*                                                               *\r\n");
		printf("*  Thank you for using YuanDi Development Board ！^_^  *\r\n");
		printf("*                                                               *\r\n");
		printf("*****************************************************************\r\n");
		printf("CAN-Bus Test \r\n");

    /* CAN transmit at 100Kb/s and receive by polling in loopback mode */
    TestRx = CAN_Polling();

    if (TestRx == DISABLE)
    {
      printf("CAN-Bus by polling in loopback mode is False \r\n");
    }
    else
    {
	  printf("CAN-Bus by polling in loopback mode is OK \r\n");
    }

    /* CAN transmit at 500Kb/s and receive by interrupt in loopback mode */
    TestRx = CAN_Interrupt();

    if (TestRx == DISABLE)
    {
      printf("CAN-Bus by interrupt in loopback mode is False \r\n");
    }
    else
    {
      printf("CAN-Bus by interrupt in loopback mode is OK \r\n");
    }
    /* Infinite loop */
    while (1)
    {
			delay_ms(500);
			LEDXToggle(LED1);
			
    }
}





/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





