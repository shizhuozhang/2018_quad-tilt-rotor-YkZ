#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"


#if __SETITIM1							//TIM1�������ж�
	void TIM1_Init(u16 arr,u16 psc);
#endif
#if __SETITIM2							//TIM2�������ж�
	void TIM2_Init(u16 arr,u16 psc);
#endif
#if __SETITIM3							//TIM3�������ж�
	void TIM3_Init(u16 arr,u16 psc);
#endif
#if __SETITIM4							//TIM4�������ж�
	void TIM4_Init(u16 arr,u16 psc);
#endif
#if __SETITIM5							//TIM5�������ж�
	void TIM5_Init(u16 arr,u16 psc);
#endif
#if __SETITIM6							//TIM6�������ж�
	void TIM6_Init(u16 arr,u16 psc);
#endif
#if __SETITIM7							//TIM7�������ж�
	void TIM7_Init(u16 arr,u16 psc);
#endif
#if __SETITIM8							//TIM8�������ж�
	void TIM8_Init(u16 arr,u16 psc);
#endif





#endif
