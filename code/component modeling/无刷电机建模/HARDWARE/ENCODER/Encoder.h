#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"

#if __ENCODER1
	void Encoder1_Init(void);
#endif
#if __ENCODER2
	void Encoder2_Init(void);
#endif
#if __ENCODER3
	void Encoder3_Init(void);
#endif
#if __ENCODER4
	void Encoder4_Init(void);
#endif
#if __ENCODER5
	void Encoder5_Init(void);
#endif
#if __ENCODER8
	void Encoder8_Init(void);
#endif

s16 M_T_Speed_measure(u16 Line_num,u16 X_KHz);
s16 Motor_Time_measure(void);
#endif
