/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：向指定的Flash地址写入指定数据，并读取出来
 * 库版本  ：V3.50
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 调试方式：J-Link-OB
**********************************************************************************/	


//头文件
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "systick.h"


/* Private define ------------------------------------------------------------*/
#define  FLASH_ADR   0x0801F000  		/* 存储数据Flash页首地址 128K */
#define	 FLASH_DATA	 0x5a5a5a5a		    /* 写入的数据 */

 /**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	  uint32_t FlashData;
    LED_GPIO_Config();//初始化LED
    USART1_Config();//初始化
    SYSTICK_Init();//初始化滴答时钟，		
    printf("*****************************************************************\r\n");
    printf("*                                                               *\r\n");
    printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
    printf("*                                                               *\r\n");
    printf("*****************************************************************\r\n");
    	/* 判断此FLASH是否为空白 */
    FlashData=*(vu32*)(FLASH_ADR);	 /* 读取地址中的16位数据 */
    if(FlashData==0xffffffff)
    {
      FLASH_Unlock();		/* 每次擦除Flash中数据时得先解锁 */
      FLASH_ProgramWord(FLASH_ADR,FLASH_DATA);   /* 写16位半字 */
      FLASH_Lock();							   /* 上锁 */
      printf("\r\n要写入的地址为空,写入认证数据 \r\n");
    }
    else if(FlashData==FLASH_DATA)
    {
      printf("\r\n地址数据与认证数据符合 \r\n");
      printf("%x \r\n",FlashData);
    }
    else
    {
      printf("\r\n地址上的数据与认证的数据不符合,有可能是写入失败或者是要写入的地址非空\r\n");
      FLASH_Unlock();
      FLASH_ErasePage(FLASH_ADR);		  /* 擦除页 */
      FLASH_Lock();
      printf("\r\n已经刷除要写入的地址\r\n");
    }
    while(1)
    {
      LEDXToggle(LED1);
      LEDXToggle(LED2);
      delay_ms(500);
      
    }
}



/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





