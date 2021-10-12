//////////////////////////////////////////////////////////////////////////////////	 
//REFER TO:����ԭ��@ALIENTEK
//������̳:www.openedv.com
//////////////////////////////////////////////////////////////////////////////////  
#include "stm32f4xx_conf.h"

//����ϵͳ����ʱ��Ϊ168MHzʱ��ʱ������Ϊ1/168us,
//�������ڣ���һ�������������ڣ�ȡָ���д�洢���ȣ�Ϊ12��ʱ�����ڣ�1/14us��
//ָ�����ڣ���ִ��һ��ָ�������Ϊ1-4���������ڣ����ԼΪ0.3us,Ҳ����1us����������3�����롣	
void Init1(void)
{
	Stm32_Clock_Init(336,8,2,7);//ϵͳʱ��,����ʱ��,168Mhz 	
	MY_NVIC_PriorityGroupConfig(4);//�����ж����ȼ�����Ϊ4
	delay_init(168);		//��ʼ����ʱ����
	
	////////////����//////////////
	#if __USART1
		Usart1_init(84,115200);	//���ڳ�ʼ��Ϊ115200  
	#endif
	
	#if __USART2
		Usart2_init(42,115200);	//���ڳ�ʼ��Ϊ115200 
	#endif
	
	#if __USART3
		Usart3_init(42,100000);	//���ڳ�ʼ��Ϊ100000,100K 
	#endif
	
	#if __UART4
		Uart4_init(42,115200);	//���ڳ�ʼ��Ϊ115200 
	#endif
	
	#if __UART5
		Uart5_init(42,115200);	//���ڳ�ʼ��Ϊ115200 
	#endif
	
	#if __USART6
		Usart6_init(84,115200);	//���ڳ�ʼ��Ϊ115200 
	#endif
	
	#if __DMA_USART1
		
	#endif
	
	#if __DMA_USART2	
	DMA_Config_USART2(DMA1_Stream5,4,(u32)&USART2->DR,(u32)AHRS_DATA,42,2);	
	//AHRS���ݴ��ڽ��գ����ȼ���	
	#endif
	
	#if __DMA_USART3
	DMA_Config_USART3(DMA1_Stream1,4,(u32)&USART3->DR,(u32)SBUS_DATA,25,3);	
	//ң��������SBUS���ڽ��գ����ȼ����
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
	#if __SETITIM1							//TIM1�������ж�
		TIM1_Init(9,71);
	#endif
	#if __SETITIM2							//TIM2�������ж�
		TIM2_Init(9999,7199);
	#endif
	#if __SETITIM3							//TIM3�������ж�
		TIM3_Init(99,35999);
	#endif
	#if __SETITIM4							//TIM4�������ж�
		TIM4_Init(9999,7199);
	#endif
	#if __SETITIM5							//TIM5�������ж�
		TIM5_Init(999,7199);
	#endif
	#if __SETITIM6							//TIM6�������ж�
		TIM6_Init(2000,84);  					//Ƶ��84M/2000/84=500HZ
	#endif
	#if __SETITIM7							//TIM7�������ж�//������������ʱ��ļ��
//		TIM7_Init(50,84); 					//Ƶ��84M/50/84=20KHZ
	#endif
	#if __SETITIM8							//TIM8�������ж�
		TIM8_Init(9999,7199);
	#endif
	
	/*********PWMOUT***********/
//�����ĸ������ϵĶ���͵����FL(��ǰ)Ϊ1�ţ�FR(��ǰ)Ϊ2�ţ�BR(�Һ�)Ϊ3�ţ�FL(���)Ϊ4��
//ÿ�����Ͷ���ֱ��ӦPWM���ͨ����CH1-4��

	//(4200,20)10KHz;;(4200,40)168M/1KHz;(60000,28)84M/50Hz
	#if __TIM1_PWM					//ʱ��168MHz	
		TIM1_PWM_Init(60000-1,56-1);//
	#endif
	#if __TIM2_PWM					//ʱ��84MHz
		TIM2_PWM_Init(60000-1,28-1);//50Hz
	#endif
	#if __TIM3_PWM					//ʱ��84MHz
		TIM3_PWM_Init(60000-1,28-1);	//50Hz
	#endif
	#if __TIM4_PWM					//ʱ��84MHz
		TIM4_PWM_Init(60000-1,28-1);//50Hz
	#endif
	#if __TIM5_PWM					//ʱ��84MHz
		TIM5_PWM_Init(3600-1,20-1);
	#endif
	#if __TIM8_PWM					///ʱ��168MHz
		TIM8_PWM_Init(60000-1,56-1);	//50//������ת�Ķ�����ƣ�CH1-4�ֱ��Ӧ���1-4	
	#endif
	#if __TIM9_PWM					//ʱ��168MHz
		TIM9_PWM_Init(4500-1,40-1);
	#endif
	#if __TIM10_PWM					//ʱ��168MHz
		TIM10_PWM_Init(60000-1,28-1);
	#endif
	#if __TIM11_PWM					//ʱ��168MHz
		TIM11_PWM_Init(60000-1,28-1);
	#endif
	#if __TIM12_PWM					//ʱ��84MHz
		TIM12_PWM_Init(60000-1,28-1);
	#endif
	#if __TIM13_PWM					//ʱ��84MHz
		TIM13_PWM_Init(3600-1,20-1);
	#endif
	#if __TIM14_PWM					//ʱ��84MHz
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
	//ADC1_DATA���յ�ѹ���ݣ����ȼ���	
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












