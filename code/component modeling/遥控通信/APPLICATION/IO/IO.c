/**
  * @attention
  *	IO口引脚配置文件
  * 
  * 
  ******************************************************************************
**/  

#include "H_define.h"

#if __LED
void LED_Init(void)
{
	RCC->AHB1ENR|=1<<4;//使能PORTE时钟 
	GPIO_Set(GPIOE,PIN1|PIN2,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);
	//PE1,PE2设置推挽，上拉，50M速度，输出，
	LED0=1;//LED0关闭
	LED1=1;//LED1关闭
}

#endif


#if __BEEP
void BEEP_Init(void)
{
	RCC->AHB1ENR|=1<<4;//使能PORTE时钟 
	GPIO_Set(GPIOE,PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PD);
	//PE0设置推挽，下拉，50M速度，输出，
	BEEP=0;//BEEP关闭
}
#endif

#if __KEY
void KEY_Init(void)
{
	RCC->AHB1ENR|=1<<4;//使能PORTE时钟 
	GPIO_Set(GPIOE,PIN3|PIN4,GPIO_MODE_IN,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);
	//PE3,PE4设置上拉，普通输入，速度和推挽类型无效
} 	

u8 KEY_Scan(void)
{	 
	if(KEY1==0||KEY2==0)
	{
		delay_ms(5);//去抖动 
		if(KEY1==0)
			return KEY1_PRES;
		else if(KEY2==0)
			return KEY2_PRES;
	} 	     
	return 0;// 无按键按下
}

#endif


#if __ELSE
//IO口时钟分布:portA～portI对应RCC_AHB1ENR[0:8]
//即portA对应RCC_AHB1ENR[0];//portB对应RCC_AHB1ENR[1];//portC对应RCC_AHB1ENR[2];
//即portD对应RCC_AHB1ENR[3];//portE对应RCC_AHB1ENR[4];//portF对应RCC_AHB1ENR[5];
//即portG对应RCC_AHB1ENR[6];//portH对应RCC_AHB1ENR[7];//portI对应RCC_AHB1ENR[8];
void ELSE_IO_Init(void)
{
	RCC->AHB1ENR|=1<<4;//使能PORTE时钟 
	GPIO_Set(GPIOE,PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PD);
}

#endif

#if __EXTI	
/*
//IO口的外部中断要在内部设置好上下拉，若在干扰较大的地方，外部也要加上下拉电阻
//开了中断，一定要写相应的中断服务函数，否则可能导致程序崩溃
//外部中断0～4都有单独的中断服务函数，但是从5开始，就是多个中断共用一个服务函数
//所有中断服务函数的名字，在启动文件xx.s里面定义好，用到的时候要去找*/

//外部中断配置
void EXTIx_Init(void)		//直接调用sys.c对外部中断的配置
{
	Ex_NVIC_Config(GPIO_E,3,FTIR);//PA0，外部上升沿触发
	Ex_NVIC_Config(GPIO_E,4,FTIR);//PA1，外部上升沿触发
	MY_NVIC_Init(2,0,EXTI3_IRQn,2);//中断优先级设为低
	MY_NVIC_Init(2,1,EXTI4_IRQn,2);//中断优先级设为低
}
//extern u8 t;
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(5);	//消抖
	if(KEY1==0)	//对应确认按键 
	{
	//	BEEP0=!BEEP0;
//	t=1;
	}		 
	EXTI->PR=1<<3;  //清除LINE0上的中断标志位  
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{			
	delay_ms(5);   //消抖			 
    if(KEY2==0)	//对应取消按键
	{
//		t=2;
	}
 	EXTI->PR=1<<4;     //清除LINE1上的中断标志位  
}

#endif


