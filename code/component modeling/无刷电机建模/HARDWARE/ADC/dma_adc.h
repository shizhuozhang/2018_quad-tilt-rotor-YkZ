#ifndef __DMA_H
#define __DMA_H
#include"sys.h"

#if __DMA_ADC1
void DMA1_Init(u16 cndtr,u32 cpar,u32 cmar);
#endif

#if __DMA_ADC3
void DMA2_Init(u16 cndtr,u32 cpar,u32 cmar);
#endif

#endif
