/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：CAN_Normal模式测试，不断接收数据
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


extern uint16_t CAN_ID;
extern uint8_t CAN_DATA0,CAN_DATA1,CAN_DATA2,CAN_DATA3,CAN_DATA4,CAN_DATA5,CAN_DATA6,CAN_DATA7;
extern uint8_t CanFlag,Display;
	
/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    LED_GPIO_Config();//初始化LED
    CAN_Configuration();
    USART1_Config();
    SYSTICK_Init();
    printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
    printf("CAN-Bus Test \r\n");
    printf("CAN-Bus Speed 100kHz \r\n");
    while (1)
    {
      printf("CAN Receive Data \r\n");
      printf("CAN ID %x \r\n",CAN_ID);	
      printf("CAN_DATA0 %x \r\n",CAN_DATA0);
      
      printf("CAN_DATA1 %x \r\n",CAN_DATA1);
      printf("CAN_DATA2 %x \r\n",CAN_DATA2);
      printf("CAN_DATA3 %x \r\n",CAN_DATA3);
      printf("CAN_DATA4 %x \r\n",CAN_DATA4);
      printf("CAN_DATA5 %x \r\n",CAN_DATA5);
			delay_ms(100);
			LEDXToggle(LED1);
    }
}




/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





