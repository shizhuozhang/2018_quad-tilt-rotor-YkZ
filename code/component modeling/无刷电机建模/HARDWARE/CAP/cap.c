#include "H_define.h"


#if __TIM1_CAP
	void TIM1_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB2ENR|=1<<11; 	//TIM1时钟使能  
		RCC->APB2ENR|=1<<2;		//IO端口A的时钟使能
		GPIOA->CRH&=0XFFFF0000;	//PA8,PA9,PA10,PA11
		GPIOA->CRH|=0X00008888;	//复用功能输出 
		
		TIM1->ARR=arr;  		//设定计数器自动重装值   
		TIM1->PSC=psc;  		//预分频器 

		TIM1->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
		TIM1->CCMR1|=0<<2; 	//IC1PS=00 	配置输入分频,不分频 
		TIM1->CCMR1|=1<<4; 		//IC1F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM1->CCMR1|=1<<8;		//CC2S=01 	选择输入端 IC2映射到TI2上
		TIM1->CCMR1|=0<<10; 	//IC2PS=00 	配置输入分频,不分频 
		TIM1->CCMR1|=1<<12; 	//IC2F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效

		TIM1->CCMR2|=1<<0;		//CC3S=01 	选择输入端 IC3映射到TI3上
		TIM1->CCMR2|=0<<2; 	    //IC3PS=00 	配置输入分频,不分频 
		TIM1->CCMR2|=1<<4; 		//IC3F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM1->CCMR2|=1<<8;		//CC4S=01 	选择输入端 IC4映射到TI4上
		TIM1->CCMR2|=0<<10; 	//IC4PS=00 	配置输入分频,不分频 
		TIM1->CCMR2|=1<<12; 	//IC4F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM1->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中
		TIM1->CCER|=0<<1; 		//CC1P=0	上升沿捕获
		TIM1->CCER|=1<<4; 		//CC2E=1 	允许捕获计数器的值到捕获寄存器中
		TIM1->CCER|=0<<5; 		//CC2P=0	上升沿捕获
		TIM1->CCER|=1<<8; 		//CC3E=1 	允许捕获计数器的值到捕获寄存器中
		TIM1->CCER|=0<<9; 		//CC3P=0	上升沿捕获
		TIM1->CCER|=1<<12; 		//CC4E=1 	允许捕获计数器的值到捕获寄存器中
		TIM1->CCER|=0<<13; 		//CC4P=0	上升沿捕获
		
		TIM1->DIER|=0xf<<1;   	//允许捕获中断				
		TIM1->DIER|=1<<0;   	//允许更新中断	
		TIM1->CR1|=0x01;    	//使能定时器5
		MY_NVIC_Init(2,0,TIM1_UP_IRQn,2);//抢占2，子优先级0，组2	   
	}
	void TIM1_UP_IRQHandler(void)
	{ 		    	     	    					   
		 
	}
#endif
#if __TIM2_CAP
	void TIM2_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB1ENR|=1<<0; 	//TIM2时钟使能  
		RCC->APB2ENR|=1<<2;		//IO端口A的时钟使能
		RCC->APB2ENR|=1<<3;		//IO端口B的时钟使能	
		RCC->APB2ENR|=1<<0;		//AFIO端口复用时钟使能
		
		JTAG_Set(SWD_ENABLE);	//关闭jtag
		AFIO->MAPR|=3<<8;		//将TIM2部分重映射
		//注意此时的重映射中带有SWD的引脚PB3(CH2)，按ret下载
		//若将上面两语句反过来，则只有CH2可用，且下程序正常
		
		GPIOA->CRH&=0X0FFFFFFF;	//PA15,注意上电复位后，该脚默认为JTAG引脚，要禁用JTAG模式
		GPIOA->CRH|=0X80000000;	//复用功能输出 
		GPIOB->CRL&=0XFFFF0FFF;	//PB3，注意上电复位后，该脚默认为JTAG引脚，要禁用JTAG模式
		GPIOB->CRL|=0X00008000;	//复用功能输出 	
		GPIOB->CRH&=0XFFFF00FF;	//PB10,PB11
		GPIOB->CRH|=0X00008800;	//复用功能输出 
		
		TIM2->ARR=arr;  		//设定计数器自动重装值   
		TIM2->PSC=psc;  		//预分频器 

		TIM2->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
		TIM2->CCMR1|=0<<2; 	//IC1PS=00 	配置输入分频,不分频 
		TIM2->CCMR1|=1<<4; 		//IC1F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM2->CCMR1|=1<<8;		//CC2S=01 	选择输入端 IC2映射到TI2上
		TIM2->CCMR1|=0<<10; 	//IC2PS=00 	配置输入分频,不分频 
		TIM2->CCMR1|=1<<12; 	//IC2F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效

		TIM2->CCMR2|=1<<0;		//CC3S=01 	选择输入端 IC3映射到TI3上
		TIM2->CCMR2|=0<<2; 	    //IC3PS=00 	配置输入分频,不分频 
		TIM2->CCMR2|=1<<4; 		//IC3F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM2->CCMR2|=1<<8;		//CC4S=01 	选择输入端 IC4映射到TI4上
		TIM2->CCMR2|=0<<10; 	//IC4PS=00 	配置输入分频,不分频 
		TIM2->CCMR2|=1<<12; 	//IC4F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM2->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中
		TIM2->CCER|=0<<1; 		//CC1P=0	上升沿捕获
		TIM2->CCER|=1<<4; 		//CC2E=1 	允许捕获计数器的值到捕获寄存器中
		TIM2->CCER|=0<<5; 		//CC2P=0	上升沿捕获
		TIM2->CCER|=1<<8; 		//CC3E=1 	允许捕获计数器的值到捕获寄存器中
		TIM2->CCER|=0<<9; 		//CC3P=0	上升沿捕获
		TIM2->CCER|=1<<12; 		//CC4E=1 	允许捕获计数器的值到捕获寄存器中
		TIM2->CCER|=0<<13; 		//CC4P=0	上升沿捕获
		
		TIM2->DIER|=0xf<<1;   	//允许捕获中断				
		TIM2->DIER|=1<<0;   	//允许更新中断	
		TIM2->CR1|=0x01;    	//使能定时器5
		MY_NVIC_Init(2,0,TIM2_IRQn,2);//抢占2，子优先级0，组2	   
	}
	void TIM2_IRQHandler(void)
	{ 		    	     	    					   
		 
	}
#endif
#if __TIM3_CAP
	void TIM3_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB1ENR|=1<<1;   	//TIM3 时钟使能 
		RCC->APB2ENR|=1<<2;    	//使能PORTA时钟  
		RCC->APB2ENR|=1<<3;    	//使能PORTB时钟  
		
		GPIOA->CRL&=0X00FFFFFF;	//PA6,7 清除之前设置  
		GPIOA->CRL|=0X88000000;	//PA6,7 输入   
		GPIOB->CRL&=0XFFFFFF00;	//PB0,1 清除之前设置  
		GPIOB->CRL|=0X00000088;	//PB0,1 输入
		
		TIM3->ARR=arr;  		//设定计数器自动重装值   
		TIM3->PSC=psc;  		//预分频器 

		TIM3->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
		TIM3->CCMR1|=0<<2; 	//IC1PS=00 	配置输入分频,不分频 
		TIM3->CCMR1|=1<<4; 		//IC1F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM3->CCMR1|=1<<8;		//CC2S=01 	选择输入端 IC2映射到TI2上
		TIM3->CCMR1|=0<<10; 	//IC2PS=00 	配置输入分频,不分频 
		TIM3->CCMR1|=1<<12; 	//IC2F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效

		TIM3->CCMR2|=1<<0;		//CC3S=01 	选择输入端 IC3映射到TI3上
		TIM3->CCMR2|=0<<2; 	    //IC3PS=00 	配置输入分频,不分频 
		TIM3->CCMR2|=1<<4; 		//IC3F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM3->CCMR2|=1<<8;		//CC4S=01 	选择输入端 IC4映射到TI4上
		TIM3->CCMR2|=0<<10; 	//IC4PS=00 	配置输入分频,不分频 
		TIM3->CCMR2|=1<<12; 	//IC4F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM3->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中
		TIM3->CCER|=0<<1; 		//CC1P=0	上升沿捕获
		TIM3->CCER|=1<<4; 		//CC2E=1 	允许捕获计数器的值到捕获寄存器中
		TIM3->CCER|=0<<5; 		//CC2P=0	上升沿捕获
		TIM3->CCER|=1<<8; 		//CC3E=1 	允许捕获计数器的值到捕获寄存器中
		TIM3->CCER|=0<<9; 		//CC3P=0	上升沿捕获
		TIM3->CCER|=1<<12; 		//CC4E=1 	允许捕获计数器的值到捕获寄存器中
		TIM3->CCER|=0<<13; 		//CC4P=0	上升沿捕获
		
		TIM3->DIER|=0xf<<1;   	//允许捕获中断				
		TIM3->DIER|=1<<0;   	//允许更新中断	
		TIM3->CR1|=0x01;    	//使能定时器5
		MY_NVIC_Init(2,0,TIM3_IRQn,2);//抢占2，子优先级0，组2	   
	}
	void TIM3_IRQHandler(void)
	{ 		    	     	    					   
		 
	}		
#endif
#if __TIM4_CAP
	void TIM4_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB1ENR|=1<<2;   	//TIM4 时钟使能 
		RCC->APB2ENR|=1<<3;    	//使能PORTB时钟  
		
		GPIOB->CRL&=0X00FFFFFF;	//PB6,7 清除之前设置  
		GPIOB->CRL|=0X88000000;	//PB6,7 输入   
		GPIOB->CRH&=0XFFFFFF00;	//PB8,9 清除之前设置  
		GPIOB->CRH|=0X00000088;	//PB8,9 输入
		
		TIM4->ARR=arr;  		//设定计数器自动重装值   
		TIM4->PSC=psc;  		//预分频器 

		TIM4->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
		TIM4->CCMR1|=0<<2; 	//IC1PS=00 	配置输入分频,不分频 
		TIM4->CCMR1|=1<<4; 		//IC1F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
//		TIM4->CCMR1|=1<<8;		//CC2S=01 	选择输入端 IC2映射到TI2上
//		TIM4->CCMR1|=0<<10; 	//IC2PS=00 	配置输入分频,不分频 
//		TIM4->CCMR1|=1<<12; 	//IC2F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效

//		TIM4->CCMR2|=1<<0;		//CC3S=01 	选择输入端 IC3映射到TI3上
//		TIM4->CCMR2|=0<<2; 	    //IC3PS=00 	配置输入分频,不分频 
//		TIM4->CCMR2|=1<<4; 		//IC3F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
//		
//		TIM4->CCMR2|=1<<8;		//CC4S=01 	选择输入端 IC4映射到TI4上
//		TIM4->CCMR2|=0<<10; 	//IC4PS=00 	配置输入分频,不分频 
//		TIM4->CCMR2|=1<<12; 	//IC4F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM4->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中
		TIM4->CCER|=0<<1; 		//CC1P=0	上升沿捕获
//		TIM4->CCER|=1<<4; 		//CC2E=1 	允许捕获计数器的值到捕获寄存器中
//		TIM4->CCER|=0<<5; 		//CC2P=0	上升沿捕获
//		TIM4->CCER|=1<<8; 		//CC3E=1 	允许捕获计数器的值到捕获寄存器中
//		TIM4->CCER|=0<<9; 		//CC3P=0	上升沿捕获
//		TIM4->CCER|=1<<12; 		//CC4E=1 	允许捕获计数器的值到捕获寄存器中
//		TIM4->CCER|=0<<13; 		//CC4P=0	上升沿捕获
		
		TIM4->DIER|=0xf<<1;   	//允许捕获中断				
		TIM4->DIER|=0<<0;   	//允许更新中断	
		TIM4->CR1|=0x01;    	//使能定时器5
		MY_NVIC_Init(0,0,TIM4_IRQn,2);//抢占2，子优先级0，组2	   
	}
	
	    				
	u16	TIM4CH1_CAPTURE_VAL;	//输入捕获值
//	u16 TIM4CH1_CNT=0;			//计数值
	u16 Freq=0;//频率值

	void TIM4_IRQHandler(void)
	{ 		    
		u16 tsr;
		tsr=TIM4->SR;
		
//		if(tsr&0X01)//溢出
//		{	    							
//			Freq=0;	 
//		}
		if(tsr&0x02)//捕获1发生捕获事件
		{					  			
			TIM4CH1_CAPTURE_VAL=TIM4->CCR1;	//获取当前的捕获值.
			TIM4->CNT=0; 
			TIM4->CCR1=0; 
		}	
		
		Freq=(u16)(100000/TIM4CH1_CAPTURE_VAL);//计数频率是100KHz

		
		TIM4->SR=0;//清除中断标志位 	    
	}		 		
#endif
#if __TIM5_CAP
	void TIM5_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB1ENR|=1<<3;   	//TIM5 时钟使能 
		RCC->APB2ENR|=1<<2;    	//使能PORTA时钟  
		 
		GPIOA->CRL&=0XFFFF0000;	//PA0,1,2,3 清除之前设置  
		GPIOA->CRL|=0X00008888;	//PA0,1,2,3 输入   
		  
		TIM5->ARR=arr;  		//设定计数器自动重装值   
		TIM5->PSC=psc;  		//预分频器 

		TIM5->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
		TIM5->CCMR1|=0<<2; 	//IC1PS=00 	配置输入分频,不分频 
		TIM5->CCMR1|=1<<4; 		//IC1F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM5->CCMR1|=1<<8;		//CC2S=01 	选择输入端 IC2映射到TI2上
		TIM5->CCMR1|=0<<10; 	//IC2PS=00 	配置输入分频,不分频 
		TIM5->CCMR1|=1<<12; 	//IC2F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效

		TIM5->CCMR2|=1<<0;		//CC3S=01 	选择输入端 IC3映射到TI3上
		TIM5->CCMR2|=0<<2; 	    //IC3PS=00 	配置输入分频,不分频 
		TIM5->CCMR2|=1<<4; 		//IC3F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM5->CCMR2|=1<<8;		//CC4S=01 	选择输入端 IC4映射到TI4上
		TIM5->CCMR2|=0<<10; 	//IC4PS=00 	配置输入分频,不分频 
		TIM5->CCMR2|=1<<12; 	//IC4F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM5->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中
		TIM5->CCER|=0<<1; 		//CC1P=0	上升沿捕获
		TIM5->CCER|=1<<4; 		//CC2E=1 	允许捕获计数器的值到捕获寄存器中
		TIM5->CCER|=0<<5; 		//CC2P=0	上升沿捕获
		TIM5->CCER|=1<<8; 		//CC3E=1 	允许捕获计数器的值到捕获寄存器中
		TIM5->CCER|=0<<9; 		//CC3P=0	上升沿捕获
		TIM5->CCER|=1<<12; 		//CC4E=1 	允许捕获计数器的值到捕获寄存器中
		TIM5->CCER|=0<<13; 		//CC4P=0	上升沿捕获
		
		TIM5->DIER|=0xf<<1;   	//允许捕获中断				
		TIM5->DIER|=1<<0;   	//允许更新中断	
		TIM5->CR1|=0x01;    	//使能定时器5
		MY_NVIC_Init(2,0,TIM5_IRQn,2);//抢占2，子优先级0，组2	   
	}

	//捕获状态
	//[7]:0,没有成功的捕获;1,成功捕获到一次.
	//[6]:0,还没捕获到高电平;1,已经捕获到高电平了.
	//[5:0]:捕获高电平后溢出的次数
	u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
	u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
	u16 TIM5CH1_CNT=0;			//计数值
	u8  TIM5CH2_CAPTURE_STA=0;	//输入捕获状态		    				
	u16	TIM5CH2_CAPTURE_VAL;	//输入捕获值
	u16 TIM5CH2_CNT=0;			//计数值
	u8  TIM5CH3_CAPTURE_STA=0;	//输入捕获状态		    				
	u16	TIM5CH3_CAPTURE_VAL;	//输入捕获值
	u16 TIM5CH3_CNT=0;			//计数值
	u8  TIM5CH4_CAPTURE_STA=0;	//输入捕获状态		    				
	u16	TIM5CH4_CAPTURE_VAL;	//输入捕获值
	u16 TIM5CH4_CNT=0;			//计数值
	//定时器5中断服务程序
	//注意：TIM5CH1_CAPTURE_STA在中断中没有清零，需外部清零，
	//TIM5CH1_CAPTURE_STA在捕获成功后清零，若捕获未成功清零，数据错乱
	//参考程序：
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
		if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
		{
			if(tsr&0X01)//溢出
			{	    
				if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
				{
					if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
					{
						TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
						TIM5CH1_CAPTURE_VAL=0XFFFF;
					}else TIM5CH1_CAPTURE_STA++;
				}	 
			}
			if(tsr&0x02)//捕获1发生捕获事件
			{	
				if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
				{	  			
					TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
					TIM5CH1_CAPTURE_VAL=TIM5->CCR1;	//获取当前的捕获值.
					TIM5->CCER&=~(1<<1);			//CC1P=0 设置为上升沿捕获
				}else  								//还未开始,第一次捕获上升沿
				{ 
					TIM5CH1_CAPTURE_VAL=0;
					TIM5CH1_CAPTURE_STA=0X40;		//标记捕获到了上升沿
					TIM5CH1_CNT=TIM5->CNT;			//计数器保存
					TIM5->CCER|=1<<1; 				//CC1P=1 设置为下降沿捕获 
				}		    
			}			     	    					   
		}
		if((TIM5CH2_CAPTURE_STA&0X80)==0)//还未成功捕获	
		{
			if(tsr&0X01)//溢出
			{	    
				if(TIM5CH2_CAPTURE_STA&0X40)//已经捕获到高电平了
				{
					if((TIM5CH2_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
					{
						TIM5CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
						TIM5CH2_CAPTURE_VAL=0XFFFF;
					}else TIM5CH2_CAPTURE_STA++;
				}	 
			}
			if(tsr&0x04)//捕获2发生捕获事件
			{	
				if(TIM5CH2_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
				{	  			
					TIM5CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
					TIM5CH2_CAPTURE_VAL=TIM5->CCR2;	//获取当前的捕获值.
					TIM5->CCER&=~(1<<5);			//CC2P=0 设置为上升沿捕获
				}else  								//还未开始,第一次捕获上升沿
				{ 
					TIM5CH2_CAPTURE_VAL=0;
					TIM5CH2_CAPTURE_STA=0X40;		//标记捕获到了上升沿
					TIM5CH2_CNT=TIM5->CNT;			//计数器保存
					TIM5->CCER|=1<<5; 				//CC2P=1 设置为下降沿捕获 
				}		    
			}			     	    					   
		}
		if((TIM5CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
		{
			if(tsr&0X01)//溢出
			{	    
				if(TIM5CH3_CAPTURE_STA&0X40)//已经捕获到高电平了
				{
					if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
					{
						TIM5CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
						TIM5CH2_CAPTURE_VAL=0XFFFF;
					}else TIM5CH3_CAPTURE_STA++;
				}	 
			}
			if(tsr&0x08)//捕获3发生捕获事件
			{	
				if(TIM5CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
				{	  			
					TIM5CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
					TIM5CH3_CAPTURE_VAL=TIM5->CCR3;	//获取当前的捕获值.
					TIM5->CCER&=~(1<<9);			//CC3P=0 设置为上升沿捕获
				}else  								//还未开始,第一次捕获上升沿
				{ 
					TIM5CH3_CAPTURE_VAL=0;
					TIM5CH3_CAPTURE_STA=0X40;		//标记捕获到了上升沿
					TIM5CH3_CNT=TIM5->CNT;			//计数器保存
					TIM5->CCER|=1<<9; 				//CC3P=1 设置为下降沿捕获 
				}		    
			}			     	    					   
		}
		if((TIM5CH4_CAPTURE_STA&0X80)==0)//还未成功捕获	
		{
			if(tsr&0X01)//溢出
			{	    
				if(TIM5CH4_CAPTURE_STA&0X40)//已经捕获到高电平了
				{
					if((TIM5CH4_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
					{
						TIM5CH4_CAPTURE_STA|=0X80;//标记成功捕获了一次
						TIM5CH4_CAPTURE_VAL=0XFFFF;
					}else TIM5CH4_CAPTURE_STA++;
				}	 
			}
			if(tsr&0x10)//捕获1发生捕获事件
			{	
				if(TIM5CH4_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
				{	  			
					TIM5CH4_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
					TIM5CH4_CAPTURE_VAL=TIM5->CCR4;	//获取当前的捕获值.
					TIM5->CCER&=~(1<<13);			//CC4P=0 设置为上升沿捕获
				}else  								//还未开始,第一次捕获上升沿
				{ 
					TIM5CH4_CAPTURE_VAL=0;
					TIM5CH4_CAPTURE_STA=0X40;		//标记捕获到了上升沿
					TIM5CH3_CNT=TIM5->CNT;			//计数器保存
					TIM5->CCER|=1<<13; 				//CC4P=1 设置为下降沿捕获 
				}		    
			}			     	    					   
		}
		TIM5->SR=0;//清除中断标志位 	    
	}		
#endif
#if __TIM8_CAP
	void TIM8_Cap_Init(u16 arr,u16 psc)
	{		 
		RCC->APB2ENR|=1<<13; 	//TIM8时钟使能 
		RCC->APB2ENR|=1<<4;		////IO端口C的时钟使能
		GPIOC->CRL&=0X00FFFFFF;	//PC6,PC7
		GPIOC->CRL|=0X88000000;	//复用功能输出 	
		GPIOC->CRH&=0XFFFFFF00;	//PC8,PC9
		GPIOC->CRH|=0X00000088;	//复用功能输出 
		
		TIM8->ARR=arr;  		//设定计数器自动重装值   
		TIM8->PSC=psc;  		//预分频器 

		TIM8->CCMR1|=1<<0;		//CC1S=01 	选择输入端 IC1映射到TI1上
		TIM8->CCMR1|=0<<2; 	//IC1PS=00 	配置输入分频,不分频 
		TIM8->CCMR1|=1<<4; 		//IC1F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM8->CCMR1|=1<<8;		//CC2S=01 	选择输入端 IC2映射到TI2上
		TIM8->CCMR1|=0<<10; 	//IC2PS=00 	配置输入分频,不分频 
		TIM8->CCMR1|=1<<12; 	//IC2F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效

		TIM8->CCMR2|=1<<0;		//CC3S=01 	选择输入端 IC3映射到TI3上
		TIM8->CCMR2|=0<<2; 	    //IC3PS=00 	配置输入分频,不分频 
		TIM8->CCMR2|=1<<4; 		//IC3F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM8->CCMR2|=1<<8;		//CC4S=01 	选择输入端 IC4映射到TI4上
		TIM8->CCMR2|=0<<10; 	//IC4PS=00 	配置输入分频,不分频 
		TIM8->CCMR2|=1<<12; 	//IC4F=0001 配置输入滤波器 以Fck_int采样，2个事件后有效
		
		TIM8->CCER|=1<<0; 		//CC1E=1 	允许捕获计数器的值到捕获寄存器中
		TIM8->CCER|=0<<1; 		//CC1P=0	上升沿捕获
		TIM8->CCER|=1<<4; 		//CC2E=1 	允许捕获计数器的值到捕获寄存器中
		TIM8->CCER|=0<<5; 		//CC2P=0	上升沿捕获
		TIM8->CCER|=1<<8; 		//CC3E=1 	允许捕获计数器的值到捕获寄存器中
		TIM8->CCER|=0<<9; 		//CC3P=0	上升沿捕获
		TIM8->CCER|=1<<12; 		//CC4E=1 	允许捕获计数器的值到捕获寄存器中
		TIM8->CCER|=0<<13; 		//CC4P=0	上升沿捕获
		
		TIM8->DIER|=0xf<<1;   	//允许捕获中断				
		TIM8->DIER|=1<<0;   	//允许更新中断	
		TIM8->CR1|=0x01;    	//使能定时器5
		MY_NVIC_Init(2,0,TIM8_UP_IRQn,2);//抢占2，子优先级0，组2	   
	}
	void TIM8_UP_IRQHandler(void)
	{ 		    	     	    					   
		 
	}
#endif













