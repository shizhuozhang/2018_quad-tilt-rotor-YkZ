#ifndef __H_DEFINE_H 
#define __H_DEFINE_H 

#include "sys.h"
#include "stdio.h"
#include "string.h"
#include "DMA_USART.h"
#include "math.h"
#include "PID.h"
/**************************���ܿ�**************************/

/**********��ʱ********/
#define		__DELAY  		1
#if __DELAY
	#include "delay.h"
#endif

/*************����*************/
/*ע��Printf����ʱ�ܳ�������1��Ƶ72MHz�����������ֽ�֮���ʱ���Լ��2.5ms
����2��3����Ƶ��36MHz��ʱ���Լ��5ms,��ˣ������ж�ʱ��ܳ�������Ҫ���ж���ʹ��*/
#define		__USART  		1	
#if __USART
	#define 	___USART_PRINTF	1				//��printf���������Ĵ��ں�,
												//ע��Ҫ������ʹ�ܵĴ���ƥ��
	#define 	__USART1 		1				//����1
	#define 	__USART2		1				//����2
												//ע�⴮��2��IO�ںͰ�����ͻ
	#define 	__USART3		0				//����3
	#include 	"usart.h"
#endif


/************IO��**************/
#define		__IO_PORT  		1
#if __IO_PORT
	#define		__LED  		1
	#define		__BEEP  	0
	#define		__KEY  		1		//������IO�ںʹ���2��ͻ
	#define		__EXTI		0
	#define		__ELSE  	1		//���������õ�IO�ڵ�����
	#include "IO.h"
#endif

/**************TIMER************/
#define		__TIM  		1
#if __TIM
	#define __SETITIM1		0       //TIM1��ʱ���ж�
	#define __SETITIM2		0       //TIM2��ʱ���ж�
	#define __SETITIM3		1       //TIM3��ʱ���ж�
	#define __SETITIM4		0       //TIM4��ʱ���ж�

		#include "timer.h"
#endif

/**************PWMOUT************/
#define		__PWMOUT 		1
#if __PWMOUT
	#define __TIM1_PWM		0  //TIM1��PWM�����//��ʱ��1��2��3ͨ���ʹ���1�����ų�ͻ											  
	#define __TIM2_PWM		0   //TIM2��PWM�����//TIM2�����ź�TIM5��ͻ��ʹ����ӳ������
//��ӳ�����ź�SWD���ų�ͻPB3������Jlink��ⲻ��оƬ
//�����ʹ��CH1��CH2������ʱҪ����״̬����
	#define __TIM3_PWM		0   //TIM3��PWM�����
	#define __TIM4_PWM		1  //TIM4��PWM�����											  
	#include "pwm.h"
#endif


#define	G	9.8


/**************************ͨ���ⲿ��������**************************/

extern u8 D_6050[32];	//6050��������
extern u8 sign_usrt2;			//6050���������ź�
extern u8 Dma1_C6_Close;		//DMA1Channel6�ر��ź�
extern u8 Tim_flag;

extern volatile WAng_XYZ   WAng_Now;
extern volatile Angle_XYZ  Angle_Now; 
extern float Angle_Init[3];
///////////////////////////////////////////////////////////////////////////////////

/**********************����ʹ�ܳ�ʼ����������**************************/
void Init1(void);

#endif



