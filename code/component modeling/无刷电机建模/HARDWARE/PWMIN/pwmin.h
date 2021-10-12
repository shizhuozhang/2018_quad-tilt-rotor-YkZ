#ifndef __PWMIN_H
#define __PWMIN_H

#include "sys.h"

#if __TIM1_PWMIN
	void TIM1_PWMIN_Init(u16 arr,u16 psc);
#endif
#if __TIM2_PWMIN
	void TIM2_PWMIN_Init(u16 arr,u16 psc);
#endif
#if __TIM3_PWMIN
	void TIM3_PWMIN_Init(u16 arr,u16 psc);
#endif
#if __TIM4_PWMIN
	void TIM4_PWMIN_Init(u16 arr,u16 psc);
#endif
#if __TIM5_PWMIN
	void TIM5_PWMIN_Init(u16 arr,u16 psc);
#endif
#if __TIM8_PWMIN
	void TIM8_PWMIN_Init(u16 arr,u16 psc);
#endif

#endif
