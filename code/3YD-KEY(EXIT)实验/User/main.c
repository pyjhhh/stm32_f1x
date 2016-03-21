/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：按下S1，S2，S3函数进入中断函数，翻转相应led灯的状态（由灭到亮/由亮到灭）      
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
#include "exti.h"
#include "key.h"


/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  Exti_Config();//初始化中断配置	
  Nvic_Config();//初始化中断向量
  KEY_GPIO_Config();//按键引脚配置
  LED_GPIO_Config();//初始化LED端口
  while(1)
  {
  }		
}




