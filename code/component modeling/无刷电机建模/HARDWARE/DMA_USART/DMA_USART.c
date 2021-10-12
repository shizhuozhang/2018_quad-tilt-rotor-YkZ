#include "H_define.h"


u8 SBUS_DATA[25];
//u8 D_K60[10];

//cndtr:��������
//cpar:�����ַ
//cmar:�洢��ַ
void DMA1_Channel3_Init(u16 cndtr,u32 cpar,u32 cmar)  //usart3
{
	RCC->AHBENR|=1<<0;			//����DMA1ʱ��
	delay_ms(5);				//�ȴ�DMAʱ���ȶ�
	DMA1_Channel3->CPAR=cpar; 	 	//DMA1 �����ַ 
	DMA1_Channel3->CMAR=cmar; 	//DMA1,�洢����ַ
	DMA1_Channel3->CNDTR=cndtr;    	//DMA1,����������
	DMA1_Channel3->CCR=0X00000000;	//��λ
	DMA1_Channel3->CCR|=0<<4;  		//�������
	DMA1_Channel3->CCR|=1<<5;  		//ѭ��ģʽ
	DMA1_Channel3->CCR|=0<<6; 		//�����ַ������ģʽ
	DMA1_Channel3->CCR|=1<<7; 	 	//�洢������ģʽ
	DMA1_Channel3->CCR|=0<<8; 	 	//�������ݿ��Ϊ8λ
	DMA1_Channel3->CCR|=0<<10; 		//�洢�����ݿ��8λ
	DMA1_Channel3->CCR|=1<<12; 		//�е����ȼ�
	DMA1_Channel3->CCR|=0<<14; 		//�Ǵ洢�����洢��ģʽ
	DMA1_Channel3->CCR|=1<<1;			//����TC�ж�
	DMA1_Channel3->CCR|=1<<0;			//ͨ������
	MY_NVIC_Init(0,0,DMA1_Channel3_IRQn,2);
}
////cndtr:��������
////cpar:�����ַ
////cmar:�洢��ַ
//void DMA1_Channel5_Init(u16 cndtr,u32 cpar,u32 cmar)//����1 dam���ݴ���  ͨ��5
//{
//	RCC->AHBENR|=1<<0;			//����DMA1ʱ��
//	delay_ms(5);				//�ȴ�DMAʱ���ȶ�
//	DMA1_Channel5->CPAR=cpar; 	 	//DMA1 �����ַ 
//	DMA1_Channel5->CMAR=cmar; 	//DMA1,�洢����ַ
//	DMA1_Channel5->CNDTR=cndtr;    	//DMA1,����������
//	DMA1_Channel5->CCR=0X00000000;	//��λ
//	DMA1_Channel5->CCR|=0<<4;  		//�������
//	DMA1_Channel5->CCR|=1<<5;  		//��ͨģʽ
//	DMA1_Channel5->CCR|=0<<6; 		//�����ַ������ģʽ
//	DMA1_Channel5->CCR|=1<<7; 	 	//�洢������ģʽ
//	DMA1_Channel5->CCR|=0<<8; 	 	//�������ݿ��Ϊ8λ
//	DMA1_Channel5->CCR|=0<<10; 		//�洢�����ݿ��8λ
//	DMA1_Channel5->CCR|=1<<12; 		//�е����ȼ�
//	DMA1_Channel5->CCR|=0<<14; 		//�Ǵ洢�����洢��ģʽ
//	DMA1_Channel5->CCR|=1<<1;			//����TC�ж�
//	DMA1_Channel5->CCR|=1<<0;			//ͨ������
//	MY_NVIC_Init(1,3,DMA1_Channel5_IRQn,2);
//}

//cndtr:��������
//cpar:�����ַ
//cmar:�洢��ַ
void DMA1_Channel6_Init(u16 cndtr,u32 cpar,u32 cmar)   //usart2
{
	RCC->AHBENR|=1<<0;			//����DMA1ʱ��
	delay_ms(5);				//�ȴ�DMAʱ���ȶ�
	DMA1_Channel6->CPAR=cpar; 	 	//DMA1 �����ַ 
	DMA1_Channel6->CMAR=cmar; 	//DMA1,�洢����ַ
	DMA1_Channel6->CNDTR=cndtr;    	//DMA1,����������
	DMA1_Channel6->CCR=0X00000000;	//��λ
	DMA1_Channel6->CCR|=0<<4;  		//�������
	DMA1_Channel6->CCR|=1<<5;  		//��ͨģʽ
	DMA1_Channel6->CCR|=0<<6; 		//�����ַ������ģʽ
	DMA1_Channel6->CCR|=1<<7; 	 	//�洢������ģʽ
	DMA1_Channel6->CCR|=0<<8; 	 	//�������ݿ��Ϊ8λ
	DMA1_Channel6->CCR|=0<<10; 		//�洢�����ݿ��8λ
	DMA1_Channel6->CCR|=1<<12; 		//�е����ȼ�
	DMA1_Channel6->CCR|=0<<14; 		//�Ǵ洢�����洢��ģʽ
	DMA1_Channel6->CCR|=1<<1;			//����TC�ж�
	DMA1_Channel6->CCR|=1<<0;			//ͨ������
	MY_NVIC_Init(1,3,DMA1_Channel6_IRQn,2);
}

u8 sign_usrt3=0;
u8 Dma1_C3_Close=1;
void  DMA1_Channel3_IRQHandler()//dma1�ж�  usart3
{
	if(DMA1->ISR&(1<<9))//�������
	{
		DMA1->IFCR|=1<<8;//�����־λ
		if((0X0F!=SBUS_DATA[0])||(0!=SBUS_DATA[24]))//
		{
			DMA1_Channel3->CCR&=~(1<<0);			//ͨ���ر�
			Dma1_C3_Close=1;
		}else
		{
			SBUS_data_Pro();
			sign_usrt3=1;
		}
	}
	
}

//void DMA1_Channel5_IRQHandler()
//{
//	if(DMA1->ISR&1<<17)//ͨ��5�������
//	{
//		DMA1->ISR|=1<<16;
//		
//	}
//	
//}



//u8 sign_usrt2=0;
//u8 Dma1_C6_Close=0;
void  DMA1_Channel6_IRQHandler()//dma1�ж�
{
	if(DMA1->ISR&(1<<21))//�������
	{
		DMA1->IFCR|=1<<21;//�����־λ
//		if(0X55!=D_6050[0])
//		{
//			DMA1_Channel6->CCR&=~(1<<0);			//ͨ������
//			Dma1_C6_Close=1;
//		}else
//		{
//			sign_usrt2=1;
//		}
	}
	
}









