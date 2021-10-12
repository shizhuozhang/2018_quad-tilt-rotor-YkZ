#include "H_define.h"

/*�ο�ԭ��ALIENTEKԴ��*/    

#if __TIM1_PWM
void TIM1_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��  
	RCC->APB2ENR|=1<<2;		//IO�˿�A��ʱ��ʹ��
	GPIOA->CRH&=0XFFFF0000;	//PA8,PA9,PA10,PA11
	GPIOA->CRH|=0X0000BBBB;	//���ù������ 
	
	TIM1->ARR=arr;			//�趨�������Զ���װֵ 
	TIM1->PSC=psc;			//Ԥ��Ƶ������
  
	TIM1->CCMR1|=0X0D<<3;  	//CH1���,PWM1ģʽ,Ԥװ��ʹ��			 
	TIM1->CCMR1|=0X0D<<11; 	//CH2���,PWM1ģʽ,Ԥװ��ʹ��
	TIM1->CCMR2|=0X0D<<3;  	//CH3���,PWM1ģʽ,Ԥװ��ʹ��			 
	TIM1->CCMR2|=0X0D<<11; 	//CH4���,PWM1ģʽ,Ԥװ��ʹ��
							
 	TIM1->CCER|=0X1111;   	//OC1,2,3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч	   
	TIM1->BDTR|=1<<15;   	//�߼���ʱ�����еļĴ�����MOE �����ʹ��	   

	TIM1->CR1=0x0080;   	//���ϼ������Զ���װ��ʹ�� 
	TIM1->CR1|=0x01;    	//ʹ�ܶ�ʱ��1 
	
    TIM1->CCR1=0;    	//��ʼװ��ֵ
	TIM1->CCR2=0;    	//��ʼװ��ֵ
	TIM1->CCR3=0;    	//��ʼװ��ֵ
	TIM1->CCR4=0;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM2_PWM
//��ӳ�����ŵ�ͨ��1��2��JTAGϵͳ���ų�ͻ������JTAGģʽ���޷����س���ԭ��δ����
//�����ʱTIM2ֻʹ��3��4ͨ�������
void TIM2_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 	
	RCC->APB1ENR|=1<<0; 	//TIM2ʱ��ʹ��  
	RCC->APB2ENR|=1<<2;		//IO�˿�A��ʱ��ʹ��
	RCC->APB2ENR|=1<<3;		//IO�˿�B��ʱ��ʹ��	
	RCC->APB2ENR|=1<<0;		//AFIO�˿ڸ���ʱ��ʹ��
	
	JTAG_Set(SWD_ENABLE);	//�ر�jtag
	AFIO->MAPR|=3<<8;		//��TIM2������ӳ��
	//ע���ʱ����ӳ���д���SWD������PB3(CH2)����ret����
	//������������䷴��������ֻ��CH2���ã����³�������
	
	GPIOA->CRH&=0X0FFFFFFF;	//PA15,ע���ϵ縴λ�󣬸ý�Ĭ��ΪJTAG���ţ�Ҫ����JTAGģʽ
	GPIOA->CRH|=0XB0000000;	//���ù������ 
	GPIOB->CRL&=0XFFFF0FFF;	//PB3��ע���ϵ縴λ�󣬸ý�Ĭ��ΪJTAG���ţ�Ҫ����JTAGģʽ
	GPIOB->CRL|=0X0000B000;	//���ù������ 	
	GPIOB->CRH&=0XFFFF00FF;	//PB10,PB11
	GPIOB->CRH|=0X0000BB00;	//���ù������ 	
	
	TIM2->ARR=arr;			//�趨�������Զ���װֵ 
	TIM2->PSC=psc;			//Ԥ��Ƶ������
  
	TIM2->CCMR1|=0X0D<<3;  	//CH1���,PWM1ģʽ,Ԥװ��ʹ��			 
	TIM2->CCMR1|=0X0D<<11; 	//CH2���,PWM1ģʽ,Ԥװ��ʹ��
	TIM2->CCMR2|=0X0D<<3;  	//CH3���,PWM1ģʽ,Ԥװ��ʹ��			 
	TIM2->CCMR2|=0X0D<<11; 	//CH4���,PWM1ģʽ,Ԥװ��ʹ��
							
 	TIM2->CCER|=0X1111;   	//OC3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч	   	   

	TIM2->CR1=0x0080;   	//���ϼ������Զ���װ��ʹ�� 
	TIM2->CR1|=0x01;    	//ʹ�ܶ�ʱ��2 
	 
    TIM2->CCR1=0;    	//��ʼװ��ֵ
	TIM2->CCR2=0;    	//��ʼװ��ֵ
	TIM2->CCR3=0;    	//��ʼװ��ֵ
	TIM2->CCR4=0;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM3_PWM
void TIM3_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB1ENR|=1<<1; 	//TIM3ʱ��ʹ��  
	RCC->APB2ENR|=1<<2;		//IO�˿�A��ʱ��ʹ��
	RCC->APB2ENR|=1<<3;		//IO�˿�B��ʱ��ʹ��	
	GPIOA->CRL&=0X00FFFFFF;	//PA6,PA7
	GPIOA->CRL|=0XBB000000;	//���ù������ 	
	GPIOB->CRL&=0XFFFFFF00;	//PB0,PB1
	GPIOB->CRL|=0X000000BB;	//���ù������ 	
	
	TIM3->ARR=arr;			//�趨�������Զ���װֵ 
	TIM3->PSC=psc;			//Ԥ��Ƶ������
  
	TIM3->CCMR1|=0X0D<<3;  	//CH1���,PWM1ģʽ,Ԥװ��ʹ��			 
	TIM3->CCMR1|=0X0D<<11; 	//CH2���,PWM1ģʽ,Ԥװ��ʹ��
	TIM3->CCMR2|=0X0D<<3;  	//CH3���,PWM1ģʽ,Ԥװ��ʹ��			 
	TIM3->CCMR2|=0X0D<<11; 	//CH4���,PWM1ģʽ,Ԥװ��ʹ��
							
 	TIM3->CCER|=0X1111;   	//OC1,2,3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч	   	   

	TIM3->CR1=0x0080;   	//���ϼ������Զ���װ��ʹ�� 
	TIM3->CR1|=0x01;    	//ʹ�ܶ�ʱ��3 
	
    TIM3->CCR1=0;    	//��ʼװ��ֵ
	TIM3->CCR2=0;    	//��ʼװ��ֵ
	TIM3->CCR3=0;    	//��ʼװ��ֵ
	TIM3->CCR4=0;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif

#if __TIM4_PWM
void TIM4_PWM_Init(u16 arr,u16 psc)//arr���Զ���װֵ; psc��ʱ��Ԥ��Ƶ��
{		 					 
	RCC->APB1ENR|=1<<2; 	//TIM4ʱ��ʹ��  
	RCC->APB2ENR|=1<<3;		//IO�˿�B��ʱ��ʹ��
	GPIOB->CRL&=0X00FFFFFF;	//PB6,PB7
	GPIOB->CRL|=0XBB000000;	//���ù������ 	
	GPIOB->CRH&=0XFFFFFF00;	//PB8,PB9
	GPIOB->CRH|=0X000000BB;	//���ù������  
	
	TIM4->ARR=arr;			//�趨�������Զ���װֵ 
	TIM4->PSC=psc;			//Ԥ��Ƶ������
  
	TIM4->CCMR1|=0X0D<<3;  	//CH1���,PWM1ģʽ,Ԥװ��ʹ��			 
	TIM4->CCMR1|=0X0D<<11; 	//CH2���,PWM1ģʽ,Ԥװ��ʹ��
	TIM4->CCMR2|=0X0D<<3;  	//CH3���,PWM1ģʽ,Ԥװ��ʹ��			 
	TIM4->CCMR2|=0X0D<<11; 	//CH4���,PWM1ģʽ,Ԥװ��ʹ��
							
 	TIM4->CCER|=0X1111;   	//OC1,2,3,4 ���ʹ�ܣ��������Ϊ�ߵ�ƽ��Ч	   

	TIM4->CR1=0x0080;   	//���ϼ������Զ���װ��ʹ�� 
	TIM4->CR1|=0x01;    	//ʹ�ܶ�ʱ��4 
	
    TIM4->CCR1=4500;    	//��ʼװ��ֵ
	TIM4->CCR2=4500;    	//��ʼװ��ֵ
	TIM4->CCR3=4500;    	//��ʼװ��ֵ
	TIM4->CCR4=4500;    	//��ʼװ��ֵ
	//PWM���ģʽ1�£�ռ�ձȵļ��㷽��ΪCCR1/ARR*100%
	//PWM���ģʽ2�£�ռ�ձȵļ��㷽��Ϊ(1-CCR1/ARR)*100%
} 
#endif




