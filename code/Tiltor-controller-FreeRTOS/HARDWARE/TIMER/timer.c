#include "stm32f4xx_conf.h"

#if __SETITIM1
	void TIM1_Init(u16 arr,u16 psc)
	{
		RCC->APB2ENR|=1<<11;//定时器1初始化
		TIM1->ARR=arr;
		TIM1->PSC=psc;
		TIM1->DIER|=1<<0;//使能中断
		TIM1->CR1|=1<<7;//arpe使能
		TIM1->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(3,2,TIM1_UP_IRQn,2);
	}
	
	void TIM1_UP_IRQHandler(void) //计数器中断
	{
		if(TIM1->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM1->SR&=~(1<<0);//清除中断标志位 
	}		
#endif
	
#if __SETITIM2
	void TIM2_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<0;//定时器2初始化
		TIM2->ARR=arr;
		TIM2->PSC=psc;
		TIM2->DIER|=1<<0;//使能中断
		TIM2->CR1|=1<<7;//arpe使能
		TIM2->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(3,2,TIM2_IRQn,2);
	}
	
	void TIM2_IRQHandler(void) //计数器中断
	{
		if(TIM2->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM2->SR&=~(1<<0);//清除中断标志位 
	}
#endif
	
#if __SETITIM3
	void TIM3_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<1;//定时器3初始化
		TIM3->ARR=arr;
		TIM3->PSC=psc;
		TIM3->DIER|=1<<0;//使能中断
		TIM3->CR1|=1<<7;//arpe使能
		TIM3->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(3,2,TIM3_IRQn,2);
	}
	
	void TIM3_IRQHandler(void) //计数器中断
	{
		if(TIM3->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM3->SR&=~(1<<0);//清除中断标志位 
	}
#endif
	
#if __SETITIM4
	void TIM4_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<2;//定时器4初始化
		TIM4->ARR=arr;
		TIM4->PSC=psc;
		TIM4->DIER|=1<<0;//使能中断
		TIM4->CR1|=1<<7;//arpe使能
		TIM4->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(3,2,TIM4_IRQn,2);
	}
	
	void TIM4_IRQHandler(void) //计数器中断
	{
		if(TIM4->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM4->SR&=~(1<<0);//清除中断标志位 
	}
#endif
	
#if __SETITIM5
	void TIM5_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<3;//定时器5初始化
		TIM5->ARR=arr;
		TIM5->PSC=psc;
		TIM5->DIER|=1<<0;//使能中断
		TIM5->CR1|=1<<7;//arpe使能
		TIM5->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(3,2,TIM5_IRQn,2);
	}
	
	void TIM5_IRQHandler(void) //计数器中断
	{
		if(TIM5->SR&0x0001)
		{
			LED0=~LED0;
			LED1=~LED1;
		}
		TIM5->SR&=~(1<<0);//清除中断标志位 
	}
#endif
	
#if __SETITIM6
	void TIM6_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<4;//定时器6初始化
		TIM6->ARR=arr;
		TIM6->PSC=psc;
		TIM6->DIER|=1<<0;//使能中断
		TIM6->CR1|=1<<7;//arpe使能
		TIM6->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(1,2,TIM6_DAC_IRQn,2);
	}
	
	void TIM6_DAC_IRQHandler(void) //计数器中断
	{
		static u8 num1=0;
		if(TIM6->SR&0x0001)
		{
			if(Sbus_OK)
			{
				TIM8->CCR1=(u16)(4630-2.2*ControL_Data[1]);    	//初始装载值3000~6000
				TIM8->CCR2=(u16)(4440+2.2*ControL_Data[1]);  	//初始装载值
				TIM8->CCR3=(u16)(4680+2.2*ControL_Data[1]);     	//初始装载值
				TIM8->CCR4=(u16)(4430-2.2*ControL_Data[1]);     	//初始装载值
				
				TIM3->CCR1=(u16)(4500+2.16*ControL_Data[0]);    	//初始装载值3000~6000
				TIM3->CCR2=(u16)(4500+2.16*ControL_Data[0]);  	//初始装载值
				TIM3->CCR3=(u16)(4500+2.16*ControL_Data[3]);     	//初始装载值
				TIM3->CCR4=(u16)(4500-2.16*ControL_Data[3]);     	//初始装载值
				
				TIM1->CCR1=(u16)(3000+2*ControL_Data[2]);    	//初始装载值3000~6000
				TIM1->CCR2=(u16)(3000+2*ControL_Data[2]);     	//初始装载值
				TIM1->CCR3=(u16)(3000+2*ControL_Data[2]);    	//初始装载值
				TIM1->CCR4=(u16)(3000+2*ControL_Data[2]);     	//初始装载值
			}
			else
			{
				TIM8->CCR1=4630;    	//初始装载值
				TIM8->CCR2=4440;    	//初始装载值
				TIM8->CCR3=4680;    	//初始装载值
				TIM8->CCR4=4430;    	//初始装载值
				
				TIM3->CCR1=4500;    	//初始装载值
				TIM3->CCR2=4500;    	//初始装载值
				TIM3->CCR3=4500;    	//初始装载值
				TIM3->CCR4=4500;    	//初始装载值
				
				TIM1->CCR1=3000;    	//初始装载值
				TIM1->CCR2=3000;    	//初始装载值
				TIM1->CCR3=3000;    	//初始装载值
				TIM1->CCR4=3000;    	//初始装载值
			}
			num1++;
			if(num1>=250)
			{
				num1=0;
				LED0=~LED0;			
			}
			
		}
		TIM6->SR&=~(1<<0);//清除中断标志位 
	}
#endif
	
#if __SETITIM7

	void TIM7_Init(u16 arr,u16 psc)
	{
		RCC->APB1ENR|=1<<5;//定时器7初始化
		TIM7->ARR=arr;
		TIM7->PSC=psc;
		TIM7->DIER|=1<<0;//使能中断
		TIM7->CR1|=1<<7;//arpe使能
		TIM7->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(0,0,TIM7_IRQn,2);
	}

	void TIM7_IRQHandler(void) //计数器中断
	{
		if(TIM7->SR&0x0001)
		{
			FreeRTOSRunTimeTicks++;
		}
		TIM7->SR&=~(1<<0);//清除中断标志位 
	}
#endif
	
#if __SETITIM8
	void TIM8_Init(u16 arr,u16 psc)
	{
		RCC->APB2ENR|=1<<13;//定时器8初始化
		TIM8->ARR=arr;
		TIM8->PSC=psc;
		TIM8->DIER|=1<<0;//使能中断
		TIM8->CR1|=1<<7;//arpe使能
		TIM8->CR1|=1<<0;//使能计数器
		MY_NVIC_Init(3,2,TIM8_UP_IRQn,2);
	}
	
	void TIM8_UP_IRQHandler(void) //计数器中断
	{
		if(TIM8->SR&0x0001)
		{
			
		}
		TIM8->SR&=~(1<<0);//清除中断标志位 
	}
#endif


