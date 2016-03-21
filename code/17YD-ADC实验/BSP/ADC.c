/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��ADC.c
 * ����    �����ADC�ĳ�ʼ��   
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������: ADC Channel-->PA0
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/
#include "ADC.h"


float AD_value;
vu16 ADC_ConvertedValue;

 /**
  * @file   ADC_Configuration
  * @brief  ���ADC��DMA�ĳ�ʼ��
  * @param  ��
  * @retval ��
  */
void ADC_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
   
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	                /* ����ģʽ */
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;			                /* ������ͨ��ģʽ */
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	                /* ����ת�� */
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;   /* ת������������ */
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		        /* �Ҷ��� */
  ADC_InitStructure.ADC_NbrOfChannel = 1;					            /* ɨ��ͨ���� */
  ADC_Init(ADC1, &ADC_InitStructure);

 /* ADC1 regular channel0 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
  ADC_Cmd(ADC1, ENABLE);                                                /* Enable ADC1 */                      
  ADC_SoftwareStartConvCmd(ADC1,ENABLE);                                /* ʹ��ת����ʼ */
}


