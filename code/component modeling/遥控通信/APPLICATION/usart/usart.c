#include "H_define.h"

#if __USART
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	   
//REFER TO:正点原子@ALIENTEK
//技术论坛:www.openedv.com
////////////////////////////////////////////////////////////////////////////////// 	

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
		#elif ___USART_PRINTF == 4
			while((UART4->SR&0X40)==0);//循环发送,直到发送完毕   
			UART4->DR = (u8) ch;
		#elif ___USART_PRINTF == 5
			while((UART5->SR&0X40)==0);//循环发送,直到发送完毕   
			UART5->DR = (u8) ch;      
		#elif ___USART_PRINTF == 6
			while((USART6->SR&0X40)==0);//循环发送,直到发送完毕   
			USART6->DR = (u8) ch;      
		#endif
		return ch;
	}
#endif
	
#endif 
//end
//////////////////////////////////////////////////////////////////
/**串口1初始化函数*/
#if __USART1	
	//pclk2:PCLK2时钟频率(Mhz)
	//bound:波特率 
	void Usart1_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV@OVER8=0
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分@OVER8=0 
		mantissa<<=4;//无符号定点类型，后四位是小数部分
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<0;   	//使能PORTA口时钟  
		RCC->APB2ENR|=1<<4;  	//使能串口1时钟 
		GPIO_Set(GPIOA,PIN9|PIN10,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,复用功能,上拉输出
		GPIO_AF_Set(GPIOA,9,7);	//PA9,AF7
		GPIO_AF_Set(GPIOA,10,7);//PA10,AF7  	   
		
		RCC->APB2RSTR|=1<<4;   //复位串口1
		RCC->APB2RSTR&=~(1<<4);//停止复位	   
		//波特率设置
		USART1->BRR=mantissa; 	//波特率设置	 
		USART1->CR1&=~(1<<15); 	//设置OVER8=0 //保证最高的容错性
		USART1->CR1|=1<<3;  	//串口发送使能 
	//	USART1->CR1|=0X200C;  //1位停止,无校验位.
	//默认1起始位，8数据位，1停止位,无奇偶校验
	
		#if __DMA_USART1 
		USART1->CR3|=1<<6;    //DMA	接受
		#endif
	
		//使能接收中断 
		USART1->CR1|=1<<2;  	//串口接收使能
		USART1->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
		MY_NVIC_Init(3,3,USART1_IRQn,2);//组2，最低优先级 
		
		USART1->CR1|=1<<13;  	//串口使能
	}

	//串口1中断服务程序
	//注意,读取USARTx->SR能避免莫名其妙的错误   	  
	void USART1_IRQHandler(void)
	{
		u8 res;	
		
	#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntEnter();    
	#endif
		
		if(USART1->SR&(1<<5))//接收到数据
		{	 		
			res=USART1->DR; //DR寄存器是一个双寄存器，读数据的时候读取的是RDR
					//写数据的时候写的是TDR,但是TDR和RDR对外不可见，都是DR寄存器
			USART1->DR=res*2;	//	接收到的数据以2倍发出				     
		} 
							//读完数据该标志位自动清零，
	//	USART1->SR&=~(1<<5);//没必要用这行代码手动清除标志位
		
	#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntExit();  											 
	#endif
	} 
#endif

/**串口2初始化函数*/
#if __USART2	
	//pclk2:PCLK2时钟频率(Mhz)
	//bound:波特率 
	void Usart2_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV@OVER8=0
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分@OVER8=0 
		mantissa<<=4;//无符号定点类型，后四位是小数部分
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<0;   	//使能PORTA口时钟  
		RCC->APB1ENR|=1<<17;  	//使能串口2时钟 
		GPIO_Set(GPIOA,PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA2,PA3,复用功能,上拉输出
		GPIO_AF_Set(GPIOA,2,7);	//PA9,AF7
		GPIO_AF_Set(GPIOA,3,7);//PA10,AF7  	   
		
		RCC->APB1RSTR|=1<<17;   //复位串口2
		RCC->APB1RSTR&=~(1<<17);//停止复位	   
		//波特率设置
		USART2->BRR=mantissa; 	//波特率设置	 
		USART2->CR1&=~(1<<15); 	//设置OVER8=0 //保证最高的容错性
		USART2->CR1|=1<<3;  	//串口发送使能 
	//	USART2->CR1|=0X200C;  //1位停止,无校验位.
	//默认1起始位，8数据位，1停止位,无奇偶校验
	
		#if __DMA_USART2 
		USART2->CR3|=1<<6;    //DMA	接受
		#endif
		
		//使能接收中断 
		USART2->CR1|=1<<2;  	//串口接收使能
		USART2->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
		MY_NVIC_Init(2,2,USART2_IRQn,2);//组2，最低优先级 
		
		USART2->CR1|=1<<13;  	//串口使能
	}

	u8 Ahrs_Flag1=1;
	//串口1中断服务程序
	//注意,读取USARTx->SR能避免莫名其妙的错误   	  
	void USART2_IRQHandler(void)
	{
		static u8 Judge_Flag1=0;
		static u8 Judge_Flag2=0;
		
	#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntEnter();    
	#endif
		
		if(USART2->SR&(1<<5))//接收到数据
		{	 		
			if(Ahrs_Flag1)//每组数据的帧头校验
			{
				if(0XA5==USART2->DR)
					Judge_Flag1=1;
				else if((0X5A==USART2->DR) && Judge_Flag1)
				{
					Judge_Flag2=1;
					USART2->CR3|=1<<6;    //DMA	接受
				}
				else
					Judge_Flag1=0;
				
				if((0X12==USART2->DR) && Dma1_T5_Close && Judge_Flag2 )//
				{
					Dma1_T5_Close=0;
					Judge_Flag2=0;
					while(DMA1_Stream5->CR&0X1);	//确保DMA可以被设置  
					DMA1_Stream5->CR|=1<<0;		//开启DMA传输
					Ahrs_Flag1=0;//帧头校验完毕后，其余数据的接收使用DMA，不再在此处处理
				}		
			}	
			
		} 						//读完数据该标志位自动清零，
		USART2->SR&=~(1<<5);//没必要用这行代码手动清除标志位
		
	#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
/**串口3初始化函数*/
#if __USART3	
	//pclk2:PCLK2时钟频率(Mhz)
	//bound:波特率 
	void Usart3_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV@OVER8=0
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分@OVER8=0 
		mantissa<<=4;//无符号定点类型，后四位是小数部分
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<1;   	//使能PORTB口时钟  
		RCC->APB1ENR|=1<<18;  	//使能串口3时钟 
		GPIO_Set(GPIOB,PIN10|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,复用功能,上拉输出
		GPIO_AF_Set(GPIOB,10,7);	//PB10,AF7
		GPIO_AF_Set(GPIOB,11,7);//PB11,AF7  	   
		
		RCC->APB1RSTR|=1<<18;   //复位串口1
		RCC->APB1RSTR&=~(1<<18);//停止复位	   
		//波特率设置
		USART3->BRR=mantissa; 	//波特率设置
		
		USART3->CR1=0;
		USART3->CR2=0;
		USART3->CR3=0;
		
		USART3->CR1&=~(1<<15); 	//设置OVER8=0 //保证最高的容错性
		
//		USART3->CR1|=1<<3;  	//串口发送使能		
//		USART3->CR1|=0X200C;  //1位停止,无校验位.
	//默认1起始位，8数据位，1停止位,无奇偶校验
	
		USART3->CR1|=0<<9;  	
		USART3->CR1|=1<<10;  	//开启偶校验
		USART3->CR2|=2<<12;  	//2位停止位
		
		#if __DMA_USART1 
		USART3->CR3|=1<<6;    //DMA	接受
		#endif
		
		//使能接收中断 
		USART3->CR1|=1<<2;  	//串口接收使能
		USART3->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
		MY_NVIC_Init(3,3,USART3_IRQn,2);//组2，最低优先级 
		
		USART3->CR1|=1<<13;  	//串口使能
	}

	//串口3中断服务程序
	//注意,读取USARTx->SR能避免莫名其妙的错误   	  
	void USART3_IRQHandler(void)
	{
//		u8 res=0;
	#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntEnter();    
	#endif
		
		if(USART3->SR&(1<<5))//接收到数据
		{
//	 		res=USART3->DR;
//			USART1->DR=res;			
			USART3->CR3|=1<<6;    //DMA	接受
			if(0X0F==USART3->DR&&1==Dma1_T1_Close)//
			{
				Dma1_T1_Close=0;				
				while(DMA1_Stream1->CR&0X1);	//确保DMA可以被设置  
				DMA1_Stream1->CR|=1<<0;		//开启DMA传输
			}				     
		} 
							//读完数据该标志位自动清零，
		USART3->SR&=~(1<<5);//没必要用这行代码手动清除标志位
		
	#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
/**串口4初始化函数*/
#if __UART4	
	//pclk2:PCLK2时钟频率(Mhz)
	//bound:波特率 
	void Uart4_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV@OVER8=0
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分@OVER8=0 
		mantissa<<=4;//无符号定点类型，后四位是小数部分
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<0;   	//使能PORTA口时钟  
		RCC->APB1ENR|=1<<19;  	//使能串口1时钟 
		GPIO_Set(GPIOA,PIN0|PIN1,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,复用功能,上拉输出
		GPIO_AF_Set(GPIOA,0,8);	//PA9,AF7
		GPIO_AF_Set(GPIOA,1,8);//PA10,AF7  	   
		
		RCC->APB1RSTR|=1<<19;   //复位串口1
		RCC->APB1RSTR&=~(1<<19);//停止复位	   
		//波特率设置
		UART4->BRR=mantissa; 	//波特率设置	 
		UART4->CR1&=~(1<<15); 	//设置OVER8=0 //保证最高的容错性
		UART4->CR1|=1<<3;  	//串口发送使能 
	//	UART4->CR1|=0X200C;  //1位停止,无校验位.
	//默认1起始位，8数据位，1停止位,无奇偶校验

		#if __DMA_USART1 
		UART4->CR3|=1<<6;    //DMA	接受
		#endif
		//使能接收中断 
		UART4->CR1|=1<<2;  	//串口接收使能
		UART4->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
		MY_NVIC_Init(3,3,UART4_IRQn,2);//组2，最低优先级 
		
		UART4->CR1|=1<<13;  	//串口使能
	}

	//串口1中断服务程序
	//注意,读取USARTx->SR能避免莫名其妙的错误   	  
	void UART4_IRQHandler(void)
	{
		u8 res;	
		
	#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntEnter();    
	#endif
		
		if(UART4->SR&(1<<5))//接收到数据
		{	 		
			res=UART4->DR; //DR寄存器是一个双寄存器，读数据的时候读取的是RDR
					//写数据的时候写的是TDR,但是TDR和RDR对外不可见，都是DR寄存器
			UART4->DR=res*2;	//	接收到的数据以2倍发出				     
		} 
							//读完数据该标志位自动清零，
	//	UART4->SR&=~(1<<5);//没必要用这行代码手动清除标志位
		
	#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
/**串口5初始化函数*/
#if __UART5	
	//pclk2:PCLK2时钟频率(Mhz)
	//bound:波特率 
	void Uart5_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV@OVER8=0
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分@OVER8=0 
		mantissa<<=4;//无符号定点类型，后四位是小数部分
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<2;   	//使能PORTC口时钟 
		RCC->AHB1ENR|=1<<3;   	//使能PORTD口时钟		
		RCC->APB1ENR|=1<<20;  	//使能串口5时钟 
		GPIO_Set(GPIOC,PIN12,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,复用功能,上拉输出
		GPIO_Set(GPIOD,PIN2,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,复用功能,上拉输出
		GPIO_AF_Set(GPIOC,12,8);	//PC12,AF8
		GPIO_AF_Set(GPIOD,2,8);//PD2,AF8  	   
		
		RCC->APB1RSTR|=1<<20;   //复位串口1
		RCC->APB1RSTR&=~(1<<20);//停止复位	   
		//波特率设置
		UART5->BRR=mantissa; 	//波特率设置	 
		UART5->CR1&=~(1<<15); 	//设置OVER8=0 //保证最高的容错性
		UART5->CR1|=1<<3;  	//串口发送使能 
	//	USART5->CR1|=0X200C;  //1位停止,无校验位.
	//默认1起始位，8数据位，1停止位,无奇偶校验

		#if __DMA_USART1 
		UART5->CR3|=1<<6;    //DMA	接受
		#endif
		//使能接收中断 
		UART5->CR1|=1<<2;  	//串口接收使能
		UART5->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
		MY_NVIC_Init(3,3,UART5_IRQn,2);//组2，最低优先级 
		
		UART5->CR1|=1<<13;  	//串口使能
	}

	//串口1中断服务程序
	//注意,读取USARTx->SR能避免莫名其妙的错误   	  
	void UART5_IRQHandler(void)
	{
		u8 res;	
		
	#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntEnter();    
	#endif
		
		if(UART5->SR&(1<<5))//接收到数据
		{	 		
			res=UART5->DR; //DR寄存器是一个双寄存器，读数据的时候读取的是RDR
					//写数据的时候写的是TDR,但是TDR和RDR对外不可见，都是DR寄存器
			UART5->DR=res*2;	//	接收到的数据以2倍发出				     
		} 
							//读完数据该标志位自动清零，
	//	UART5->SR&=~(1<<5);//没必要用这行代码手动清除标志位
		
	#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
/**串口6初始化函数*////未验证，应该没问题
#if __USART6	
	//pclk2:PCLK2时钟频率(Mhz)
	//bound:波特率 
	void Usart6_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV@OVER8=0
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分@OVER8=0 
		mantissa<<=4;//无符号定点类型，后四位是小数部分
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<2;   	//使能PORTC口时钟
		RCC->APB2ENR|=1<<5;  	//使能串口1时钟 
		GPIO_Set(GPIOC,PIN6|PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,复用功能,上拉输出
		GPIO_AF_Set(GPIOC,6,8);	//PA9,AF7
		GPIO_AF_Set(GPIOC,7,8);//PA10,AF7  	   
		
		RCC->APB2RSTR|=1<<5;   //复位串口1
		RCC->APB2RSTR&=~(1<<5);//停止复位	   
		//波特率设置
		USART6->BRR=mantissa; 	//波特率设置	 
		USART6->CR1&=~(1<<15); 	//设置OVER8=0 //保证最高的容错性
		USART6->CR1|=1<<3;  	//串口发送使能 
	//	USART6->CR1|=0X200C;  //1位停止,无校验位.
	//默认1起始位，8数据位，1停止位,无奇偶校验

		#if __DMA_USART1 
		USART6->CR3|=1<<6;    //DMA	接受
		#endif
		//使能接收中断 
		USART6->CR1|=1<<2;  	//串口接收使能
		USART6->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
		MY_NVIC_Init(3,3,USART6_IRQn,2);//组2，最低优先级 
		
		USART6->CR1|=1<<13;  	//串口使能
	}

	//串口1中断服务程序
	//注意,读取USARTx->SR能避免莫名其妙的错误   	  
	void USART6_IRQHandler(void)
	{
		u8 res;	
		
	#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntEnter();    
	#endif
		
		if(USART6->SR&(1<<5))//接收到数据
		{	 		
			res=USART6->DR; //DR寄存器是一个双寄存器，读数据的时候读取的是RDR
					//写数据的时候写的是TDR,但是TDR和RDR对外不可见，都是DR寄存器
			USART6->DR=res*2;	//	接收到的数据以2倍发出				     
		} 
							//读完数据该标志位自动清零，
	//	USART6->SR&=~(1<<5);//没必要用这行代码手动清除标志位
		
	#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
	


#endif
	
	
	
	
	