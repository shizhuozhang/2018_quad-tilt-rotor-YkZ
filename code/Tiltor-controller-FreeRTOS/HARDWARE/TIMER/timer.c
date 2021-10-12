#include "stm32f4xx_conf.h"

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
		TIM3->CR1|=1<<0;//ʹ�ܼ�����
		MY_NVIC_Init(3,2,TIM3_IRQn,2);
	}
	
	void TIM3_IRQHandler(void) //�������ж�
	{
		if(TIM3->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
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
			LED1=~LED1;
		}
		TIM4->SR&=~(1<<0);//����жϱ�־λ 
	}
#endif
	
#if __SETITIM5
	void TIM5_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<3;//��ʱ��5��ʼ��
		TIM5->ARR=arr;
		TIM5->PSC=psc;
		TIM5->DIER|=1<<0;//ʹ���ж�
		TIM5->CR1|=1<<7;//arpeʹ��
		TIM5->CR1|=1<<0;//ʹ�ܼ�����
		MY_NVIC_Init(3,2,TIM5_IRQn,2);
	}
	
	void TIM5_IRQHandler(void) //�������ж�
	{
		if(TIM5->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM5->SR&=~(1<<0);//����жϱ�־λ 
	}
#endif
	
#if __SETITIM6
	void TIM6_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<4;//��ʱ��6��ʼ��
		TIM6->ARR=arr;
		TIM6->PSC=psc;
		TIM6->DIER|=1<<0;//ʹ���ж�
		TIM6->CR1|=1<<7;//arpeʹ��
		TIM6->CR1|=1<<0;//ʹ�ܼ�����
		MY_NVIC_Init(1,2,TIM6_DAC_IRQn,2);
	}
	
	void TIM6_DAC_IRQHandler(void) //�������ж�
	{
		static u8 num1=0;
		if(TIM6->SR&0x0001)
		{
			if(Sbus_OK)
			{
				TIM8->CCR1=(u16)(4630-2.2*ControL_Data[1]);    	//��ʼװ��ֵ3000~6000
				TIM8->CCR2=(u16)(4440+2.2*ControL_Data[1]);  	//��ʼװ��ֵ
				TIM8->CCR3=(u16)(4680+2.2*ControL_Data[1]);     	//��ʼװ��ֵ
				TIM8->CCR4=(u16)(4430-2.2*ControL_Data[1]);     	//��ʼװ��ֵ
				
				TIM3->CCR1=(u16)(4500+2.16*ControL_Data[0]);    	//��ʼװ��ֵ3000~6000
				TIM3->CCR2=(u16)(4500+2.16*ControL_Data[0]);  	//��ʼװ��ֵ
				TIM3->CCR3=(u16)(4500+2.16*ControL_Data[3]);     	//��ʼװ��ֵ
				TIM3->CCR4=(u16)(4500-2.16*ControL_Data[3]);     	//��ʼװ��ֵ
				
				TIM1->CCR1=(u16)(3000+2*ControL_Data[2]);    	//��ʼװ��ֵ3000~6000
				TIM1->CCR2=(u16)(3000+2*ControL_Data[2]);     	//��ʼװ��ֵ
				TIM1->CCR3=(u16)(3000+2*ControL_Data[2]);    	//��ʼװ��ֵ
				TIM1->CCR4=(u16)(3000+2*ControL_Data[2]);     	//��ʼװ��ֵ
			}
			else
			{
				TIM8->CCR1=4630;    	//��ʼװ��ֵ
				TIM8->CCR2=4440;    	//��ʼװ��ֵ
				TIM8->CCR3=4680;    	//��ʼװ��ֵ
				TIM8->CCR4=4430;    	//��ʼװ��ֵ
				
				TIM3->CCR1=4500;    	//��ʼװ��ֵ
				TIM3->CCR2=4500;    	//��ʼװ��ֵ
				TIM3->CCR3=4500;    	//��ʼװ��ֵ
				TIM3->CCR4=4500;    	//��ʼװ��ֵ
				
				TIM1->CCR1=3000;    	//��ʼװ��ֵ
				TIM1->CCR2=3000;    	//��ʼװ��ֵ
				TIM1->CCR3=3000;    	//��ʼװ��ֵ
				TIM1->CCR4=3000;    	//��ʼװ��ֵ
			}
			num1++;
			if(num1>=250)
			{
				num1=0;
				LED0=~LED0;			
			}
			
		}
		TIM6->SR&=~(1<<0);//����жϱ�־λ 
	}
#endif
	
#if __SETITIM7

	void TIM7_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<5;//��ʱ��7��ʼ��
		TIM7->ARR=arr;
		TIM7->PSC=psc;
		TIM7->DIER|=1<<0;//ʹ���ж�
		TIM7->CR1|=1<<7;//arpeʹ��
		TIM7->CR1|=1<<0;//ʹ�ܼ�����
		MY_NVIC_Init(0,0,TIM7_IRQn,2);
	}

	void TIM7_IRQHandler(void) //�������ж�
	{
		if(TIM7->SR&0x0001)
		{
			FreeRTOSRunTimeTicks++;
		}
		TIM7->SR&=~(1<<0);//����жϱ�־λ 
	}
#endif
	
#if __SETITIM8
	void TIM8_Init(u16 arr,u16 psc)
	{
		RCC->APB2ENR|=1<<13;//��ʱ��8��ʼ��
		TIM8->ARR=arr;
		TIM8->PSC=psc;
		TIM8->DIER|=1<<0;//ʹ���ж�
		TIM8->CR1|=1<<7;//arpeʹ��
		TIM8->CR1|=1<<0;//ʹ�ܼ�����
		MY_NVIC_Init(3,2,TIM8_UP_IRQn,2);
	}
	
	void TIM8_UP_IRQHandler(void) //�������ж�
	{
		if(TIM8->SR&0x0001)
		{
			
		}
		TIM8->SR&=~(1<<0);//����жϱ�־λ 
	}
#endif


