#ifndef __PWM_H
#define __PWM_H

#include "sys.h"

#if __TIM1_PWM
	void TIM1_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM2_PWM
	void TIM2_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM3_PWM
	void TIM3_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM4_PWM
	void TIM4_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM5_PWM
	void TIM5_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM8_PWM
	void TIM8_PWM_Init(u16 arr,u16 psc);
#endif

#endif
