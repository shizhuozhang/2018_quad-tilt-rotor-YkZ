#ifndef __CAP_H
#define __CAP_H

#include "sys.h"

#if __TIM1_CAP
	void TIM1_Cap_Init(u16 arr,u16 psc); 
#endif
#if __TIM2_CAP
	void TIM2_Cap_Init(u16 arr,u16 psc); 
#endif
#if __TIM3_CAP
	void TIM3_Cap_Init(u16 arr,u16 psc); 
#endif
#if __TIM4_CAP
	void TIM4_Cap_Init(u16 arr,u16 psc); 
#endif
#if __TIM5_CAP
	void TIM5_Cap_Init(u16 arr,u16 psc); 
#endif
#if __TIM8_CAP
	void TIM8_Cap_Init(u16 arr,u16 psc); 
#endif

#endif





