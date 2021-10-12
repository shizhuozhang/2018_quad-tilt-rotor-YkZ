/**
  * @attention
  *	IO口引脚配置文件
  * 一方面作为输出口，用于LED和蜂鸣器的驱动，一方面作为输入口，接收外部中断。
  * LED0作为系统运行指示灯，LED1为状态指示灯，BEEP为状态提醒
  * 
  ******************************************************************************
**/  

#include "H_define.h"


#if __LED
void LED_Init(void)
{
	RCC->APB2ENR|=1<<4;   //使能PORTC口时钟  
	GPIOC->CRL&=0XFFFFF0FF;//IO状态设置
	GPIOC->CRL|=0X00000300;//IO状态设置 
	GPIOC->ODR|=1<<2;		//PC2
	RCC->APB2ENR|=1<<5;   //使能PORTD口时钟  
	GPIOD->CRL&=0XFFFFF0FF;//IO状态设置
	GPIOD->CRL|=0X00000300;//IO状态设置 
	GPIOD->ODR|=1<<2;		//PD2
}

#endif


#if __BEEP
void BEEP_Init(void)
{
	RCC->APB2ENR|=1<<3;   //使能PORTB口时钟  
	GPIOB->CRH&=0XFFFF0FFF;//IO状态设置
	GPIOB->CRH|=0X00003000;//IO状态设置 
	GPIOB->ODR|=0<<11;		//PB11
}

#endif

#if __KEY
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	GPIOA->CRL&=0XFFFF0000;		  
	GPIOA->CRL|=0X00008888; //PA0,1,2,3设置成输入  		 
	GPIOA->ODR|=1<<1;//PA0默认下拉,PA1,2,3上拉
	GPIOA->ODR|=1<<2;
	GPIOA->ODR|=1<<3;
//	GPIOA->ODR|=0X00001110;//为什么这样写不能上拉??
} 	

u8 KEY_Scan(void)
{	 
	if(KEY1==1||KEY2==0||KEY3==0||KEY4==0)
	{
		delay_ms(5);//去抖动 
		if(KEY1==1)
			return KEY1_PRES;
		else if(KEY2==0)
			return KEY2_PRES;
		else if(KEY3==0)
			return KEY3_PRES; 
		else if(KEY4==0)
			return KEY4_PRES; 
	} 	     
	return 0;// 无按键按下
}

#endif


#if __ELSE
void ELSE_IO_Init(void)
{
//	JTAG_Set(SWD_ENABLE);	//若使用到默认IO引脚，关闭JTAG,开启SWD
	RCC->APB2ENR|=1<<3;   //使能PORTB口时钟  
	GPIOB->CRL&=0XFFFFFFF0;//IO状态设置
	GPIOB->CRL|=0X00000003;//IO状态设置 
	GPIOB->ODR|=0<<0;		//PB11
}

#endif

#if __EXTI	
//外部中断配置
void EXTIx_Init(void)		//直接调用sys.c对外部中断的配置
{
	Ex_NVIC_Config(GPIO_A,0,RTIR);//PA0，外部上升沿触发
	Ex_NVIC_Config(GPIO_A,1,FTIR);//PA1，外部上升沿触发
	Ex_NVIC_Config(GPIO_A,2,FTIR);//PA2，外部上升沿触发
	Ex_NVIC_Config(GPIO_A,3,FTIR);//PA3，外部上升沿触发	
	MY_NVIC_Init(2,0,EXTI0_IRQn,2);//中断优先级设为低
	MY_NVIC_Init(2,1,EXTI1_IRQn,2);//中断优先级设为低
	MY_NVIC_Init(2,1,EXTI2_IRQn,2);//中断优先级设为低
	MY_NVIC_Init(2,1,EXTI3_IRQn,2);//中断优先级设为低
}
//extern u8 t;
//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY1==1)	//对应确认按键 
	{
	//	BEEP0=!BEEP0;
//	t=1;
	}		 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}
//外部中断1服务程序
void EXTI1_IRQHandler(void)
{			
	delay_ms(10);   //消抖			 
    if(KEY2==0)	//对应取消按键
	{
//		t=2;
	}
 	EXTI->PR=1<<1;     //清除LINE1上的中断标志位  
}
//外部中断2服务程序
void EXTI2_IRQHandler(void)
{			
	delay_ms(10);   //消抖			 
    if(KEY3==0)	//对应取消按键
	{
//		t=3;
	}
 	EXTI->PR=1<<2;     //清除LINE1上的中断标志位  
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{			
	delay_ms(10);   //消抖			 
    if(KEY4==0)	//对应取消按键
	{
//		t=4;
	}
 	EXTI->PR=1<<3;     //清除LINE1上的中断标志位  
}

#endif


