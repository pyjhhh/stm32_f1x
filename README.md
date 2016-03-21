# stm32_f1x
pyjhhh@gmail.com stm32_f1x

1、 STM32F103C8T6： 
内    核：Cortex-M3 32-bit RISC； 
工作频率：72MHz； 
存储资源：64K Byte Flash ，20KByte SRAM； 
2、AT24C08：1024Byte x8，高数据传输速率为400KHz和IIC总线兼容，擦除次数在100万次左右，数据存储可大100年； 
3、RS485电路：采用美信的MAX485芯片，可实现高达2.5Mbps的传输速度。 
4、CAN电路：采用TI的3.3V CAN收发器SN65HVD230芯片，具有较高的通讯速率、良好抗干扰能力和高可靠性CAN总线的船型通信。 
5、 RS232电路：采用美信低功耗、3.0至5.5V供电、1Mbps的RS232收发器MAX3232ECAE。 
6、USB串口电路采用的是CH340 USB转串口电路 
7、RTC电路：针对STM32 RTC不起振的问题，我们采用了官方建议的低负载RTC晶振方案，并使用了爱普生品牌的晶振，而没有使用廉价的圆柱晶振。 
8、继电器电路:采用的是松乐的SRD-05VDC-SL-C型号的继电器，可接直流或者交流电、 
   其他参数：交流电压10A/250VAC  直流电压10A/30VDC 

