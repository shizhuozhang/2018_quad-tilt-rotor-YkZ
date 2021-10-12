#include "H_define.h"


#if __USART
//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
#if ___USART_PRINTF
	int fputc(int ch, FILE *f)
	{      
		#if ___USART_PRINTF == 1
			while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
			USART1->DR = (u8) ch;      	
		#elif ___USART_PRINTF == 2
			while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
			USART2->DR = (u8) ch;      
		#elif ___USART_PRINTF == 3
			while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
			USART3->DR = (u8) ch;      
		#endif
		return ch;
	}
#endif

#endif 
//////////////////////////////////////////////////////////////////

////////////����1/////////////
#if __USART1

	//��ʼ��IO ����1
	//pclk2:PCLK2ʱ��Ƶ��(Mhz)
	//bound:������
	//CHECK OK
	//091209
	void usart1(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������	 
		mantissa<<=4;
		mantissa+=fraction; 
		RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
		RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
		GPIOA->CRH&=0XFFFFF00F;//IO״̬����
		GPIOA->CRH|=0X000008B0;//IO״̬����
			  
		RCC->APB2RSTR|=1<<14;   //��λ����1
		RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
		//����������
		USART1->BRR=mantissa; // ����������	 
		USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
//		USART1->CR3|=1<<6;    //����DMA
////		//ʹ�ܽ����ж�
////		USART1->CR1|=1<<8;    //PE�ж�ʹ��
////		USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
////		MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
	}


#endif
/////////////////////////////

////////////����2/////////////
#if __USART2

	//��ʼ��IO ����1
	//pclk2:PCLK2ʱ��Ƶ��(Mhz)
	//bound:������
	//CHECK OK
	//091209
	void usart2(u32 pclk1,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk1*1000000)/(bound*16);//�õ�USARTDIV
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������	 
		mantissa<<=4;
		mantissa+=fraction; 
		
		RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
		RCC->APB1ENR|=1<<17;  //ʹ�ܴ���ʱ�� 
		GPIOA->CRL&=0XFFFF00FF;//IO״̬����
		GPIOA->CRL|=0X00008B00;//IO״̬���� 
		RCC->APB1RSTR|=1<<17;   //��λ����1
		RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ
		//����������
		USART2->BRR=mantissa; // ����������	 
		USART2->CR1|=0X200C;  //1λֹͣ,��У��λ.
		USART2->CR3|=1<<6;	//dmaʹ�ܽ���

		//ʹ�ܽ����ж�
		USART2->CR1|=1<<8;    //PE�ж�ʹ��
		USART2->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
		MY_NVIC_Init(3,3,USART2_IRQn,2);//��2��������ȼ� 
	}
u8 Usart2_flag1=0;
u8 Usart2_flag2=0;
	void USART2_IRQHandler(void)
	{
		if(USART2->SR&(1<<5))//���յ�����
		{	 
			USART2->SR&=~(1<<5);
			
			if(0X55==USART2->DR)
				Usart2_flag1=1;
			
			else if((0X51==USART2->DR)&&Usart2_flag1)
				Usart2_flag2=1;
			else
				Usart2_flag1=0;
			
			if(Usart2_flag2&&Dma1_C6_Close)
			{
				Dma1_C6_Close=0;
				Usart2_flag2=0;
				DMA1_Channel6->CCR|=1<<0;			//ͨ������
			}
		}

	} 
#endif
/////////////////////////////

////////////����3/////////////
#if __USART3

	//��ʼ��IO ����1
	//pclk2:PCLK2ʱ��Ƶ��(Mhz)
	//bound:������
	//CHECK OK
	//091209
	void usart3(u32 pclk1,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk1*1000000)/(bound*16);//�õ�USARTDIV
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������	 
		mantissa<<=4;
		mantissa+=fraction; 
		RCC->APB2ENR|=1<<3;   //ʹ��PORTB��ʱ��  
		RCC->APB1ENR|=1<<18;  //ʹ�ܴ���ʱ�� 
		GPIOB->CRH&=0XFFFF00FF;//IO״̬����
		GPIOB->CRH|=0X00008B00;//IO״̬���� 
		RCC->APB1RSTR|=1<<18;   //��λ����1
		RCC->APB1RSTR&=~(1<<18);//ֹͣ��λ	   	   
		//����������
		USART3->BRR=mantissa; // ����������	 
		USART3->CR1|=0X200C;  //1λֹͣ,��У��λ.
		USART3->CR3|=1<<6;	//dmaʹ�ܽ���
		//ʹ�ܽ����ж�
		USART3->CR1|=1<<8;    //PE�ж�ʹ��
		USART3->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
		MY_NVIC_Init(3,2,USART3_IRQn,2);//��2��������ȼ� 
	}

u8 count=1;
	void USART3_IRQHandler(void)
	{
		if(USART3->SR&(1<<5))//���յ�����
		{	
			USART3->SR=0;		
			D_K60[count++]=USART3->DR;
			if(count==3) count=1;
			
		}
	} 
#endif
/////////////////////////////

#endif	
	
