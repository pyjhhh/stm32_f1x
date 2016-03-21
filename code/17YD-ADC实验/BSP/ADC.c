/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：ADC.c
 * 描述    ：完成ADC的初始化   
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 硬件连接: ADC Channel-->PA0
 * 调试方式：J-Link-OB
**********************************************************************************/
#include "ADC.h"


float AD_value;
vu16 ADC_ConvertedValue;

 /**
  * @file   ADC_Configuration
  * @brief  完成ADC和DMA的初始化
  * @param  无
  * @retval 无
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
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	                /* 独立模式 */
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;			                /* 连续多通道模式 */
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	                /* 连续转换 */
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;   /* 转换不受外界决定 */
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		        /* 右对齐 */
  ADC_InitStructure.ADC_NbrOfChannel = 1;					            /* 扫描通道数 */
  ADC_Init(ADC1, &ADC_InitStructure);

 /* ADC1 regular channel0 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
  ADC_Cmd(ADC1, ENABLE);                                                /* Enable ADC1 */                      
  ADC_SoftwareStartConvCmd(ADC1,ENABLE);                                /* 使能转换开始 */
}


