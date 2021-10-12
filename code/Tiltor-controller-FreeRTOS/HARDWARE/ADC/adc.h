#ifndef __ADC_H
#define __ADC_H

#include "sys.h"


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
