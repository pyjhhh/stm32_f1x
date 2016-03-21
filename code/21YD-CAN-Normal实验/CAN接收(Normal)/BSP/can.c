/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��can.c
 * ����    ��CANͨѶģ��ĳ�ʼ������
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������: CAN_RX-->PB8;CAN_TX-->PB9
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/	


//ͷ�ļ�
#include "can.h"

uint16_t CAN_ID;
uint8_t CAN_DATA0,CAN_DATA1,CAN_DATA2,CAN_DATA3,CAN_DATA4,CAN_DATA5,CAN_DATA6,CAN_DATA7;
uint8_t CanFlag,Display;
/* Private function prototypes -----------------------------------------------*/


 /**
  * @file   GPIO_Configuration
  * @brief  Configures the different GPIO ports.
  * @param  ��
  * @retval ��
  */
void GPIO_Configuration(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
  /* CAN Periph clock enable */
  RCC_APB2PeriphClockCmd(CANx_GPIO_RCC | RCC_APB2Periph_AFIO ,ENABLE);
  RCC_APB1PeriphClockCmd(CANx_RCC, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap1_CANx,ENABLE); 
  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = CANx_RX;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(CANx_GPIO_PORT, &GPIO_InitStructure);   
  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = CANx_TX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(CANx_GPIO_PORT, &GPIO_InitStructure);	       
}

 /**
  * @file   NVIC_Configuration
  * @brief  Configures the nested vectored interrupt controller.
  * @param  ��
  * @retval ��
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable CAN1 RX0 interrupt IRQ channel */
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @file   CAN_Configuration
  * @brief  Configures the CAN
  * @param  ��
  * @retval ��
  */
void CAN_Configuration(void)
{
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  NVIC_Configuration();
  GPIO_Configuration();
  /* CAN register init */
  CAN_DeInit(CANx);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE; /* ʱ�䴥����ֹ, ʱ�䴥����CANӲ�����ڲ���ʱ����������ұ����ڲ���ʱ��� */
  CAN_InitStructure.CAN_ABOM = DISABLE; /* �Զ����߽�ֹ���Զ����ߣ�һ��Ӳ����ص�128��11������λ�����Զ��˳�����״̬��������Ҫ����趨������˳� */
  CAN_InitStructure.CAN_AWUM = DISABLE; /* �Զ����ѽ�ֹ���б�������ʱ���Զ��˳�����	*/
  CAN_InitStructure.CAN_NART = DISABLE; /* �����ش�, �������һֱ�����ɹ�ֹ������ֻ��һ�� */
  CAN_InitStructure.CAN_RFLM = DISABLE; /* ����FIFO����, 1--��������յ��µı���ժ��Ҫ��0--���յ��µı����򸲸�ǰһ����	*/
  CAN_InitStructure.CAN_TXFP = ENABLE;  /* �������ȼ�  0---�ɱ�ʶ������  1---�ɷ�������˳�����	*/
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; /* ģʽ	*/
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;      /* ����ͬ������ֻ��canӲ�����ڳ�ʼ��ģʽʱ���ܷ�������Ĵ��� */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;      /* ʱ���1 */
  CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;      /* ʱ���2 */
  CAN_InitStructure.CAN_Prescaler = 45;         /* ������Ԥ��Ƶ�� */  
 
  /* �����ʼ��㷽�� */
  /* CANbps= Fpclk/((BRP+1)*((Tseg1+1)+(Tseg2+1)+1)  �˴�����Ϊ  CANbps=36000000/(45*(4+3+1))=100kHz */   														  //�˴�Tseg1+1 = CAN_BS1_8tp
  /* ���ô���: Tseg1>=Tseg2  Tseg2>=tq; Tseg2>=2TSJW */
    
  if (CAN_Init(CANx,&CAN_InitStructure) == CANINITFAILED) 		
  {
    /* ��ʼ��ʱ������CAN_MCR�ĳ�ʼ��λ */  														
    /* Ȼ��鿴Ӳ���Ƿ����������CAN_MSR�ĳ�ʼ��λ��ȷ���Ƿ�����˳�ʼ��ģʽ  */		 													                  
  }	
  /* ����CAN������ */
  /* 32λ��Ӧ��id */
  /* stdid[10:0]��extid[17:0],ide,rtr	*/
  /* 16λ��Ӧ��id */
  /* stdid[10:0],ide,rtr,extid[17:15] */
  /* һ��ʹ������ģʽ	*/
  /* Ҫע�����fifo���մ������жϣ����о���fifo�ĸ����ȡ��һֱ��������һ�����ݣ� Ҫ�ͷŲ���ȡ��һ������ */
  /* ��ʹ�õ��ж��� */
  /* 1,����Ϣ�жϣ���fifo�Һ��ж� */
  /* 2,fifo���ж�	*/
  /* 3,fifo��֮��������Ϣ�����жϣ���fifo����ж�	*/
  CAN_FilterInitStructure.CAN_FilterNumber=0;     /* ������0 */
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;  /* ����ģʽ */
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; /* 32λ */
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;  /* �����ĸ���Ϊ0, �����������κ�id */
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;  /* �ܹ�ͨ���ù������ı��Ĵ浽fifo0�� */
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
  CAN_ITConfig(CANx,CAN_IT_FMP0, ENABLE);   /* �Һ��ж�, �����жϺ��fifo�ı��ĺ����ͷű������жϱ�־ */
  CAN_FilterInit(&CAN_FilterInitStructure);
	CAN_ITConfig(CANx,CAN_IT_FMP0, ENABLE);//FIFO0��Ϣ�Һ��ж�ʹ��
	
}
 /**
  * @file   USB_LP_CAN1_RX0_IRQHandler
  * @brief  This function handles USB Low Priority or CAN RX0 interrupts 
  * @param  ��
  * @retval ��
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	
  CanRxMsg RxMessage;
  CAN_Receive(CANx,CAN_FIFO0, &RxMessage);  /* �˺��������ͷ���������˵�,�ڷǱ�Ҫʱ,����Ҫ�Լ��ͷ� */
  CAN_ID=RxMessage.StdId;
  CAN_DATA0=RxMessage.Data[0];
  CAN_DATA1=RxMessage.Data[1];
  CAN_DATA2=RxMessage.Data[2];
  CAN_DATA3=RxMessage.Data[3];
  CAN_DATA4=RxMessage.Data[4];
  CAN_DATA5=RxMessage.Data[5];
  CAN_DATA6=RxMessage.Data[6];
  CAN_DATA7=RxMessage.Data[7];
  CAN_ClearITPendingBit(CANx,CAN_IT_FMP0);  /* ��������ж� */
 // CanFlag = ENABLE;
}




