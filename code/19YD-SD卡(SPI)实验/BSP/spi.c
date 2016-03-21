/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：SPI.c
 * 描述    ：SPI初始化
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 硬件连接  :SCLK--PA5;MISO---PA6;MOSI--PA7
 * 调试方式：J-Link-OB
********************************************************************************/
#include "spi.h"

 /**
  * @file   SPIx_Init
  * @brief  SPI模块的初始化代码，配置成主机模式，访问SD Card/W25X16/24L01/JF24C		
  * @param  无
  * @retval 无
  */  
SPI_InitTypeDef  SPI_InitStructure;
void SPIx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(	SD_SPI_RCC, ENABLE );	
	RCC_APB2PeriphClockCmd(	SD_SPI_SCK_GPIO_RCC|SD_SPI_MISO_GPIO_RCC|SD_SPI_MOSI_GPIO_RCC, ENABLE );	
 
	GPIO_InitStructure.GPIO_Pin = SD_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SD_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SD_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SD_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SD_SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SD_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

 	GPIO_SetBits(SD_SPI_SCK_GPIO_PORT,SD_SPI_SCK_PIN);
	GPIO_SetBits(SD_SPI_MISO_GPIO_PORT,SD_SPI_MISO_PIN);
	GPIO_SetBits(SD_SPI_MOSI_GPIO_PORT,SD_SPI_MOSI_PIN);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SD_SPI, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SD_SPI, ENABLE); //使能SPI外设
	
	SPIx_ReadWriteByte(0xff);//启动传输		 
}   

 /**
  * @file   SPIx_SetSpeed
  * @brief  速度设置
  * @param  SpeedSet:速度参数
  * @retval 无
  */ 
void SPIx_SetSpeed(u8 SpeedSet)
{
	SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
  SPI_Init(SD_SPI, &SPI_InitStructure);
	SPI_Cmd(SD_SPI,ENABLE);
} 



 /**
  * @file   SPIx_ReadWriteByte
  * @brief  读写一个字节
  * @param  TxData:要写入的字节
  * @retval 读取到的字节
  */
u8 SPIx_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 
	while (SPI_I2S_GetFlagStatus(SD_SPI, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  

	SPI_I2S_SendData(SD_SPI, TxData); //通过外设SPIx发送一个数据
	retry=0;
	while (SPI_I2S_GetFlagStatus(SD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
	{
		;
	} //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SD_SPI); //返回通过SPIx最近接收的数据					    
}












