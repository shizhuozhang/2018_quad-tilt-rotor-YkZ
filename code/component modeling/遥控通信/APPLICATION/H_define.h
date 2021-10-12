#ifndef __H_DEFINE_H 
#define __H_DEFINE_H 

#include "sys.h"
#include  "math.h" 

/**************************���ܿ�**************************/

/**********��ʱ********/
#define		__DELAY  		1
#if __DELAY
	#include "delay.h"
#endif

/*************����*************/
#define		__USART  		1	
//USART1,6ʱ����APB2,������APB1
#if __USART
/*ע��Printf����ʱ�ܳ�������1��Ƶ168MHz�����������ֽ�֮���ʱ���Լ��ms
����2��3����Ƶ��MHz��ʱ���Լ��5ms,��ˣ������ж�ʱ��ܳ�������Ҫ���ж���ʹ��*/
	#define 	___USART_PRINTF	1				//��printf���������Ĵ��ں�,��Ч������Χ1-6
												//ע��Ҫ������ʹ�ܵĴ���ƥ��
	#define 	__USART1 		1				//����1
	#define 	__USART2		1				//����2											
	#define 	__USART3		1				//����3
	#define 	__UART4 		0				//����4
	#define 	__UART5		    0				//����5											
	#define 	__USART6		0				//����6	
	#include 	"usart.h"
	//����3����ң�������ݣ�����2����AHRS����
	#define		__DMA_USART  	1	//DMA1��2��ʱ�Ӿ�ΪAHB1
	
	#if __DMA_USART 
		#define		__DMA_USART1  	0		//����1		DMA����
		#define		__DMA_USART2  	1		//����2		DMA����
		#define		__DMA_USART3  	1		//����3		DMA����
		#define		__DMA_UART4  	0		//����4		DMA����
		#define		__DMA_UART5  	0		//����5		DMA����
		#define		__DMA_USART6  	0		//����6		DMA����
		
		#include  "DMA.h"
	#endif

#endif

/************IO��**************/
//IO��ʱ�ӷֲ�:portA��portI��ӦRCC_AHB1ENR[0:8]
//��portA��ӦRCC_AHB1ENR[0];//portB��ӦRCC_AHB1ENR[1];//portC��ӦRCC_AHB1ENR[2];
//��portD��ӦRCC_AHB1ENR[3];//portE��ӦRCC_AHB1ENR[4];//portF��ӦRCC_AHB1ENR[5];
//��portG��ӦRCC_AHB1ENR[6];//portH��ӦRCC_AHB1ENR[7];//portI��ӦRCC_AHB1ENR[8];
#define		__IO_PORT  		1
#if __IO_PORT
	#define		__LED  		1
	#define		__BEEP  	0
	#define		__KEY  		0		//������IO��
	#define		__EXTI		0
	#define		__ELSE  	1		//���������õ�IO�ڵ�����
	#include "IO.h"
#endif

/**************TIMER************/
//TIM1��8��9,10,11ʱ��ΪAPB2��TIM2��3��4��5��6��7��12��13��14ʱ��ΪAPB1
//APB1ʱ��42M����Ƶϵ��������1����������Ķ�ʱ��ʱ�Ӿ���84M
//APB2ʱ��84M����Ƶϵ��������1����������Ķ�ʱ��ʱ�Ӿ���168M
#define		__TIM  		1
#if __TIM
	#define __SETITIM1		0       //TIM1��ʱ���ж�
	#define __SETITIM2		0       //TIM2��ʱ���ж�
	#define __SETITIM3		0       //TIM3��ʱ���ж�
	#define __SETITIM4		0       //TIM4��ʱ���ж�
	#define __SETITIM5		0       //TIM5��ʱ���ж�
	#define __SETITIM6		1       //TIM6��ʱ���ж�
	#define __SETITIM7		1       //TIM7��ʱ���ж�
	#define __SETITIM8		0       //TIM8��ʱ���ж�
	#include "timer.h"
#endif

/**************PWMOUT************/
//TIM1��8Ϊ�߼���ʱ����32λ������
//TIM2-5Ϊͨ�ö�ʱ��������3��4��Ϊ16λ��������2��5��Ϊ32λ������
//TIM9-14Ϊͨ�ö�ʱ����16λ������������9.12Ϊ����ͨ����10.11.13.14Ϊ����ͨ��
#define		__PWMOUT 		1
#if __PWMOUT
	#define __TIM1_PWM		1   //TIM1��PWM�����//��ʱ��1��2��3ͨ���ʹ���1�����ų�ͻ											  
	#define __TIM2_PWM		0   //TIM2��PWM�����//TIM2�����ź�TIM5��ͻ��ʹ����ӳ������
	#define __TIM3_PWM		1   //TIM3��PWM�����
	#define __TIM4_PWM		0   //TIM4��PWM�����											  
	#define __TIM5_PWM		0   //TIM5��PWM�����//ע��TIM5���źͰ��������Լ�����2��ͻ											  
	#define __TIM8_PWM		1  //TIM8��PWM�����
	#define __TIM9_PWM		0   //TIM1��PWM�����//��ʱ��1��2��3ͨ���ʹ���1�����ų�ͻ											  
	#define __TIM10_PWM		0   //TIM2��PWM�����//TIM2�����ź�TIM5��ͻ��ʹ����ӳ������
	#define __TIM11_PWM		0   //TIM3��PWM�����
	#define __TIM12_PWM		0   //TIM4��PWM�����											  
	#define __TIM13_PWM		0   //TIM5��PWM�����//ע��TIM5���źͰ��������Լ�����2��ͻ											  
	#define __TIM14_PWM		0  //TIM8��PWM�����
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
#define __CAP  0
#if __CAP 
	#define __TIM1_CAP   0
	#define __TIM2_CAP   0			 //TIM2��PWM������//TIM2�����ź�TIM5��ͻ��ʹ����ӳ������
//��ӳ�����ź�SWD���ų�ͻPB3������Jlink��ⲻ��оƬ
//�����ʹ��CH1��CH2������ʱҪ����״̬����
	#define __TIM3_CAP   0
	#define __TIM4_CAP   0
	#define __TIM5_CAP   0			//ע��TIM5���źͰ��������Լ�����2��ͻ		
	#define __TIM8_CAP   0
	#include "cap.h"
#endif

/******************ADC*********************/
//adcʹ��ʱע�⣺ADC��ͨ����ͨ�õ�ADC�����һ��ͨ�����ӵ���оƬ�ڲ����¶ȴ�����
//adc2�����ݴ����ADC1->DR�У����Բ�Ӧ�õ���ʹ��ADC2
#define __ADC  1
#if __ADC
	#define __ADC1   	1
	#define __ADC2      0
	#define __ADC3      0
	#include "adc.h"
	
	#define __DMA_ADC   1
	
	#if __DMA_ADC
	//adc_dma ע��  adc2�����ݷ���ADC1��DR�У�����û�е�����dmaͨ��
	//���ʹ��adc2��һ�����dma�жϣ���adc1��adc2�����ݷֿ�
		#define __DMA_ADC1   1
		#define __DMA_ADC3   0
		
		#include  "DMA.h"
		
	#endif
	
#endif 

/******************SPI****************/
#define __SPI 0
#if __SPI 
	#define __SPI1  0
	#define __SPI2  0
	#define __SPI3  0
	#include "spi.h"
#endif

#define __SBUS 1
#if __SBUS  
	#include "SBUS.h"
#endif

#define __AHRS 1
#if __AHRS  
	#include "AHRS.h"
#endif

/**************************ͨ�ú궨��**************************/


///////////////////////////////////////////////////////////////////////////////////

/**************************ͨ���ⲿ��������**************************/
extern volatile u8 SBUS_DATA[25];
//extern volatile u16 ChanneL_Data[10];
extern volatile s16 ControL_Data[10];//ң����10��ͨ���Ŀ�������
extern u8 Sbus_OK;			//ң�����źŽ��յ�

extern volatile u8 AHRS_DATA[42];
extern volatile POSE  Att_Angle;
extern u8 Ahrs_Flag1;	//����2�����ж���֡ͷ�ж�ʹ�ܱ�־λ
extern u8 Ahrs_OK;		//AHRS���ݽ��յ�

extern volatile u16 ADC1_DATA[6];
extern u8 sign_Adc1;
extern volatile float Voltage[6];//�ɵ��ĵ�ѹֵ
extern volatile float Current[5];//�����ܵ�������·����ĵ�����������ѹ��ת����ϵ��40mv/A
extern volatile float Walte[5];//�ܹ��ʺ���·����Ĺ���
extern u8 PowerOff_Flag;
extern volatile u8 Dma1_T1_Close;		//DMA1Channel3�ر��ź�
extern volatile u8 Dma1_T5_Close;		//DMA1Channel6�ر��ź�

///////////////////////////////////////////////////////////////////////////////////
/**********************����ʹ�ܳ�ʼ����������**************************/

void Init1(void);
void Init2(void);

#endif




