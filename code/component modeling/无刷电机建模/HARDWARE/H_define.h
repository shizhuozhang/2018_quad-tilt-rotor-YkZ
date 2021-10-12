#ifndef __H_DEFINE_H 
#define __H_DEFINE_H 

#include "sys.h"
#include "stdio.h"
#include  "math.h"  

/**************************���ܿ�**************************/

/**********��ʱ********/
#define		__DELAY  		1
#if __DELAY
	#include "delay.h"
#endif

/*************����*************/

#define		__USART  		1	

#if __USART
/*ע��Printf����ʱ�ܳ�������1��Ƶ72MHz�����������ֽ�֮���ʱ���Լ��2.5ms
����2��3����Ƶ��36MHz��ʱ���Լ��5ms,��ˣ������ж�ʱ��ܳ�������Ҫ���ж���ʹ��*/
//PA9-TX1;PA10-RX1;PA2-TX1;PA3-RX2;PB10-TX3;PB11-RX3
	#define 	___USART_PRINTF	1				//��printf���������Ĵ��ں�,
												//ע��Ҫ������ʹ�ܵĴ���ƥ��
	#define 	__USART1 		1				//����1
	#define 	__USART2		0				//����2
												//ע�⴮��2��IO�ںͰ�����ͻ
	#define 	__USART3		0				//����3
	#include 	"usart.h"
	#include "DMA_USART.h"
#endif


/*************LCD*************/
#define		__LCD  		0
#if __LCD
	#include "QDTFT_demo.h"
	#include "Lcd_Driver.h"
	#include "GUI.h"
#endif


/************IO��**************/
#define		__IO_PORT  		1
#if __IO_PORT
	#define		__LED  		1
	#define		__BEEP  	0
	#define		__KEY  		1		//������IO�ںʹ���2��ͻ
	#define		__EXTI		1
	#define		__ELSE  	0		//���������õ�IO�ڵ�����
	#include "IO.h"
#endif

/**************TIMER************/
#define		__TIM  		1
#if __TIM
	#define __SETITIM1		0       //TIM1��ʱ���ж�
	#define __SETITIM2		0       //TIM2��ʱ���ж�
	#define __SETITIM3		0       //TIM3��ʱ���ж�
	#define __SETITIM4		0       //TIM4��ʱ���ж�
	#define __SETITIM5		0       //TIM5��ʱ���ж�
	#define __SETITIM6		1       //TIM6��ʱ���ж�
	#define __SETITIM7		0       //TIM7��ʱ���ж�
	#define __SETITIM8		0       //TIM8��ʱ���ж�
	#include "timer.h"
#endif

/**************PWMOUT************/
#define		__PWMOUT 		1
#if __PWMOUT
	#define __TIM1_PWM		0   //TIM1��PWM�����//��ʱ��1��2��3ͨ���ʹ���1�����ų�ͻ											  
	#define __TIM2_PWM		0   //TIM2��PWM�����//TIM2�����ź�TIM5��ͻ��ʹ����ӳ������
//��ӳ�����ź�SWD���ų�ͻPB3������Jlink��ⲻ��оƬ
//�����ʹ��CH1��CH2������ʱҪ����״̬����
	#define __TIM3_PWM		1   //TIM3��PWM�����
	#define __TIM4_PWM		0   //TIM4��PWM�����											  
	#define __TIM5_PWM		0   //TIM5��PWM�����//ע��TIM5���źͰ��������Լ�����2��ͻ											  
	#define __TIM8_PWM		0  //TIM8��PWM�����
	#include "pwm.h"
#endif


/**************PWMIN************/
//PWM����ֻ����CH1/CH2
//CH1����
//	TIM8->CCMR1|=1<<0;//CC1��ӳ����TI1��
//	TIM8->CCMR1|=2<<8;//CC2��Ӱ����TI1��
//	TIM8->SMCR|=5<<4;//�˲���ʱ������1
//CH2����
//	TIM8->CCMR1|=2<<0;//CC1��ӳ����TI2��
//	TIM8->CCMR1|=1<<8;//CC2��Ӱ����TI2��
//	TIM8->SMCR|=6<<4;//�˲���ʱ������2
//TIM1 TIM2 TIM3 ���õ���CH1
//TIM4 TIM5 TIM8 ���õ���CH2
#define		__PWMIN 		0
#if __PWMIN
	#define __TIM1_PWMIN		0   //TIM1��PWM������//��ʱ��1��2��3ͨ���ʹ���1�����ų�ͻ											  
	#define __TIM2_PWMIN		0   //TIM2��PWM������//TIM2�����ź�TIM5��ͻ��ʹ����ӳ������
//��ӳ�����ź�SWD���ų�ͻPB3������Jlink��ⲻ��оƬ
//�����ʹ��CH1��CH2������ʱҪ����״̬����
	#define __TIM3_PWMIN		0   //TIM3��PWM������
	#define __TIM4_PWMIN		0   //TIM4��PWM������											  
	#define __TIM5_PWMIN		0   //TIM5��PWM������//ע��TIM5���źͰ��������Լ�����2��ͻ											  
	#define __TIM8_PWMIN		0   //TIM8��PWM������
	#include "pwmin.h"
#endif

/****************���벶��*******************/
/*ע�⣺ӦΪ�жϹ���������ֻд��TIM5���жϣ�����ο�TIM5
TIM1��TIM8�ն�������������TIM8_UP_IRQn�������жϣ���û�ԣ�
����һ��TIM8_CC_IRQn�����벶���жϣ���Ӧ��ʹ��������Ѹ��*/
#define __CAP  1
#if __CAP 
	#define __TIM1_CAP   0
	#define __TIM2_CAP   0			 //TIM2��PWM������//TIM2�����ź�TIM5��ͻ��ʹ����ӳ������
//��ӳ�����ź�SWD���ų�ͻPB3������Jlink��ⲻ��оƬ
//�����ʹ��CH1��CH2������ʱҪ����״̬����
	#define __TIM3_CAP   0
	#define __TIM4_CAP   1
	#define __TIM5_CAP   0			//ע��TIM5���źͰ��������Լ�����2��ͻ		
	#define __TIM8_CAP   0
	#include "cap.h"
#endif

/**************ENCODER************/
#define		__TIM_ENCODER 		0
#if __TIM_ENCODER
	#define __ENCODER1		0
	#define __ENCODER2		0
//��ӳ�����ź�SWD���ų�ͻPB3������Jlink��ⲻ��оƬ
//�����ʹ��CH1��CH2������ʱҪ����״̬����
	#define __ENCODER3		0
	#define __ENCODER4		0
	#define __ENCODER5		0
	#define __ENCODER8		0
	#include  "Encoder.h"

#endif
/******************ADC*********************/
//adcʹ��ʱע�⣺ADC��ͨ����ͨ�õ�ADC�����һ��ͨ�����ӵ���оƬ�ڲ����¶ȴ�����
//adc2�����ݴ����ADC1->DR�У����Բ�Ӧ�õ���ʹ��ADC2
#define __ADC  0
#if __ADC
	#define __ADC1   	0
	#define __ADC2      0
	#define __ADC3      0
	#include "adc.h"
	#define __DMA_ADC   0
	#if __DMA_ADC
	//adc_dma ע��  adc2�����ݷ���ADC1��DR�У�����û�е�����dmaͨ��
	//���ʹ��adc2��һ�����dma�жϣ���adc1��adc2�����ݷֿ�
		#define __DMA_ADC1   0
		#define __DMA_ADC3   0
		#include "dma_adc.h"
	#endif
#endif 

///////////////////////////////////////////////////////////////////////////////////

/**************************ͨ���ⲿ��������**************************/

extern u16 Freq;//Ƶ��ֵ
extern u8 Flag;


///////////////////////////////////////////////////////////////////////////////////
/**********************����ʹ�ܳ�ʼ����������**************************/

void Init1(void);
void Init2(void);

#endif




