/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：IWDG.c
 * 描述    ：初始化IWDG
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 硬件连接  :无
 * 调试方式：J-Link-OB
********************************************************************************/
#include "iwdg.h"

 /**
  * @file   IWDG_Config
  * @brief  初始化独立看门狗
  * @param  无
  * @retval 无
  */
void IWDG_Config(void)
{
	// 注意   :独立看门狗以片内40k RC振荡器作为时钟，据说不太准-_-!
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //使能对寄存器IWDG_PR、IWDG_RLR的写操作
	IWDG_SetPrescaler(IWDG_Prescaler_32);		  //设置IWDG预分频值：256分频最大
	IWDG_SetReload(40000/128);	   //设置IWDG的重装载值	:范围0~0x0FFF
	IWDG_ReloadCounter();	   //喂狗：重新装载计数器
	IWDG_Enable();			   //使能IWDG定时器
}

  /* 
设定IWDG重载溢出时间 250ms
     Counter Reload Value = 250ms/IWDG counter clock period
                          = 250ms / (LSI/32)
                          = 0.25s / (LsiFreq/32)
                          = LsiFreq/(32 * 4)
                          = LsiFreq/128
  */





