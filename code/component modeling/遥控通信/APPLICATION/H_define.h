#ifndef __H_DEFINE_H 
#define __H_DEFINE_H 

#include "sys.h"
#include  "math.h" 

/**************************功能块**************************/

/**********延时********/
#define		__DELAY  		1
#if __DELAY
	#include "delay.h"
#endif

/*************串口*************/
#define		__USART  		1	
//USART1,6时钟是APB2,其余是APB1
#if __USART
/*注意Printf语句耗时很长，串口1主频168MHz，发送两个字节之间的时间大约是ms
串口2，3，主频是MHz，时间大约是5ms,因此，除非中断时间很长，否则不要在中断中使用*/
	#define 	___USART_PRINTF	1				//与printf函数关联的串口号,有效参数范围1-6
												//注意要与下面使能的串口匹配
	#define 	__USART1 		1				//串口1
	#define 	__USART2		1				//串口2											
	#define 	__USART3		1				//串口3
	#define 	__UART4 		0				//串口4
	#define 	__UART5		    0				//串口5											
	#define 	__USART6		0				//串口6	
	#include 	"usart.h"
	//串口3接受遥控器数据，串口2接受AHRS数据
	#define		__DMA_USART  	1	//DMA1和2的时钟均为AHB1
	
	#if __DMA_USART 
		#define		__DMA_USART1  	0		//串口1		DMA配置
		#define		__DMA_USART2  	1		//串口2		DMA配置
		#define		__DMA_USART3  	1		//串口3		DMA配置
		#define		__DMA_UART4  	0		//串口4		DMA配置
		#define		__DMA_UART5  	0		//串口5		DMA配置
		#define		__DMA_USART6  	0		//串口6		DMA配置
		
		#include  "DMA.h"
	#endif

#endif

/************IO口**************/
//IO口时钟分布:portA～portI对应RCC_AHB1ENR[0:8]
//即portA对应RCC_AHB1ENR[0];//portB对应RCC_AHB1ENR[1];//portC对应RCC_AHB1ENR[2];
//即portD对应RCC_AHB1ENR[3];//portE对应RCC_AHB1ENR[4];//portF对应RCC_AHB1ENR[5];
//即portG对应RCC_AHB1ENR[6];//portH对应RCC_AHB1ENR[7];//portI对应RCC_AHB1ENR[8];
#define		__IO_PORT  		1
#if __IO_PORT
	#define		__LED  		1
	#define		__BEEP  	0
	#define		__KEY  		0		//按键的IO口
	#define		__EXTI		0
	#define		__ELSE  	1		//其他可能用到IO口的配置
	#include "IO.h"
#endif

/**************TIMER************/
//TIM1，8，9,10,11时钟为APB2，TIM2，3，4，5，6，7，12，13，14时钟为APB1
//APB1时钟42M，分频系数均不是1，故其下面的定时器时钟均是84M
//APB2时钟84M，分频系数均不是1，故其下面的定时器时钟均是168M
#define		__TIM  		1
#if __TIM
	#define __SETITIM1		0       //TIM1计时器中断
	#define __SETITIM2		0       //TIM2计时器中断
	#define __SETITIM3		0       //TIM3计时器中断
	#define __SETITIM4		0       //TIM4计时器中断
	#define __SETITIM5		0       //TIM5计时器中断
	#define __SETITIM6		1       //TIM6计时器中断
	#define __SETITIM7		1       //TIM7计时器中断
	#define __SETITIM8		0       //TIM8计时器中断
	#include "timer.h"
#endif

/**************PWMOUT************/
//TIM1，8为高级定时器，32位计数器
//TIM2-5为通用定时器，其中3，4，为16位计数器，2，5，为32位计数器
//TIM9-14为通用定时器，16位计数器，其中9.12为两个通道，10.11.13.14为独立通道
#define		__PWMOUT 		1
#if __PWMOUT
	#define __TIM1_PWM		1   //TIM1，PWM波输出//定时器1的2，3通道和串口1的引脚冲突											  
	#define __TIM2_PWM		0   //TIM2，PWM波输出//TIM2的引脚和TIM5冲突，使用重映射引脚
	#define __TIM3_PWM		1   //TIM3，PWM波输出
	#define __TIM4_PWM		0   //TIM4，PWM波输出											  
	#define __TIM5_PWM		0   //TIM5，PWM波输出//注意TIM5引脚和按键引脚以及串口2冲突											  
	#define __TIM8_PWM		1  //TIM8，PWM波输出
	#define __TIM9_PWM		0   //TIM1，PWM波输出//定时器1的2，3通道和串口1的引脚冲突											  
	#define __TIM10_PWM		0   //TIM2，PWM波输出//TIM2的引脚和TIM5冲突，使用重映射引脚
	#define __TIM11_PWM		0   //TIM3，PWM波输出
	#define __TIM12_PWM		0   //TIM4，PWM波输出											  
	#define __TIM13_PWM		0   //TIM5，PWM波输出//注意TIM5引脚和按键引脚以及串口2冲突											  
	#define __TIM14_PWM		0  //TIM8，PWM波输出
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
#define __CAP  0
#if __CAP 
	#define __TIM1_CAP   0
	#define __TIM2_CAP   0			 //TIM2，PWM波输入//TIM2的引脚和TIM5冲突，使用重映射引脚
//重映射引脚和SWD引脚冲突PB3，导致Jlink检测不到芯片
//因此若使用CH1，CH2，下载时要重启状态下载
	#define __TIM3_CAP   0
	#define __TIM4_CAP   0
	#define __TIM5_CAP   0			//注意TIM5引脚和按键引脚以及串口2冲突		
	#define __TIM8_CAP   0
	#include "cap.h"
#endif

/******************ADC*********************/
//adc使用时注意：ADC的通道是通用的ADC的最后一个通道连接的是芯片内部的温度传感器
//adc2的数据存放在ADC1->DR中，所以不应该单独使用ADC2
#define __ADC  1
#if __ADC
	#define __ADC1   	1
	#define __ADC2      0
	#define __ADC3      0
	#include "adc.h"
	
	#define __DMA_ADC   1
	
	#if __DMA_ADC
	//adc_dma 注意  adc2的数据放在ADC1的DR中，所以没有单独的dma通道
	//如果使用adc2，一般会用dma中断，将adc1和adc2的数据分开
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

/**************************通用宏定义**************************/


///////////////////////////////////////////////////////////////////////////////////

/**************************通用外部变量定义**************************/
extern volatile u8 SBUS_DATA[25];
//extern volatile u16 ChanneL_Data[10];
extern volatile s16 ControL_Data[10];//遥控器10个通道的控制数据
extern u8 Sbus_OK;			//遥控器信号接收到

extern volatile u8 AHRS_DATA[42];
extern volatile POSE  Att_Angle;
extern u8 Ahrs_Flag1;	//串口2接受中断中帧头判断使能标志位
extern u8 Ahrs_OK;		//AHRS数据接收到

extern volatile u16 ADC1_DATA[6];
extern u8 sign_Adc1;
extern volatile float Voltage[6];//采到的电压值
extern volatile float Current[5];//其中总电流和四路电机的电流，电流电压的转换关系是40mv/A
extern volatile float Walte[5];//总功率和四路电机的功率
extern u8 PowerOff_Flag;
extern volatile u8 Dma1_T1_Close;		//DMA1Channel3关闭信号
extern volatile u8 Dma1_T5_Close;		//DMA1Channel6关闭信号

///////////////////////////////////////////////////////////////////////////////////
/**********************外设使能初始化函数声明**************************/

void Init1(void);
void Init2(void);

#endif




