#ifndef __H_DEFINE_H 
#define __H_DEFINE_H 

#include "sys.h"
#include "stdio.h"
#include  "math.h"  

/**************************功能块**************************/

/**********延时********/
#define		__DELAY  		1
#if __DELAY
	#include "delay.h"
#endif

/*************串口*************/

#define		__USART  		1	

#if __USART
/*注意Printf语句耗时很长，串口1主频72MHz，发送两个字节之间的时间大约是2.5ms
串口2，3，主频是36MHz，时间大约是5ms,因此，除非中断时间很长，否则不要在中断中使用*/
//PA9-TX1;PA10-RX1;PA2-TX1;PA3-RX2;PB10-TX3;PB11-RX3
	#define 	___USART_PRINTF	1				//与printf函数关联的串口号,
												//注意要与下面使能的串口匹配
	#define 	__USART1 		1				//串口1
	#define 	__USART2		0				//串口2
												//注意串口2的IO口和按键冲突
	#define 	__USART3		0				//串口3
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


/************IO口**************/
#define		__IO_PORT  		1
#if __IO_PORT
	#define		__LED  		1
	#define		__BEEP  	0
	#define		__KEY  		1		//按键的IO口和串口2冲突
	#define		__EXTI		1
	#define		__ELSE  	0		//其他可能用到IO口的配置
	#include "IO.h"
#endif

/**************TIMER************/
#define		__TIM  		1
#if __TIM
	#define __SETITIM1		0       //TIM1计时器中断
	#define __SETITIM2		0       //TIM2计时器中断
	#define __SETITIM3		0       //TIM3计时器中断
	#define __SETITIM4		0       //TIM4计时器中断
	#define __SETITIM5		0       //TIM5计时器中断
	#define __SETITIM6		1       //TIM6计时器中断
	#define __SETITIM7		0       //TIM7计时器中断
	#define __SETITIM8		0       //TIM8计时器中断
	#include "timer.h"
#endif

/**************PWMOUT************/
#define		__PWMOUT 		1
#if __PWMOUT
	#define __TIM1_PWM		0   //TIM1，PWM波输出//定时器1的2，3通道和串口1的引脚冲突											  
	#define __TIM2_PWM		0   //TIM2，PWM波输出//TIM2的引脚和TIM5冲突，使用重映射引脚
//重映射引脚和SWD引脚冲突PB3，导致Jlink检测不到芯片
//因此若使用CH1，CH2，下载时要重启状态下载
	#define __TIM3_PWM		1   //TIM3，PWM波输出
	#define __TIM4_PWM		0   //TIM4，PWM波输出											  
	#define __TIM5_PWM		0   //TIM5，PWM波输出//注意TIM5引脚和按键引脚以及串口2冲突											  
	#define __TIM8_PWM		0  //TIM8，PWM波输出
	#include "pwm.h"
#endif


/**************PWMIN************/
//PWM输入只能用CH1/CH2
//CH1配置
//	TIM8->CCMR1|=1<<0;//CC1被映射在TI1上
//	TIM8->CCMR1|=2<<8;//CC2被影设在TI1上
//	TIM8->SMCR|=5<<4;//滤波后定时器输入1
//CH2配置
//	TIM8->CCMR1|=2<<0;//CC1被映射在TI2上
//	TIM8->CCMR1|=1<<8;//CC2被影设在TI2上
//	TIM8->SMCR|=6<<4;//滤波后定时器输入2
//TIM1 TIM2 TIM3 配置的是CH1
//TIM4 TIM5 TIM8 配置的是CH2
#define		__PWMIN 		0
#if __PWMIN
	#define __TIM1_PWMIN		0   //TIM1，PWM波输入//定时器1的2，3通道和串口1的引脚冲突											  
	#define __TIM2_PWMIN		0   //TIM2，PWM波输入//TIM2的引脚和TIM5冲突，使用重映射引脚
//重映射引脚和SWD引脚冲突PB3，导致Jlink检测不到芯片
//因此若使用CH1，CH2，下载时要重启状态下载
	#define __TIM3_PWMIN		0   //TIM3，PWM波输入
	#define __TIM4_PWMIN		0   //TIM4，PWM波输入											  
	#define __TIM5_PWMIN		0   //TIM5，PWM波输入//注意TIM5引脚和按键引脚以及串口2冲突											  
	#define __TIM8_PWMIN		0   //TIM8，PWM波输入
	#include "pwmin.h"
#endif

/****************输入捕获*******************/
/*注意：应为中断过长，所以只写了TIM5的中断，其余参考TIM5
TIM1和TIM8终端类型理论上是TIM8_UP_IRQn（更新中断）（没试）
还有一个TIM8_CC_IRQn（输入捕获中断），应该使用这个会更迅速*/
#define __CAP  1
#if __CAP 
	#define __TIM1_CAP   0
	#define __TIM2_CAP   0			 //TIM2，PWM波输入//TIM2的引脚和TIM5冲突，使用重映射引脚
//重映射引脚和SWD引脚冲突PB3，导致Jlink检测不到芯片
//因此若使用CH1，CH2，下载时要重启状态下载
	#define __TIM3_CAP   0
	#define __TIM4_CAP   1
	#define __TIM5_CAP   0			//注意TIM5引脚和按键引脚以及串口2冲突		
	#define __TIM8_CAP   0
	#include "cap.h"
#endif

/**************ENCODER************/
#define		__TIM_ENCODER 		0
#if __TIM_ENCODER
	#define __ENCODER1		0
	#define __ENCODER2		0
//重映射引脚和SWD引脚冲突PB3，导致Jlink检测不到芯片
//因此若使用CH1，CH2，下载时要重启状态下载
	#define __ENCODER3		0
	#define __ENCODER4		0
	#define __ENCODER5		0
	#define __ENCODER8		0
	#include  "Encoder.h"

#endif
/******************ADC*********************/
//adc使用时注意：ADC的通道是通用的ADC的最后一个通道连接的是芯片内部的温度传感器
//adc2的数据存放在ADC1->DR中，所以不应该单独使用ADC2
#define __ADC  0
#if __ADC
	#define __ADC1   	0
	#define __ADC2      0
	#define __ADC3      0
	#include "adc.h"
	#define __DMA_ADC   0
	#if __DMA_ADC
	//adc_dma 注意  adc2的数据放在ADC1的DR中，所以没有单独的dma通道
	//如果使用adc2，一般会用dma中断，将adc1和adc2的数据分开
		#define __DMA_ADC1   0
		#define __DMA_ADC3   0
		#include "dma_adc.h"
	#endif
#endif 

///////////////////////////////////////////////////////////////////////////////////

/**************************通用外部变量定义**************************/

extern u16 Freq;//频率值
extern u8 Flag;


///////////////////////////////////////////////////////////////////////////////////
/**********************外设使能初始化函数声明**************************/

void Init1(void);
void Init2(void);

#endif




