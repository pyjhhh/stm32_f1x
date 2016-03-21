/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：通过滴答时钟精确产生延时，点亮三个LED灯(LED1->D1，LED2->D2,LED3->D4)
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
#include "SYSTICK.h"
#include "led.h"



/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  USART1_Config();   //初始化串口
  LED_GPIO_Config();//初始化LED
  SYSTICK_Init();   //初始化SYSTICK
  printf("*****************************************************************\r\n");
  printf("*                                                               *\r\n");
  printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
  printf("*                                                               *\r\n");
  printf("*****************************************************************\r\n");
  while (1)
  {
		LEDXToggle(LED1);
		LEDXToggle(LED2);
		LEDXToggle(LED3);
		delay_ms(500);
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





