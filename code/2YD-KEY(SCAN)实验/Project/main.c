/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ������S1��S2��S3�������밴��ɨ�躯��,��ʱ�䰴�Ļ�����Ӧ��led�ƻ���˸S1->D1;S2->D2;S3->D4;       
 * ��汾  ��V3.50
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/	

//ͷ�ļ�
#include "stm32f10x.h"
#include "led.h"
#include "key.h"


//��������
void Delay_ms( uint16_t time_ms );

/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
 int main(void)
{
	LED_GPIO_Config();/*��ʼ��LED�˿�*/
	KEY_GPIO_Config();/*��ʼ��KEY�˿�*/	
 	while(1)
 	{	 
		if(KEY1_Status_Read()==0||KEY2_Status_Read()==0||KEY3_Status_Read()==0)//�ж�3�������Ƿ��а���
		{
			Delay_ms(20);
			if(KEY1_Status_Read()==0)//ȷ��S1������
			{
				Delay_ms(250);
				LEDXToggle(LED1);
			}
			else if(KEY2_Status_Read()==0)//ȷ��S2������
			{
				Delay_ms(250);
				LEDXToggle(LED2);
			}
			else if(KEY3_Status_Read()==0)//ȷ��S3������
			{
				Delay_ms(250);
				LEDXToggle(LED3);
			}
		}
		else
		{
			LED1_ONOFF(Bit_SET);
			LED2_ONOFF(Bit_SET);
			LED3_ONOFF(Bit_SET);
		}
 	} 			
}

 /**
  * @file   Delay_ms������ȷ��
  * @brief  ������ʱtime_ms ms
  * @param   time_ms ��ʱʱ��
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
