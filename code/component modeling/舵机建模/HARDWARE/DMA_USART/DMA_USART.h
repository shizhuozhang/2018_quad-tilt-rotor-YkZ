#ifndef  __DMA_USART_H
#define  __DMA_USART_H

#include "sys.h"

//cndtr:数据数量
//cpar:外设地址
//cmar:存储地址
void DMA1_Channel3_Init(u16 cndtr,u32 cpar,u32 cmar);
//cndtr:数据数量
//cpar:外设地址
//cmar:存储地址
void DMA1_Channel6_Init(u16 cndtr,u32 cpar,u32 cmar);
//cndtr:数据数量
//cpar:外设地址
//cmar:存储地址
void DMA1_Channel5_Init(u16 cndtr,u32 cpar,u32 cmar);//串口1 dam数据传输  通道5

void Update_Posi(u8 *psign);
void Update_Acce(void);
void Update_Angle(void);
void Update_WAng(void);
#endif



