#include "H_define.h"


#if __USART
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
#if ___USART_PRINTF
	int fputc(int ch, FILE *f)
	{      
		#if ___USART_PRINTF == 1
			while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
			USART1->DR = (u8) ch;      	
		#elif ___USART_PRINTF == 2
			while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
			USART2->DR = (u8) ch;      
		#elif ___USART_PRINTF == 3
			while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
			USART3->DR = (u8) ch;      
		#endif
		return ch;
	}
#endif

#endif 
//////////////////////////////////////////////////////////////////

////////////串口1/////////////
#if __USART1

	//初始化IO 串口1
	//pclk2:PCLK2时钟频率(Mhz)
	//bound:波特率
	//CHECK OK
	//091209
	void usart1(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分	 
		mantissa<<=4;
		mantissa+=fraction; 
		RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
		RCC->APB2ENR|=1<<14;  //使能串口时钟 
		GPIOA->CRH&=0XFFFFF00F;//IO状态设置
		GPIOA->CRH|=0X000008B0;//IO状态设置
			  
		RCC->APB2RSTR|=1<<14;   //复位串口1
		RCC->APB2RSTR&=~(1<<14);//停止复位	   	   
		//波特率设置
		USART1->BRR=mantissa; // 波特率设置	 
		USART1->CR1|=0X200C;  //1位停止,无校验位.
//		USART1->CR3|=1<<6;    //接收DMA
////		//使能接收中断
////		USART1->CR1|=1<<8;    //PE中断使能
////		USART1->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
////		MY_NVIC_Init(3,3,USART1_IRQn,2);//组2，最低优先级 
	}


#endif
/////////////////////////////

////////////串口2/////////////
#if __USART2

	//初始化IO 串口1
	//pclk2:PCLK2时钟频率(Mhz)
	//bound:波特率
	//CHECK OK
	//091209
	void usart2(u32 pclk1,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk1*1000000)/(bound*16);//得到USARTDIV
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分	 
		mantissa<<=4;
		mantissa+=fraction; 
		
		RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
		RCC->APB1ENR|=1<<17;  //使能串口时钟 
		GPIOA->CRL&=0XFFFF00FF;//IO状态设置
		GPIOA->CRL|=0X00008B00;//IO状态设置 
		RCC->APB1RSTR|=1<<17;   //复位串口1
		RCC->APB1RSTR&=~(1<<17);//停止复位
		//波特率设置
		USART2->BRR=mantissa; // 波特率设置	 
		USART2->CR1|=0X200C;  //1位停止,无校验位.
		USART2->CR3|=1<<6;	//dma使能接受

		//使能接收中断
		USART2->CR1|=1<<8;    //PE中断使能
		USART2->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
		MY_NVIC_Init(3,3,USART2_IRQn,2);//组2，最低优先级 
	}
u8 Usart2_flag1=0;
u8 Usart2_flag2=0;
	void USART2_IRQHandler(void)
	{
		if(USART2->SR&(1<<5))//接收到数据
		{	 
			USART2->SR&=~(1<<5);
			
			if(0X55==USART2->DR)
				Usart2_flag1=1;
			
			else if((0X51==USART2->DR)&&Usart2_flag1)
				Usart2_flag2=1;
			else
				Usart2_flag1=0;
			
			if(Usart2_flag2&&Dma1_C6_Close)
			{
				Dma1_C6_Close=0;
				Usart2_flag2=0;
				DMA1_Channel6->CCR|=1<<0;			//通道开启
			}
		}

	} 
#endif
/////////////////////////////

////////////串口3/////////////
#if __USART3

	//初始化IO 串口1
	//pclk2:PCLK2时钟频率(Mhz)
	//bound:波特率
	//CHECK OK
	//091209
	void usart3(u32 pclk1,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk1*1000000)/(bound*16);//得到USARTDIV
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分	 
		mantissa<<=4;
		mantissa+=fraction; 
		RCC->APB2ENR|=1<<3;   //使能PORTB口时钟  
		RCC->APB1ENR|=1<<18;  //使能串口时钟 
		GPIOB->CRH&=0XFFFF00FF;//IO状态设置
		GPIOB->CRH|=0X00008B00;//IO状态设置 
		RCC->APB1RSTR|=1<<18;   //复位串口1
		RCC->APB1RSTR&=~(1<<18);//停止复位	   	   
		//波特率设置
		USART3->BRR=mantissa; // 波特率设置	 
		USART3->CR1|=0X200C;  //1位停止,无校验位.
		USART3->CR3|=1<<6;	//dma使能接受
		//使能接收中断
		USART3->CR1|=1<<8;    //PE中断使能
		USART3->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
		MY_NVIC_Init(3,2,USART3_IRQn,2);//组2，最低优先级 
	}

u8 count=1;
	void USART3_IRQHandler(void)
	{
		if(USART3->SR&(1<<5))//接收到数据
		{	
			USART3->SR=0;		
			D_K60[count++]=USART3->DR;
			if(count==3) count=1;
			
		}
	} 
#endif
/////////////////////////////

#endif	
	
