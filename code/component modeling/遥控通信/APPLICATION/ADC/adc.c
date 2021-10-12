#include "H_define.h"


#if __ADC1

void ADC1_Init(void)
{
	RCC->APB2ENR|=1<<8;    	//使能ADC1时钟 
	RCC->AHB1ENR|=1<<2;    	//使能PORTC时钟	ADC10-15对应PC0-PC5	
	
	GPIO_Set(GPIOC,0X003F,GPIO_MODE_AIN,0,0,GPIO_PUPD_PU);	//PC0-PC5,模拟输入,下拉 	
	
	RCC->APB2RSTR|=1<<8;   	//ADCs复位
	RCC->APB2RSTR&=~(1<<8);	//复位结束	
	
	ADC->CCR=3<<16;			//ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz
 	
	ADC1->CR1=0;   			//CR1设置清零
	ADC1->CR2=0;   			//CR2设置清零
	
	ADC1->CR1&=~(1<<24);      	//12位模式	
	
	ADC1->CR1|=1<<8;    	//多路ADC时使用扫描模式，开启扫描模式必须使用DMA
	ADC1->CR1|=1<<5; 		//使能序列转换完成中断
	MY_NVIC_Init(1,3,ADC_IRQn,2);//需要根据需要修改中断矢量号
	
//	ADC1->CR2&=~(1<<28);    //禁止外部触发检测，使用软件触发
// 	ADC1->CR2&=~(1<<11);   	//右对齐
	
//	ADC1->CR2|=1<<10;	//结束转换选择	

	#if __DMA_ADC1 
//	ADC1->CR2&=~(1<<9);	
//	ADC1->CR2|=0<<9;
	ADC1->CR2|=1<<8;	//连续转换时使用DMA		
	#endif

	ADC1->SMPR1=0;//通道10-18采样时间清空	  
 	ADC1->SMPR1|=7<<(3*0); 	//通道10  480个周期,提高采样时间可以提高精确度
	ADC1->SMPR1|=7<<(3*1); 	//通道11  480个周期,提高采样时间可以提高精确度
	ADC1->SMPR1|=7<<(3*2); 	//通道12  480个周期,提高采样时间可以提高精确度
	ADC1->SMPR1|=7<<(3*3); 	//通道13  480个周期,提高采样时间可以提高精确度
	ADC1->SMPR1|=7<<(3*4); 	//通道14  480个周期,提高采样时间可以提高精确度
	ADC1->SMPR1|=7<<(3*5); 	//通道15  480个周期,提高采样时间可以提高精确度
	
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=6<<20;     	//6个转换在规则序列中
	
	ADC1->SQR3=0;
	ADC1->SQR3|=10<<0;     	//通道10是第一次转换 
	ADC1->SQR3|=11<<5;     	//通道11是第二次转换 
	ADC1->SQR3|=12<<10;     //通道12是第三次转换  
	ADC1->SQR3|=13<<15;     //通道13是第四次转换    	
	ADC1->SQR3|=14<<20;     //通道14是第五次转换  
	ADC1->SQR3|=15<<25;     //通道15是第六次转换  
	
	ADC1->CR2|=1<<1;    	//连续转换模式
	
 	ADC1->CR2|=1<<0;	   	//使能AD转换器	
//	ADC1->CR2|=1<<30;	   	//开启AD规则转换	
}

void ADC_IRQHandler()
{
	if(ADC1->SR&(1<<1))
	{
		ADC1->SR&=~(1<<1);
		
		ADC1->CR2&=~(1<<8);	//DMA使能位清零
		while(ADC1->CR2&(1<<8));	
		ADC1->CR2|=1<<8;	
	}	
}

#endif


#if __ADC2
void ADC2_Init(void)
{

	
}
#endif

#if __ADC3
void ADC3_Init(void)
{

}
#endif
