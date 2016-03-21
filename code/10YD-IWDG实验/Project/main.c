/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：S1按键按下开始喂狗，系统不会出现复位，LED灯不闪烁，松开后，系统开
 *           始复位 ，LED灯闪烁，串口输出复位信息
 * 库版本  ：V3.5.0
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 调试方式：J-Link-OB
********************************************************************************/	

//头文件
#include "stm32f10x.h"
#include "led.h"
#include "systick.h"
#include "iwdg.h"
#include "key.h"
#include "usart.h"



void Delay_ms( uint16_t time_ms );
 /**
  * @file   Delay_ms(不精确)
  * @brief  毫秒延时
  * @param  time_ms*1(ms)
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

 /**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	LED_GPIO_Config();//初始化LED
	KEY_GPIO_Config();
	SYSTICK_Init();//初始化滴答时钟
	USART1_Config();//串口参数配置初始化
	LED2_ONOFF(Bit_SET);
	LED3_ONOFF(Bit_SET);
  Delay_ms(500);
	LED2_ONOFF(Bit_RESET);
	LED3_ONOFF(Bit_RESET);
  Delay_ms(500);
	IWDG_Config();
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		printf("IWDG复位\r\n");
		RCC_ClearFlag();
	}

	while(1)
	{
		if(KEY1_Status_Read()	==0)//S1按键
      {
        IWDG_ReloadCounter();    //去掉注解“喂狗”	
      }
		  delay_ms(200);
			LEDXToggle(LED1);
	}
}



/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





