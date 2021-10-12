/**
  * @attention
  *	IO�����������ļ�
  * һ������Ϊ����ڣ�����LED�ͷ�������������һ������Ϊ����ڣ������ⲿ�жϡ�
  * LED0��Ϊϵͳ����ָʾ�ƣ�LED1Ϊ״ָ̬ʾ�ƣ�BEEPΪ״̬����
  * 
  ******************************************************************************
**/  

#include "H_define.h"


#if __LED
void LED_Init(void)
{
	RCC->APB2ENR|=1<<4;   //ʹ��PORTC��ʱ��  
	GPIOC->CRL&=0XFFFFF0FF;//IO״̬����
	GPIOC->CRL|=0X00000300;//IO״̬���� 
	GPIOC->ODR|=1<<2;		//PC2
	RCC->APB2ENR|=1<<5;   //ʹ��PORTD��ʱ��  
	GPIOD->CRL&=0XFFFFF0FF;//IO״̬����
	GPIOD->CRL|=0X00000300;//IO״̬���� 
	GPIOD->ODR|=1<<2;		//PD2
}

#endif


#if __BEEP
void BEEP_Init(void)
{
	RCC->APB2ENR|=1<<3;   //ʹ��PORTB��ʱ��  
	GPIOB->CRH&=0XFFFF0FFF;//IO״̬����
	GPIOB->CRH|=0X00003000;//IO״̬���� 
	GPIOB->ODR|=0<<11;		//PB11
}

#endif

#if __KEY
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��
	GPIOA->CRL&=0XFFFF0000;		  
	GPIOA->CRL|=0X00008888; //PA0,1,2,3���ó�����  		 
	GPIOA->ODR|=1<<1;//PA0Ĭ������,PA1,2,3����
	GPIOA->ODR|=1<<2;
	GPIOA->ODR|=1<<3;
//	GPIOA->ODR|=0X00001110;//Ϊʲô����д��������??
} 	

u8 KEY_Scan(void)
{	 
	if(KEY1==1||KEY2==0||KEY3==0||KEY4==0)
	{
		delay_ms(5);//ȥ���� 
		if(KEY1==1)
			return KEY1_PRES;
		else if(KEY2==0)
			return KEY2_PRES;
		else if(KEY3==0)
			return KEY3_PRES; 
		else if(KEY4==0)
			return KEY4_PRES; 
	} 	     
	return 0;// �ް�������
}

#endif


#if __ELSE
void ELSE_IO_Init(void)
{
//	JTAG_Set(SWD_ENABLE);	//��ʹ�õ�Ĭ��IO���ţ��ر�JTAG,����SWD
	RCC->APB2ENR|=1<<3;   //ʹ��PORTB��ʱ��  
	GPIOB->CRL&=0XFFFFFFF0;//IO״̬����
	GPIOB->CRL|=0X00000003;//IO״̬���� 
	GPIOB->ODR|=0<<0;		//PB11
}

#endif

#if __EXTI	
//�ⲿ�ж�����
void EXTIx_Init(void)		//ֱ�ӵ���sys.c���ⲿ�жϵ�����
{
	Ex_NVIC_Config(GPIO_A,0,RTIR);//PA0���ⲿ�����ش���
	Ex_NVIC_Config(GPIO_A,1,FTIR);//PA1���ⲿ�����ش���
	Ex_NVIC_Config(GPIO_A,2,FTIR);//PA2���ⲿ�����ش���
	Ex_NVIC_Config(GPIO_A,3,FTIR);//PA3���ⲿ�����ش���	
	MY_NVIC_Init(2,0,EXTI0_IRQn,2);//�ж����ȼ���Ϊ��
	MY_NVIC_Init(2,1,EXTI1_IRQn,2);//�ж����ȼ���Ϊ��
	MY_NVIC_Init(2,1,EXTI2_IRQn,2);//�ж����ȼ���Ϊ��
	MY_NVIC_Init(2,1,EXTI3_IRQn,2);//�ж����ȼ���Ϊ��
}
//extern u8 t;
//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY1==1)	//��Ӧȷ�ϰ��� 
	{
	//	BEEP0=!BEEP0;
//	t=1;
	}		 
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}
//�ⲿ�ж�1�������
void EXTI1_IRQHandler(void)
{			
	delay_ms(10);   //����			 
    if(KEY2==0)	//��Ӧȡ������
	{
//		t=2;
	}
 	EXTI->PR=1<<1;     //���LINE1�ϵ��жϱ�־λ  
}
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{			
	delay_ms(10);   //����			 
    if(KEY3==0)	//��Ӧȡ������
	{
//		t=3;
	}
 	EXTI->PR=1<<2;     //���LINE1�ϵ��жϱ�־λ  
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{			
	delay_ms(10);   //����			 
    if(KEY4==0)	//��Ӧȡ������
	{
//		t=4;
	}
 	EXTI->PR=1<<3;     //���LINE1�ϵ��жϱ�־λ  
}

#endif


