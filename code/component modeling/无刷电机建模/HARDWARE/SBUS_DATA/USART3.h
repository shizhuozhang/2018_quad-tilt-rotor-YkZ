#ifndef __usart3_H
#define __usart3_H

#include "sys.h"

#include "stdio.h"

void USART3_Config(u32 Baudrate);
void USART3_printf(USART_TypeDef* USARTx,u8* Data);
void DMA1_TX3Init(void);
void DMA1_RX3Init(void);
#endif


