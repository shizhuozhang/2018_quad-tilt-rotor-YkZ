#include "H_define.h"

#if __SETITIM1
	void TIM1_Init(u16 arr,u16 psc)
	{
		RCC->APB2ENR|=1<<11;//��ʱ��1��ʼ��
		TIM1->ARR=arr;
		TIM1->PSC=psc;
		TIM1->DIER|=1<<0;//ʹ���ж�
		TIM1->CR1|=1<<7;//arpeʹ��
		TIM1->CR1|=1<<0;//ʹ�ܼ�����
		MY_NVIC_Init(3,2,TIM1_UP_IRQn,2);
	}
	
	void TIM1_UP_IRQHandler(void) //�������ж�
	{
		if(TIM1->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM1->SR&=~(1<<0);//����жϱ�־λ 
	}		
#endif
	
#if __SETITIM2
	void TIM2_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<0;//��ʱ��2��ʼ��
		TIM2->ARR=arr;
		TIM2->PSC=psc;
		TIM2->DIER|=1<<0;//ʹ���ж�
		TIM2->CR1|=1<<7;//arpeʹ��
		TIM2->CR1|=1<<0;//ʹ�ܼ�����
		MY_NVIC_Init(3,2,TIM2_IRQn,2);
	}
	
	void TIM2_IRQHandler(void) //�������ж�
	{
		if(TIM2->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM2->SR&=~(1<<0);//����жϱ�־λ 
	}
#endif
	
#if __SETITIM3
	void TIM3_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<1;//��ʱ��3��ʼ��
		TIM3->ARR=arr;
		TIM3->PSC=psc;
		TIM3->DIER|=1<<0;//ʹ���ж�
		TIM3->CR1|=1<<7;//arpeʹ��
//		TIM3->CR1|=1<<0;//ʹ�ܼ�����
		MY_NVIC_Init(1,1,TIM3_IRQn,2);
	}
u16 Led_num=0;
u8 time_num=0;
	void TIM3_IRQHandler(void) //�������ж�
	{
		if(TIM3->SR&0x0001)
		{										
		
			
			Led_num++;
			if(Led_num>500)//2HZ
			{
				LED1=~LED1;
				Led_num=0;
				time_num++;
			}
			if(time_num>8)
			{
				TIM4->CCR1=5000; 
			}	time_num=8;
		}
		TIM3->SR&=~(1<<0);//����жϱ�־λ 
	}
#endif
	
#if __SETITIM4
	void TIM4_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<2;//��ʱ��4��ʼ��
		TIM4->ARR=arr;
		TIM4->PSC=psc;
		TIM4->DIER|=1<<0;//ʹ���ж�
		TIM4->CR1|=1<<7;//arpeʹ��
		TIM4->CR1|=1<<0;//ʹ�ܼ�����
		MY_NVIC_Init(3,2,TIM4_IRQn,2);
	}
	
	void TIM4_IRQHandler(void) //�������ж�
	{
		if(TIM4->SR&0x0001)
		{
			LED0=~LED0;
		}
		TIM4->SR&=~(1<<0);//����жϱ�־λ 
	}
#endif
	



	
	
