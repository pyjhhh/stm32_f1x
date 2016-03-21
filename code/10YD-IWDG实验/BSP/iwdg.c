/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��IWDG.c
 * ����    ����ʼ��IWDG
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������  :��
 * ���Է�ʽ��J-Link-OB
********************************************************************************/
#include "iwdg.h"

 /**
  * @file   IWDG_Config
  * @brief  ��ʼ���������Ź�
  * @param  ��
  * @retval ��
  */
void IWDG_Config(void)
{
	// ע��   :�������Ź���Ƭ��40k RC������Ϊʱ�ӣ���˵��̫׼-_-!
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	IWDG_SetPrescaler(IWDG_Prescaler_32);		  //����IWDGԤ��Ƶֵ��256��Ƶ���
	IWDG_SetReload(40000/128);	   //����IWDG����װ��ֵ	:��Χ0~0x0FFF
	IWDG_ReloadCounter();	   //ι��������װ�ؼ�����
	IWDG_Enable();			   //ʹ��IWDG��ʱ��
}

  /* 
�趨IWDG�������ʱ�� 250ms
     Counter Reload Value = 250ms/IWDG counter clock period
                          = 250ms / (LSI/32)
                          = 0.25s / (LsiFreq/32)
                          = LsiFreq/(32 * 4)
                          = LsiFreq/128
  */





