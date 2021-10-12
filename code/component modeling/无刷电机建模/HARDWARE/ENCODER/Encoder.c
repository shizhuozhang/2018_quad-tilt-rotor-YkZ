#include "H_define.h"

#if __ENCODER1

void Encoder1_Init(void)					////TIM1���ڱ�����ģʽ
{
	RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��  
	RCC->APB2ENR|=1<<2;		//IO�˿�A��ʱ��ʹ��                                                                  	
    GPIOA->CRH&=0xffffff00;
    GPIOA->CRH|=0x00000044;
	TIM1->ARR=0xffff;		//�Զ���װ��ֵ
	TIM1->CNT=32760;		//��ֵ
	TIM1->SMCR|=3<<0;//������ģʽ3
	TIM1->CCMR1|=1<<0;//����ͨ��ӳ��
	TIM1->CCMR1|=1<<8;//����ͨ��ӳ��
	TIM1->CR1|=1<<0;//ʹ�ܼ�����
} 
		
#endif  

#if __ENCODER2
void Encoder2_Init(void)					////TIM2���ڱ�����ģʽ
{
	RCC->APB1ENR|=1<<0;//tim2 enable
	RCC->APB2ENR|=1<<2;//GPIOA enable
	RCC->APB2ENR|=1<<3;//GPIOB enable
	RCC->APB2ENR|=1<<0;		//AFIO�˿ڸ���ʱ��ʹ��
    GPIOA->CRH&=0x0fffffff;
    GPIOA->CRH|=0x40000000;
	GPIOB->CRL&=0xffff0fff;
    GPIOB->CRL|=0x00004000;
	JTAG_Set(SWD_ENABLE);	//�ر�jtag
	AFIO->MAPR|=3<<8;		//��TIM2������ӳ��
	//ע���ʱ����ӳ���д���SWD������PB3(CH2)����ret����
	TIM2->ARR=0xffff;
	TIM2->CNT=32760;
	TIM2->SMCR|=3<<0;//������ģʽ3
	TIM2->CCMR1|=1<<0;//����ͨ��ӳ��
	TIM2->CCMR1|=1<<8;//����ͨ��ӳ��
	TIM2->CR1|=1<<0;//ʹ�ܼ�����
}
#endif

#if __ENCODER3
void Encoder3_Init(void)					////TIM3���ڱ�����ģʽ
{
	RCC->APB1ENR|=1<<1;//tim3 enable
	RCC->APB2ENR|=1<<2;//GPIOA enable
    GPIOA->CRL&=0x00ffffff;
    GPIOA->CRL|=0x44000000;
	TIM3->ARR=0xffff;
	TIM3->CNT=32760;
	TIM3->SMCR|=3<<0;//������ģʽ3
	TIM3->CCMR1|=1<<0;//����ͨ��ӳ��
	TIM3->CCMR1|=1<<8;//����ͨ��ӳ��
	TIM3->CR1|=1<<0;//ʹ�ܼ�����
}	
#endif

#if __ENCODER4
void Encoder4_Init(void)					////TIM4���ڱ�����ģʽ
{
	RCC->APB1ENR|=1<<2;//tim4 enable
	RCC->APB2ENR|=1<<3;//GPIOB enable
    GPIOB->CRL&=0x00ffffff;
    GPIOB->CRL|=0x44000000;
	TIM4->ARR=0xffff;
	TIM4->CNT=32760;
	TIM4->SMCR|=3<<0;//������ģʽ3
	TIM4->CCMR1|=1<<0;//����ͨ��ӳ��
	TIM4->CCMR1|=1<<8;//����ͨ��ӳ��
	TIM4->CR1|=1<<0;//ʹ�ܼ�����
}	
#endif

#if __ENCODER5
void Encoder5_Init(void)					////TIM5���ڱ�����ģʽ
{
	RCC->APB1ENR|=1<<3;//tim5 enable
	RCC->APB2ENR|=1<<2;//GPIOA enable
    GPIOA->CRL&=0xffffff00;
    GPIOA->CRL|=0x00000044;
	TIM5->ARR=0xffff;
	TIM5->CNT=32760;
	TIM5->SMCR|=3<<0;//������ģʽ3
	TIM5->CCMR1|=1<<0;//����ͨ��ӳ��
	TIM5->CCMR1|=1<<8;//����ͨ��ӳ��
	TIM5->CR1|=1<<0;//ʹ�ܼ�����
}	
#endif


#if __ENCODER8

void Encoder8_Init(void)					////TIM8���ڱ�����ģʽ
{
	RCC->APB2ENR|=1<<13;//tim8 enable
	RCC->APB2ENR|=1<<4;//GPIOC enable
    GPIOC->CRL&=0x00ffffff;
    GPIOC->CRL|=0x44000000;
	TIM8->ARR=0xffff;
	TIM8->CNT=32760;
	TIM8->SMCR|=3<<0;//������ģʽ3
	TIM8->CCMR1|=1<<0;//����ͨ��ӳ��
	TIM8->CCMR1|=1<<8;//����ͨ��ӳ��
	TIM8->CR1|=1<<0;//ʹ�ܼ�����
}

#endif


/*
��ڲ���
Line_num �������ֱ��ʣ�������
X_KHz ��ʱ��Ƶ��
���ڶ�ʱ���ж���
ע���޸ı�������ʹ�õĶ�ʱ��TIMx->CNT
*/
s16 M_T_Speed_measure(u16 Line_num,u16 X_KHz)//   	M/T�����㷨
{
	static u8 Tc=100;   //�̶�ʱ��
	static u8 t1=0 ;	//��һ������ǰʱ��
    static u8 t2=0;	//���һ������ǰʱ��	   
	static u8 T=0;	//����ʱ��,
	static u16 cntL=0;	//��������ȥֵ
	static s16 Z=0;		//�����������
	
	if(cntL==TIM4->CNT)
	{
		if(Tc==100)
		{
			t2++;					//���һ������ǰʱ������	
			if(t2>50)				//��ʱ����
			{
				T=Tc-t1+t2-1;
				Z=cntL-32760;			//��������װֵ��100
				Tc=0;
				t1=0;
				t2=0;
				TIM4->CNT=32760;		//��������װֵ��100
				cntL=TIM4->CNT;
			}
		}
		else
		{
			t1++;					//��һ������ǰʱ������	
		}
	}
	else
	{
		if(Tc==100)					//һ�μ�ʱ����
		{
			T=Tc-t1+t2;
			Z=cntL-32760;
			Tc=0;
			t1=0;
			t2=0;
			TIM4->CNT=32760;
			cntL=TIM4->CNT;
		}
	}
	if(Tc<100)		//�̶�ʱ������
	{
		Tc++;
		if(Tc==100)
		{
			cntL=TIM4->CNT;
		}
	}
	return (s16)(60*1000*X_KHz*Z/4/Line_num/(float)T);//������ٶȵ�λ��r/min
			/*			      60*Z*����ʱ��Ƶ��f��
			//�����ٶ�Ϊ     --------------------   ��r/min��
							 ��4*�������ֱ��ʣ�*T
			*/
}

/*����ֱ������Ļ���ʱ�䳣�����������ַ�����
ע���޸ı�������ʹ�õĶ�ʱ��TIMx->CNT
*/
	/*����1��ʹ��1KHz�Ķ�ʱ�жϲ����ٶȣ�Ȼ�󻭳��ٶ�ʱ�����ߣ�
	0.632��������ٶȶ�Ӧ��ʱ�伴Ϊ����ʱ�䳣��*/
////			if(Count_num>3000)
////			{
////				Count_num=0;
////				LED0=~LED0;
////				IO_PC4=1;
////				y=1;
////			}
////			
////			if(y==1)
////			{
////				if(i<800)
////				{
////					i++;
////					Speed_data[i]=TIM4->CNT-32760;
////					TIM4->CNT=32760;
////				}
////				else Print_Flag=1;
////			
////			}
	/*����2
	ʹ��ʱ���ж϶�ʱƵ����10HZ,�������ñ�������������Ҫ300��
	���ּ���������ʱ�䳣�����㷨��ͨ�������������Ӧ��Ծ����
	�ĵ�һ��100MS����������͵ڶ�100MS�ڵ����������������*/
//	      s16 Z1=0;//�ⲿȫ�ֱ���
//	      s16 Z2=0;	//�ⲿȫ�ֱ���
//�жϺ���������
//	static u8 x=2,y=0;
//		if(TIM7->SR&0x0001)
//		{
//			if(y==1)
//			{
//				if(x==1)
//				{
//					Z2=TIM4->CNT-32760;
//					TIM4->CNT=32760;
//					x--;
//					Print_Flag=1;
//				}	
//				else if(x==2)
//				{
//					Z1=TIM4->CNT-32760;
//					TIM4->CNT=32760;
//					x--;
//				}
//				else if(x==0)
//					x=0;
//									
//			}
//			Count_num++;
//			if(Count_num>30)
//			{
//				Count_num=0;
//				LED0=~LED0;
//				IO_PC4=1;
//				y=1;
//			}
//			delay_ms(2);

			
	/*			        Z1(��һ��100ms)
	//�����ٶ�Ϊ T -  --------------------  (��λ��s)��
					  10*Z2���ڶ���100ms��
	  
	���ڵ���Ļ���ʱ�䳣��һ����10ms���ң��ʲ�����ʱ��ѡȡ10����Զ���ڣ���0.1S
	ʹ�ø÷�װ�ĺ���ʱ���ж϶�ʱƵ�ʱ�����1KHZ�����ܱ�֤T=0.1S	
			*/













