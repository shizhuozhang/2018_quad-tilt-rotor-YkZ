#ifndef __ADC_H
#define __ADC_H

#include "sys.h"

#define CH0  0
#define CH1  1
#define CH2  2
#define CH3  3
#define CH4  4
#define CH5  5
#define CH6  6
#define CH7  7
#define CH8  8
#define CH9  9
#define CH10 10
#define CH11 11
#define CH12 12
#define CH13 13
#define CH14 14
#define CH15 15

#if __ADC1
void ADC1_Init(void);
#endif

#if __ADC2
void ADC2_Init(void);
#endif

#if __ADC3
void ADC3_Init(void);
#endif

#endif
