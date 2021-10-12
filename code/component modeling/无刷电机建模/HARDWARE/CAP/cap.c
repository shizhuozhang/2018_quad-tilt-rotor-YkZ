#include "H_define.h"


#if __TIM1_CAP
	void TIM1_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��  
		RCC->APB2ENR|=1<<2;		//IO�˿�A��ʱ��ʹ��
		GPIOA->CRH&=0XFFFF0000;	//PA8,PA9,PA10,PA11
		GPIOA->CRH|=0X00008888;	//���ù������ 
		
		TIM1->ARR=arr;  		//�趨�������Զ���װֵ   
		TIM1->PSC=psc;  		//Ԥ��Ƶ�� 

		TIM1->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
		TIM1->CCMR1|=0<<2; 	//IC1PS=00 	���������Ƶ,����Ƶ 
		TIM1->CCMR1|=1<<4; 		//IC1F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM1->CCMR1|=1<<8;		//CC2S=01 	ѡ������� IC2ӳ�䵽TI2��
		TIM1->CCMR1|=0<<10; 	//IC2PS=00 	���������Ƶ,����Ƶ 
		TIM1->CCMR1|=1<<12; 	//IC2F=0001 ���������˲��� ��Fck_int������2���¼�����Ч

		TIM1->CCMR2|=1<<0;		//CC3S=01 	ѡ������� IC3ӳ�䵽TI3��
		TIM1->CCMR2|=0<<2; 	    //IC3PS=00 	���������Ƶ,����Ƶ 
		TIM1->CCMR2|=1<<4; 		//IC3F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM1->CCMR2|=1<<8;		//CC4S=01 	ѡ������� IC4ӳ�䵽TI4��
		TIM1->CCMR2|=0<<10; 	//IC4PS=00 	���������Ƶ,����Ƶ 
		TIM1->CCMR2|=1<<12; 	//IC4F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM1->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����
		TIM1->CCER|=0<<1; 		//CC1P=0	�����ز���
		TIM1->CCER|=1<<4; 		//CC2E=1 	�������������ֵ������Ĵ�����
		TIM1->CCER|=0<<5; 		//CC2P=0	�����ز���
		TIM1->CCER|=1<<8; 		//CC3E=1 	�������������ֵ������Ĵ�����
		TIM1->CCER|=0<<9; 		//CC3P=0	�����ز���
		TIM1->CCER|=1<<12; 		//CC4E=1 	�������������ֵ������Ĵ�����
		TIM1->CCER|=0<<13; 		//CC4P=0	�����ز���
		
		TIM1->DIER|=0xf<<1;   	//�������ж�				
		TIM1->DIER|=1<<0;   	//��������ж�	
		TIM1->CR1|=0x01;    	//ʹ�ܶ�ʱ��5
		MY_NVIC_Init(2,0,TIM1_UP_IRQn,2);//��ռ2�������ȼ�0����2	   
	}
	void TIM1_UP_IRQHandler(void)
	{ 		    	     	    					   
		 
	}
#endif
#if __TIM2_CAP
	void TIM2_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB1ENR|=1<<0; 	//TIM2ʱ��ʹ��  
		RCC->APB2ENR|=1<<2;		//IO�˿�A��ʱ��ʹ��
		RCC->APB2ENR|=1<<3;		//IO�˿�B��ʱ��ʹ��	
		RCC->APB2ENR|=1<<0;		//AFIO�˿ڸ���ʱ��ʹ��
		
		JTAG_Set(SWD_ENABLE);	//�ر�jtag
		AFIO->MAPR|=3<<8;		//��TIM2������ӳ��
		//ע���ʱ����ӳ���д���SWD������PB3(CH2)����ret����
		//������������䷴��������ֻ��CH2���ã����³�������
		
		GPIOA->CRH&=0X0FFFFFFF;	//PA15,ע���ϵ縴λ�󣬸ý�Ĭ��ΪJTAG���ţ�Ҫ����JTAGģʽ
		GPIOA->CRH|=0X80000000;	//���ù������ 
		GPIOB->CRL&=0XFFFF0FFF;	//PB3��ע���ϵ縴λ�󣬸ý�Ĭ��ΪJTAG���ţ�Ҫ����JTAGģʽ
		GPIOB->CRL|=0X00008000;	//���ù������ 	
		GPIOB->CRH&=0XFFFF00FF;	//PB10,PB11
		GPIOB->CRH|=0X00008800;	//���ù������ 
		
		TIM2->ARR=arr;  		//�趨�������Զ���װֵ   
		TIM2->PSC=psc;  		//Ԥ��Ƶ�� 

		TIM2->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
		TIM2->CCMR1|=0<<2; 	//IC1PS=00 	���������Ƶ,����Ƶ 
		TIM2->CCMR1|=1<<4; 		//IC1F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM2->CCMR1|=1<<8;		//CC2S=01 	ѡ������� IC2ӳ�䵽TI2��
		TIM2->CCMR1|=0<<10; 	//IC2PS=00 	���������Ƶ,����Ƶ 
		TIM2->CCMR1|=1<<12; 	//IC2F=0001 ���������˲��� ��Fck_int������2���¼�����Ч

		TIM2->CCMR2|=1<<0;		//CC3S=01 	ѡ������� IC3ӳ�䵽TI3��
		TIM2->CCMR2|=0<<2; 	    //IC3PS=00 	���������Ƶ,����Ƶ 
		TIM2->CCMR2|=1<<4; 		//IC3F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM2->CCMR2|=1<<8;		//CC4S=01 	ѡ������� IC4ӳ�䵽TI4��
		TIM2->CCMR2|=0<<10; 	//IC4PS=00 	���������Ƶ,����Ƶ 
		TIM2->CCMR2|=1<<12; 	//IC4F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM2->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����
		TIM2->CCER|=0<<1; 		//CC1P=0	�����ز���
		TIM2->CCER|=1<<4; 		//CC2E=1 	�������������ֵ������Ĵ�����
		TIM2->CCER|=0<<5; 		//CC2P=0	�����ز���
		TIM2->CCER|=1<<8; 		//CC3E=1 	�������������ֵ������Ĵ�����
		TIM2->CCER|=0<<9; 		//CC3P=0	�����ز���
		TIM2->CCER|=1<<12; 		//CC4E=1 	�������������ֵ������Ĵ�����
		TIM2->CCER|=0<<13; 		//CC4P=0	�����ز���
		
		TIM2->DIER|=0xf<<1;   	//�������ж�				
		TIM2->DIER|=1<<0;   	//��������ж�	
		TIM2->CR1|=0x01;    	//ʹ�ܶ�ʱ��5
		MY_NVIC_Init(2,0,TIM2_IRQn,2);//��ռ2�������ȼ�0����2	   
	}
	void TIM2_IRQHandler(void)
	{ 		    	     	    					   
		 
	}
#endif
#if __TIM3_CAP
	void TIM3_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB1ENR|=1<<1;   	//TIM3 ʱ��ʹ�� 
		RCC->APB2ENR|=1<<2;    	//ʹ��PORTAʱ��  
		RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��  
		
		GPIOA->CRL&=0X00FFFFFF;	//PA6,7 ���֮ǰ����  
		GPIOA->CRL|=0X88000000;	//PA6,7 ����   
		GPIOB->CRL&=0XFFFFFF00;	//PB0,1 ���֮ǰ����  
		GPIOB->CRL|=0X00000088;	//PB0,1 ����
		
		TIM3->ARR=arr;  		//�趨�������Զ���װֵ   
		TIM3->PSC=psc;  		//Ԥ��Ƶ�� 

		TIM3->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
		TIM3->CCMR1|=0<<2; 	//IC1PS=00 	���������Ƶ,����Ƶ 
		TIM3->CCMR1|=1<<4; 		//IC1F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM3->CCMR1|=1<<8;		//CC2S=01 	ѡ������� IC2ӳ�䵽TI2��
		TIM3->CCMR1|=0<<10; 	//IC2PS=00 	���������Ƶ,����Ƶ 
		TIM3->CCMR1|=1<<12; 	//IC2F=0001 ���������˲��� ��Fck_int������2���¼�����Ч

		TIM3->CCMR2|=1<<0;		//CC3S=01 	ѡ������� IC3ӳ�䵽TI3��
		TIM3->CCMR2|=0<<2; 	    //IC3PS=00 	���������Ƶ,����Ƶ 
		TIM3->CCMR2|=1<<4; 		//IC3F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM3->CCMR2|=1<<8;		//CC4S=01 	ѡ������� IC4ӳ�䵽TI4��
		TIM3->CCMR2|=0<<10; 	//IC4PS=00 	���������Ƶ,����Ƶ 
		TIM3->CCMR2|=1<<12; 	//IC4F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM3->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����
		TIM3->CCER|=0<<1; 		//CC1P=0	�����ز���
		TIM3->CCER|=1<<4; 		//CC2E=1 	�������������ֵ������Ĵ�����
		TIM3->CCER|=0<<5; 		//CC2P=0	�����ز���
		TIM3->CCER|=1<<8; 		//CC3E=1 	�������������ֵ������Ĵ�����
		TIM3->CCER|=0<<9; 		//CC3P=0	�����ز���
		TIM3->CCER|=1<<12; 		//CC4E=1 	�������������ֵ������Ĵ�����
		TIM3->CCER|=0<<13; 		//CC4P=0	�����ز���
		
		TIM3->DIER|=0xf<<1;   	//�������ж�				
		TIM3->DIER|=1<<0;   	//��������ж�	
		TIM3->CR1|=0x01;    	//ʹ�ܶ�ʱ��5
		MY_NVIC_Init(2,0,TIM3_IRQn,2);//��ռ2�������ȼ�0����2	   
	}
	void TIM3_IRQHandler(void)
	{ 		    	     	    					   
		 
	}		
#endif
#if __TIM4_CAP
	void TIM4_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB1ENR|=1<<2;   	//TIM4 ʱ��ʹ�� 
		RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��  
		
		GPIOB->CRL&=0X00FFFFFF;	//PB6,7 ���֮ǰ����  
		GPIOB->CRL|=0X88000000;	//PB6,7 ����   
		GPIOB->CRH&=0XFFFFFF00;	//PB8,9 ���֮ǰ����  
		GPIOB->CRH|=0X00000088;	//PB8,9 ����
		
		TIM4->ARR=arr;  		//�趨�������Զ���װֵ   
		TIM4->PSC=psc;  		//Ԥ��Ƶ�� 

		TIM4->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
		TIM4->CCMR1|=0<<2; 	//IC1PS=00 	���������Ƶ,����Ƶ 
		TIM4->CCMR1|=1<<4; 		//IC1F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
//		TIM4->CCMR1|=1<<8;		//CC2S=01 	ѡ������� IC2ӳ�䵽TI2��
//		TIM4->CCMR1|=0<<10; 	//IC2PS=00 	���������Ƶ,����Ƶ 
//		TIM4->CCMR1|=1<<12; 	//IC2F=0001 ���������˲��� ��Fck_int������2���¼�����Ч

//		TIM4->CCMR2|=1<<0;		//CC3S=01 	ѡ������� IC3ӳ�䵽TI3��
//		TIM4->CCMR2|=0<<2; 	    //IC3PS=00 	���������Ƶ,����Ƶ 
//		TIM4->CCMR2|=1<<4; 		//IC3F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
//		
//		TIM4->CCMR2|=1<<8;		//CC4S=01 	ѡ������� IC4ӳ�䵽TI4��
//		TIM4->CCMR2|=0<<10; 	//IC4PS=00 	���������Ƶ,����Ƶ 
//		TIM4->CCMR2|=1<<12; 	//IC4F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM4->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����
		TIM4->CCER|=0<<1; 		//CC1P=0	�����ز���
//		TIM4->CCER|=1<<4; 		//CC2E=1 	�������������ֵ������Ĵ�����
//		TIM4->CCER|=0<<5; 		//CC2P=0	�����ز���
//		TIM4->CCER|=1<<8; 		//CC3E=1 	�������������ֵ������Ĵ�����
//		TIM4->CCER|=0<<9; 		//CC3P=0	�����ز���
//		TIM4->CCER|=1<<12; 		//CC4E=1 	�������������ֵ������Ĵ�����
//		TIM4->CCER|=0<<13; 		//CC4P=0	�����ز���
		
		TIM4->DIER|=0xf<<1;   	//�������ж�				
		TIM4->DIER|=0<<0;   	//��������ж�	
		TIM4->CR1|=0x01;    	//ʹ�ܶ�ʱ��5
		MY_NVIC_Init(0,0,TIM4_IRQn,2);//��ռ2�������ȼ�0����2	   
	}
	
	    				
	u16	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ
//	u16 TIM4CH1_CNT=0;			//����ֵ
	u16 Freq=0;//Ƶ��ֵ

	void TIM4_IRQHandler(void)
	{ 		    
		u16 tsr;
		tsr=TIM4->SR;
		
//		if(tsr&0X01)//���
//		{	    							
//			Freq=0;	 
//		}
		if(tsr&0x02)//����1���������¼�
		{					  			
			TIM4CH1_CAPTURE_VAL=TIM4->CCR1;	//��ȡ��ǰ�Ĳ���ֵ.
			TIM4->CNT=0; 
			TIM4->CCR1=0; 
		}	
		
		Freq=(u16)(100000/TIM4CH1_CAPTURE_VAL);//����Ƶ����100KHz

		
		TIM4->SR=0;//����жϱ�־λ 	    
	}		 		
#endif
#if __TIM5_CAP
	void TIM5_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB1ENR|=1<<3;   	//TIM5 ʱ��ʹ�� 
		RCC->APB2ENR|=1<<2;    	//ʹ��PORTAʱ��  
		 
		GPIOA->CRL&=0XFFFF0000;	//PA0,1,2,3 ���֮ǰ����  
		GPIOA->CRL|=0X00008888;	//PA0,1,2,3 ����   
		  
		TIM5->ARR=arr;  		//�趨�������Զ���װֵ   
		TIM5->PSC=psc;  		//Ԥ��Ƶ�� 

		TIM5->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
		TIM5->CCMR1|=0<<2; 	//IC1PS=00 	���������Ƶ,����Ƶ 
		TIM5->CCMR1|=1<<4; 		//IC1F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM5->CCMR1|=1<<8;		//CC2S=01 	ѡ������� IC2ӳ�䵽TI2��
		TIM5->CCMR1|=0<<10; 	//IC2PS=00 	���������Ƶ,����Ƶ 
		TIM5->CCMR1|=1<<12; 	//IC2F=0001 ���������˲��� ��Fck_int������2���¼�����Ч

		TIM5->CCMR2|=1<<0;		//CC3S=01 	ѡ������� IC3ӳ�䵽TI3��
		TIM5->CCMR2|=0<<2; 	    //IC3PS=00 	���������Ƶ,����Ƶ 
		TIM5->CCMR2|=1<<4; 		//IC3F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM5->CCMR2|=1<<8;		//CC4S=01 	ѡ������� IC4ӳ�䵽TI4��
		TIM5->CCMR2|=0<<10; 	//IC4PS=00 	���������Ƶ,����Ƶ 
		TIM5->CCMR2|=1<<12; 	//IC4F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM5->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����
		TIM5->CCER|=0<<1; 		//CC1P=0	�����ز���
		TIM5->CCER|=1<<4; 		//CC2E=1 	�������������ֵ������Ĵ�����
		TIM5->CCER|=0<<5; 		//CC2P=0	�����ز���
		TIM5->CCER|=1<<8; 		//CC3E=1 	�������������ֵ������Ĵ�����
		TIM5->CCER|=0<<9; 		//CC3P=0	�����ز���
		TIM5->CCER|=1<<12; 		//CC4E=1 	�������������ֵ������Ĵ�����
		TIM5->CCER|=0<<13; 		//CC4P=0	�����ز���
		
		TIM5->DIER|=0xf<<1;   	//�������ж�				
		TIM5->DIER|=1<<0;   	//��������ж�	
		TIM5->CR1|=0x01;    	//ʹ�ܶ�ʱ��5
		MY_NVIC_Init(2,0,TIM5_IRQn,2);//��ռ2�������ȼ�0����2	   
	}

	//����״̬
	//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
	//[6]:0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.
	//[5:0]:����ߵ�ƽ������Ĵ���
	u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
	u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ
	u16 TIM5CH1_CNT=0;			//����ֵ
	u8  TIM5CH2_CAPTURE_STA=0;	//���벶��״̬		    				
	u16	TIM5CH2_CAPTURE_VAL;	//���벶��ֵ
	u16 TIM5CH2_CNT=0;			//����ֵ
	u8  TIM5CH3_CAPTURE_STA=0;	//���벶��״̬		    				
	u16	TIM5CH3_CAPTURE_VAL;	//���벶��ֵ
	u16 TIM5CH3_CNT=0;			//����ֵ
	u8  TIM5CH4_CAPTURE_STA=0;	//���벶��״̬		    				
	u16	TIM5CH4_CAPTURE_VAL;	//���벶��ֵ
	u16 TIM5CH4_CNT=0;			//����ֵ
	//��ʱ��5�жϷ������
	//ע�⣺TIM5CH1_CAPTURE_STA���ж���û�����㣬���ⲿ���㣬
	//TIM5CH1_CAPTURE_STA�ڲ���ɹ������㣬������δ�ɹ����㣬���ݴ���
	//�ο�����
	//	u32 temp1=0;
	//	if(TIM5CH1_CAPTURE_STA&0x80)
	//	{
	//		temp1=(TIM5CH1_CAPTURE_STA&0x3f)*65535+TIM5CH1_CAPTURE_VAL-TIM5CH1_CNT;
	//		printf("%d,%d,%d,%d\r\n",TIM5CH1_CAPTURE_STA&0x3f,TIM5CH1_CNT,TIM5CH1_CAPTURE_VAL,temp1);
	//		TIM5CH1_CAPTURE_STA=0;
	//	}
	void TIM5_IRQHandler(void)
	{ 		    
		u16 tsr;
		tsr=TIM5->SR;
		if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
		{
			if(tsr&0X01)//���
			{	    
				if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
				{
					if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
					{
						TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
						TIM5CH1_CAPTURE_VAL=0XFFFF;
					}else TIM5CH1_CAPTURE_STA++;
				}	 
			}
			if(tsr&0x02)//����1���������¼�
			{	
				if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
				{	  			
					TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
					TIM5CH1_CAPTURE_VAL=TIM5->CCR1;	//��ȡ��ǰ�Ĳ���ֵ.
					TIM5->CCER&=~(1<<1);			//CC1P=0 ����Ϊ�����ز���
				}else  								//��δ��ʼ,��һ�β���������
				{ 
					TIM5CH1_CAPTURE_VAL=0;
					TIM5CH1_CAPTURE_STA=0X40;		//��ǲ�����������
					TIM5CH1_CNT=TIM5->CNT;			//����������
					TIM5->CCER|=1<<1; 				//CC1P=1 ����Ϊ�½��ز��� 
				}		    
			}			     	    					   
		}
		if((TIM5CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
		{
			if(tsr&0X01)//���
			{	    
				if(TIM5CH2_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
				{
					if((TIM5CH2_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
					{
						TIM5CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
						TIM5CH2_CAPTURE_VAL=0XFFFF;
					}else TIM5CH2_CAPTURE_STA++;
				}	 
			}
			if(tsr&0x04)//����2���������¼�
			{	
				if(TIM5CH2_CAPTURE_STA&0X40)		//����һ���½��� 		
				{	  			
					TIM5CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
					TIM5CH2_CAPTURE_VAL=TIM5->CCR2;	//��ȡ��ǰ�Ĳ���ֵ.
					TIM5->CCER&=~(1<<5);			//CC2P=0 ����Ϊ�����ز���
				}else  								//��δ��ʼ,��һ�β���������
				{ 
					TIM5CH2_CAPTURE_VAL=0;
					TIM5CH2_CAPTURE_STA=0X40;		//��ǲ�����������
					TIM5CH2_CNT=TIM5->CNT;			//����������
					TIM5->CCER|=1<<5; 				//CC2P=1 ����Ϊ�½��ز��� 
				}		    
			}			     	    					   
		}
		if((TIM5CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
		{
			if(tsr&0X01)//���
			{	    
				if(TIM5CH3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
				{
					if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
					{
						TIM5CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
						TIM5CH2_CAPTURE_VAL=0XFFFF;
					}else TIM5CH3_CAPTURE_STA++;
				}	 
			}
			if(tsr&0x08)//����3���������¼�
			{	
				if(TIM5CH3_CAPTURE_STA&0X40)		//����һ���½��� 		
				{	  			
					TIM5CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
					TIM5CH3_CAPTURE_VAL=TIM5->CCR3;	//��ȡ��ǰ�Ĳ���ֵ.
					TIM5->CCER&=~(1<<9);			//CC3P=0 ����Ϊ�����ز���
				}else  								//��δ��ʼ,��һ�β���������
				{ 
					TIM5CH3_CAPTURE_VAL=0;
					TIM5CH3_CAPTURE_STA=0X40;		//��ǲ�����������
					TIM5CH3_CNT=TIM5->CNT;			//����������
					TIM5->CCER|=1<<9; 				//CC3P=1 ����Ϊ�½��ز��� 
				}		    
			}			     	    					   
		}
		if((TIM5CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
		{
			if(tsr&0X01)//���
			{	    
				if(TIM5CH4_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
				{
					if((TIM5CH4_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
					{
						TIM5CH4_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
						TIM5CH4_CAPTURE_VAL=0XFFFF;
					}else TIM5CH4_CAPTURE_STA++;
				}	 
			}
			if(tsr&0x10)//����1���������¼�
			{	
				if(TIM5CH4_CAPTURE_STA&0X40)		//����һ���½��� 		
				{	  			
					TIM5CH4_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
					TIM5CH4_CAPTURE_VAL=TIM5->CCR4;	//��ȡ��ǰ�Ĳ���ֵ.
					TIM5->CCER&=~(1<<13);			//CC4P=0 ����Ϊ�����ز���
				}else  								//��δ��ʼ,��һ�β���������
				{ 
					TIM5CH4_CAPTURE_VAL=0;
					TIM5CH4_CAPTURE_STA=0X40;		//��ǲ�����������
					TIM5CH3_CNT=TIM5->CNT;			//����������
					TIM5->CCER|=1<<13; 				//CC4P=1 ����Ϊ�½��ز��� 
				}		    
			}			     	    					   
		}
		TIM5->SR=0;//����жϱ�־λ 	    
	}		
#endif
#if __TIM8_CAP
	void TIM8_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB2ENR|=1<<13; 	//TIM8ʱ��ʹ�� 
		RCC->APB2ENR|=1<<4;		////IO�˿�C��ʱ��ʹ��
		GPIOC->CRL&=0X00FFFFFF;	//PC6,PC7
		GPIOC->CRL|=0X88000000;	//���ù������ 	
		GPIOC->CRH&=0XFFFFFF00;	//PC8,PC9
		GPIOC->CRH|=0X00000088;	//���ù������ 
		
		TIM8->ARR=arr;  		//�趨�������Զ���װֵ   
		TIM8->PSC=psc;  		//Ԥ��Ƶ�� 

		TIM8->CCMR1|=1<<0;		//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
		TIM8->CCMR1|=0<<2; 	//IC1PS=00 	���������Ƶ,����Ƶ 
		TIM8->CCMR1|=1<<4; 		//IC1F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM8->CCMR1|=1<<8;		//CC2S=01 	ѡ������� IC2ӳ�䵽TI2��
		TIM8->CCMR1|=0<<10; 	//IC2PS=00 	���������Ƶ,����Ƶ 
		TIM8->CCMR1|=1<<12; 	//IC2F=0001 ���������˲��� ��Fck_int������2���¼�����Ч

		TIM8->CCMR2|=1<<0;		//CC3S=01 	ѡ������� IC3ӳ�䵽TI3��
		TIM8->CCMR2|=0<<2; 	    //IC3PS=00 	���������Ƶ,����Ƶ 
		TIM8->CCMR2|=1<<4; 		//IC3F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM8->CCMR2|=1<<8;		//CC4S=01 	ѡ������� IC4ӳ�䵽TI4��
		TIM8->CCMR2|=0<<10; 	//IC4PS=00 	���������Ƶ,����Ƶ 
		TIM8->CCMR2|=1<<12; 	//IC4F=0001 ���������˲��� ��Fck_int������2���¼�����Ч
		
		TIM8->CCER|=1<<0; 		//CC1E=1 	�������������ֵ������Ĵ�����
		TIM8->CCER|=0<<1; 		//CC1P=0	�����ز���
		TIM8->CCER|=1<<4; 		//CC2E=1 	�������������ֵ������Ĵ�����
		TIM8->CCER|=0<<5; 		//CC2P=0	�����ز���
		TIM8->CCER|=1<<8; 		//CC3E=1 	�������������ֵ������Ĵ�����
		TIM8->CCER|=0<<9; 		//CC3P=0	�����ز���
		TIM8->CCER|=1<<12; 		//CC4E=1 	�������������ֵ������Ĵ�����
		TIM8->CCER|=0<<13; 		//CC4P=0	�����ز���
		
		TIM8->DIER|=0xf<<1;   	//�������ж�				
		TIM8->DIER|=1<<0;   	//��������ж�	
		TIM8->CR1|=0x01;    	//ʹ�ܶ�ʱ��5
		MY_NVIC_Init(2,0,TIM8_UP_IRQn,2);//��ռ2�������ȼ�0����2	   
	}
	void TIM8_UP_IRQHandler(void)
	{ 		    	     	    					   
		 
	}
#endif













