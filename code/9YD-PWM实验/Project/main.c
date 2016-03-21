//=============================================================================
//�ļ�����:main.c
//���ܸ�Ҫ:S2�������£���������ʼ������S3�������£�������ֹͣ������
//��Ȩ����:Դ�ع�����http://vcc-gnd.taobao.com/
//�汾����:2015-02-20 v1.0
//���Է�ʽ:J-LINK-OB
//=============================================================================


//ͷ�ļ�
#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "exti.h"
#include "systick.h"
#include "key.h"

//��������
void System_Run(void);


/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
		LED_GPIO_Config();//��ʼ��LED
		USART1_Config();
	  Exti_Config();
  	KEY_GPIO_Config();
		SYSTICK_Init();//��ʼ���δ�ʱ�ӣ�		
		TIM2_PWM_Init();//��ʼ��ͨ�ö�ʱ��TIM2
    printf("*****************************************************************\r\n");
    printf("*                                                               *\r\n");
    printf("*  Thank you for using The Development Board Of YuanDi   ! ^_^  *\r\n");
	  printf("*  ����S1�����󣬷�������ʼ��   \r\n");
	  printf("*  ����S2�����󣬷�����ֹͣ��   \r\n");
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





