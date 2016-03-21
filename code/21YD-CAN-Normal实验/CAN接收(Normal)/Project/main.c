/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��main.c
 * ����    ��CAN_Normalģʽ���ԣ����Ͻ�������
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
#include "can.h"
#include "systick.h"


extern uint16_t CAN_ID;
extern uint8_t CAN_DATA0,CAN_DATA1,CAN_DATA2,CAN_DATA3,CAN_DATA4,CAN_DATA5,CAN_DATA6,CAN_DATA7;
extern uint8_t CanFlag,Display;
	
/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    LED_GPIO_Config();//��ʼ��LED
    CAN_Configuration();
    USART1_Config();
    SYSTICK_Init();
    printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
    printf("CAN-Bus Test \r\n");
    printf("CAN-Bus Speed 100kHz \r\n");
    while (1)
    {
      printf("CAN Receive Data \r\n");
      printf("CAN ID %x \r\n",CAN_ID);	
      printf("CAN_DATA0 %x \r\n",CAN_DATA0);
      
      printf("CAN_DATA1 %x \r\n",CAN_DATA1);
      printf("CAN_DATA2 %x \r\n",CAN_DATA2);
      printf("CAN_DATA3 %x \r\n",CAN_DATA3);
      printf("CAN_DATA4 %x \r\n",CAN_DATA4);
      printf("CAN_DATA5 %x \r\n",CAN_DATA5);
			delay_ms(100);
			LEDXToggle(LED1);
    }
}




/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





