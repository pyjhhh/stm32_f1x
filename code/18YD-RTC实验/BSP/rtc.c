/*******************************************************************************
* ���ļ�ʵ�ֻ���RTC�����ڹ��ܣ��ṩ�����յĶ�д��������ANSI-C��time.h��
* 
* RTC�б����ʱ���ʽ����UNIXʱ�����ʽ�ġ���һ��32bit��time_t������ʵΪu32��
*
* ANSI-C�ı�׼���У��ṩ�����ֱ�ʾʱ�������  �ͣ�
* time_t:   	UNIXʱ�������1970-1-1��ĳʱ�侭����������
* typedef unsigned int time_t;
* 
* struct tm:	Calendar��ʽ����������ʽ��
*   tm�ṹ���£�
*   struct tm {
*   int tm_sec;   // �� seconds after the minute, 0 to 60  (0 - 60 allows for the occasional leap second)
*   int tm_min;   // �� minutes after the hour, 0 to 59
*		int tm_hour;  // ʱ hours since midnight, 0 to 23
*		int tm_mday;  // �� day of the month, 1 to 31
*		int tm_mon;   // �� months since January, 0 to 11
*		int tm_year;  // �� years since 1900
*		int tm_wday;  // ���� days since Sunday, 0 to 6
*		int tm_yday;  // ��Ԫ��������� days since January 1, 0 to 365
* 	int tm_isdst; // ����ʱ����Daylight Savings Time flag
* 		...
* 	}
* 	����wday��yday�����Զ����������ֱ�Ӷ�ȡ
* 	mon��ȡֵΪ0-11
*	***ע��***��
*	tm_year:��time.h���ж���Ϊ1900�������ݣ���2008��Ӧ��ʾΪ2008-1900=108
* 	���ֱ�ʾ�������û���˵����ʮ���Ѻã�����ʵ�нϴ���졣
* 	�����ڱ��ļ��У����������ֲ��졣
* 	���ⲿ���ñ��ļ��ĺ���ʱ��tm�ṹ�����͵����ڣ�tm_year��Ϊ2008
* 	ע�⣺��Ҫ����ϵͳ��time.c�еĺ�������Ҫ���н�tm_year-=1900
* 
* ��Ա����˵����
* struct tm Time_ConvUnixToCalendar(time_t t);
* 	����һ��Unixʱ�����time_t��������Calendar��ʽ����
* time_t Time_ConvCalendarToUnix(struct tm t);
* 	����һ��Calendar��ʽ���ڣ�����Unixʱ�����time_t��
* time_t Time_GetUnixTime(void);
* 	��RTCȡ��ǰʱ���Unixʱ���ֵ
* struct tm Time_GetCalendarTime(void);
* 	��RTCȡ��ǰʱ�������ʱ��
* void Time_SetUnixTime(time_t);
* 	����UNIXʱ�����ʽʱ�䣬����Ϊ��ǰRTCʱ��
* void Time_SetCalendarTime(struct tm t);
* 	����Calendar��ʽʱ�䣬����Ϊ��ǰRTCʱ��
* 
* �ⲿ����ʵ����
* ����һ��Calendar��ʽ�����ڱ�����
* struct tm now;
* now.tm_year = 2008;
* now.tm_mon = 11;		//12��
* now.tm_mday = 20;
* now.tm_hour = 20;
* now.tm_min = 12;
* now.tm_sec = 30;
* 
* ��ȡ��ǰ����ʱ�䣺
* tm_now = Time_GetCalendarTime();
* Ȼ�����ֱ�Ӷ�tm_now.tm_wday��ȡ������
* 
* ����ʱ�䣺
* Step1. tm_now.xxx = xxxxxxxxx;
* Step2. Time_SetCalendarTime(tm_now);
* 
* ��������ʱ��Ĳ�
* struct tm t1,t2;
* t1_t = Time_ConvCalendarToUnix(t1);
* t2_t = Time_ConvCalendarToUnix(t2);
* dt = t1_t - t2_t;
* dt��������ʱ��������
* dt_tm = mktime(dt);	//ע��dt�����ƥ�䣬ansi���к���Ϊ�����ݣ�ע�ⳬ��
* ����Բο�������ϣ�����ansi-c��ĸ�ʽ������ȹ��ܣ�ctime��strftime��
* 
*******************************************************************************/

/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��RTC.c
 * ����    ����ʼ��RTC 
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2015-10-20
 * Ӳ������: ��
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/
#include "stm32f10x.h"
#include "rtc.h"
#include "led.h"
#include "OLED.h"
void Time_Set(u32 t);

 /**
  * @file   Time_ConvUnixToCalendar
  * @brief  ת��UNIXʱ���Ϊ����ʱ��
  * @param  - t: ��ǰʱ���UNIXʱ���
  * @retval struct tm
  */
struct tm Time_ConvUnixToCalendar(time_t t)
{
	struct tm *t_tm;
	t_tm = localtime(&t);
	t_tm->tm_year += 1900;	/* localtimeת�������tm_year�����ֵ����Ҫת�ɾ���ֵ */
	return *t_tm;
}


 /**
  * @file   Time_ConvCalendarToUnix
  * @brief  д��RTCʱ�ӵ�ǰʱ��
  * @param  - t: struct tm
  * @retval time_t
  */
time_t Time_ConvCalendarToUnix(struct tm t)
{
	t.tm_year -= 1900;  /* �ⲿtm�ṹ��洢�����Ϊ2008��ʽ	*/
						/* ��time.h�ж������ݸ�ʽΪ1900�꿪ʼ����� */
						/* ���ԣ�������ת��ʱҪ���ǵ�������ء�*/
	return mktime(&t);
}



 /**
  * @file   Time_GetUnixTime
  * @brief  ��RTCȡ��ǰʱ���Unixʱ���ֵ
  * @param  ��
  * @retval time_t
  */
time_t Time_GetUnixTime(void)
{
	return (time_t)RTC_GetCounter();
}

 /**
  * @file   Time_GetCalendarTime
  * @brief  ��RTCȡ��ǰʱ�������ʱ�䣨struct tm��
  * @param  ��
  * @retval struct tm
  */
struct tm Time_GetCalendarTime(void)
{
	time_t t_t;
	struct tm t_tm;

	t_t = (time_t)RTC_GetCounter();
	t_tm = Time_ConvUnixToCalendar(t_t);
	return t_tm;
}

 /**
  * @file   Time_SetUnixTime
  * @brief  ��������Unixʱ���д��RTC
  * @param  - t: time_t 
  * @retval ��
  */
void Time_SetUnixTime(time_t t)
{
	RTC_WaitForLastTask();
	RTC_SetCounter((u32)t);
	RTC_WaitForLastTask();
	return;
}

 /**
  * @file   Time_SetCalendarTime
  * @brief  ��������Calendar��ʽʱ��ת����UNIXʱ���д��RTC
  * @param  - t: struct tm
  * @retval ��
  */
void Time_SetCalendarTime(struct tm t)
{
	Time_SetUnixTime(Time_ConvCalendarToUnix(t));
	return;
}

 /**
  * @file   NVIC_Configuration
  * @brief  Configures the nested vectored interrupt controller.
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @file   RTC_Configuration
  * @brief  Configures the RTC.
  * @param  ��
  * @retval ��
  */
static void RTC_Configuration(void)
{
  //����PWR��BKP��ʱ�ӣ�from APB1��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
  //�������
  PWR_BackupAccessCmd(ENABLE);
  //���ݼĴ���ģ�鸴λ
  BKP_DeInit();
  //�ⲿ32.768Kʱ��ʹ��
  RCC_LSEConfig(RCC_LSE_ON);
  //�ȴ��ȶ�
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}
  //RTCʱ��Դ���ó�LSE���ⲿ32.768K��
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
  //RTC����
  RCC_RTCCLKCmd(ENABLE);
  //��������Ҫ�ȴ�APB1ʱ����RTCʱ��ͬ�������ܶ�д�Ĵ���
  RTC_WaitForSynchro();
  //��д�Ĵ���ǰ��Ҫȷ����һ�������Ѿ�����
  RTC_WaitForLastTask();
  //ʹ�����ж�
  RTC_ITConfig(RTC_IT_SEC, ENABLE);
  //�ȴ��Ĵ���д�����
  RTC_WaitForLastTask();
  //����RTC��Ƶ����ʹRTCʱ��Ϊ1Hz
  //RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)
  RTC_SetPrescaler(32767); 
  //�ȴ�д�����
  RTC_WaitForLastTask();
}

 /**
  * @file   USART_Scanf
  * @brief  USART Receive
  * @param  
	*					- min_value: 
	*         - max_value:
	*         - lenght:
  * @retval ��
  */
static uint16_t USART_Scanf(uint32_t min_value,uint32_t max_value,uint8_t lenght)
{
  uint16_t index = 0;
  uint32_t tmp[4] = {0, 0, 0, 0};
  while (index < lenght)
		{
			/* Loop until RXNE = 1 */
			while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
			{}
			tmp[index++] = (USART_ReceiveData(USART1));
			if( tmp[index - 1] == 0x0D ) 
				 { 
					 index--; 
					 continue;
				 }
			if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
					{
						printf("Please enter valid number between 0 and 9\r\n");
						index--;
					}
		 }
      /* Calculate the Corresponding value */
			if( lenght ==2 )
			index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10 );

			else  /* lenght ==4 */
      index = (tmp[3] - 0x30) + ((tmp[2] - 0x30) * 10 ) + ((tmp[1] - 0x30) * 100 ) + ((tmp[0] - 0x30) * 1000 );
      /* Checks */
			if (index > max_value || index < min_value)
			{
			  printf("Please enter valid number between %d and %d\r\n", min_value, max_value);
				return 0;
			}
      return index;
}

 /**
  * @file   Time_Regulate
  * @brief  RTCУ׼
  * @param  ��
  * @retval ��
  */
void Time_Regulate(void)
{
  struct tm time;
  memset(&time, 0 , sizeof(time) );	/* ��սṹ�� */
  printf("=======================Time Settings==========================\r\n");
  printf("Please Set Years between 1970 to 2037\r\n");
	
  while ( time.tm_year>2037 || time.tm_year<1970)
  {   
    time.tm_year = USART_Scanf(1970,2037,4);
  }
  printf("Set Years:  %d\r\n", time.tm_year);

  printf("Please Set Months between 01 to 12\r\n");
  while (time.tm_mon >12 || time.tm_mon < 1 )
  {
    time.tm_mon= USART_Scanf(1,12,2)-1;
  }
  printf("Set Months:  %d\r\n", time.tm_mon);

  printf("Please Set Days between 01 to 31\r\n");
  while (time.tm_mday >31 ||time.tm_mday <1 )
  {
    time.tm_mday = USART_Scanf(1,31,2);
  }
  printf("Set Days:  %d\r\n", time.tm_mday);

  printf("Please Set Hours between 01 to 23\r\n");
  while (time.tm_hour >23 ||time.tm_hour <1 )
  {
    time.tm_hour = USART_Scanf(1,23,2);
  }
  printf("Set Hours:  %d\r\n", time.tm_hour);

  printf("Please Set Minutes between 01 to 59\r\n");
  while (time.tm_min >59 || time.tm_min <1 )
  {
    time.tm_min = USART_Scanf(1,59,2);
  }
  printf("Set Minutes:  %d\r\n", time.tm_min);

  printf("Please Set Seconds between 01 to 59\r\n");
  while (time.tm_sec >59 || time.tm_sec <1 )
  {
    time.tm_sec = USART_Scanf(1,59,2);
  }
  printf("Set Seconds:  %d\r\n", time.tm_sec);
  /* Return the value to store in RTC counter register */
  Time_SetCalendarTime(time);  
}

 /**
  * @file   RTC_Init
  * @brief  RTC Initialization
  * @param  ��
  * @retval ��
  */
void RTC_Init(void)
{
  if (BKP_ReadBackupRegister(BKP_DR1)!= 0xA5A5)
  {
    /* Backup data register value is not correct or not yet programmed (when
    the first time the program is executed) */
    printf("RTC not yet configured....\r\n");
    /* RTC Configuration */
     RTC_Configuration();
	   Time_Regulate();
	/* Adjust time by values entred by the user on the hyperterminal */
    printf("RTC configured....\r\n");
    BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
  }
  else
  {
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      printf("Power On Reset occurred....\r\n");
    }
    /* Check if the Pin Reset flag is set */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      printf("External Reset occurred....\r\n");
    }

    printf("No need to configure RTC....\r\n");
    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }

   /* NVIC configuration */
   NVIC_Configuration();

#ifdef RTCClockOutput_Enable
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Disable the Tamper Pin */
  BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
                                 functionality must be disabled */

  /* Enable RTC Clock Output on Tamper Pin */
  BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif

   /* Clear reset flags */
  RCC_ClearFlag();
  return;
}

 /**
  * @file   Time_Init
  * @brief  Printf Time
  * @param  ��
  * @retval ��
  */
void Time_Init(void)
{
    struct tm time;
    memset(&time, 0 , sizeof(time) );	/* ��սṹ�� */
    PWR_BackupAccessCmd(ENABLE);	
    RTC_WaitForLastTask(); 
    time.tm_year=2070;
    time.tm_mon=00;
    time.tm_mday=00;
    time.tm_hour=0;
    time.tm_min=0;
    time.tm_sec=0;
    Time_SetCalendarTime(time); 
    RTC_WaitForLastTask();
    PWR_BackupAccessCmd(DISABLE);	
    printf("=======================Time Settings==========================\r\n");
	 
}
 /**
  * @file   DateTimeDis_Init
  * @brief  ��ʼ����ʾ����ʾ
  * @param  ��
  * @retval ��
  */
void DateTimeDis_Init(void)
{
	 OLED_DispStr(10, 25, "    ��  ��  ��", &tFont12);
	 OLED_DispStr(10, 40, "  ʱ  ��  ��", &tFont12);
}

/**
  * @file   Time_Display
  * @brief  OLED��ʾʱ������
  * @param  ��
  * @retval ��
  */
u8 displayflag;
void Time_Display(void)
{
	 struct tm time;
	 time = Time_GetCalendarTime();
	 printf("Time: %d-%d-%d   %02d:%02d:%02d \r\n", time.tm_year, \
									 time.tm_mon+1, time.tm_mday,\
									 time.tm_hour, time.tm_min, time.tm_sec);
	OLED_DisDigital(10, 25,time.tm_year, &tFont12);//��ʾ��
	if((time.tm_mon+1)==1 && time.tm_mday==1 && time.tm_hour == 0 && time.tm_min == 0 && time.tm_sec == 0)
	{
		 OLED_DispStr(55, 25,"  ", &tFont12);
	}
	OLED_DisDigital(55, 25,(time.tm_mon+1), &tFont12);//��ʾ��
	
	if(time.tm_mday==1 && time.tm_hour == 0 && time.tm_min == 0 && time.tm_sec == 0)
	{
		 OLED_DispStr(78, 25,"  ", &tFont12);
	}
	OLED_DisDigital(78, 25,time.tm_mday, &tFont12);//��ʾ��
	
	if(time.tm_hour == 0 && time.tm_min == 0 && time.tm_sec == 0)
	{
		 OLED_DispStr(10, 40,"  ", &tFont12);
	}
	OLED_DisDigital(10, 40,time.tm_hour, &tFont12);//��ʾʱ
	
	if(time.tm_min == 0 && time.tm_sec == 0)
	{
		 OLED_DispStr(37, 40,"  ", &tFont12);
	}
	OLED_DisDigital(37, 40,time.tm_min, &tFont12);//��ʾ��
	
	if(time.tm_sec == 0)
	{
		 OLED_DispStr(63, 40,"  ", &tFont12);
	}
	OLED_DisDigital(63, 40,time.tm_sec, &tFont12);//��ʾ��
}

/**
  * @file   RTC_IRQHandler
  * @brief  RTC�жϴ���
  * @param  ��
  * @retval ��
  */
void RTC_IRQHandler(void)
{
  static uint8_t Display;
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
    /* Clear the RTC Second interrupt */
    RTC_ClearITPendingBit(RTC_IT_SEC);
//	  Display = ~Display;
    LEDXToggle(LED1);		
    Time_Display();
  }
}
