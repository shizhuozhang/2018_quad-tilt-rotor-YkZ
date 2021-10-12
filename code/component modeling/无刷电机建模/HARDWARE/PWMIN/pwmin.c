#include "H_define.h"

#if __TIM1_PWMIN
void TIM1_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<11; 	//TIM1时钟使能  
	RCC->APB2ENR|=1<<2;//GPIOA使能
	GPIOA->CRH&=0xfffffff0;//PA8浮空输入
	GPIOA->CRH|=0x00000008;
	TIM1->ARR=arr;			//设定计数器自动重装值 
	TIM1->PSC=psc;			//预分频器设置
	TIM1->CCMR1|=1<<0;//CC1被映射在TI1上
	TIM1->CCMR1|=2<<8;//CC2被影设在TI1上
	TIM1->SMCR|=5<<4;//滤波后定时器输入1
	TIM1->SMCR|=4<<0;//从模式为复位模式
	TIM1->CCER|=0<<1;//CC1上升沿有效
	TIM1->CCER|=1<<5;//CC2下降沿有效
	TIM1->CCER|=1<<0;//使能捕获
	TIM1->CCER|=1<<4;//使能捕获
	TIM1->CR1|=1<<0;//使能计数器
}
#endif
#if __TIM2_PWMIN
void TIM2_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;//tim2使能
	RCC->APB2ENR|=1<<2;//GPIOA使能
	GPIOA->CRH&=0x0fffffff;//PA15 浮空输入
	GPIOA->CRH|=0x80000000;
	JTAG_Set(SWD_ENABLE);	//关闭jtag
	AFIO->MAPR|=3<<8;		//将TIM2部分重映射
	//注意此时的重映射中带有SWD的引脚PB3(CH2)，按ret下载
	//若将上面两语句反过来，则只有CH2可用，且下程序正常
	TIM2->ARR=arr;			//设定计数器自动重装值 
	TIM2->PSC=psc;			//预分频器设置
	TIM2->CCMR1|=1<<0;//CC1被映射在TI1上
	TIM2->CCMR1|=2<<8;//CC2被影设在TI1上
	TIM2->SMCR|=5<<4;//滤波后定时器输入1
	TIM2->SMCR|=4<<0;//从模式为复位模式
	TIM2->CCER|=0<<1;//CC1上升沿有效
	TIM2->CCER|=1<<5;//CC2下降沿有效
	TIM2->CCER|=1<<0;//使能捕获
	TIM2->CCER|=1<<4;//使能捕获
	TIM2->CR1|=1<<0;//使能计数器
}
#endif
#if __TIM3_PWMIN
void TIM3_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;//tim3使能
	RCC->APB2ENR|=1<<2;//GPIOA使能
	GPIOA->CRL&=0xf0ffffff;//PA6 浮空输入
	GPIOA->CRL|=0x08000000;
	TIM3->ARR=arr;			//设定计数器自动重装值 
	TIM3->PSC=psc;			//预分频器设置
	TIM3->CCMR1|=1<<0;//CC1被映射在TI1上
	TIM3->CCMR1|=2<<8;//CC2被影设在TI1上
	TIM3->SMCR|=5<<4;//滤波后定时器输入1
	TIM3->SMCR|=4<<0;//从模式为复位模式
	TIM3->CCER|=0<<1;//CC1上升沿有效
	TIM3->CCER|=1<<5;//CC2下降沿有效
	TIM3->CCER|=1<<0;//使能捕获
	TIM3->CCER|=1<<4;//使能捕获
	TIM3->CR1|=1<<0;//使能计数器
}
#endif
#if __TIM4_PWMIN
void TIM4_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;//tim4使能
	RCC->APB2ENR|=1<<3;//GPIOB使能
	GPIOB->CRL&=0x0fffffff;//PB7 浮空输入
	GPIOB->CRL|=0x80000000;
	TIM4->ARR=arr;			//设定计数器自动重装值 
	TIM4->PSC=psc;			//预分频器设置
	TIM4->CCMR1|=2<<0;//CC1被映射在TI2上
	TIM4->CCMR1|=1<<8;//CC2被影设在TI2上
	TIM4->SMCR|=6<<4;//滤波后定时器输入1
	TIM4->SMCR|=4<<0;//从模式为复位模式
	TIM4->CCER|=0<<1;//CC1上升沿有效
	TIM4->CCER|=1<<5;//CC2下降沿有效
	TIM4->CCER|=1<<0;//使能捕获
	TIM4->CCER|=1<<4;//使能捕获
	TIM4->CR1|=1<<0;//使能计数器
}
#endif
#if __TIM5_PWMIN
void TIM5_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<3;//tim5使能
	RCC->APB2ENR|=1<<2;//GPIOA使能
	GPIOA->CRL&=0xffffff0f;//PA1 浮空输入
	GPIOA->CRL|=0x00000080;
	TIM5->ARR=arr;			//设定计数器自动重装值 
	TIM5->PSC=psc;			//预分频器设置
	TIM5->CCMR1|=2<<0;//CC1被映射在TI2上
	TIM5->CCMR1|=1<<8;//CC2被影设在TI2上
	TIM5->SMCR|=6<<4;//滤波后定时器输入1
	TIM5->SMCR|=4<<0;//从模式为复位模式
	TIM5->CCER|=0<<1;//CC1上升沿有效
	TIM5->CCER|=1<<5;//CC2下降沿有效
	TIM5->CCER|=1<<0;//使能捕获
	TIM5->CCER|=1<<4;//使能捕获
	TIM5->CR1|=1<<0;//使能计数器
}
#endif
#if __TIM8_PWMIN
void TIM8_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<13; 	//TIM8时钟使能 
	RCC->APB2ENR|=1<<4;//GPIOC使能
	GPIOC->CRL&=0x0fffffff;//PC7 浮空输入
	GPIOC->CRL|=0x80000000;
	TIM8->ARR=arr;			//设定计数器自动重装值 
	TIM8->PSC=psc;			//预分频器设置
	
	TIM8->CCMR1|=2<<0;//CC1被映射在TI2上
	TIM8->CCMR1|=1<<8;//CC2被影设在TI2上
	TIM8->SMCR|=6<<4;//滤波后定时器输入1
	
	TIM8->SMCR|=4<<0;//从模式为复位模式
	TIM8->CCER|=0<<1;//CC1上升沿有效
	TIM8->CCER|=1<<5;//CC2下降沿有效
	TIM8->CCER|=1<<0;//使能捕获
	TIM8->CCER|=1<<4;//使能捕获
	TIM8->CR1|=1<<0;//使能计数器
}
#endif


