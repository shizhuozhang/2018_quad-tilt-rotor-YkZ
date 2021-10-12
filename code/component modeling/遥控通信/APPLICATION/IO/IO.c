/**
  * @attention
  *	IO�����������ļ�
  * 
  * 
  ******************************************************************************
**/  

#include "H_define.h"

#if __LED
void LED_Init(void)
{
	RCC->AHB1ENR|=1<<4;//ʹ��PORTEʱ�� 
	GPIO_Set(GPIOE,PIN1|PIN2,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);
	//PE1,PE2�������죬������50M�ٶȣ������
	LED0=1;//LED0�ر�
	LED1=1;//LED1�ر�
}

#endif


#if __BEEP
void BEEP_Init(void)
{
	RCC->AHB1ENR|=1<<4;//ʹ��PORTEʱ�� 
	GPIO_Set(GPIOE,PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PD);
	//PE0�������죬������50M�ٶȣ������
	BEEP=0;//BEEP�ر�
}
#endif

#if __KEY
void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<4;//ʹ��PORTEʱ�� 
	GPIO_Set(GPIOE,PIN3|PIN4,GPIO_MODE_IN,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);
	//PE3,PE4������������ͨ���룬�ٶȺ�����������Ч
} 	

u8 KEY_Scan(void)
{	 
	if(KEY1==0||KEY2==0)
	{
		delay_ms(5);//ȥ���� 
		if(KEY1==0)
			return KEY1_PRES;
		else if(KEY2==0)
			return KEY2_PRES;
	} 	     
	return 0;// �ް�������
}

#endif


#if __ELSE
//IO��ʱ�ӷֲ�:portA��portI��ӦRCC_AHB1ENR[0:8]
//��portA��ӦRCC_AHB1ENR[0];//portB��ӦRCC_AHB1ENR[1];//portC��ӦRCC_AHB1ENR[2];
//��portD��ӦRCC_AHB1ENR[3];//portE��ӦRCC_AHB1ENR[4];//portF��ӦRCC_AHB1ENR[5];
//��portG��ӦRCC_AHB1ENR[6];//portH��ӦRCC_AHB1ENR[7];//portI��ӦRCC_AHB1ENR[8];
void ELSE_IO_Init(void)
{
	RCC->AHB1ENR|=1<<4;//ʹ��PORTEʱ�� 
	GPIO_Set(GPIOE,PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PD);
}

#endif

#if __EXTI	
/*
//IO�ڵ��ⲿ�ж�Ҫ���ڲ����ú������������ڸ��Žϴ�ĵط����ⲿҲҪ������������
//�����жϣ�һ��Ҫд��Ӧ���жϷ�������������ܵ��³������
//�ⲿ�ж�0��4���е������жϷ����������Ǵ�5��ʼ�����Ƕ���жϹ���һ��������
//�����жϷ����������֣��������ļ�xx.s���涨��ã��õ���ʱ��Ҫȥ��*/

//�ⲿ�ж�����
void EXTIx_Init(void)		//ֱ�ӵ���sys.c���ⲿ�жϵ�����
{
	Ex_NVIC_Config(GPIO_E,3,FTIR);//PA0���ⲿ�����ش���
	Ex_NVIC_Config(GPIO_E,4,FTIR);//PA1���ⲿ�����ش���
	MY_NVIC_Init(2,0,EXTI3_IRQn,2);//�ж����ȼ���Ϊ��
	MY_NVIC_Init(2,1,EXTI4_IRQn,2);//�ж����ȼ���Ϊ��
}
//extern u8 t;
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(5);	//����
	if(KEY1==0)	//��Ӧȷ�ϰ��� 
	{
	//	BEEP0=!BEEP0;
//	t=1;
	}		 
	EXTI->PR=1<<3;  //���LINE0�ϵ��жϱ�־λ  
}
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{			
	delay_ms(5);   //����			 
    if(KEY2==0)	//��Ӧȡ������
	{
//		t=2;
	}
 	EXTI->PR=1<<4;     //���LINE1�ϵ��жϱ�־λ  
}

#endif


