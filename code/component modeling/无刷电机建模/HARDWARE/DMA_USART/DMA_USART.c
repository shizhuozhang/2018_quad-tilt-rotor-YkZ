#include "H_define.h"


u8 SBUS_DATA[25];
//u8 D_K60[10];

//cndtr:数据数量
//cpar:外设地址
//cmar:存储地址
void DMA1_Channel3_Init(u16 cndtr,u32 cpar,u32 cmar)  //usart3
{
	RCC->AHBENR|=1<<0;			//开启DMA1时钟
	delay_ms(5);				//等待DMA时钟稳定
	DMA1_Channel3->CPAR=cpar; 	 	//DMA1 外设地址 
	DMA1_Channel3->CMAR=cmar; 	//DMA1,存储器地址
	DMA1_Channel3->CNDTR=cndtr;    	//DMA1,传输数据量
	DMA1_Channel3->CCR=0X00000000;	//复位
	DMA1_Channel3->CCR|=0<<4;  		//从外设读
	DMA1_Channel3->CCR|=1<<5;  		//循环模式
	DMA1_Channel3->CCR|=0<<6; 		//外设地址非增量模式
	DMA1_Channel3->CCR|=1<<7; 	 	//存储器增量模式
	DMA1_Channel3->CCR|=0<<8; 	 	//外设数据宽度为8位
	DMA1_Channel3->CCR|=0<<10; 		//存储器数据宽度8位
	DMA1_Channel3->CCR|=1<<12; 		//中等优先级
	DMA1_Channel3->CCR|=0<<14; 		//非存储器到存储器模式
	DMA1_Channel3->CCR|=1<<1;			//允许TC中断
	DMA1_Channel3->CCR|=1<<0;			//通道开启
	MY_NVIC_Init(0,0,DMA1_Channel3_IRQn,2);
}
////cndtr:数据数量
////cpar:外设地址
////cmar:存储地址
//void DMA1_Channel5_Init(u16 cndtr,u32 cpar,u32 cmar)//串口1 dam数据传输  通道5
//{
//	RCC->AHBENR|=1<<0;			//开启DMA1时钟
//	delay_ms(5);				//等待DMA时钟稳定
//	DMA1_Channel5->CPAR=cpar; 	 	//DMA1 外设地址 
//	DMA1_Channel5->CMAR=cmar; 	//DMA1,存储器地址
//	DMA1_Channel5->CNDTR=cndtr;    	//DMA1,传输数据量
//	DMA1_Channel5->CCR=0X00000000;	//复位
//	DMA1_Channel5->CCR|=0<<4;  		//从外设读
//	DMA1_Channel5->CCR|=1<<5;  		//普通模式
//	DMA1_Channel5->CCR|=0<<6; 		//外设地址非增量模式
//	DMA1_Channel5->CCR|=1<<7; 	 	//存储器增量模式
//	DMA1_Channel5->CCR|=0<<8; 	 	//外设数据宽度为8位
//	DMA1_Channel5->CCR|=0<<10; 		//存储器数据宽度8位
//	DMA1_Channel5->CCR|=1<<12; 		//中等优先级
//	DMA1_Channel5->CCR|=0<<14; 		//非存储器到存储器模式
//	DMA1_Channel5->CCR|=1<<1;			//允许TC中断
//	DMA1_Channel5->CCR|=1<<0;			//通道开启
//	MY_NVIC_Init(1,3,DMA1_Channel5_IRQn,2);
//}

//cndtr:数据数量
//cpar:外设地址
//cmar:存储地址
void DMA1_Channel6_Init(u16 cndtr,u32 cpar,u32 cmar)   //usart2
{
	RCC->AHBENR|=1<<0;			//开启DMA1时钟
	delay_ms(5);				//等待DMA时钟稳定
	DMA1_Channel6->CPAR=cpar; 	 	//DMA1 外设地址 
	DMA1_Channel6->CMAR=cmar; 	//DMA1,存储器地址
	DMA1_Channel6->CNDTR=cndtr;    	//DMA1,传输数据量
	DMA1_Channel6->CCR=0X00000000;	//复位
	DMA1_Channel6->CCR|=0<<4;  		//从外设读
	DMA1_Channel6->CCR|=1<<5;  		//普通模式
	DMA1_Channel6->CCR|=0<<6; 		//外设地址非增量模式
	DMA1_Channel6->CCR|=1<<7; 	 	//存储器增量模式
	DMA1_Channel6->CCR|=0<<8; 	 	//外设数据宽度为8位
	DMA1_Channel6->CCR|=0<<10; 		//存储器数据宽度8位
	DMA1_Channel6->CCR|=1<<12; 		//中等优先级
	DMA1_Channel6->CCR|=0<<14; 		//非存储器到存储器模式
	DMA1_Channel6->CCR|=1<<1;			//允许TC中断
	DMA1_Channel6->CCR|=1<<0;			//通道开启
	MY_NVIC_Init(1,3,DMA1_Channel6_IRQn,2);
}

u8 sign_usrt3=0;
u8 Dma1_C3_Close=1;
void  DMA1_Channel3_IRQHandler()//dma1中断  usart3
{
	if(DMA1->ISR&(1<<9))//传输完成
	{
		DMA1->IFCR|=1<<8;//清除标志位
		if((0X0F!=SBUS_DATA[0])||(0!=SBUS_DATA[24]))//
		{
			DMA1_Channel3->CCR&=~(1<<0);			//通道关闭
			Dma1_C3_Close=1;
		}else
		{
			SBUS_data_Pro();
			sign_usrt3=1;
		}
	}
	
}

//void DMA1_Channel5_IRQHandler()
//{
//	if(DMA1->ISR&1<<17)//通道5传输完成
//	{
//		DMA1->ISR|=1<<16;
//		
//	}
//	
//}



//u8 sign_usrt2=0;
//u8 Dma1_C6_Close=0;
void  DMA1_Channel6_IRQHandler()//dma1中断
{
	if(DMA1->ISR&(1<<21))//传输完成
	{
		DMA1->IFCR|=1<<21;//清除标志位
//		if(0X55!=D_6050[0])
//		{
//			DMA1_Channel6->CCR&=~(1<<0);			//通道开启
//			Dma1_C6_Close=1;
//		}else
//		{
//			sign_usrt2=1;
//		}
	}
	
}









