/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ����ָ����Flash��ַд��ָ�����ݣ�����ȡ����
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
#include "systick.h"


/* Private define ------------------------------------------------------------*/
#define  FLASH_ADR   0x0801F000  		/* �洢����Flashҳ�׵�ַ 128K */
#define	 FLASH_DATA	 0x5a5a5a5a		    /* д������� */

 /**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	  uint32_t FlashData;
    LED_GPIO_Config();//��ʼ��LED
    USART1_Config();//��ʼ��
    SYSTICK_Init();//��ʼ���δ�ʱ�ӣ�		
    printf("*****************************************************************\r\n");
    printf("*                                                               *\r\n");
    printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
    printf("*                                                               *\r\n");
    printf("*****************************************************************\r\n");
    	/* �жϴ�FLASH�Ƿ�Ϊ�հ� */
    FlashData=*(vu32*)(FLASH_ADR);	 /* ��ȡ��ַ�е�16λ���� */
    if(FlashData==0xffffffff)
    {
      FLASH_Unlock();		/* ÿ�β���Flash������ʱ���Ƚ��� */
      FLASH_ProgramWord(FLASH_ADR,FLASH_DATA);   /* д16λ���� */
      FLASH_Lock();							   /* ���� */
      printf("\r\nҪд��ĵ�ַΪ��,д����֤���� \r\n");
    }
    else if(FlashData==FLASH_DATA)
    {
      printf("\r\n��ַ��������֤���ݷ��� \r\n");
      printf("%x \r\n",FlashData);
    }
    else
    {
      printf("\r\n��ַ�ϵ���������֤�����ݲ�����,�п�����д��ʧ�ܻ�����Ҫд��ĵ�ַ�ǿ�\r\n");
      FLASH_Unlock();
      FLASH_ErasePage(FLASH_ADR);		  /* ����ҳ */
      FLASH_Lock();
      printf("\r\n�Ѿ�ˢ��Ҫд��ĵ�ַ\r\n");
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





