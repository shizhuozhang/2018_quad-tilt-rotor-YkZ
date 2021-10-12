#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"


#if __SETITIM1							//TIM1计数器中断
	void TIM1_Init(u16 arr,u16 psc);
#endif
#if __SETITIM2							//TIM2计数器中断
	void TIM2_Init(u16 arr,u16 psc);
#endif
#if __SETITIM3							//TIM3计数器中断
	void TIM3_Init(u16 arr,u16 psc);
#endif
#if __SETITIM4							//TIM4计数器中断
	void TIM4_Init(u16 arr,u16 psc);
#endif
#if __SETITIM5							//TIM5计数器中断
	void TIM5_Init(u16 arr,u16 psc);
#endif
#if __SETITIM6							//TIM6计数器中断
	void TIM6_Init(u16 arr,u16 psc);
#endif
#if __SETITIM7							//TIM7计数器中断
	void TIM7_Init(u16 arr,u16 psc);
#endif
#if __SETITIM8							//TIM8计数器中断
	void TIM8_Init(u16 arr,u16 psc);
#endif





#endif
