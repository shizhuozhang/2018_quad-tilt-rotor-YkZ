#ifndef __IO_H
#define __IO_H	

#include "sys.h"

#if __LED
#define LED0 PDout(2)
#define LED1 PCout(2)
void LED_Init(void);
#endif


#if __BEEP
#define  BEEP0   PBout(11)	
void BEEP_Init(void);
#endif


#if __KEY
#define KEY1	PAin(0)		//KEY1是高电平触发，可作为WAKE_UP唤醒
#define KEY2	PAin(1)
#define KEY3	PAin(2)
#define KEY4	PAin(3)
#define KEY1_PRES	1
#define KEY2_PRES	2
#define KEY3_PRES	3
#define KEY4_PRES	4
void KEY_Init(void);
u8 KEY_Scan(void);//按键扫描函数应配合定时器中断使用，以一定频率扫描
#endif

#if __EXTI
void EXTIx_Init(void);
#endif

#if __ELSE
#define MPU9250_CS  PCout(4)
void ELSE_IO_Init(void);
#endif

#endif

