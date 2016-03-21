/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    :循环点亮LED灯    
 * 库版本  ： V3.50
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 调试方式：J-Link-OB
**********************************************************************************/	
//头文件
#include "stm32f10x.h"
#include "led.h"
                         
//函数声明
void Delay_ms( uint16_t time_ms );
/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
 int main(void)
{
  /*初始化LED端口*/
  LED_GPIO_Config();
  while(1)
  {	   
    /*D1、D2、D4全灭*/
    LED1_ONOFF(Bit_SET);
    LED2_ONOFF(Bit_SET);
    LED3_ONOFF(Bit_SET);
    Delay_ms(500);
    /*D1、D2、D4全亮*/
    LED1_ONOFF(Bit_RESET);
    LED2_ONOFF(Bit_RESET);
    LED3_ONOFF(Bit_RESET);
    Delay_ms(500);
  }		
}


 /**
  * @file   Delay_ms（不精确）
  * @brief  毫秒延时time_ms ms
  * @param   time_ms 延时时间
  * @retval 无
  */
void Delay_ms( uint16_t time_ms )
{
  uint16_t i,j;
  for( i=0;i<time_ms;i++ )
  {
		for( j=0;j<10309;j++ );//大约1ms
  }
}
