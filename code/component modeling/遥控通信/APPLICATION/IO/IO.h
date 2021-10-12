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
#define KEY1	PEin(3)		//KEY1�Ǹߵ�ƽ����������ΪWAKE_UP����
#define KEY2	PEin(4)
#define KEY1_PRES	1
#define KEY2_PRES	2
void KEY_Init(void);
u8 KEY_Scan(void);//����ɨ�躯��Ӧ��϶�ʱ���ж�ʹ�ã���һ��Ƶ��ɨ��
#endif

#if __EXTI
void EXTIx_Init(void);
#endif

#if __ELSE
void ELSE_IO_Init(void);
#endif

#endif

