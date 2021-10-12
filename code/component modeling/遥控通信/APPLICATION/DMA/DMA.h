#ifndef  __DMA_H
#define  __DMA_H

#include "sys.h"

#if __DMA_USART2

void DMA_Config_USART2(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr,u8 rank);

#endif

#if __DMA_USART3

void DMA_Config_USART3(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr,u8 rank);

#endif

//#if __DMA_ADC1

void DMA_Config_ADC1(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr,u8 rank);
void Power_Monitor(void);
//#endif


#endif

