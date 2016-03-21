
/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：完成对窗口看门狗的喂狗操作，否则会出现程序复位
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
#include "key.h"
#include "systick.h"
#include "usart.h"
#include "wwdg.h"


 /**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	LED_GPIO_Config();
	KEY_GPIO_Config();
	USART1_Config();	
	SYSTICK_Init();
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) != RESET)/* Check if the system has resumed from WWDG reset */
	{ 
		printf("WWDG Reset\r\n");
		LED1_ONOFF(Bit_SET);LED2_ONOFF(Bit_SET);
		RCC_ClearFlag();/* Clear reset flags */
	}
	else
	{
		/* WWDGRST flag is not set */
		LED1_ONOFF(Bit_RESET);LED2_ONOFF(Bit_RESET);
	}
  WWDG_Config();
    while (1)
    {
     LEDXToggle(LED3);
      delay_ms(45);
      /* Update WWDG counter */
      if(KEY1_Status_Read()==0)
      {
				WWDG_SetCounter(127);
      }			
    }
    
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





