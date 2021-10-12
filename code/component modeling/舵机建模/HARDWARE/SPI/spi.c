#include "H_define.h"



#if __SPI1
	void SPI1_Init(void)
	{	 
	RCC->APB2ENR|=1<<2;       //PORTA时钟使能 	 
	RCC->APB2ENR|=1<<12;      //SPI1时钟使能 
		   
	//这里只针对SPI口初始化
	GPIOA->CRL&=0X000FFFFF; 
	GPIOA->CRL|=0XBBB00000;//PA5.6.7复用 	    
	GPIOA->ODR|=0X7<<5;    //PA5.6.7上拉
		
	SPI1->CR1|=0<<10;//全双工模式	
	SPI1->CR1|=1<<9; //软件nss管理
	SPI1->CR1|=1<<8;  

	SPI1->CR1|=1<<2; //SPI主机
	SPI1->CR1|=0<<11;//8bit数据格式	
		
	SPI1->CR1|=1<<1; //空闲模式下SCK为1 CPOL=1
	SPI1->CR1|=1<<0; //数据采样从第二个时间边沿开始,CPHA=1 
		
	SPI1->CR1|=7<<3; //Fsck=Fcpu/128
	SPI1->CR1|=0<<7; //MSBfirst   
	SPI1->CR1|=1<<6; //SPI设备使能
	SPI1_ReadWriteByte(0xff);//启动传输(主要作用：维持MOSI为高)		 
	}   
	//SPI1 速度设置函数
	//SpeedSet:0~7
	//SPI速度=fAPB2/2^(SpeedSet+1)
	//APB2时钟一般为72Mhz
	void SPI1_SetSpeed(u8 SpeedSet)
	{
		SpeedSet&=0X07;			//限制范围
		SPI1->CR1&=0XFFC7; 
		SPI1->CR1|=SpeedSet<<3;	//设置SPI1速度  
		SPI1->CR1|=1<<6; 		//SPI设备使能 
	} 
	//SPI1 读写一个字节
	//TxData:要写入的字节
	//返回值:读取到的字节
	//全双工读写必须放到一起！
	//读的时候需要通过主设备写数据来提供SCK
	//写的完后主设备的DR中会多一个无用的数据，需要读走来清缓存
	u8 SPI1_ReadWriteByte(u8 TxData)
	{		
		u16 retry=0;				 
		while((SPI1->SR&1<<1)==0)//等待发送区空	
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}			  
		SPI1->DR=TxData;	 	  //发送一个byte 
		retry=0;
		while((SPI1->SR&1<<0)==0) //等待接收完一个byte  
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}	  						    
		return SPI1->DR;          //返回收到的数据				    
	} 
#endif

#if __SPI2
	void SPI2_Init(void)
	{	 
		RCC->APB2ENR|=1<<3;       //PORTB时钟使能 	 
		RCC->APB1ENR|=1<<14;      //SPI2时钟使能 
			   
		//这里只针对SPI口初始化
		GPIOB->CRH&=0X000FFFFF; 
		GPIOB->CRH|=0XBBB00000;//PB13,14,15复用 	    
		GPIOB->ODR|=0X7<<13;    //PB13,14,15上拉
			
		SPI2->CR1|=0<<10;//全双工模式	
		SPI2->CR1|=1<<9; //软件nss管理
		SPI2->CR1|=1<<8;  

		SPI2->CR1|=1<<2; //SPI主机
		SPI2->CR1|=0<<11;//8bit数据格式	
			
		SPI2->CR1|=1<<1; //空闲模式下SCK为1 CPOL=1
		SPI2->CR1|=1<<0; //数据采样从第二个时间边沿开始,CPHA=1 
			
		SPI2->CR1|=7<<3; //Fsck=Fcpu/128
		SPI2->CR1|=0<<7; //MSBfirst   
		SPI2->CR1|=1<<6; //SPI设备使能
		SPI2_ReadWriteByte(0xff);//启动传输(主要作用：维持MOSI为高)		 
	}   
	//SPI2 速度设置函数
	//SpeedSet:0~7
	//SPI速度=fAPB2/2^(SpeedSet+1)
	//APB1时钟一般为36Mhz
	void SPI2_SetSpeed(u8 SpeedSet)
	{
		SpeedSet&=0X07;			//限制范围
		SPI2->CR1&=0XFFC7; 
		SPI2->CR1|=SpeedSet<<3;	//设置SPI1速度  
		SPI2->CR1|=1<<6; 		//SPI设备使能 
	} 
	//SPI2 读写一个字节
	//TxData:要写入的字节
	//返回值:读取到的字节
	//全双工读写必须放到一起！
	//读的时候需要通过主设备写数据来提供SCK
	//写的完后主设备的DR中会多一个无用的数据，需要读走来清缓存
	u8 SPI2_ReadWriteByte(u8 TxData)
	{		
		u16 retry=0;				 
		while((SPI2->SR&1<<1)==0)//等待发送区空	
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}			  
		SPI2->DR=TxData;	 	  //发送一个byte 
		retry=0;
		while((SPI2->SR&1<<0)==0) //等待接收完一个byte  
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}	  						    
		return SPI2->DR;          //返回收到的数据				    
	} 
#endif

#if __SPI3
	void SPI3_Init(void)
	{	 
		RCC->APB2ENR|=1<<3;       //PORTB时钟使能 	 
		RCC->APB1ENR|=1<<15;      //SPI3时钟使能 
			   
		//这里只针对SPI口初始化
		GPIOB->CRL&=0XFF000FFF; 
		GPIOB->CRL|=0X00BBB000;//PB3,4,5复用 	    
		GPIOB->ODR|=0X7<<3;    //PB3,4,5上拉
			
		SPI3->CR1|=0<<10;//全双工模式	
		SPI3->CR1|=1<<9; //软件nss管理
		SPI3->CR1|=1<<8;  

		SPI3->CR1|=1<<2; //SPI主机
		SPI3->CR1|=0<<11;//8bit数据格式	
			
		SPI3->CR1|=1<<1; //空闲模式下SCK为1 CPOL=1
		SPI3->CR1|=1<<0; //数据采样从第二个时间边沿开始,CPHA=1 
			
		SPI3->CR1|=7<<3; //Fsck=Fcpu/128
		SPI3->CR1|=0<<7; //MSBfirst   
		SPI3->CR1|=1<<6; //SPI设备使能
		SPI3_ReadWriteByte(0xff);//启动传输(主要作用：维持MOSI为高)		 
	}   
	//SPI3 速度设置函数
	//SpeedSet:0~7
	//SPI速度=fAPB2/2^(SpeedSet+1)
	//APB1时钟一般为36Mhz
	void SPI3_SetSpeed(u8 SpeedSet)
	{
		SpeedSet&=0X07;			//限制范围
		SPI3->CR1&=0XFFC7; 
		SPI3->CR1|=SpeedSet<<3;	//设置SPI1速度  
		SPI3->CR1|=1<<6; 		//SPI设备使能 
	} 
	//SPI3 读写一个字节
	//TxData:要写入的字节
	//返回值:读取到的字节
	//全双工读写必须放到一起！
	//读的时候需要通过主设备写数据来提供SCK
	//写的完后主设备的DR中会多一个无用的数据，需要读走来清缓存
	u8 SPI3_ReadWriteByte(u8 TxData)
	{		
		u16 retry=0;				 
		while((SPI3->SR&1<<1)==0)//等待发送区空	
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}			  
		SPI3->DR=TxData;	 	  //发送一个byte 
		retry=0;
		while((SPI3->SR&1<<0)==0) //等待接收完一个byte  
		{
			retry++;
			if(retry>0XFFFE)return 0;
		}	  						    
		return SPI3->DR;          //返回收到的数据				    
	} 
#endif















