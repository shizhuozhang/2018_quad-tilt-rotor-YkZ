#include "H_define.h"

/*参考原子ALIENTEK源码*/    

#if __TIM1_PWM
void TIM1_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB2ENR|=1<<11; 	//TIM1时钟使能  
	RCC->APB2ENR|=1<<2;		//IO端口A的时钟使能
	GPIOA->CRH&=0XFFFF0000;	//PA8,PA9,PA10,PA11
	GPIOA->CRH|=0X0000BBBB;	//复用功能输出 
	
	TIM1->ARR=arr;			//设定计数器自动重装值 
	TIM1->PSC=psc;			//预分频器设置
  
	TIM1->CCMR1|=0X0D<<3;  	//CH1输出,PWM1模式,预装载使能			 
	TIM1->CCMR1|=0X0D<<11; 	//CH2输出,PWM1模式,预装载使能
	TIM1->CCMR2|=0X0D<<3;  	//CH3输出,PWM1模式,预装载使能			 
	TIM1->CCMR2|=0X0D<<11; 	//CH4输出,PWM1模式,预装载使能
							
 	TIM1->CCER|=0X1111;   	//OC1,2,3,4 输出使能，输出极性为高电平有效	   
	TIM1->BDTR|=1<<15;   	//高级定时器特有的寄存器，MOE 主输出使能	   

	TIM1->CR1=0x0080;   	//向上计数，自动重装载使能 
	TIM1->CR1|=0x01;    	//使能定时器1 
	
    TIM1->CCR1=0;    	//初始装载值
	TIM1->CCR2=0;    	//初始装载值
	TIM1->CCR3=0;    	//初始装载值
	TIM1->CCR4=0;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM2_PWM
//重映射引脚的通道1，2和JTAG系统引脚冲突，禁用JTAG模式后，无法下载程序，原因未明，
//因此暂时TIM2只使能3，4通道输出。
void TIM2_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 	
	RCC->APB1ENR|=1<<0; 	//TIM2时钟使能  
	RCC->APB2ENR|=1<<2;		//IO端口A的时钟使能
	RCC->APB2ENR|=1<<3;		//IO端口B的时钟使能	
	RCC->APB2ENR|=1<<0;		//AFIO端口复用时钟使能
	
	JTAG_Set(SWD_ENABLE);	//关闭jtag
	AFIO->MAPR|=3<<8;		//将TIM2部分重映射
	//注意此时的重映射中带有SWD的引脚PB3(CH2)，按ret下载
	//若将上面两语句反过来，则只有CH2可用，且下程序正常
	
	GPIOA->CRH&=0X0FFFFFFF;	//PA15,注意上电复位后，该脚默认为JTAG引脚，要禁用JTAG模式
	GPIOA->CRH|=0XB0000000;	//复用功能输出 
	GPIOB->CRL&=0XFFFF0FFF;	//PB3，注意上电复位后，该脚默认为JTAG引脚，要禁用JTAG模式
	GPIOB->CRL|=0X0000B000;	//复用功能输出 	
	GPIOB->CRH&=0XFFFF00FF;	//PB10,PB11
	GPIOB->CRH|=0X0000BB00;	//复用功能输出 	
	
	TIM2->ARR=arr;			//设定计数器自动重装值 
	TIM2->PSC=psc;			//预分频器设置
  
	TIM2->CCMR1|=0X0D<<3;  	//CH1输出,PWM1模式,预装载使能			 
	TIM2->CCMR1|=0X0D<<11; 	//CH2输出,PWM1模式,预装载使能
	TIM2->CCMR2|=0X0D<<3;  	//CH3输出,PWM1模式,预装载使能			 
	TIM2->CCMR2|=0X0D<<11; 	//CH4输出,PWM1模式,预装载使能
							
 	TIM2->CCER|=0X1111;   	//OC3,4 输出使能，输出极性为高电平有效	   	   

	TIM2->CR1=0x0080;   	//向上计数，自动重装载使能 
	TIM2->CR1|=0x01;    	//使能定时器2 
	 
    TIM2->CCR1=0;    	//初始装载值
	TIM2->CCR2=0;    	//初始装载值
	TIM2->CCR3=0;    	//初始装载值
	TIM2->CCR4=0;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM3_PWM
void TIM3_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB1ENR|=1<<1; 	//TIM3时钟使能  
	RCC->APB2ENR|=1<<2;		//IO端口A的时钟使能
	RCC->APB2ENR|=1<<3;		//IO端口B的时钟使能	
	GPIOA->CRL&=0X00FFFFFF;	//PA6,PA7
	GPIOA->CRL|=0XBB000000;	//复用功能输出 	
	GPIOB->CRL&=0XFFFFFF00;	//PB0,PB1
	GPIOB->CRL|=0X000000BB;	//复用功能输出 	
	
	TIM3->ARR=arr;			//设定计数器自动重装值 
	TIM3->PSC=psc;			//预分频器设置
  
	TIM3->CCMR1|=0X0D<<3;  	//CH1输出,PWM1模式,预装载使能			 
	TIM3->CCMR1|=0X0D<<11; 	//CH2输出,PWM1模式,预装载使能
	TIM3->CCMR2|=0X0D<<3;  	//CH3输出,PWM1模式,预装载使能			 
	TIM3->CCMR2|=0X0D<<11; 	//CH4输出,PWM1模式,预装载使能
							
 	TIM3->CCER|=0X1111;   	//OC1,2,3,4 输出使能，输出极性为高电平有效	   	   

	TIM3->CR1=0x0080;   	//向上计数，自动重装载使能 
	TIM3->CR1|=0x01;    	//使能定时器3 
	
    TIM3->CCR1=0;    	//初始装载值
	TIM3->CCR2=0;    	//初始装载值
	TIM3->CCR3=0;    	//初始装载值
	TIM3->CCR4=0;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif

#if __TIM4_PWM
void TIM4_PWM_Init(u16 arr,u16 psc)//arr：自动重装值; psc：时钟预分频数
{		 					 
	RCC->APB1ENR|=1<<2; 	//TIM4时钟使能  
	RCC->APB2ENR|=1<<3;		//IO端口B的时钟使能
	GPIOB->CRL&=0X00FFFFFF;	//PB6,PB7
	GPIOB->CRL|=0XBB000000;	//复用功能输出 	
	GPIOB->CRH&=0XFFFFFF00;	//PB8,PB9
	GPIOB->CRH|=0X000000BB;	//复用功能输出  
	
	TIM4->ARR=arr;			//设定计数器自动重装值 
	TIM4->PSC=psc;			//预分频器设置
  
	TIM4->CCMR1|=0X0D<<3;  	//CH1输出,PWM1模式,预装载使能			 
	TIM4->CCMR1|=0X0D<<11; 	//CH2输出,PWM1模式,预装载使能
	TIM4->CCMR2|=0X0D<<3;  	//CH3输出,PWM1模式,预装载使能			 
	TIM4->CCMR2|=0X0D<<11; 	//CH4输出,PWM1模式,预装载使能
							
 	TIM4->CCER|=0X1111;   	//OC1,2,3,4 输出使能，输出极性为高电平有效	   

	TIM4->CR1=0x0080;   	//向上计数，自动重装载使能 
	TIM4->CR1|=0x01;    	//使能定时器4 
	
    TIM4->CCR1=4500;    	//初始装载值
	TIM4->CCR2=4500;    	//初始装载值
	TIM4->CCR3=4500;    	//初始装载值
	TIM4->CCR4=4500;    	//初始装载值
	//PWM输出模式1下，占空比的计算方法为CCR1/ARR*100%
	//PWM输出模式2下，占空比的计算方法为(1-CCR1/ARR)*100%
} 
#endif




