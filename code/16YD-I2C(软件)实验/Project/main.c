/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：主要是完成对eeprom的写操作和读操作
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
#include "SYSTICK.h"
#include "usart.h"
#include "i2c.h"
#include <stdio.h>



void I2C_Test(void);


/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    SYSTICK_Init();
    USART1_Config();
    LED_GPIO_Config();	
    I2C_Configuration();
    printf("\r\n 这是一个I2C外设(AT24C08)读写测试例程 \r\n");
    I2C_Test();
    while (1)
    {
     LEDXToggle(LED1);
    LEDXToggle(LED2);
    LEDXToggle(LED3);
    delay_ms(500);
    }
    
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





