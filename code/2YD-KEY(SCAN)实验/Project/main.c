/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：按下S1，S2，S3函数进入按键扫描函数,长时间按的话，相应的led灯会闪烁S1->D1;S2->D2;S3->D4;       
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
#include "key.h"


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
	LED_GPIO_Config();/*初始化LED端口*/
	KEY_GPIO_Config();/*初始化KEY端口*/	
 	while(1)
 	{	 
		if(KEY1_Status_Read()==0||KEY2_Status_Read()==0||KEY3_Status_Read()==0)//判断3个按键是否有按下
		{
			Delay_ms(20);
			if(KEY1_Status_Read()==0)//确认S1键按下
			{
				Delay_ms(250);
				LEDXToggle(LED1);
			}
			else if(KEY2_Status_Read()==0)//确认S2键按下
			{
				Delay_ms(250);
				LEDXToggle(LED2);
			}
			else if(KEY3_Status_Read()==0)//确认S3键按下
			{
				Delay_ms(250);
				LEDXToggle(LED3);
			}
		}
		else
		{
			LED1_ONOFF(Bit_SET);
			LED2_ONOFF(Bit_SET);
			LED3_ONOFF(Bit_SET);
		}
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
