#ifndef  __DMA_USART_H
#define  __DMA_USART_H

#include "sys.h"

//cndtr:��������
//cpar:�����ַ
//cmar:�洢��ַ
void DMA1_Channel3_Init(u16 cndtr,u32 cpar,u32 cmar);
//cndtr:��������
//cpar:�����ַ
//cmar:�洢��ַ
void DMA1_Channel6_Init(u16 cndtr,u32 cpar,u32 cmar);
//cndtr:��������
//cpar:�����ַ
//cmar:�洢��ַ
void DMA1_Channel5_Init(u16 cndtr,u32 cpar,u32 cmar);//����1 dam���ݴ���  ͨ��5

void Update_Posi(u8 *psign);
void Update_Acce(void);
void Update_Angle(void);
void Update_WAng(void);
#endif



