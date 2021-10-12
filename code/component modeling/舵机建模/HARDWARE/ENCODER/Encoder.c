#include "H_define.h"

#if __ENCODER1

void Encoder1_Init(void)					////TIM8用于编码器模式
{
	RCC->APB2ENR|=1<<11; 	//TIM1时钟使能  
	RCC->APB2ENR|=1<<2;		//IO端口A的时钟使能                                                                  	
    GPIOA->CRH&=0xffffff00;
    GPIOA->CRH|=0x00000044;
	TIM1->ARR=0xffff;		//自动重装载值
	TIM1->CNT=32760;		//初值
	TIM1->SMCR|=3<<0;//编码器模式3
	TIM1->CCMR1|=1<<0;//输入通道映射
	TIM1->CCMR1|=1<<8;//输入通道映射
	TIM1->CR1|=1<<0;//使能计数器
} 
		
#endif  

#if __ENCODER2
void Encoder2_Init(void)					////TIM2用于编码器模式
{
	RCC->APB1ENR|=1<<0;//tim2 enable
	RCC->APB2ENR|=1<<2;//GPIOA enable
	RCC->APB2ENR|=1<<3;//GPIOB enable
	RCC->APB2ENR|=1<<0;		//AFIO端口复用时钟使能
    GPIOA->CRH&=0x0fffffff;
    GPIOA->CRH|=0x40000000;
	GPIOB->CRL&=0xffff0fff;
    GPIOB->CRL|=0x00004000;
	JTAG_Set(SWD_ENABLE);	//关闭jtag
	AFIO->MAPR|=3<<8;		//将TIM2部分重映射
	//注意此时的重映射中带有SWD的引脚PB3(CH2)，按ret下载
	TIM2->ARR=0xffff;
	TIM2->CNT=32760;
	TIM2->SMCR|=3<<0;//编码器模式3
	TIM2->CCMR1|=1<<0;//输入通道映射
	TIM2->CCMR1|=1<<8;//输入通道映射
	TIM2->CR1|=1<<0;//使能计数器
}
#endif

#if __ENCODER3
void Encoder3_Init(void)					////TIM3用于编码器模式
{
	RCC->APB1ENR|=1<<1;//tim3 enable
	RCC->APB2ENR|=1<<2;//GPIOA enable
    GPIOA->CRL&=0x00ffffff;
    GPIOA->CRL|=0x44000000;
	TIM3->ARR=0xffff;
	TIM3->CNT=32760;
	TIM3->SMCR|=3<<0;//编码器模式3
	TIM3->CCMR1|=1<<0;//输入通道映射
	TIM3->CCMR1|=1<<8;//输入通道映射
	TIM3->CR1|=1<<0;//使能计数器
}	
#endif

#if __ENCODER4
void Encoder4_Init(void)					////TIM4用于编码器模式
{
	RCC->APB1ENR|=1<<2;//tim4 enable
	RCC->APB2ENR|=1<<3;//GPIOB enable
    GPIOB->CRL&=0x00ffffff;
    GPIOB->CRL|=0x44000000;
	TIM4->ARR=0xffff;
	TIM4->CNT=32760;
	TIM4->SMCR|=3<<0;//编码器模式3
	TIM4->CCMR1|=1<<0;//输入通道映射
	TIM4->CCMR1|=1<<8;//输入通道映射
	TIM4->CR1|=1<<0;//使能计数器
}	
#endif

#if __ENCODER5
void Encoder5_Init(void)					////TIM5用于编码器模式
{
	RCC->APB1ENR|=1<<3;//tim5 enable
	RCC->APB2ENR|=1<<2;//GPIOA enable
    GPIOA->CRL&=0xffffff00;
    GPIOA->CRL|=0x00000044;
	TIM5->ARR=0xffff;
	TIM5->CNT=32760;
	TIM5->SMCR|=3<<0;//编码器模式3
	TIM5->CCMR1|=1<<0;//输入通道映射
	TIM5->CCMR1|=1<<8;//输入通道映射
	TIM5->CR1|=1<<0;//使能计数器
}	
#endif


#if __ENCODER8

void Encoder8_Init(void)					////TIM8用于编码器模式
{
	RCC->APB2ENR|=1<<13;//tim8 enable
	RCC->APB2ENR|=1<<4;//GPIOC enable
    GPIOC->CRL&=0x00ffffff;
    GPIOC->CRL|=0x44000000;
	TIM8->ARR=0xffff;
	TIM8->CNT=32760;
	TIM8->SMCR|=3<<0;//编码器模式3
	TIM8->CCMR1|=1<<0;//输入通道映射
	TIM8->CCMR1|=1<<8;//输入通道映射
	TIM8->CR1|=1<<0;//使能计数器
}

#endif




//int encoder=0;
//u16 control_num=0;
//u16 encoder_num=0;

////定时器7中断服务函数
//void TIM7_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //溢出中断
//	{  
//        encoder_num+=1;
//        control_num+=1; 
//        
//        if((encoder_num>=50)&&(display_flag==0))//10Hz的读取频率100ms
//        {
//            encoder_num=0;
//            encoder=(int)(32760-TIM8->CNT);//速度有正负之分，表示正反转         
//            TIM8->CNT=32760;				//重新赋中值
//            
//            LED1=!LED1;
//            display_flag=1;
//        }
//        
//		if(control_num>=5)//控制频率100Hz
//		{ 
//            control_num=0;
//            control_flag=1;	//标志位置1，用于主函数里控制函数运行          
//		}		
//	}
//	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //清除中断标志位
//}		

/*
入口参数
Line_num 编码器分辨率，即线数
X_KHz 定时器频率
用在定时器中断中
注意修改编码器所使用的定时器TIMx->CNT
*/
//s16 M_T_Speed_measure(u16 Line_num,u16 X_KHz)//   	M/T测速算法
//{
//	static u8 Tc=100;   //固定时长
//	static u8 t1=0 ;	//第一个脉冲前时长
//    static u8 t2=0;	//最后一个脉冲前时长	   
//	static u8 T=0;	//最终时长,
//	static u16 cntL=0;	//编码器过去值
//	static s16 Z=0;		//最终脉冲个数
//	
//	if(cntL==TIM4->CNT)
//	{
//		if(Tc==100)
//		{
//			t2++;					//最后一个脉冲前时长计数	
//			if(t2>50)				//超时处理
//			{
//				T=Tc-t1+t2-1;
//				Z=cntL-32760;			//编码器重装值是100
//				Tc=0;
//				t1=0;
//				t2=0;
//				TIM4->CNT=32760;		//编码器重装值是100
//				cntL=TIM4->CNT;
//			}
//		}
//		else
//		{
//			t1++;					//第一个脉冲前时长计数	
//		}
//	}
//	else
//	{
//		if(Tc==100)					//一次计时结束
//		{
//			T=Tc-t1+t2;
//			Z=cntL-32760;
//			Tc=0;
//			t1=0;
//			t2=0;
//			TIM4->CNT=32760;
//			cntL=TIM4->CNT;
//		}
//	}
//	if(Tc<100)		//固定时长计数
//	{
//		Tc++;
//		if(Tc==100)
//		{
//			cntL=TIM4->CNT;
//		}
//	}
//	return (s16)(60*1000*X_KHz*Z/4/Line_num/(float)T);//算出的速度单位是r/min
//			/*			      60*Z*（定时器频率f）
//			//最终速度为     --------------------   （r/min）
//							 （4*编码器分辨率）*T
//			*/
//}

/*测试直流电机的机电时间常数的两种数字方法，
注意修改编码器所使用的定时器TIMx->CNT
*/
	/*方法1是使用1KHz的定时中断采样速度，然后画出速度时间曲线，
	0.632倍的最大速度对应的时间即为机电时间常数*/
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
	/*方法2
	使用时，中断定时频率是10HZ,测速所用编码器线数至少要300线
	这种计算电机机电时间常数的算法是通过测量电机在响应阶跃输入
	的第一个100MS内脉冲个数和第二100MS内的脉冲个数间接推算的*/
//	      s16 Z1=0;//外部全局变量
//	      s16 Z2=0;	//外部全局变量
//中断函数中内容
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

			
	/*			        Z1(第一个100ms)
	//最终速度为 T -  --------------------  (单位是s)，
					  10*Z2（第二个100ms）
	  
	由于电机的机电时间常数一般在10ms左右，故测量的时间选取10倍（远大于）即0.1S
	使用该封装的函数时，中断定时频率必须是1KHZ，才能保证T=0.1S	
			*/













