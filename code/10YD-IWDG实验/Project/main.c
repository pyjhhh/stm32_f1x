/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ��S1�������¿�ʼι����ϵͳ������ָ�λ��LED�Ʋ���˸���ɿ���ϵͳ��
 *           ʼ��λ ��LED����˸�����������λ��Ϣ
 * ��汾  ��V3.5.0
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * ���Է�ʽ��J-Link-OB
********************************************************************************/	

//ͷ�ļ�
#include "stm32f10x.h"
#include "led.h"
#include "systick.h"
#include "iwdg.h"
#include "key.h"
#include "usart.h"



void Delay_ms( uint16_t time_ms );
 /**
  * @file   Delay_ms(����ȷ)
  * @brief  ������ʱ
  * @param  time_ms*1(ms)
  * @retval ��
  */
void Delay_ms( uint16_t time_ms )
{
  uint16_t i,j;
  for( i=0;i<time_ms;i++ )
  {
		for( j=0;j<10309;j++ );//��Լ1ms
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
	LED_GPIO_Config();//��ʼ��LED
	KEY_GPIO_Config();
	SYSTICK_Init();//��ʼ���δ�ʱ��
	USART1_Config();//���ڲ������ó�ʼ��
	LED2_ONOFF(Bit_SET);
	LED3_ONOFF(Bit_SET);
  Delay_ms(500);
	LED2_ONOFF(Bit_RESET);
	LED3_ONOFF(Bit_RESET);
  Delay_ms(500);
	IWDG_Config();
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		printf("IWDG��λ\r\n");
		RCC_ClearFlag();
	}

	while(1)
	{
		if(KEY1_Status_Read()	==0)//S1����
      {
        IWDG_ReloadCounter();    //ȥ��ע�⡰ι����	
      }
		  delay_ms(200);
			LEDXToggle(LED1);
	}
}



/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





