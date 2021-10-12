//////////////////////////////////////////////////////////////////////////////////	 
//REFER TO:正点原子@ALIENTEK
//技术论坛:www.openedv.com
//////////////////////////////////////////////////////////////////////////////////  
#include "stm32f4xx_conf.h"

//设置系统运行时钟为168MHz时，时钟周期为1/168us,
//机器周期，即一个基本操作周期（取指令，读写存储器等）为12个时钟周期，1/14us，
//指令周期，即执行一条指令的周期为1-4个机器周期，最多约为0.3us,也就是1us至少能运行3条代码。	
void Init1(void)
{
	Stm32_Clock_Init(336,8,2,7);//系统时钟,设置时钟,168Mhz 	
	MY_NVIC_PriorityGroupConfig(4);//设置中断优先级分组为4
	delay_init(168);		//初始化延时函数
	
	////////////串口//////////////
	#if __USART1
		Usart1_init(84,115200);	//串口初始化为115200  
	#endif
	
	#if __USART2
		Usart2_init(42,115200);	//串口初始化为115200 
	#endif
	
	#if __USART3
		Usart3_init(42,100000);	//串口初始化为100000,100K 
	#endif
	
	#if __UART4
		Uart4_init(42,115200);	//串口初始化为115200 
	#endif
	
	#if __UART5
		Uart5_init(42,115200);	//串口初始化为115200 
	#endif
	
	#if __USART6
		Usart6_init(84,115200);	//串口初始化为115200 
	#endif
	
	#if __DMA_USART1
		
	#endif
	
	#if __DMA_USART2	
	DMA_Config_USART2(DMA1_Stream5,4,(u32)&USART2->DR,(u32)AHRS_DATA,42,2);	
	//AHRS数据串口接收，优先级高	
	#endif
	
	#if __DMA_USART3
	DMA_Config_USART3(DMA1_Stream1,4,(u32)&USART3->DR,(u32)SBUS_DATA,25,3);	
	//遥控器数据SBUS串口接收，优先级最高
	#endif	
	
	////////////LED//////////////
	#if __LED
		LED_Init();
	#endif
	#if __BEEP
		BEEP_Init();
	#endif
	#if __KEY
		KEY_Init();
	#endif
	#if __EXTI
		EXTIx_Init();
	#endif
	#if __ELSE
		ELSE_IO_Init();
	#endif
	
	/*********TIM***********///////////////////////////
	#if __SETITIM1							//TIM1计数器中断
		TIM1_Init(9,71);
	#endif
	#if __SETITIM2							//TIM2计数器中断
		TIM2_Init(9999,7199);
	#endif
	#if __SETITIM3							//TIM3计数器中断
		TIM3_Init(99,35999);
	#endif
	#if __SETITIM4							//TIM4计数器中断
		TIM4_Init(9999,7199);
	#endif
	#if __SETITIM5							//TIM5计数器中断
		TIM5_Init(999,7199);
	#endif
	#if __SETITIM6							//TIM6计数器中断
		TIM6_Init(2000,84);  					//频率84M/2000/84=500HZ
	#endif
	#if __SETITIM7							//TIM7计数器中断//用于任务运行时间的检测
//		TIM7_Init(50,84); 					//频率84M/50/84=20KHZ
	#endif
	#if __SETITIM8							//TIM8计数器中断
		TIM8_Init(9999,7199);
	#endif
	
	/*********PWMOUT***********/
//定义四个方向上的舵机和电机，FL(左前)为1号，FR(右前)为2号，BR(右后)为3号，FL(左后)为4号
//每组电机和舵机分别对应PWM输出通道的CH1-4。

	//(4200,20)10KHz;;(4200,40)168M/1KHz;(60000,28)84M/50Hz
	#if __TIM1_PWM					//时钟168MHz	
		TIM1_PWM_Init(60000-1,56-1);//
	#endif
	#if __TIM2_PWM					//时钟84MHz
		TIM2_PWM_Init(60000-1,28-1);//50Hz
	#endif
	#if __TIM3_PWM					//时钟84MHz
		TIM3_PWM_Init(60000-1,28-1);	//50Hz
	#endif
	#if __TIM4_PWM					//时钟84MHz
		TIM4_PWM_Init(60000-1,28-1);//50Hz
	#endif
	#if __TIM5_PWM					//时钟84MHz
		TIM5_PWM_Init(3600-1,20-1);
	#endif
	#if __TIM8_PWM					///时钟168MHz
		TIM8_PWM_Init(60000-1,56-1);	//50//用于倾转的舵机控制，CH1-4分别对应舵机1-4	
	#endif
	#if __TIM9_PWM					//时钟168MHz
		TIM9_PWM_Init(4500-1,40-1);
	#endif
	#if __TIM10_PWM					//时钟168MHz
		TIM10_PWM_Init(60000-1,28-1);
	#endif
	#if __TIM11_PWM					//时钟168MHz
		TIM11_PWM_Init(60000-1,28-1);
	#endif
	#if __TIM12_PWM					//时钟84MHz
		TIM12_PWM_Init(60000-1,28-1);
	#endif
	#if __TIM13_PWM					//时钟84MHz
		TIM13_PWM_Init(3600-1,20-1);
	#endif
	#if __TIM14_PWM					//时钟84MHz
		TIM14_PWM_Init(3599,1);		//
	#endif
	
	/*********PWMOUT***********/
	#if __TIM1_PWMIN
		 TIM1_PWMIN_Init(65535,71);
	#endif
	#if __TIM2_PWMIN
		 TIM2_PWMIN_Init(65535,71);
	#endif
	#if __TIM3_PWMIN
		 TIM3_PWMIN_Init(65535,71);
	#endif
	#if __TIM4_PWMIN
		 TIM4_PWMIN_Init(65535,71);
	#endif
	#if __TIM5_PWMIN
		 TIM5_PWMIN_Init(65535,71);
	#endif
	#if __TIM8_PWMIN
		 TIM8_PWMIN_Init(65535,71);
	#endif
	/**********cap********/
		#if __TIM1_CAP
		TIM1_Cap_Init(0xffff,71); 
	#endif
	#if __TIM2_CAP
		TIM2_Cap_Init(0xffff,71); 
	#endif
	#if __TIM3_CAP
		TIM3_Cap_Init(0xffff,71); 
	#endif
	#if __TIM4_CAP
		TIM4_Cap_Init(0xffff,71); 
	#endif
	#if __TIM5_CAP
		TIM5_Cap_Init(0xffff,71); 
	#endif
	#if __TIM8_CAP
		TIM8_Cap_Init(0xffff,71); 
	#endif
	
	/************ADC**********/
	#if __ADC1
	 ADC1_Init();
	#endif
	
	#if __ADC2
	 ADC2_Init();
	#endif
	
	#if __ADC3
	 ADC3_Init();
	#endif
	
	#if __DMA_ADC1
	DMA_Config_ADC1(DMA2_Stream0,0,(u32)&ADC1->DR,(u32)ADC1_DATA,6,1);
	//ADC1_DATA接收电压数据，优先级低	
	#endif

	#if __DMA_ADC3
		
	#endif
	
	/**********SPI************/
	#if __SPI1
		SPI1_Init();
	#endif
	#if __SPI2
		SPI2_Init();
	#endif
	#if __SPI3
		SPI3_Init();
	#endif

}

void Init2(void)//
{
	
}












