#ifndef __H_DEFINE_H 
#define __H_DEFINE_H 

#include "sys.h"
#include "stdio.h"
#include "string.h"
#include "DMA_USART.h"
#include "math.h"
#include "PID.h"
/**************************功能块**************************/

/**********延时********/
#define		__DELAY  		1
#if __DELAY
	#include "delay.h"
#endif

/*************串口*************/
/*注意Printf语句耗时很长，串口1主频72MHz，发送两个字节之间的时间大约是2.5ms
串口2，3，主频是36MHz，时间大约是5ms,因此，除非中断时间很长，否则不要在中断中使用*/
#define		__USART  		1	
#if __USART
	#define 	___USART_PRINTF	1				//与printf函数关联的串口号,
												//注意要与下面使能的串口匹配
	#define 	__USART1 		1				//串口1
	#define 	__USART2		1				//串口2
												//注意串口2的IO口和按键冲突
	#define 	__USART3		0				//串口3
	#include 	"usart.h"
#endif


/************IO口**************/
#define		__IO_PORT  		1
#if __IO_PORT
	#define		__LED  		1
	#define		__BEEP  	0
	#define		__KEY  		1		//按键的IO口和串口2冲突
	#define		__EXTI		0
	#define		__ELSE  	1		//其他可能用到IO口的配置
	#include "IO.h"
#endif

/**************TIMER************/
#define		__TIM  		1
#if __TIM
	#define __SETITIM1		0       //TIM1计时器中断
	#define __SETITIM2		0       //TIM2计时器中断
	#define __SETITIM3		1       //TIM3计时器中断
	#define __SETITIM4		0       //TIM4计时器中断

		#include "timer.h"
#endif

/**************PWMOUT************/
#define		__PWMOUT 		1
#if __PWMOUT
	#define __TIM1_PWM		0  //TIM1，PWM波输出//定时器1的2，3通道和串口1的引脚冲突											  
	#define __TIM2_PWM		0   //TIM2，PWM波输出//TIM2的引脚和TIM5冲突，使用重映射引脚
//重映射引脚和SWD引脚冲突PB3，导致Jlink检测不到芯片
//因此若使用CH1，CH2，下载时要重启状态下载
	#define __TIM3_PWM		0   //TIM3，PWM波输出
	#define __TIM4_PWM		1  //TIM4，PWM波输出											  
	#include "pwm.h"
#endif


#define	G	9.8


/**************************通用外部变量定义**************************/

extern u8 D_6050[32];	//6050串口数据
extern u8 sign_usrt2;			//6050读到数据信号
extern u8 Dma1_C6_Close;		//DMA1Channel6关闭信号
extern u8 Tim_flag;

extern volatile WAng_XYZ   WAng_Now;
extern volatile Angle_XYZ  Angle_Now; 
extern float Angle_Init[3];
///////////////////////////////////////////////////////////////////////////////////

/**********************外设使能初始化函数声明**************************/
void Init1(void);

#endif



