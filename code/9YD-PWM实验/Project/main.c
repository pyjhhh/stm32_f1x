//=============================================================================
//文件名称:main.c
//功能概要:S2按键按下，蜂鸣器开始发声，S3按键按下，蜂鸣器停止发声；
//版权所有:源地工作室http://vcc-gnd.taobao.com/
//版本更新:2015-02-20 v1.0
//调试方式:J-LINK-OB
//=============================================================================


//头文件
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "exti.h"
#include "systick.h"
#include "key.h"

//函数声明
void System_Run(void);


/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
		LED_GPIO_Config();//初始化LED
		USART1_Config();
	  Exti_Config();
  	KEY_GPIO_Config();
		SYSTICK_Init();//初始化滴答时钟，		
		TIM2_PWM_Init();//初始化通用定时器TIM2
    printf("*****************************************************************\r\n");
    printf("*                                                               *\r\n");
    printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
	  printf("*  按下S1按键后，蜂鸣器开始响   \r\n");
	  printf("*  按下S2按键后，蜂鸣器停止响   \r\n");
    printf("*                                                               *\r\n");
    printf("*****************************************************************\r\n");
		while(1)
		{
			LEDXToggle(LED3);
			delay_ms(500);
		  
		}
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





