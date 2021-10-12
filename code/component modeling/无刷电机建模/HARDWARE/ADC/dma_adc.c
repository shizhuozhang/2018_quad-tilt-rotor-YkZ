#include "H_define.h"


#if __DMA_ADC1
//cndtr:��������
//cpar:�����ַ
//cmar:�洢��ַ
void DMA1_Init(u16 cndtr,u32 cpar,u32 cmar)
{
	
	RCC->AHBENR|=1<<0;
	DMA1_Channel1->CNDTR=cndtr;	//���ݴ�������
	DMA1_Channel1->CPAR=cpar;	//�����ַ
	DMA1_Channel1->CMAR=cmar;	//�洢����ַ
	DMA1_Channel1->CCR=0;
	DMA1_Channel1->CCR&=~(1<<14);//�Ǵ�������������ģʽ
	DMA1_Channel1->CCR&=~(3<<14);
	DMA1_Channel1->CCR|=3<<12;//ͨ�����ȼ����
	DMA1_Channel1->CCR&=~(3<<10);
	DMA1_Channel1->CCR|=2<<10;//�洢�����ݿ��16
	DMA1_Channel1->CCR&=~(3<<8);
	DMA1_Channel1->CCR|=2<<8;//�������ݿ��16
	DMA1_Channel1->CCR|=2<<6;//�洢����ַ�����������ַ������
	DMA1_Channel1->CCR|=1<<5;//ѭ��ģʽ
	DMA1_Channel1->CCR&=~(1<<4);//�������
	DMA1_Channel1->CCR&=~(7<<1);
//	DMA1_Channel1->CCR|=1<<1;//tc������TE��HT�ر�
	DMA1_Channel1->CCR|=1<<0;//ͨ������
	MY_NVIC_Init(0,0,DMA1_Channel1_IRQn,2);
}
#endif




#if __DMA_ADC3
//cndtr:��������
//cpar:�����ַ
//cmar:�洢��ַ
void DMA2_Init(u16 cndtr,u32 cpar,u32 cmar)
{
	
	RCC->AHBENR|=1<<1;//DMA2ʹ��
	
	DMA2_Channel5->CNDTR=cndtr;	//���ݴ�������
	DMA2_Channel5->CPAR=cpar;	//�����ַ
	DMA2_Channel5->CMAR=cmar;	//�洢����ַ
	DMA2_Channel5->CCR=0;
	DMA2_Channel5->CCR&=~(1<<14);//�Ǵ�������������ģʽ
	DMA2_Channel5->CCR&=~(3<<14);
	DMA2_Channel5->CCR|=3<<12;//ͨ�����ȼ����
	DMA2_Channel5->CCR&=~(3<<10);
	DMA2_Channel5->CCR|=1<<10;//�洢�����ݿ��16
	DMA2_Channel5->CCR&=~(3<<8);
	DMA2_Channel5->CCR|=1<<8;//�������ݿ��16
	DMA2_Channel5->CCR|=2<<6;//�洢����ַ�����������ַ������
	DMA2_Channel5->CCR|=1<<5;//ѭ��ģʽ
	DMA2_Channel5->CCR&=~(1<<4);//�������
	DMA2_Channel5->CCR&=~(7<<1);
//	DMA2_Channel5->CCR|=1<<1;//tc������TE��HT�ر�
	DMA2_Channel5->CCR|=1<<0;//ͨ������
}
#endif

//extern u16 ADC[16];
//extern u16 adc[6];
//void  DMA1_Channel1_IRQHandler()//dma1�ж�
//{
//	u8 i;
//	if(DMA1->ISR&(1<<1))//�������
//	{
//		for(i=0;i<6;i++)	
//			ADC[i+4]=adc[i]&0xffff;
//		for(i=0;i<6;i++)	
//			ADC[i+10]=(adc[i]&0xffff0000)>>16;
//	}
//	DMA1->IFCR|=1<<1;//�����־λ
//}
