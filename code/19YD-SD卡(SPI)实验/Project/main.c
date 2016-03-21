/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ����ɶ�SD����д������������
 * ��汾  ��V3.50
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/	

//ͷ�ļ�
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "spi.h"
#include "mmc_sd.h"
#include "systick.h"

//��������
u8 buf[512];//SD�����ݻ�����
/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	extern u8  SD_Type;
  u32 sector_size;
  u8 t=0;
  u8 ledflag=0;	
  SYSTICK_Init();
  LED_GPIO_Config();//��ʼ��LED
  USART1_Config(); 
  while(SD_Initialize()!=0)//��ⲻ��SD��
  {
    printf("SD Card Failed!");
    delay_ms(500);
    printf("Please Check!");
    delay_ms(500);
    if(ledflag)
    {
      ledflag=~ledflag;
      LED1_ONOFF(Bit_SET);
    }
    else
    {
      ledflag=~ledflag;
      LED1_ONOFF(Bit_RESET);	
    }
  }
  //���SD���ɹ�
  
  sector_size=SD_GetCapacity();
  printf(" SD Sector Size:%x\r\n",sector_size);
	printf("SD ���汾��%d\r\n",SD_Type);
	if(SD_Type==4)   //V2.0  С�ڵ���2G
	{
		printf("SD ������(M)��%f\r\n",(float)SD_GetCapacity()/1024/1024);
		printf("SD ������(G)��%f\r\n",(float)SD_GetCapacity()/1024/1024/1024);
	}
	if(SD_Type==6)        //V2.0HC  2G~32G
	{ 
		printf("SD ������(M)��%f\r\n",(float)SD_GetCapacity()/1024);
		printf("SD ������(G)��%f\r\n",(float)SD_GetCapacity()/1024/1024);	 
	}
  while (1)
  {
    if(t==30)//ÿ6s��ִ��һ��
    {
      if(SD_ReadDisk(buf,0,1)==0)//��ȡMBR����
      {	
          printf("SECTOR 0 DATA:\n");
          for(sector_size=0;sector_size<512;sector_size++)printf("%x ",buf[sector_size]);//��ӡMBR��������    	   
          printf("\nDATA ENDED\n");
      }
      t=0;
    }   
    t++;
    delay_ms(200);
    if(ledflag)
    {
      ledflag=~ledflag;
      LED2_ONOFF(Bit_RESET);	
    }
    else
    {
      ledflag=~ledflag;
      LED2_ONOFF(Bit_SET);
    }
		
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

