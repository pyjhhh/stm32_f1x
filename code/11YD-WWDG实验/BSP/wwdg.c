/******************** (C) COPYRIGHT  Ô´µØ¹¤×÷ÊÒ ********************************
 * ÎÄ¼şÃû  £ºWWDG.c
 * ÃèÊö    £º³õÊ¼»¯WWDG
 * ×÷Õß    £ºzhuoyingxingyu
 * ÌÔ±¦    £ºÔ´µØ¹¤×÷ÊÒhttp://vcc-gnd.taobao.com/
 * ÂÛÌ³µØÖ·£º¼«¿ÍÔ°µØ-Ç¶ÈëÊ½¿ª·¢ÂÛÌ³http://vcc-gnd.com/
 * °æ±¾¸üĞÂ: 2015-10-20
 * Ó²¼şÁ¬½Ó  :ÎŞ
 * µ÷ÊÔ·½Ê½£ºJ-Link-OB
**********************************************************************************/
#include "wwdg.h"
 /**
  * @file   WWDG_Config
  * @brief  ³õÊ¼»¯´°¿Ú¿´ÃÅ¹·
  * @param  None
  * @retval None
	*×¢Òâ   :´°¿Ú¿´ÃÅ¹·Î¹¹·µÄÊ±¼ä·Ç³£¹Ø¼ü£¬Î¹ÔçÁË²»ĞĞ£¬ÍíÁË²»ĞĞ¡£
  *        ËùÒÔ¾ÍÓÃÖĞ¶ÏÎ¹¹·ÁË,µ±ÏòÏÂ¼ÆÊıÆ÷´ïµ½40HÊ±£¬²úÉúÖĞ¶Ï£»
  *        µ±ÏòÏÂ¼ÆÊıÆ÷´Ó40HÏÂ½µµ½3FHÊ±£¬½«ÒıÆğ¸´Î»¡
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
