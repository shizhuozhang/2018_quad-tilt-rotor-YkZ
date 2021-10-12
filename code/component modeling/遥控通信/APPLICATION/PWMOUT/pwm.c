#include "H_define.h"

/*参考原子ALIENTEK源码*/    

#if __TIM1_PWM
void TIM1_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB2ENR|=1<<0; 	//TIM1时钟使能    
	RCC->AHB1ENR|=1<<4;   	//使能PORTE时钟	
	GPIO_Set(GPIOE,PIN9 |PIN11 |PIN13 |PIN14,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOE,9,1);	//PE9,AF1 
	GPIO_AF_Set(GPIOE,11,1);	//PE11,AF1 	
	GPIO_AF_Set(GPIOE,13,1);	//PE13,AF1 	
	GPIO_AF_Set(GPIOE,14,1);	//PE14,AF1 	
	
	TIM1->ARR=arr;		//设定计数器自动重装值 
	TIM1->PSC=psc;		//预分频器不分频 
	TIM1->CCMR1|=6<<4;  //CH1 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM1->CCMR1|=6<<12;  //CH2 PWM1模式
	TIM1->CCMR1|=1<<3; 	//CH1 预装载使能
	TIM1->CCMR1|=1<<11; //CH2 预装载使能
	
	TIM1->CCMR2|=6<<4;  //CH3 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM1->CCMR2|=6<<12;  //CH3 PWM1模式
	TIM1->CCMR2|=1<<3; 	//CH4 预装载使能
	TIM1->CCMR2|=1<<11; //CH4 预装载使能
	
	TIM1->CCER|=1<<0;   //OC1 输出使能	
	TIM1->CCER|=0<<1;   //OC1 高电平有效
	TIM1->CCER|=1<<4;   //OC2 输出使能	
	TIM1->CCER|=0<<5;   //OC2 高电平有效
	TIM1->CCER|=1<<8;   //OC3 输出使能	
	TIM1->CCER|=0<<9;   //OC3 高电平有效	
	TIM1->CCER|=1<<12;  //OC4 输出使能	
	TIM1->CCER|=0<<13;  //OC4 高电平有效
	//可用下面一行代码替代
//	TIM1->CCER|=0X1111;   	//OC1,2,3,4 输出使能，输出极性为高电平有效

	TIM1->CR1|=1<<7;   	//ARPE使能
	TIM1->CR1|=0<<4;   	//递增计数	
	TIM1->BDTR|=1<<15;   	//高级定时器特有的寄存器，MOE 主输出使能
	
 	TIM1->CR1|=1<<0;    //使能定时器1	
	
    TIM1->CCR1=3000;    	//初始装载值
	TIM1->CCR2=3000;    	//初始装载值
	TIM1->CCR3=3000;    	//初始装载值
	TIM1->CCR4=3000;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM2_PWM
void TIM2_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 	

} 
#endif

#if __TIM3_PWM
void TIM3_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB1ENR|=1<<1; 	//TIM3时钟使能    
	RCC->AHB1ENR|=1<<0;   	//使能PORTA时钟	
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟
	GPIO_Set(GPIOA,PIN6 |PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_Set(GPIOB,PIN0 |PIN1,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOA,6,2);	//PA6,AF0 
	GPIO_AF_Set(GPIOA,7,2);	//PA7,AF2 	
	GPIO_AF_Set(GPIOB,0,2);	//PB0,AF2 	
	GPIO_AF_Set(GPIOB,1,2);	//PB1,AF2 	
	
	TIM3->ARR=arr;		//设定计数器自动重装值 
	TIM3->PSC=psc;		//预分频器不分频 
	TIM3->CCMR1|=6<<4;  //CH1 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM3->CCMR1|=6<<12;  //CH2 PWM1模式
	TIM3->CCMR1|=1<<3; 	//CH1 预装载使能
	TIM3->CCMR1|=1<<11; //CH2 预装载使能
	
	TIM3->CCMR2|=6<<4;  //CH3 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM3->CCMR2|=6<<12;  //CH3 PWM1模式
	TIM3->CCMR2|=1<<3; 	//CH4 预装载使能
	TIM3->CCMR2|=1<<11; //CH4 预装载使能
	
	TIM3->CCER|=1<<0;   //OC1 输出使能	
	TIM3->CCER|=0<<1;   //OC1 高电平有效
	TIM3->CCER|=1<<4;   //OC2 输出使能	
	TIM3->CCER|=0<<5;   //OC2 高电平有效
	TIM3->CCER|=1<<8;   //OC3 输出使能	
	TIM3->CCER|=0<<9;   //OC3 高电平有效	
	TIM3->CCER|=1<<12;  //OC4 输出使能	
	TIM3->CCER|=0<<13;  //OC4 高电平有效
	//可用下面一行代码替代
//	TIM3->CCER|=0X1111;   	//OC1,2,3,4 输出使能，输出极性为高电平有效

	TIM3->CR1|=1<<7;   	//ARPE使能
	TIM3->CR1|=0<<4;   	//递增计数	
	
 	TIM3->CR1|=1<<0;    //使能定时器1	
	
    TIM3->CCR1=4500;    	//初始装载值
	TIM3->CCR2=4500;    	//初始装载值
	TIM3->CCR3=4500;    	//初始装载值
	TIM3->CCR4=4500;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM4_PWM
void TIM4_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB1ENR|=1<<2; 	//TIM4时钟使能    
	RCC->AHB1ENR|=1<<3;   	//使能PORTD时钟	
	GPIO_Set(GPIOD,PIN12 |PIN13 |PIN14 |PIN15,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOD,12,2);	//PD12,AF2 
	GPIO_AF_Set(GPIOD,13,2);	//PD13,AF2 	
	GPIO_AF_Set(GPIOD,14,2);	//PD14,AF2 	
	GPIO_AF_Set(GPIOD,15,2);	//PD15,AF2	
	
	TIM4->ARR=arr;		//设定计数器自动重装值 
	TIM4->PSC=psc;		//预分频器不分频 
	TIM4->CCMR1|=6<<4;  //CH1 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM4->CCMR1|=6<<12;  //CH2 PWM1模式
	TIM4->CCMR1|=1<<3; 	//CH1 预装载使能
	TIM4->CCMR1|=1<<11; //CH2 预装载使能
	
	TIM4->CCMR2|=6<<4;  //CH3 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM4->CCMR2|=6<<12;  //CH3 PWM1模式
	TIM4->CCMR2|=1<<3; 	//CH4 预装载使能
	TIM4->CCMR2|=1<<11; //CH4 预装载使能
	
	TIM4->CCER|=1<<0;   //OC1 输出使能	
	TIM4->CCER|=0<<1;   //OC1 高电平有效
	TIM4->CCER|=1<<4;   //OC2 输出使能	
	TIM4->CCER|=0<<5;   //OC2 高电平有效
	TIM4->CCER|=1<<8;   //OC3 输出使能	
	TIM4->CCER|=0<<9;   //OC3 高电平有效	
	TIM4->CCER|=1<<12;  //OC4 输出使能	
	TIM4->CCER|=0<<13;  //OC4 高电平有效
	//可用下面一行代码替代
//	TIM4->CCER|=0X1111;   	//OC1,2,3,4 输出使能，输出极性为高电平有效

	TIM4->CR1|=1<<7;   	//ARPE使能
	TIM4->CR1|=0<<4;   	//递增计数	
	
 	TIM4->CR1|=1<<0;    //使能定时器1	
	
    TIM4->CCR1=4500;    	//初始装载值
	TIM4->CCR2=4500;    	//初始装载值
	TIM4->CCR3=4500;    	//初始装载值
	TIM4->CCR4=4500;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM5_PWM
void TIM5_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	
} 
#endif

#if __TIM8_PWM
void TIM8_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB2ENR|=1<<1; 	//TIM8时钟使能    
	RCC->AHB1ENR|=1<<2;   	//使能PORTC时钟	
	GPIO_Set(GPIOC,PIN6 |PIN7 |PIN8 |PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOC,6,3);	//PC6,AF1 
	GPIO_AF_Set(GPIOC,7,3);	//PC7,AF1 	
	GPIO_AF_Set(GPIOC,8,3);	//PC8,AF1 	
	GPIO_AF_Set(GPIOC,9,3);	//PC9,AF1 	
	
	TIM8->ARR=arr;		//设定计数器自动重装值 
	TIM8->PSC=psc;		//预分频器不分频 
	TIM8->CCMR1|=6<<4;  //CH1 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM8->CCMR1|=6<<12;  //CH2 PWM1模式
	TIM8->CCMR1|=1<<3; 	//CH1 预装载使能
	TIM8->CCMR1|=1<<11; //CH2 预装载使能
	
	TIM8->CCMR2|=6<<4;  //CH3 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM8->CCMR2|=6<<12;  //CH3 PWM1模式
	TIM8->CCMR2|=1<<3; 	//CH4 预装载使能
	TIM8->CCMR2|=1<<11; //CH4 预装载使能
	
	TIM8->CCER|=1<<0;   //OC1 输出使能	
	TIM8->CCER|=0<<1;   //OC1 高电平有效
	TIM8->CCER|=1<<4;   //OC2 输出使能	
	TIM8->CCER|=0<<5;   //OC2 高电平有效
	TIM8->CCER|=1<<8;   //OC3 输出使能	
	TIM8->CCER|=0<<9;   //OC3 高电平有效	
	TIM8->CCER|=1<<12;  //OC4 输出使能	
	TIM8->CCER|=0<<13;  //OC4 高电平有效
	//可用下面一行代码替代
//	TIM8->CCER|=0X1111;   	//OC1,2,3,4 输出使能，输出极性为高电平有效

	TIM8->CR1|=1<<7;   	//ARPE使能
	TIM8->CR1|=0<<4;   	//递增计数	
	TIM8->BDTR|=1<<15;   	//高级定时器特有的寄存器，MOE 主输出使能
	
 	TIM8->CR1|=1<<0;    //使能定时器1	
	
    TIM8->CCR1=4500;    	//初始装载值
	TIM8->CCR2=4500;    	//初始装载值
	TIM8->CCR3=4500;    	//初始装载值
	TIM8->CCR4=4500;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM9_PWM
void TIM9_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB2ENR|=1<<16; 	//TIM9时钟使能    
	RCC->AHB1ENR|=1<<4;   	//使能PORTE时钟	
	GPIO_Set(GPIOE,PIN5 |PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOE,5,3);	//PE5,AF3 
	GPIO_AF_Set(GPIOE,6,3);	//PE6,AF3 	
	
	TIM9->ARR=arr;		//设定计数器自动重装值 
	TIM9->PSC=psc;		//预分频器不分频 
	TIM9->CCMR1|=0<<0;  //CH1配置为输出
	TIM9->CCMR1|=0<<8;	//CH2配置为输出
	TIM9->CCMR1|=6<<4;  //CH1 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM9->CCMR1|=6<<12;  //CH2 PWM1模式
	TIM9->CCMR1|=1<<3; 	//CH1 预装载使能
	TIM9->CCMR1|=1<<11; //CH2 预装载使能
	
	TIM9->CCER|=1<<0;   //OC1 输出使能	
	TIM9->CCER|=0<<1;   //OC1 高电平有效
	TIM9->CCER|=1<<4;   //OC2 输出使能	
	TIM9->CCER|=0<<5;   //OC2 高电平有效
	//可用下面一行代码替代
//	TIM9->CCER|=0X0011;   	//OC1,2,3,4 输出使能，输出极性为高电平有效

	TIM9->CR1|=1<<7;   	//ARPE使能
 	TIM9->CR1|=1<<0;    //使能定时器1	
	
    TIM9->CCR1=3000;    	//初始装载值
	TIM9->CCR2=3000;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM10_PWM
void TIM10_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB2ENR|=1<<17; 	//TIM10时钟使能    
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOB,8,3);	//PB8,AF3
	
	TIM10->ARR=arr;		//设定计数器自动重装值 
	TIM10->PSC=psc;		//预分频器不分频 
	
	TIM10->CCMR1|=6<<4;  //CH1 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM10->CCMR1|=1<<3; 	//CH1 预装载使能
	
	TIM10->CCER|=1<<0;   //OC1 输出使能	
	TIM10->CCER|=0<<1;   //OC1 高电平有效

	TIM10->CR1|=1<<7;   	//ARPE使能
	TIM10->CR1|=0<<4;   	//递增计数	
	
 	TIM10->CR1|=1<<0;    //使能定时器1	
	
    TIM10->CCR1=3000;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM11_PWM
void TIM11_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB2ENR|=1<<18; 	//TIM11时钟使能    
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOB,9,3);	//PA6,AF3 
	
	TIM11->ARR=arr;		//设定计数器自动重装值 
	TIM11->PSC=psc;		//预分频器不分频 
	
	TIM11->CCMR1|=6<<4;  //CH1 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM11->CCMR1|=1<<3; 	//CH1 预装载使能
	
	TIM11->CCER|=1<<0;   //OC1 输出使能	
	TIM11->CCER|=0<<1;   //OC1 高电平有效

	TIM11->CR1|=1<<7;   	//ARPE使能
	TIM11->CR1|=0<<4;   	//递增计数	
	
 	TIM11->CR1|=1<<0;    //使能定时器1	
	
    TIM11->CCR1=3000;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM12_PWM
void TIM12_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB1ENR|=1<<6; 	//TIM12时钟使能    
	RCC->AHB1ENR|=1<<1;   	//使能PORTB时钟	
	GPIO_Set(GPIOB,PIN14 |PIN15,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOB,14,9);	//PE5,AF3 
	GPIO_AF_Set(GPIOB,15,9);	//PE6,AF3 	
	
	TIM12->ARR=arr;		//设定计数器自动重装值 
	TIM12->PSC=psc;		//预分频器不分频 
	TIM12->CCMR1|=0<<0;  //CH1配置为输出
	TIM12->CCMR1|=0<<8;	//CH2配置为输出
	TIM12->CCMR1|=6<<4;  //CH1 PWM1模式	计数值小于装载值时是有效电平，低电平
	TIM12->CCMR1|=6<<12;  //CH2 PWM1模式
	TIM12->CCMR1|=1<<3; 	//CH1 预装载使能
	TIM12->CCMR1|=1<<11; //CH2 预装载使能
	
	TIM12->CCER|=1<<0;   //OC1 输出使能	
	TIM12->CCER|=0<<1;   //OC1 高电平有效
	TIM12->CCER|=1<<4;   //OC2 输出使能	
	TIM12->CCER|=0<<5;   //OC2 高电平有效
	//可用下面一行代码替代
//	TIM12->CCER|=0X0011;   	//OC1,2,3,4 输出使能，输出极性为高电平有效

	TIM12->CR1|=1<<7;   	//ARPE使能
 	TIM12->CR1|=1<<0;    //使能定时器1	
	
    TIM12->CCR1=3000;    	//初始装载值
	TIM12->CCR2=3000;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif


