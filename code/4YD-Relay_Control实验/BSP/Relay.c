/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：Relay.c
 * 描述    ：继电器GPIO引脚配置   
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 硬件连接: Relay_GPIO-->PB3
 * 调试方式：J-Link-OB
**********************************************************************************/	

//头文件
#include "Relay.h"

 /**
  * @file   LED_GPIO_Config
  * @brief  LED灯引脚配置
  * @param  无
  * @retval 无
  */
void Relay_GPIO_Config(void)
{	
    //定义一个GPIO_InitTypeDef 类型的结构体
    GPIO_InitTypeDef  GPIO_InitStructure;	
    RCC_APB2PeriphClockCmd(Relay_GPIO_RCC,ENABLE);//使能GPIO的外设时钟
    /*Relay*/
    GPIO_InitStructure.GPIO_Pin =Relay_GPIO_PIN;//选择要用的GPIO引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置引脚模式为推免输出模式						 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置引脚速度为50MHZ         
    GPIO_Init(Relay_GPIO_PORT, &GPIO_InitStructure);//调用库函数，初始化GPIO

}


