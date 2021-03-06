/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：WWDG.c
 * 描述    ：初始化WWDG
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 硬件连接  :无
 * 调试方式：J-Link-OB
**********************************************************************************/
#include "wwdg.h"
 /**
  * @file   WWDG_Config
  * @brief  初始化窗口看门狗
  * @param  None
  * @retval None
	*注意   :窗口看门狗喂狗的时间非常关键，喂早了不行，晚了不行。
  *        所以就用中断喂狗了,当向下计数器达到40H时，产生中断；
  *        当向下计数器从40H下降到3FH时，将引起复位�
  */
void WWDG_Config(void)
{
    /* Enable WWDG clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); 
	 /* WWDG clock counter = (PCLK1 (36MHz)/4096)/8 = 1098Hz(~910us) */
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    /* Set Window value to 80; WWDG counter should be refreshed only when the counter
    is below 80 (and greater than 64) otherwise a reset will be generated */
    WWDG_SetWindowValue(80);	
     /* Enable WWDG and set counter value to 127, WWDG timeout = ~910 us * 64 = 58.24 ms 
     In this case the refresh window is: ~910 * (127-80)= 42.77ms < refresh window < ~910 * 64 = 58.24ms*/
    WWDG_Enable(0x7F);
				    
}
