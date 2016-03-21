/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��Relay.c
 * ����    ���̵���GPIO��������   
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������: Relay_GPIO-->PB3
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/	

//ͷ�ļ�
#include "Relay.h"

 /**
  * @file   LED_GPIO_Config
  * @brief  LED����������
  * @param  ��
  * @retval ��
  */
void Relay_GPIO_Config(void)
{	
    //����һ��GPIO_InitTypeDef ���͵Ľṹ��
    GPIO_InitTypeDef  GPIO_InitStructure;	
    RCC_APB2PeriphClockCmd(Relay_GPIO_RCC,ENABLE);//ʹ��GPIO������ʱ��
    /*Relay*/
    GPIO_InitStructure.GPIO_Pin =Relay_GPIO_PIN;//ѡ��Ҫ�õ�GPIO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //��������ģʽΪ�������ģʽ						 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���������ٶ�Ϊ50MHZ         
    GPIO_Init(Relay_GPIO_PORT, &GPIO_InitStructure);//���ÿ⺯������ʼ��GPIO

}


