#include "H_define.h"

#if __USART
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	   
//REFER TO:����ԭ��@ALIENTEK
//������̳:www.openedv.com
////////////////////////////////////////////////////////////////////////////////// 	

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
		#elif ___USART_PRINTF == 4
			while((UART4->SR&0X40)==0);//ѭ������,ֱ���������   
			UART4->DR = (u8) ch;
		#elif ___USART_PRINTF == 5
			while((UART5->SR&0X40)==0);//ѭ������,ֱ���������   
			UART5->DR = (u8) ch;      
		#elif ___USART_PRINTF == 6
			while((USART6->SR&0X40)==0);//ѭ������,ֱ���������   
			USART6->DR = (u8) ch;      
		#endif
		return ch;
	}
#endif
	
#endif 
//end
//////////////////////////////////////////////////////////////////
/**����1��ʼ������*/
#if __USART1	
	//pclk2:PCLK2ʱ��Ƶ��(Mhz)
	//bound:������ 
	void Usart1_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV@OVER8=0
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������@OVER8=0 
		mantissa<<=4;//�޷��Ŷ������ͣ�����λ��С������
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<0;   	//ʹ��PORTA��ʱ��  
		RCC->APB2ENR|=1<<4;  	//ʹ�ܴ���1ʱ�� 
		GPIO_Set(GPIOA,PIN9|PIN10,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,���ù���,�������
		GPIO_AF_Set(GPIOA,9,7);	//PA9,AF7
		GPIO_AF_Set(GPIOA,10,7);//PA10,AF7  	   
		
		RCC->APB2RSTR|=1<<4;   //��λ����1
		RCC->APB2RSTR&=~(1<<4);//ֹͣ��λ	   
		//����������
		USART1->BRR=mantissa; 	//����������	 
		USART1->CR1&=~(1<<15); 	//����OVER8=0 //��֤��ߵ��ݴ���
		USART1->CR1|=1<<3;  	//���ڷ���ʹ�� 
	//	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//Ĭ��1��ʼλ��8����λ��1ֹͣλ,����żУ��
	
		#if __DMA_USART1 
		USART1->CR3|=1<<6;    //DMA	����
		#endif
	
		//ʹ�ܽ����ж� 
		USART1->CR1|=1<<2;  	//���ڽ���ʹ��
		USART1->CR1|=1<<5;    	//���ջ������ǿ��ж�ʹ��	    	
		MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
		
		USART1->CR1|=1<<13;  	//����ʹ��
	}

	//����1�жϷ������
	//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	  
	void USART1_IRQHandler(void)
	{
		u8 res;	
		
	#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntEnter();    
	#endif
		
		if(USART1->SR&(1<<5))//���յ�����
		{	 		
			res=USART1->DR; //DR�Ĵ�����һ��˫�Ĵ����������ݵ�ʱ���ȡ����RDR
					//д���ݵ�ʱ��д����TDR,����TDR��RDR���ⲻ�ɼ�������DR�Ĵ���
			USART1->DR=res*2;	//	���յ���������2������				     
		} 
							//�������ݸñ�־λ�Զ����㣬
	//	USART1->SR&=~(1<<5);//û��Ҫ�����д����ֶ������־λ
		
	#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntExit();  											 
	#endif
	} 
#endif

/**����2��ʼ������*/
#if __USART2	
	//pclk2:PCLK2ʱ��Ƶ��(Mhz)
	//bound:������ 
	void Usart2_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV@OVER8=0
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������@OVER8=0 
		mantissa<<=4;//�޷��Ŷ������ͣ�����λ��С������
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<0;   	//ʹ��PORTA��ʱ��  
		RCC->APB1ENR|=1<<17;  	//ʹ�ܴ���2ʱ�� 
		GPIO_Set(GPIOA,PIN2|PIN3,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA2,PA3,���ù���,�������
		GPIO_AF_Set(GPIOA,2,7);	//PA9,AF7
		GPIO_AF_Set(GPIOA,3,7);//PA10,AF7  	   
		
		RCC->APB1RSTR|=1<<17;   //��λ����2
		RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ	   
		//����������
		USART2->BRR=mantissa; 	//����������	 
		USART2->CR1&=~(1<<15); 	//����OVER8=0 //��֤��ߵ��ݴ���
		USART2->CR1|=1<<3;  	//���ڷ���ʹ�� 
	//	USART2->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//Ĭ��1��ʼλ��8����λ��1ֹͣλ,����żУ��
	
		#if __DMA_USART2 
		USART2->CR3|=1<<6;    //DMA	����
		#endif
		
		//ʹ�ܽ����ж� 
		USART2->CR1|=1<<2;  	//���ڽ���ʹ��
		USART2->CR1|=1<<5;    	//���ջ������ǿ��ж�ʹ��	    	
		MY_NVIC_Init(2,2,USART2_IRQn,2);//��2��������ȼ� 
		
		USART2->CR1|=1<<13;  	//����ʹ��
	}

	u8 Ahrs_Flag1=1;
	//����1�жϷ������
	//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	  
	void USART2_IRQHandler(void)
	{
		static u8 Judge_Flag1=0;
		static u8 Judge_Flag2=0;
		
	#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntEnter();    
	#endif
		
		if(USART2->SR&(1<<5))//���յ�����
		{	 		
			if(Ahrs_Flag1)//ÿ�����ݵ�֡ͷУ��
			{
				if(0XA5==USART2->DR)
					Judge_Flag1=1;
				else if((0X5A==USART2->DR) && Judge_Flag1)
				{
					Judge_Flag2=1;
					USART2->CR3|=1<<6;    //DMA	����
				}
				else
					Judge_Flag1=0;
				
				if((0X12==USART2->DR) && Dma1_T5_Close && Judge_Flag2 )//
				{
					Dma1_T5_Close=0;
					Judge_Flag2=0;
					while(DMA1_Stream5->CR&0X1);	//ȷ��DMA���Ա�����  
					DMA1_Stream5->CR|=1<<0;		//����DMA����
					Ahrs_Flag1=0;//֡ͷУ����Ϻ��������ݵĽ���ʹ��DMA�������ڴ˴�����
				}		
			}	
			
		} 						//�������ݸñ�־λ�Զ����㣬
		USART2->SR&=~(1<<5);//û��Ҫ�����д����ֶ������־λ
		
	#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
/**����3��ʼ������*/
#if __USART3	
	//pclk2:PCLK2ʱ��Ƶ��(Mhz)
	//bound:������ 
	void Usart3_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV@OVER8=0
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������@OVER8=0 
		mantissa<<=4;//�޷��Ŷ������ͣ�����λ��С������
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<1;   	//ʹ��PORTB��ʱ��  
		RCC->APB1ENR|=1<<18;  	//ʹ�ܴ���3ʱ�� 
		GPIO_Set(GPIOB,PIN10|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,���ù���,�������
		GPIO_AF_Set(GPIOB,10,7);	//PB10,AF7
		GPIO_AF_Set(GPIOB,11,7);//PB11,AF7  	   
		
		RCC->APB1RSTR|=1<<18;   //��λ����1
		RCC->APB1RSTR&=~(1<<18);//ֹͣ��λ	   
		//����������
		USART3->BRR=mantissa; 	//����������
		
		USART3->CR1=0;
		USART3->CR2=0;
		USART3->CR3=0;
		
		USART3->CR1&=~(1<<15); 	//����OVER8=0 //��֤��ߵ��ݴ���
		
//		USART3->CR1|=1<<3;  	//���ڷ���ʹ��		
//		USART3->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//Ĭ��1��ʼλ��8����λ��1ֹͣλ,����żУ��
	
		USART3->CR1|=0<<9;  	
		USART3->CR1|=1<<10;  	//����żУ��
		USART3->CR2|=2<<12;  	//2λֹͣλ
		
		#if __DMA_USART1 
		USART3->CR3|=1<<6;    //DMA	����
		#endif
		
		//ʹ�ܽ����ж� 
		USART3->CR1|=1<<2;  	//���ڽ���ʹ��
		USART3->CR1|=1<<5;    	//���ջ������ǿ��ж�ʹ��	    	
		MY_NVIC_Init(3,3,USART3_IRQn,2);//��2��������ȼ� 
		
		USART3->CR1|=1<<13;  	//����ʹ��
	}

	//����3�жϷ������
	//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	  
	void USART3_IRQHandler(void)
	{
//		u8 res=0;
	#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntEnter();    
	#endif
		
		if(USART3->SR&(1<<5))//���յ�����
		{
//	 		res=USART3->DR;
//			USART1->DR=res;			
			USART3->CR3|=1<<6;    //DMA	����
			if(0X0F==USART3->DR&&1==Dma1_T1_Close)//
			{
				Dma1_T1_Close=0;				
				while(DMA1_Stream1->CR&0X1);	//ȷ��DMA���Ա�����  
				DMA1_Stream1->CR|=1<<0;		//����DMA����
			}				     
		} 
							//�������ݸñ�־λ�Զ����㣬
		USART3->SR&=~(1<<5);//û��Ҫ�����д����ֶ������־λ
		
	#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
/**����4��ʼ������*/
#if __UART4	
	//pclk2:PCLK2ʱ��Ƶ��(Mhz)
	//bound:������ 
	void Uart4_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV@OVER8=0
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������@OVER8=0 
		mantissa<<=4;//�޷��Ŷ������ͣ�����λ��С������
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<0;   	//ʹ��PORTA��ʱ��  
		RCC->APB1ENR|=1<<19;  	//ʹ�ܴ���1ʱ�� 
		GPIO_Set(GPIOA,PIN0|PIN1,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,���ù���,�������
		GPIO_AF_Set(GPIOA,0,8);	//PA9,AF7
		GPIO_AF_Set(GPIOA,1,8);//PA10,AF7  	   
		
		RCC->APB1RSTR|=1<<19;   //��λ����1
		RCC->APB1RSTR&=~(1<<19);//ֹͣ��λ	   
		//����������
		UART4->BRR=mantissa; 	//����������	 
		UART4->CR1&=~(1<<15); 	//����OVER8=0 //��֤��ߵ��ݴ���
		UART4->CR1|=1<<3;  	//���ڷ���ʹ�� 
	//	UART4->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//Ĭ��1��ʼλ��8����λ��1ֹͣλ,����żУ��

		#if __DMA_USART1 
		UART4->CR3|=1<<6;    //DMA	����
		#endif
		//ʹ�ܽ����ж� 
		UART4->CR1|=1<<2;  	//���ڽ���ʹ��
		UART4->CR1|=1<<5;    	//���ջ������ǿ��ж�ʹ��	    	
		MY_NVIC_Init(3,3,UART4_IRQn,2);//��2��������ȼ� 
		
		UART4->CR1|=1<<13;  	//����ʹ��
	}

	//����1�жϷ������
	//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	  
	void UART4_IRQHandler(void)
	{
		u8 res;	
		
	#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntEnter();    
	#endif
		
		if(UART4->SR&(1<<5))//���յ�����
		{	 		
			res=UART4->DR; //DR�Ĵ�����һ��˫�Ĵ����������ݵ�ʱ���ȡ����RDR
					//д���ݵ�ʱ��д����TDR,����TDR��RDR���ⲻ�ɼ�������DR�Ĵ���
			UART4->DR=res*2;	//	���յ���������2������				     
		} 
							//�������ݸñ�־λ�Զ����㣬
	//	UART4->SR&=~(1<<5);//û��Ҫ�����д����ֶ������־λ
		
	#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
/**����5��ʼ������*/
#if __UART5	
	//pclk2:PCLK2ʱ��Ƶ��(Mhz)
	//bound:������ 
	void Uart5_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV@OVER8=0
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������@OVER8=0 
		mantissa<<=4;//�޷��Ŷ������ͣ�����λ��С������
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<2;   	//ʹ��PORTC��ʱ�� 
		RCC->AHB1ENR|=1<<3;   	//ʹ��PORTD��ʱ��		
		RCC->APB1ENR|=1<<20;  	//ʹ�ܴ���5ʱ�� 
		GPIO_Set(GPIOC,PIN12,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,���ù���,�������
		GPIO_Set(GPIOD,PIN2,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,���ù���,�������
		GPIO_AF_Set(GPIOC,12,8);	//PC12,AF8
		GPIO_AF_Set(GPIOD,2,8);//PD2,AF8  	   
		
		RCC->APB1RSTR|=1<<20;   //��λ����1
		RCC->APB1RSTR&=~(1<<20);//ֹͣ��λ	   
		//����������
		UART5->BRR=mantissa; 	//����������	 
		UART5->CR1&=~(1<<15); 	//����OVER8=0 //��֤��ߵ��ݴ���
		UART5->CR1|=1<<3;  	//���ڷ���ʹ�� 
	//	USART5->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//Ĭ��1��ʼλ��8����λ��1ֹͣλ,����żУ��

		#if __DMA_USART1 
		UART5->CR3|=1<<6;    //DMA	����
		#endif
		//ʹ�ܽ����ж� 
		UART5->CR1|=1<<2;  	//���ڽ���ʹ��
		UART5->CR1|=1<<5;    	//���ջ������ǿ��ж�ʹ��	    	
		MY_NVIC_Init(3,3,UART5_IRQn,2);//��2��������ȼ� 
		
		UART5->CR1|=1<<13;  	//����ʹ��
	}

	//����1�жϷ������
	//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	  
	void UART5_IRQHandler(void)
	{
		u8 res;	
		
	#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntEnter();    
	#endif
		
		if(UART5->SR&(1<<5))//���յ�����
		{	 		
			res=UART5->DR; //DR�Ĵ�����һ��˫�Ĵ����������ݵ�ʱ���ȡ����RDR
					//д���ݵ�ʱ��д����TDR,����TDR��RDR���ⲻ�ɼ�������DR�Ĵ���
			UART5->DR=res*2;	//	���յ���������2������				     
		} 
							//�������ݸñ�־λ�Զ����㣬
	//	UART5->SR&=~(1<<5);//û��Ҫ�����д����ֶ������־λ
		
	#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
/**����6��ʼ������*////δ��֤��Ӧ��û����
#if __USART6	
	//pclk2:PCLK2ʱ��Ƶ��(Mhz)
	//bound:������ 
	void Usart6_init(u32 pclk2,u32 bound)
	{  	 
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV@OVER8=0
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������@OVER8=0 
		mantissa<<=4;//�޷��Ŷ������ͣ�����λ��С������
		mantissa+=fraction; 
		RCC->AHB1ENR|=1<<2;   	//ʹ��PORTC��ʱ��
		RCC->APB2ENR|=1<<5;  	//ʹ�ܴ���1ʱ�� 
		GPIO_Set(GPIOC,PIN6|PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,���ù���,�������
		GPIO_AF_Set(GPIOC,6,8);	//PA9,AF7
		GPIO_AF_Set(GPIOC,7,8);//PA10,AF7  	   
		
		RCC->APB2RSTR|=1<<5;   //��λ����1
		RCC->APB2RSTR&=~(1<<5);//ֹͣ��λ	   
		//����������
		USART6->BRR=mantissa; 	//����������	 
		USART6->CR1&=~(1<<15); 	//����OVER8=0 //��֤��ߵ��ݴ���
		USART6->CR1|=1<<3;  	//���ڷ���ʹ�� 
	//	USART6->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//Ĭ��1��ʼλ��8����λ��1ֹͣλ,����żУ��

		#if __DMA_USART1 
		USART6->CR3|=1<<6;    //DMA	����
		#endif
		//ʹ�ܽ����ж� 
		USART6->CR1|=1<<2;  	//���ڽ���ʹ��
		USART6->CR1|=1<<5;    	//���ջ������ǿ��ж�ʹ��	    	
		MY_NVIC_Init(3,3,USART6_IRQn,2);//��2��������ȼ� 
		
		USART6->CR1|=1<<13;  	//����ʹ��
	}

	//����1�жϷ������
	//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	  
	void USART6_IRQHandler(void)
	{
		u8 res;	
		
	#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntEnter();    
	#endif
		
		if(USART6->SR&(1<<5))//���յ�����
		{	 		
			res=USART6->DR; //DR�Ĵ�����һ��˫�Ĵ����������ݵ�ʱ���ȡ����RDR
					//д���ݵ�ʱ��д����TDR,����TDR��RDR���ⲻ�ɼ�������DR�Ĵ���
			USART6->DR=res*2;	//	���յ���������2������				     
		} 
							//�������ݸñ�־λ�Զ����㣬
	//	USART6->SR&=~(1<<5);//û��Ҫ�����д����ֶ������־λ
		
	#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
		OSIntExit();  											 
	#endif
	} 
#endif
	
	


#endif
	
	
	
	
	