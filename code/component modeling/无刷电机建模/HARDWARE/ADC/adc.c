#include "H_define.h"


#if __ADC1
void ADC1_Init(void)
{
	RCC->APB2ENR|=1<<9;//ADC1ʹ��
	RCC->APB2ENR|=1<<2;//GPIOAʹ��
	RCC->APB2ENR|=1<<3;//GPIOBʹ��
	RCC->APB2ENR|=1<<4;//GPIOCʹ��
	
	GPIOA->CRL&=0x00000000;//adcͨ��ģ������
	GPIOA->CRL|=0x00000000;
	GPIOB->CRL&=0xffffff00;
	GPIOB->CRL|=0x00000000;
	GPIOC->CRL&=0xff000000;
	GPIOC->CRL|=0x00000000;
	
	RCC->APB2RSTR|=1<<9;	//adc1�ӿڸ�λ
	RCC->APB2RSTR&=~(1<<9);	//ADC1��λ����
	
	RCC->CFGR&=~(3<<14);//adcʱ��12M
	RCC->CFGR|=2<<14;
	
	ADC1->CR1=0;
	ADC1->CR1|=6<<16;//˫adc����ͬ��ģʽ
	ADC1->CR1|=1<<8;//ɨ��ģʽ
	
	ADC1->CR2=0;
	ADC1->CR2|=1<<20;//ʹ���ⲿ����
	ADC1->CR2|=7<<17;//�������
	#if __DMA_ADC1 
	ADC1->CR2|=1<<8;//ʹ��DMA
	#endif
	ADC1->CR2|=1<<1;//����ת��

	ADC1->SMPR2|=0x0003ffff;//adcͨ������ʱ���Ϊ239.5����
	
	ADC1->SQR1=0;
	ADC1->SQR1&=~(0xf<<20);//����ͨ�����Ⱦ�Ϊ6��
	ADC1->SQR1|=5<<20;
	
	ADC1->SQR3=0;			//ADC1ǰ6��ͨ����adc2��6��ͨ��
	ADC1->SQR3|=CH0<<0;
	ADC1->SQR3|=CH1<<5;
	ADC1->SQR3|=CH2<<10;
	ADC1->SQR3|=CH3<<15;
	ADC1->SQR3|=CH4<<20;
	ADC1->SQR3|=CH5<<25;
	
	ADC1->CR2|=1<<0;		//adc1У׼
	ADC1->CR2|=1<<3;
	while(ADC1->CR2&1<<3);
	ADC1->CR2|=1<<2;
	while(ADC1->CR2&1<<2);
	ADC1->CR2|=1<<22; //��ʼת��
}

#endif


#if __ADC2
void ADC2_Init(void)
{
	RCC->APB2ENR|=1<<10;//ADC2ʹ��
	RCC->APB2ENR|=1<<2;//GPIOAʹ��
	RCC->APB2ENR|=1<<3;//GPIOBʹ��
	RCC->APB2ENR|=1<<4;//GPIOCʹ��
	
	GPIOA->CRL&=0x00000000;//adcͨ��ģ������
	GPIOA->CRL|=0x00000000;
	GPIOB->CRL&=0xffffff00;
	GPIOB->CRL|=0x00000000;
	GPIOC->CRL&=0xff000000;
	GPIOC->CRL|=0x00000000;
	
	RCC->APB2RSTR|=1<<10;	//adc2�ӿڸ�λ
	RCC->APB2RSTR&=~(1<<10);//adc2��λ����
	
	RCC->CFGR&=~(3<<14);//adcʱ��12M
	RCC->CFGR|=2<<14;
	
	ADC2->CR1=0;
	ADC2->CR1|=1<<8;//ɨ��ģʽ
	
	ADC2->CR2=0;
	ADC2->CR2|=1<<20;//ʹ���ⲿ����
	ADC2->CR2|=7<<17;//�������
//	ADC2->CR2|=1<<8;//ʹ��DMA
	ADC2->CR2|=1<<1;//����ת��

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
	
	
	ADC2->CR2|=1<<0;		//adc2У׼
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
	RCC->APB2ENR|=1<<15;//ADC3ʱ��ʹ��
	RCC->APB2ENR|=1<<4;//GPIOCʱ��ʹ��
	
	GPIOC->CRL&=0xffff0000;//GPIOCģ������
	GPIOC->CRL|=0x00000000;	
	
	RCC->APB2RSTR|=1<<15;//ADC3��λ
	RCC->APB2RSTR&=~(1<<15);
	
	RCC->CFGR&=~(3<<14);//adcʱ��12M
	RCC->CFGR|=2<<14;
	
	ADC3->CR1=0;
	ADC3->CR1|=1<<8;//����ģʽ��ɨ��ģʽ
	
	ADC3->CR2=0;
	ADC3->CR2|=1<<20;//�ⲿ�¼�����
	ADC3->CR2|=7<<17;//�������
	#if __DMA_ADC3 
	ADC3->CR2|=1<<8;//�Ҷ��룬ʹ��DMA
	#endif
	ADC3->CR2|=1<<1;//����ת��ģʽ
	
	ADC3->SMPR1|=0x00000fff;//ת��ʱ���Ϊ239.5������
	
	ADC3->SQR1|=3<<20;//4��ͨ��
	ADC3->SQR3=0;			//ADC3 4��ͨ��
	ADC3->SQR3|=CH10<<0;
	ADC3->SQR3|=CH11<<5;
	ADC3->SQR3|=CH12<<10;
	ADC3->SQR3|=CH13<<15;
	
	ADC3->CR2|=1<<0;		//adc3У׼
	ADC3->CR2|=1<<3;
	while(ADC3->CR2&1<<3);
	ADC3->CR2|=1<<2;
	while(ADC3->CR2&1<<2);
	
	ADC3->CR2|=1<<22; //��ʼת��
}
#endif
