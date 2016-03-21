/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：can.c
 * 描述    ：CAN通讯模块的初始化操作
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 硬件连接: CAN_RX-->PB8;CAN_TX-->PB9
 * 调试方式：J-Link-OB
**********************************************************************************/	


//头文件
#include "can.h"

uint16_t CAN_ID;
uint8_t CAN_DATA0,CAN_DATA1,CAN_DATA2,CAN_DATA3,CAN_DATA4,CAN_DATA5,CAN_DATA6,CAN_DATA7;
uint8_t CanFlag,Display;
/* Private function prototypes -----------------------------------------------*/


/**
  * @file   GPIO_Configuration
  * @brief  Configures the different GPIO ports.
  * @param  无
  * @retval 无
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* CAN Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO ,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE); 
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);   
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);	     
}


 /**
  * @file   CAN_Configuration
  * @brief  Configures the CAN
  * @param  无
  * @retval 无
  */
void CAN_Configuration(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;

  GPIO_Configuration();
  /* CAN register init */
  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE; /* 时间触发禁止, 时间触发：CAN硬件的内部定时器被激活，并且被用于产生时间戳 */
  CAN_InitStructure.CAN_ABOM = DISABLE; /* 自动离线禁止，自动离线：一旦硬件监控到128次11个隐性位，就自动退出离线状态。在这里要软件设定后才能退出 */
  CAN_InitStructure.CAN_AWUM = DISABLE; /* 自动唤醒禁止，有报文来的时候自动退出休眠	*/
  CAN_InitStructure.CAN_NART = DISABLE; /* 报文重传, 如果错误一直传到成功止，否则只传一次 */
  CAN_InitStructure.CAN_RFLM = DISABLE; /* 接收FIFO锁定, 1--锁定后接收到新的报文摘不要，0--接收到新的报文则覆盖前一报文	*/
  CAN_InitStructure.CAN_TXFP = ENABLE;  /* 发送优先级  0---由标识符决定  1---由发送请求顺序决定	*/
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; /* 模式	*/
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;      /* 重新同步跳宽，只有can硬件处于初始化模式时才能访问这个寄存器 */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;      /* 时间段1 */
  CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;      /* 时间段2 */
  CAN_InitStructure.CAN_Prescaler = 45;         /* 波特率预分频数 */  
 
  /* 波特率计算方法 */
  /* CANbps= Fpclk/((BRP+1)*((Tseg1+1)+(Tseg2+1)+1)  此处计算为  CANbps=36000000/(45*(4+3+1))=100kHz */   														  //此处Tseg1+1 = CAN_BS1_8tp
  /* 配置大方向: Tseg1>=Tseg2  Tseg2>=tq; Tseg2>=2TSJW */
    
  if (CAN_Init(CAN1,&CAN_InitStructure) == CANINITFAILED) 		
  {
    /* 初始化时先设置CAN_MCR的初始化位 */  														
    /* 然后查看硬件是否真的设置了CAN_MSR的初始化位来确认是否进入了初始化模式  */		 													                  
  }	
  /* 配置CAN过滤器 */
  /* 32位对应的id */
  /* stdid[10:0]，extid[17:0],ide,rtr	*/
  /* 16位对应的id */
  /* stdid[10:0],ide,rtr,extid[17:15] */
  /* 一般使用屏蔽模式	*/
  /* 要注意的是fifo接收存满了中断，还有就是fifo的概念，即取的一直是最早那一个数据， 要释放才能取下一个数据 */
  /* 常使用的中断有 */
  /* 1,有信息中断，即fifo挂号中断 */
  /* 2,fifo满中断	*/
  /* 3,fifo满之后又有信息来则中断，即fifo溢出中断	*/
  CAN_FilterInitStructure.CAN_FilterNumber=0;     /* 过滤器0 */
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;  /* 屏敝模式 */
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; /* 32位 */
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;  /* 以下四个都为0, 表明不过滤任何id */
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;  /* 能够通过该过滤器的报文存到fifo0中 */
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);   /* 挂号中断, 进入中断后读fifo的报文函数释放报文清中断标志 */
  CAN_FilterInit(&CAN_FilterInitStructure);
}

 /**
  * @file   CanWriteData
  * @brief  Can Write Date to CAN-BUS
  * @param  无
  * @retval 无
  */
void CanWriteData(uint16_t ID)
{
  CanTxMsg TxMessage;

  CAN_DATA0=0xaa;  CAN_DATA1=0xbb;  
  CAN_DATA2=0xcc;  CAN_DATA3=0xdd;  
  CAN_DATA4=0xee;  CAN_DATA5=0xff;
  /* transmit */
  TxMessage.StdId = ID;  /* 设置标准id  注意标准id的最高7位不能全是隐性(1)。共11位 ,This parameter can be a value between 0 to 0x7FF. */
//TxMessage.ExtId = 0x00;     //设置扩展id  扩展id共18位
  TxMessage.RTR = CAN_RTR_DATA; /* 设置为数据帧 */
  TxMessage.IDE = CAN_ID_STD;   /* 使用标准id	*/
  TxMessage.DLC = 6;            /* 数据长度, can报文规定最大的数据长度为8字节 */
  TxMessage.Data[0] = CAN_DATA0;    
  TxMessage.Data[1] = CAN_DATA1;    
  TxMessage.Data[2] = CAN_DATA2;    
  TxMessage.Data[3] = CAN_DATA3;    
  TxMessage.Data[4] = CAN_DATA4;    
  TxMessage.Data[5] = CAN_DATA5;     
      
  CAN_Transmit(CAN1,&TxMessage);  /* 返回这个信息请求发送的邮箱号0,1,2或没有邮箱申请发送no_box */	
}




