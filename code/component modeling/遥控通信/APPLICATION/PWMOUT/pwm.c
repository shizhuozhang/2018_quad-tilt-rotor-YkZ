#include "H_define.h"

/*�ο�ԭ��ALIENTEKԴ��*/    

#if __TIM1_PWM
void TIM1_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB2ENR|=1<<0; 	//TIM1ʱ��ʹ��    
	RCC->AHB1ENR|=1<<4;   	//ʹ��PORTEʱ��	
	GPIO_Set(GPIOE,PIN9 |PIN11 |PIN13 |PIN14,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOE,9,1);	//PE9,AF1 
	GPIO_AF_Set(GPIOE,11,1);	//PE11,AF1 	
	GPIO_AF_Set(GPIOE,13,1);	//PE13,AF1 	
	GPIO_AF_Set(GPIOE,14,1);	//PE14,AF1 	
	
	TIM1->ARR=arr;		//�趨�������Զ���װֵ 
	TIM1->PSC=psc;		//Ԥ��Ƶ������Ƶ 
	TIM1->CCMR1|=6<<4;  //CH1 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM1->CCMR1|=6<<12;  //CH2 PWM1ģʽ
	TIM1->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��
	TIM1->CCMR1|=1<<11; //CH2 Ԥװ��ʹ��
	
	TIM1->CCMR2|=6<<4;  //CH3 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM1->CCMR2|=6<<12;  //CH3 PWM1ģʽ
	TIM1->CCMR2|=1<<3; 	//CH4 Ԥװ��ʹ��
	TIM1->CCMR2|=1<<11; //CH4 Ԥװ��ʹ��
	
	TIM1->CCER|=1<<0;   //OC1 ���ʹ��	
	TIM1->CCER|=0<<1;   //OC1 �ߵ�ƽ��Ч
	TIM1->CCER|=1<<4;   //OC2 ���ʹ��	
	TIM1->CCER|=0<<5;   //OC2 �ߵ�ƽ��Ч
	TIM1->CCER|=1<<8;   //OC3 ���ʹ��	
	TIM1->CCER|=0<<9;   //OC3 �ߵ�ƽ��Ч	
	TIM1->CCER|=1<<12;  //OC4 ���ʹ��	
	TIM1->CCER|=0<<13;  //OC4 �ߵ�ƽ��Ч
	//��������һ�д������
//	TIM1->CCER|=0X1111;   	//OC1,2,3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч

	TIM1->CR1|=1<<7;   	//ARPEʹ��
	TIM1->CR1|=0<<4;   	//��������	
	TIM1->BDTR|=1<<15;   	//�߼���ʱ�����еļĴ�����MOE �����ʹ��
	
 	TIM1->CR1|=1<<0;    //ʹ�ܶ�ʱ��1	
	
    TIM1->CCR1=3000;    	//��ʼװ��ֵ
	TIM1->CCR2=3000;    	//��ʼװ��ֵ
	TIM1->CCR3=3000;    	//��ʼװ��ֵ
	TIM1->CCR4=3000;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM2_PWM
void TIM2_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 	

} 
#endif

#if __TIM3_PWM
void TIM3_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB1ENR|=1<<1; 	//TIM3ʱ��ʹ��    
	RCC->AHB1ENR|=1<<0;   	//ʹ��PORTAʱ��	
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��
	GPIO_Set(GPIOA,PIN6 |PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_Set(GPIOB,PIN0 |PIN1,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOA,6,2);	//PA6,AF0 
	GPIO_AF_Set(GPIOA,7,2);	//PA7,AF2 	
	GPIO_AF_Set(GPIOB,0,2);	//PB0,AF2 	
	GPIO_AF_Set(GPIOB,1,2);	//PB1,AF2 	
	
	TIM3->ARR=arr;		//�趨�������Զ���װֵ 
	TIM3->PSC=psc;		//Ԥ��Ƶ������Ƶ 
	TIM3->CCMR1|=6<<4;  //CH1 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM3->CCMR1|=6<<12;  //CH2 PWM1ģʽ
	TIM3->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��
	TIM3->CCMR1|=1<<11; //CH2 Ԥװ��ʹ��
	
	TIM3->CCMR2|=6<<4;  //CH3 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM3->CCMR2|=6<<12;  //CH3 PWM1ģʽ
	TIM3->CCMR2|=1<<3; 	//CH4 Ԥװ��ʹ��
	TIM3->CCMR2|=1<<11; //CH4 Ԥװ��ʹ��
	
	TIM3->CCER|=1<<0;   //OC1 ���ʹ��	
	TIM3->CCER|=0<<1;   //OC1 �ߵ�ƽ��Ч
	TIM3->CCER|=1<<4;   //OC2 ���ʹ��	
	TIM3->CCER|=0<<5;   //OC2 �ߵ�ƽ��Ч
	TIM3->CCER|=1<<8;   //OC3 ���ʹ��	
	TIM3->CCER|=0<<9;   //OC3 �ߵ�ƽ��Ч	
	TIM3->CCER|=1<<12;  //OC4 ���ʹ��	
	TIM3->CCER|=0<<13;  //OC4 �ߵ�ƽ��Ч
	//��������һ�д������
//	TIM3->CCER|=0X1111;   	//OC1,2,3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч

	TIM3->CR1|=1<<7;   	//ARPEʹ��
	TIM3->CR1|=0<<4;   	//��������	
	
 	TIM3->CR1|=1<<0;    //ʹ�ܶ�ʱ��1	
	
    TIM3->CCR1=4500;    	//��ʼװ��ֵ
	TIM3->CCR2=4500;    	//��ʼװ��ֵ
	TIM3->CCR3=4500;    	//��ʼװ��ֵ
	TIM3->CCR4=4500;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM4_PWM
void TIM4_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB1ENR|=1<<2; 	//TIM4ʱ��ʹ��    
	RCC->AHB1ENR|=1<<3;   	//ʹ��PORTDʱ��	
	GPIO_Set(GPIOD,PIN12 |PIN13 |PIN14 |PIN15,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOD,12,2);	//PD12,AF2 
	GPIO_AF_Set(GPIOD,13,2);	//PD13,AF2 	
	GPIO_AF_Set(GPIOD,14,2);	//PD14,AF2 	
	GPIO_AF_Set(GPIOD,15,2);	//PD15,AF2	
	
	TIM4->ARR=arr;		//�趨�������Զ���װֵ 
	TIM4->PSC=psc;		//Ԥ��Ƶ������Ƶ 
	TIM4->CCMR1|=6<<4;  //CH1 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM4->CCMR1|=6<<12;  //CH2 PWM1ģʽ
	TIM4->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��
	TIM4->CCMR1|=1<<11; //CH2 Ԥװ��ʹ��
	
	TIM4->CCMR2|=6<<4;  //CH3 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM4->CCMR2|=6<<12;  //CH3 PWM1ģʽ
	TIM4->CCMR2|=1<<3; 	//CH4 Ԥװ��ʹ��
	TIM4->CCMR2|=1<<11; //CH4 Ԥװ��ʹ��
	
	TIM4->CCER|=1<<0;   //OC1 ���ʹ��	
	TIM4->CCER|=0<<1;   //OC1 �ߵ�ƽ��Ч
	TIM4->CCER|=1<<4;   //OC2 ���ʹ��	
	TIM4->CCER|=0<<5;   //OC2 �ߵ�ƽ��Ч
	TIM4->CCER|=1<<8;   //OC3 ���ʹ��	
	TIM4->CCER|=0<<9;   //OC3 �ߵ�ƽ��Ч	
	TIM4->CCER|=1<<12;  //OC4 ���ʹ��	
	TIM4->CCER|=0<<13;  //OC4 �ߵ�ƽ��Ч
	//��������һ�д������
//	TIM4->CCER|=0X1111;   	//OC1,2,3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч

	TIM4->CR1|=1<<7;   	//ARPEʹ��
	TIM4->CR1|=0<<4;   	//��������	
	
 	TIM4->CR1|=1<<0;    //ʹ�ܶ�ʱ��1	
	
    TIM4->CCR1=4500;    	//��ʼװ��ֵ
	TIM4->CCR2=4500;    	//��ʼװ��ֵ
	TIM4->CCR3=4500;    	//��ʼװ��ֵ
	TIM4->CCR4=4500;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM5_PWM
void TIM5_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	
} 
#endif

#if __TIM8_PWM
void TIM8_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB2ENR|=1<<1; 	//TIM8ʱ��ʹ��    
	RCC->AHB1ENR|=1<<2;   	//ʹ��PORTCʱ��	
	GPIO_Set(GPIOC,PIN6 |PIN7 |PIN8 |PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOC,6,3);	//PC6,AF1 
	GPIO_AF_Set(GPIOC,7,3);	//PC7,AF1 	
	GPIO_AF_Set(GPIOC,8,3);	//PC8,AF1 	
	GPIO_AF_Set(GPIOC,9,3);	//PC9,AF1 	
	
	TIM8->ARR=arr;		//�趨�������Զ���װֵ 
	TIM8->PSC=psc;		//Ԥ��Ƶ������Ƶ 
	TIM8->CCMR1|=6<<4;  //CH1 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM8->CCMR1|=6<<12;  //CH2 PWM1ģʽ
	TIM8->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��
	TIM8->CCMR1|=1<<11; //CH2 Ԥװ��ʹ��
	
	TIM8->CCMR2|=6<<4;  //CH3 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM8->CCMR2|=6<<12;  //CH3 PWM1ģʽ
	TIM8->CCMR2|=1<<3; 	//CH4 Ԥװ��ʹ��
	TIM8->CCMR2|=1<<11; //CH4 Ԥװ��ʹ��
	
	TIM8->CCER|=1<<0;   //OC1 ���ʹ��	
	TIM8->CCER|=0<<1;   //OC1 �ߵ�ƽ��Ч
	TIM8->CCER|=1<<4;   //OC2 ���ʹ��	
	TIM8->CCER|=0<<5;   //OC2 �ߵ�ƽ��Ч
	TIM8->CCER|=1<<8;   //OC3 ���ʹ��	
	TIM8->CCER|=0<<9;   //OC3 �ߵ�ƽ��Ч	
	TIM8->CCER|=1<<12;  //OC4 ���ʹ��	
	TIM8->CCER|=0<<13;  //OC4 �ߵ�ƽ��Ч
	//��������һ�д������
//	TIM8->CCER|=0X1111;   	//OC1,2,3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч

	TIM8->CR1|=1<<7;   	//ARPEʹ��
	TIM8->CR1|=0<<4;   	//��������	
	TIM8->BDTR|=1<<15;   	//�߼���ʱ�����еļĴ�����MOE �����ʹ��
	
 	TIM8->CR1|=1<<0;    //ʹ�ܶ�ʱ��1	
	
    TIM8->CCR1=4500;    	//��ʼװ��ֵ
	TIM8->CCR2=4500;    	//��ʼװ��ֵ
	TIM8->CCR3=4500;    	//��ʼװ��ֵ
	TIM8->CCR4=4500;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM9_PWM
void TIM9_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB2ENR|=1<<16; 	//TIM9ʱ��ʹ��    
	RCC->AHB1ENR|=1<<4;   	//ʹ��PORTEʱ��	
	GPIO_Set(GPIOE,PIN5 |PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOE,5,3);	//PE5,AF3 
	GPIO_AF_Set(GPIOE,6,3);	//PE6,AF3 	
	
	TIM9->ARR=arr;		//�趨�������Զ���װֵ 
	TIM9->PSC=psc;		//Ԥ��Ƶ������Ƶ 
	TIM9->CCMR1|=0<<0;  //CH1����Ϊ���
	TIM9->CCMR1|=0<<8;	//CH2����Ϊ���
	TIM9->CCMR1|=6<<4;  //CH1 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM9->CCMR1|=6<<12;  //CH2 PWM1ģʽ
	TIM9->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��
	TIM9->CCMR1|=1<<11; //CH2 Ԥװ��ʹ��
	
	TIM9->CCER|=1<<0;   //OC1 ���ʹ��	
	TIM9->CCER|=0<<1;   //OC1 �ߵ�ƽ��Ч
	TIM9->CCER|=1<<4;   //OC2 ���ʹ��	
	TIM9->CCER|=0<<5;   //OC2 �ߵ�ƽ��Ч
	//��������һ�д������
//	TIM9->CCER|=0X0011;   	//OC1,2,3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч

	TIM9->CR1|=1<<7;   	//ARPEʹ��
 	TIM9->CR1|=1<<0;    //ʹ�ܶ�ʱ��1	
	
    TIM9->CCR1=3000;    	//��ʼװ��ֵ
	TIM9->CCR2=3000;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM10_PWM
void TIM10_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB2ENR|=1<<17; 	//TIM10ʱ��ʹ��    
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��	
	GPIO_Set(GPIOB,PIN8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOB,8,3);	//PB8,AF3
	
	TIM10->ARR=arr;		//�趨�������Զ���װֵ 
	TIM10->PSC=psc;		//Ԥ��Ƶ������Ƶ 
	
	TIM10->CCMR1|=6<<4;  //CH1 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM10->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��
	
	TIM10->CCER|=1<<0;   //OC1 ���ʹ��	
	TIM10->CCER|=0<<1;   //OC1 �ߵ�ƽ��Ч

	TIM10->CR1|=1<<7;   	//ARPEʹ��
	TIM10->CR1|=0<<4;   	//��������	
	
 	TIM10->CR1|=1<<0;    //ʹ�ܶ�ʱ��1	
	
    TIM10->CCR1=3000;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM11_PWM
void TIM11_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB2ENR|=1<<18; 	//TIM11ʱ��ʹ��    
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��	
	GPIO_Set(GPIOB,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOB,9,3);	//PA6,AF3 
	
	TIM11->ARR=arr;		//�趨�������Զ���װֵ 
	TIM11->PSC=psc;		//Ԥ��Ƶ������Ƶ 
	
	TIM11->CCMR1|=6<<4;  //CH1 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM11->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��
	
	TIM11->CCER|=1<<0;   //OC1 ���ʹ��	
	TIM11->CCER|=0<<1;   //OC1 �ߵ�ƽ��Ч

	TIM11->CR1|=1<<7;   	//ARPEʹ��
	TIM11->CR1|=0<<4;   	//��������	
	
 	TIM11->CR1|=1<<0;    //ʹ�ܶ�ʱ��1	
	
    TIM11->CCR1=3000;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM12_PWM
void TIM12_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB1ENR|=1<<6; 	//TIM12ʱ��ʹ��    
	RCC->AHB1ENR|=1<<1;   	//ʹ��PORTBʱ��	
	GPIO_Set(GPIOB,PIN14 |PIN15,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOB,14,9);	//PE5,AF3 
	GPIO_AF_Set(GPIOB,15,9);	//PE6,AF3 	
	
	TIM12->ARR=arr;		//�趨�������Զ���װֵ 
	TIM12->PSC=psc;		//Ԥ��Ƶ������Ƶ 
	TIM12->CCMR1|=0<<0;  //CH1����Ϊ���
	TIM12->CCMR1|=0<<8;	//CH2����Ϊ���
	TIM12->CCMR1|=6<<4;  //CH1 PWM1ģʽ	����ֵС��װ��ֵʱ����Ч��ƽ���͵�ƽ
	TIM12->CCMR1|=6<<12;  //CH2 PWM1ģʽ
	TIM12->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��
	TIM12->CCMR1|=1<<11; //CH2 Ԥװ��ʹ��
	
	TIM12->CCER|=1<<0;   //OC1 ���ʹ��	
	TIM12->CCER|=0<<1;   //OC1 �ߵ�ƽ��Ч
	TIM12->CCER|=1<<4;   //OC2 ���ʹ��	
	TIM12->CCER|=0<<5;   //OC2 �ߵ�ƽ��Ч
	//��������һ�д������
//	TIM12->CCER|=0X0011;   	//OC1,2,3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч

	TIM12->CR1|=1<<7;   	//ARPEʹ��
 	TIM12->CR1|=1<<0;    //ʹ�ܶ�ʱ��1	
	
    TIM12->CCR1=3000;    	//��ʼװ��ֵ
	TIM12->CCR2=3000;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif


