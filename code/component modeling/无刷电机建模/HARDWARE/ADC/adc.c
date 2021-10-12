#include "H_define.h"


#if __ADC1
void ADC1_Init(void)
{
	RCC->APB2ENR|=1<<9;//ADC1使能
	RCC->APB2ENR|=1<<2;//GPIOA使能
	RCC->APB2ENR|=1<<3;//GPIOB使能
	RCC->APB2ENR|=1<<4;//GPIOC使能
	
	GPIOA->CRL&=0x00000000;//adc通道模拟输入
	GPIOA->CRL|=0x00000000;
	GPIOB->CRL&=0xffffff00;
	GPIOB->CRL|=0x00000000;
	GPIOC->CRL&=0xff000000;
	GPIOC->CRL|=0x00000000;
	
	RCC->APB2RSTR|=1<<9;	//adc1接口复位
	RCC->APB2RSTR&=~(1<<9);	//ADC1复位结束
	
	RCC->CFGR&=~(3<<14);//adc时钟12M
	RCC->CFGR|=2<<14;
	
	ADC1->CR1=0;
	ADC1->CR1|=6<<16;//双adc规则同步模式
	ADC1->CR1|=1<<8;//扫描模式
	
	ADC1->CR2=0;
	ADC1->CR2|=1<<20;//使用外部触发
	ADC1->CR2|=7<<17;//软件触发
	#if __DMA_ADC1 
	ADC1->CR2|=1<<8;//使用DMA
	#endif
	ADC1->CR2|=1<<1;//连续转换

	ADC1->SMPR2|=0x0003ffff;//adc通道采样时间均为239.5周期
	
	ADC1->SQR1=0;
	ADC1->SQR1&=~(0xf<<20);//规则通道长度均为6个
	ADC1->SQR1|=5<<20;
	
	ADC1->SQR3=0;			//ADC1前6个通道，adc2后6个通道
	ADC1->SQR3|=CH0<<0;
	ADC1->SQR3|=CH1<<5;
	ADC1->SQR3|=CH2<<10;
	ADC1->SQR3|=CH3<<15;
	ADC1->SQR3|=CH4<<20;
	ADC1->SQR3|=CH5<<25;
	
	ADC1->CR2|=1<<0;		//adc1校准
	ADC1->CR2|=1<<3;
	while(ADC1->CR2&1<<3);
	ADC1->CR2|=1<<2;
	while(ADC1->CR2&1<<2);
	ADC1->CR2|=1<<22; //开始转换
}

#endif


#if __ADC2
void ADC2_Init(void)
{
	RCC->APB2ENR|=1<<10;//ADC2使能
	RCC->APB2ENR|=1<<2;//GPIOA使能
	RCC->APB2ENR|=1<<3;//GPIOB使能
	RCC->APB2ENR|=1<<4;//GPIOC使能
	
	GPIOA->CRL&=0x00000000;//adc通道模拟输入
	GPIOA->CRL|=0x00000000;
	GPIOB->CRL&=0xffffff00;
	GPIOB->CRL|=0x00000000;
	GPIOC->CRL&=0xff000000;
	GPIOC->CRL|=0x00000000;
	
	RCC->APB2RSTR|=1<<10;	//adc2接口复位
	RCC->APB2RSTR&=~(1<<10);//adc2复位结束
	
	RCC->CFGR&=~(3<<14);//adc时钟12M
	RCC->CFGR|=2<<14;
	
	ADC2->CR1=0;
	ADC2->CR1|=1<<8;//扫描模式
	
	ADC2->CR2=0;
	ADC2->CR2|=1<<20;//使用外部触发
	ADC2->CR2|=7<<17;//软件触发
//	ADC2->CR2|=1<<8;//使用DMA
	ADC2->CR2|=1<<1;//连续转换

	ADC2->SMPR2|=0x3ffc0000;
	ADC2->SMPR1|=0x0003f000;
	
	ADC2->SQR1=0;
	ADC2->SQR1&=~(0xf<<20);
	ADC2->SQR1|=5<<20;
	ADC2->SQR3=0;
	ADC2->SQR3|=CH6<<0;
	ADC2->SQR3|=CH7<<5;
	ADC2->SQR3|=CH14<<10;
	ADC2->SQR3|=CH15<<15;
	ADC2->SQR3|=CH8<<20;
	ADC2->SQR3|=CH9<<25;
	
	
	ADC2->CR2|=1<<0;		//adc2校准
	ADC2->CR2|=1<<3;
	while(ADC2->CR2&1<<3);
	ADC2->CR2|=1<<2;
	while(ADC2->CR2&1<<2);
	
	ADC2->CR2|=1<<22;	
}
#endif

#if __ADC3
void ADC3_Init(void)
{
	RCC->APB2ENR|=1<<15;//ADC3时钟使能
	RCC->APB2ENR|=1<<4;//GPIOC时钟使能
	
	GPIOC->CRL&=0xffff0000;//GPIOC模拟输入
	GPIOC->CRL|=0x00000000;	
	
	RCC->APB2RSTR|=1<<15;//ADC3复位
	RCC->APB2RSTR&=~(1<<15);
	
	RCC->CFGR&=~(3<<14);//adc时钟12M
	RCC->CFGR|=2<<14;
	
	ADC3->CR1=0;
	ADC3->CR1|=1<<8;//独立模式，扫描模式
	
	ADC3->CR2=0;
	ADC3->CR2|=1<<20;//外部事件启动
	ADC3->CR2|=7<<17;//软件触发
	#if __DMA_ADC3 
	ADC3->CR2|=1<<8;//右对齐，使用DMA
	#endif
	ADC3->CR2|=1<<1;//连续转换模式
	
	ADC3->SMPR1|=0x00000fff;//转换时间均为239.5个周期
	
	ADC3->SQR1|=3<<20;//4个通道
	ADC3->SQR3=0;			//ADC3 4个通道
	ADC3->SQR3|=CH10<<0;
	ADC3->SQR3|=CH11<<5;
	ADC3->SQR3|=CH12<<10;
	ADC3->SQR3|=CH13<<15;
	
	ADC3->CR2|=1<<0;		//adc3校准
	ADC3->CR2|=1<<3;
	while(ADC3->CR2&1<<3);
	ADC3->CR2|=1<<2;
	while(ADC3->CR2&1<<2);
	
	ADC3->CR2|=1<<22; //开始转换
}
#endif
