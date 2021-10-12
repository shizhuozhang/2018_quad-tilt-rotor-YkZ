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
		MY_NVIC_Init(3,2,TIM6_IRQn,2);
	}
	
	
u8 Flag=0;	
u16 num=0;	
	void TIM6_IRQHandler(void) //�������ж�
	{
		if(TIM6->SR&0x0001)
		{
			
			Flag=1;
			num++;
			if(num>=500)
			{
				num=0;
				LED0=~LED0;
//				LED1=~LED1;				
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

//                 60*Z*����ʱ��Ƶ��f��
//�����ٶ�Ϊ     --------------------   ��r/min��
//			     ���������ֱ��ʣ�*T
//
u8	Print_Flag=0;
s16 Speed=0;
u16 Count_num=0;
s16 Speed_data[800]={0};
//s16 Encoder_num4=0;
	
//	u8 Tc=100   //�̶�ʱ��
//	   ,t1=0 	//��һ������ǰʱ��
//       ,t2=0	//���һ������ǰʱ��	   
//	   ,T=0;	//����ʱ��,
//	u16 cntL=0;	//��������ȥֵ

	s16 Z1=0;		
	s16 Z2=0;		

	void TIM7_IRQHandler(void) //�������ж�
	{
		static u8 x=2,y=0;
		if(TIM7->SR&0x0001)
		{
			if(y==1)
			{
				if(x==1)
				{
					Z2=TIM4->CNT-32760;
					TIM4->CNT=32760;
					x--;
					Print_Flag=1;
				}	
				else if(x==2)
				{
					Z1=TIM4->CNT-32760;
					TIM4->CNT=32760;
					x--;
				}
				else if(x==0)
					x=0;
									
			}
			Count_num++;
			if(Count_num>30)
			{
				Count_num=0;
				LED0=~LED0;
				IO_PC4=1;
				y=1;
			}
			delay_ms(1);			
//			Speed=M_T_Speed_measure(500,10);
		
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


