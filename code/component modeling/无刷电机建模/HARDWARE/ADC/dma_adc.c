#include "H_define.h"


#if __DMA_ADC1
//cndtr:数据数量
//cpar:外设地址
//cmar:存储地址
void DMA1_Init(u16 cndtr,u32 cpar,u32 cmar)
{
	
	RCC->AHBENR|=1<<0;
	DMA1_Channel1->CNDTR=cndtr;	//数据传输数量
	DMA1_Channel1->CPAR=cpar;	//外设地址
	DMA1_Channel1->CMAR=cmar;	//存储器地址
	DMA1_Channel1->CCR=0;
	DMA1_Channel1->CCR&=~(1<<14);//非储存器到储存器模式
	DMA1_Channel1->CCR&=~(3<<14);
	DMA1_Channel1->CCR|=3<<12;//通道优先级最高
	DMA1_Channel1->CCR&=~(3<<10);
	DMA1_Channel1->CCR|=2<<10;//存储器数据宽度16
	DMA1_Channel1->CCR&=~(3<<8);
	DMA1_Channel1->CCR|=2<<8;//外设数据宽度16
	DMA1_Channel1->CCR|=2<<6;//存储器地址增量，外设地址非增量
	DMA1_Channel1->CCR|=1<<5;//循环模式
	DMA1_Channel1->CCR&=~(1<<4);//从外设读
	DMA1_Channel1->CCR&=~(7<<1);
//	DMA1_Channel1->CCR|=1<<1;//tc开启，TE，HT关闭
	DMA1_Channel1->CCR|=1<<0;//通道开启
	MY_NVIC_Init(0,0,DMA1_Channel1_IRQn,2);
}
#endif




#if __DMA_ADC3
//cndtr:数据数量
//cpar:外设地址
//cmar:存储地址
void DMA2_Init(u16 cndtr,u32 cpar,u32 cmar)
{
	
	RCC->AHBENR|=1<<1;//DMA2使能
	
	DMA2_Channel5->CNDTR=cndtr;	//数据传输数量
	DMA2_Channel5->CPAR=cpar;	//外设地址
	DMA2_Channel5->CMAR=cmar;	//存储器地址
	DMA2_Channel5->CCR=0;
	DMA2_Channel5->CCR&=~(1<<14);//非储存器到储存器模式
	DMA2_Channel5->CCR&=~(3<<14);
	DMA2_Channel5->CCR|=3<<12;//通道优先级最高
	DMA2_Channel5->CCR&=~(3<<10);
	DMA2_Channel5->CCR|=1<<10;//存储器数据宽度16
	DMA2_Channel5->CCR&=~(3<<8);
	DMA2_Channel5->CCR|=1<<8;//外设数据宽度16
	DMA2_Channel5->CCR|=2<<6;//存储器地址增量，外设地址非增量
	DMA2_Channel5->CCR|=1<<5;//循环模式
	DMA2_Channel5->CCR&=~(1<<4);//从外设读
	DMA2_Channel5->CCR&=~(7<<1);
//	DMA2_Channel5->CCR|=1<<1;//tc开启，TE，HT关闭
	DMA2_Channel5->CCR|=1<<0;//通道开启
}
#endif

//extern u16 ADC[16];
//extern u16 adc[6];
//void  DMA1_Channel1_IRQHandler()//dma1中断
//{
//	u8 i;
//	if(DMA1->ISR&(1<<1))//传输完成
//	{
//		for(i=0;i<6;i++)	
//			ADC[i+4]=adc[i]&0xffff;
//		for(i=0;i<6;i++)	
//			ADC[i+10]=(adc[i]&0xffff0000)>>16;
//	}
//	DMA1->IFCR|=1<<1;//清除标志位
//}
