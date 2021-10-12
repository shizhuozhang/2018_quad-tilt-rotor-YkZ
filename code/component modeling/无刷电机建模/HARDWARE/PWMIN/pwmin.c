#include "H_define.h"

#if __TIM1_PWMIN
void TIM1_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��  
	RCC->APB2ENR|=1<<2;//GPIOAʹ��
	GPIOA->CRH&=0xfffffff0;//PA8��������
	GPIOA->CRH|=0x00000008;
	TIM1->ARR=arr;			//�趨�������Զ���װֵ 
	TIM1->PSC=psc;			//Ԥ��Ƶ������
	TIM1->CCMR1|=1<<0;//CC1��ӳ����TI1��
	TIM1->CCMR1|=2<<8;//CC2��Ӱ����TI1��
	TIM1->SMCR|=5<<4;//�˲���ʱ������1
	TIM1->SMCR|=4<<0;//��ģʽΪ��λģʽ
	TIM1->CCER|=0<<1;//CC1��������Ч
	TIM1->CCER|=1<<5;//CC2�½�����Ч
	TIM1->CCER|=1<<0;//ʹ�ܲ���
	TIM1->CCER|=1<<4;//ʹ�ܲ���
	TIM1->CR1|=1<<0;//ʹ�ܼ�����
}
#endif
#if __TIM2_PWMIN
void TIM2_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;//tim2ʹ��
	RCC->APB2ENR|=1<<2;//GPIOAʹ��
	GPIOA->CRH&=0x0fffffff;//PA15 ��������
	GPIOA->CRH|=0x80000000;
	JTAG_Set(SWD_ENABLE);	//�ر�jtag
	AFIO->MAPR|=3<<8;		//��TIM2������ӳ��
	//ע���ʱ����ӳ���д���SWD������PB3(CH2)����ret����
	//������������䷴��������ֻ��CH2���ã����³�������
	TIM2->ARR=arr;			//�趨�������Զ���װֵ 
	TIM2->PSC=psc;			//Ԥ��Ƶ������
	TIM2->CCMR1|=1<<0;//CC1��ӳ����TI1��
	TIM2->CCMR1|=2<<8;//CC2��Ӱ����TI1��
	TIM2->SMCR|=5<<4;//�˲���ʱ������1
	TIM2->SMCR|=4<<0;//��ģʽΪ��λģʽ
	TIM2->CCER|=0<<1;//CC1��������Ч
	TIM2->CCER|=1<<5;//CC2�½�����Ч
	TIM2->CCER|=1<<0;//ʹ�ܲ���
	TIM2->CCER|=1<<4;//ʹ�ܲ���
	TIM2->CR1|=1<<0;//ʹ�ܼ�����
}
#endif
#if __TIM3_PWMIN
void TIM3_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;//tim3ʹ��
	RCC->APB2ENR|=1<<2;//GPIOAʹ��
	GPIOA->CRL&=0xf0ffffff;//PA6 ��������
	GPIOA->CRL|=0x08000000;
	TIM3->ARR=arr;			//�趨�������Զ���װֵ 
	TIM3->PSC=psc;			//Ԥ��Ƶ������
	TIM3->CCMR1|=1<<0;//CC1��ӳ����TI1��
	TIM3->CCMR1|=2<<8;//CC2��Ӱ����TI1��
	TIM3->SMCR|=5<<4;//�˲���ʱ������1
	TIM3->SMCR|=4<<0;//��ģʽΪ��λģʽ
	TIM3->CCER|=0<<1;//CC1��������Ч
	TIM3->CCER|=1<<5;//CC2�½�����Ч
	TIM3->CCER|=1<<0;//ʹ�ܲ���
	TIM3->CCER|=1<<4;//ʹ�ܲ���
	TIM3->CR1|=1<<0;//ʹ�ܼ�����
}
#endif
#if __TIM4_PWMIN
void TIM4_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;//tim4ʹ��
	RCC->APB2ENR|=1<<3;//GPIOBʹ��
	GPIOB->CRL&=0x0fffffff;//PB7 ��������
	GPIOB->CRL|=0x80000000;
	TIM4->ARR=arr;			//�趨�������Զ���װֵ 
	TIM4->PSC=psc;			//Ԥ��Ƶ������
	TIM4->CCMR1|=2<<0;//CC1��ӳ����TI2��
	TIM4->CCMR1|=1<<8;//CC2��Ӱ����TI2��
	TIM4->SMCR|=6<<4;//�˲���ʱ������1
	TIM4->SMCR|=4<<0;//��ģʽΪ��λģʽ
	TIM4->CCER|=0<<1;//CC1��������Ч
	TIM4->CCER|=1<<5;//CC2�½�����Ч
	TIM4->CCER|=1<<0;//ʹ�ܲ���
	TIM4->CCER|=1<<4;//ʹ�ܲ���
	TIM4->CR1|=1<<0;//ʹ�ܼ�����
}
#endif
#if __TIM5_PWMIN
void TIM5_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<3;//tim5ʹ��
	RCC->APB2ENR|=1<<2;//GPIOAʹ��
	GPIOA->CRL&=0xffffff0f;//PA1 ��������
	GPIOA->CRL|=0x00000080;
	TIM5->ARR=arr;			//�趨�������Զ���װֵ 
	TIM5->PSC=psc;			//Ԥ��Ƶ������
	TIM5->CCMR1|=2<<0;//CC1��ӳ����TI2��
	TIM5->CCMR1|=1<<8;//CC2��Ӱ����TI2��
	TIM5->SMCR|=6<<4;//�˲���ʱ������1
	TIM5->SMCR|=4<<0;//��ģʽΪ��λģʽ
	TIM5->CCER|=0<<1;//CC1��������Ч
	TIM5->CCER|=1<<5;//CC2�½�����Ч
	TIM5->CCER|=1<<0;//ʹ�ܲ���
	TIM5->CCER|=1<<4;//ʹ�ܲ���
	TIM5->CR1|=1<<0;//ʹ�ܼ�����
}
#endif
#if __TIM8_PWMIN
void TIM8_PWMIN_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR|=1<<13; 	//TIM8ʱ��ʹ�� 
	RCC->APB2ENR|=1<<4;//GPIOCʹ��
	GPIOC->CRL&=0x0fffffff;//PC7 ��������
	GPIOC->CRL|=0x80000000;
	TIM8->ARR=arr;			//�趨�������Զ���װֵ 
	TIM8->PSC=psc;			//Ԥ��Ƶ������
	
	TIM8->CCMR1|=2<<0;//CC1��ӳ����TI2��
	TIM8->CCMR1|=1<<8;//CC2��Ӱ����TI2��
	TIM8->SMCR|=6<<4;//�˲���ʱ������1
	
	TIM8->SMCR|=4<<0;//��ģʽΪ��λģʽ
	TIM8->CCER|=0<<1;//CC1��������Ч
	TIM8->CCER|=1<<5;//CC2�½�����Ч
	TIM8->CCER|=1<<0;//ʹ�ܲ���
	TIM8->CCER|=1<<4;//ʹ�ܲ���
	TIM8->CR1|=1<<0;//ʹ�ܼ�����
}
#endif


