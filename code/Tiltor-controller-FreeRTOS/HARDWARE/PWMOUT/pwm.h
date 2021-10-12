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
#if __TIM9_PWM
	void TIM9_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM10_PWM
	void TIM10_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM11_PWM
	void TIM11_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM12_PWM
	void TIM12_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM13_PWM
	void TIM13_PWM_Init(u16 arr,u16 psc);
#endif
#if __TIM14_PWM
	void TIM14_PWM_Init(u16 arr,u16 psc);
#endif

#endif


