#ifndef __IO_H
#define __IO_H	

#include "sys.h"

#if __LED
#define LED0 PEout(1)
#define LED1 PEout(2)
void LED_Init(void);
#endif


#if __BEEP
#define  BEEP   PEout(0)	
void BEEP_Init(void);
#endif


#if __KEY
#define KEY1	PEin(3)		//KEY1是高电平触发，可作为WAKE_UP唤醒
#define KEY2	PEin(4)
#define KEY1_PRES	1
#define KEY2_PRES	2
void KEY_Init(void);
u8 KEY_Scan(void);//按键扫描函数应配合定时器中断使用，以一定频率扫描
#endif

#if __EXTI
void EXTIx_Init(void);
#endif

#if __ELSE
void ELSE_IO_Init(void);
#endif

#endif

