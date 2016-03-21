/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��SPI.c
 * ����    ��SPI��ʼ��
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������  :SCLK--PA5;MISO---PA6;MOSI--PA7
 * ���Է�ʽ��J-Link-OB
********************************************************************************/
#include "spi.h"

 /**
  * @file   SPIx_Init
  * @brief  SPIģ��ĳ�ʼ�����룬���ó�����ģʽ������SD Card/W25X16/24L01/JF24C		
  * @param  ��
  * @retval ��
  */  
SPI_InitTypeDef  SPI_InitStructure;
void SPIx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(	SD_SPI_RCC, ENABLE );	
	RCC_APB2PeriphClockCmd(	SD_SPI_SCK_GPIO_RCC|SD_SPI_MISO_GPIO_RCC|SD_SPI_MOSI_GPIO_RCC, ENABLE );	
 
	GPIO_InitStructure.GPIO_Pin = SD_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SD_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SD_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SD_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SD_SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SD_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

 	GPIO_SetBits(SD_SPI_SCK_GPIO_PORT,SD_SPI_SCK_PIN);
	GPIO_SetBits(SD_SPI_MISO_GPIO_PORT,SD_SPI_MISO_PIN);
	GPIO_SetBits(SD_SPI_MOSI_GPIO_PORT,SD_SPI_MOSI_PIN);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SD_SPI, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SD_SPI, ENABLE); //ʹ��SPI����
	
	SPIx_ReadWriteByte(0xff);//��������		 
}   

 /**
  * @file   SPIx_SetSpeed
  * @brief  �ٶ�����
  * @param  SpeedSet:�ٶȲ���
  * @retval ��
  */ 
void SPIx_SetSpeed(u8 SpeedSet)
{
	SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
  SPI_Init(SD_SPI, &SPI_InitStructure);
	SPI_Cmd(SD_SPI,ENABLE);
} 



 /**
  * @file   SPIx_ReadWriteByte
  * @brief  ��дһ���ֽ�
  * @param  TxData:Ҫд����ֽ�
  * @retval ��ȡ�����ֽ�
  */
u8 SPIx_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 
	while (SPI_I2S_GetFlagStatus(SD_SPI, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  

	SPI_I2S_SendData(SD_SPI, TxData); //ͨ������SPIx����һ������
	retry=0;
	while (SPI_I2S_GetFlagStatus(SD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
	{
		;
	} //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SD_SPI); //����ͨ��SPIx������յ�����					    
}












