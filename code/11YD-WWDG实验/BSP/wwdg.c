/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��WWDG.c
 * ����    ����ʼ��WWDG
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������  :��
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/
#include "wwdg.h"
 /**
  * @file   WWDG_Config
  * @brief  ��ʼ�����ڿ��Ź�
  * @param  None
  * @retval None
	*ע��   :���ڿ��Ź�ι����ʱ��ǳ��ؼ���ι���˲��У����˲��С�
  *        ���Ծ����ж�ι����,�����¼������ﵽ40Hʱ�������жϣ�
  *        �����¼�������40H�½���3FHʱ��������λ�
  */
void WWDG_Config(void)
{
    /* Enable WWDG clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE); 
	 /* WWDG clock counter = (PCLK1 (36MHz)/4096)/8 = 1098Hz(~910us) */
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    /* Set Window value to 80; WWDG counter should be refreshed only when the counter
    is below 80 (and greater than 64) otherwise a reset will be generated */
    WWDG_SetWindowValue(80);	
     /* Enable WWDG and set counter value to 127, WWDG timeout = ~910 us * 64 = 58.24 ms 
     In this case the refresh window is: ~910 * (127-80)= 42.77ms < refresh window < ~910 * 64 = 58.24ms*/
    WWDG_Enable(0x7F);
				    
}
