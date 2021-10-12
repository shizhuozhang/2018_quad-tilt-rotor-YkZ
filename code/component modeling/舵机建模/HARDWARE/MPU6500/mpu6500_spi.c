#include "H_define.h"
/*
 * 函数名：SPI1_Init
 * 描述  ：SPI1初始化
 * 输入  ：无
 * 输出  ：无
 */ 
 void SPI1_Init(void)
	{	 
		RCC->APB2ENR|=1<<3;       //PORTB时钟使能 	 
		RCC->APB1ENR|=1<<14;      //SPI2时钟使能 
			   
		//这里只针对SPI口初始化
		GPIOB->CRH&=0X000FFFFF; 
		GPIOB->CRH|=0XBBB00000;//PB13,14,15复用 	    
		GPIOB->ODR|=0X7<<13;    //PB13,14,15上拉
		
		MPU6500_CS=1;
		
		SPI2->CR1|=0<<10;//全双工模式	
		SPI2->CR1|=1<<9; //软件nss管理
		SPI2->CR1|=1<<8;  

		SPI2->CR1|=1<<2; //SPI主机
		SPI2->CR1|=0<<11;//8bit数据格式	
			
		SPI2->CR1|=0<<1; //空闲模式下SCK为1 CPOL=1
		SPI2->CR1|=0<<0; //数据采样从第二个时间边沿开始,CPHA=1 
			
		SPI2->CR1|=2<<3; //Fsck=Fcpu/128
		SPI2->CR1|=0<<7; //MSBfirst   
		SPI2->CR1|=1<<6; //SPI设备使能
		SPI1_Read_Write_Byte(0xff);//启动传输(主要作用：维持MOSI为高)		 
	}   
// void SPI1_Init(void)
//{
//	
//	RCC->APB2ENR|=1<<2;       //PORTA时钟使能 	 
//	RCC->APB2ENR|=1<<12;      //SPI1时钟使能 
//		   
//	//这里只针对SPI口初始化	
//    GPIOA->CRL&=~(0XFFF00000);//PA5.6.7推挽复用输出 
//	GPIOA->CRL|=0XBBB00000;//PA5.6.7推挽复用输出 	    
//	GPIOA->ODR|=0X00E0;    //PA5.6.7上拉
//	
//	MPU6500_CS=1;
//	
//	SPI1->CR1=0;	
//	
//	SPI1->CR1|=0<<6; //SPI设备禁用
//	
//	SPI1->CR1|=0<<10;//全双工模式	
//	SPI1->CR1|=0<<15;//双线双向
////	SPI1->CR1|=1<<14;//单线模式下的输出使能		
//	SPI1->CR1|=1<<9; //软件nss管理
////	SPI1->CR1|=1<<8; //决定nss上的电平 /////////////////////////////////////////

//	SPI1->CR1|=1<<2; //SPI主机
//	SPI1->CR1|=0<<11;//8bit数据格式	
//	SPI1->CR1|=0<<1; //空闲模式下SCK为0 CPOL=0
//	SPI1->CR1|=0<<0; //数据采样从第1个时间边沿开始,CPHA=0  
//	SPI1->CR1|=2<<3; //Fsck=Fcpu/16
//	SPI1->CR1|=0<<7; //MSB   
//	SPI1->CR1|=1<<13; //使能CRC校验	
//	SPI1->CRCPR|=7; //CRC计算时用到的多项式
//	
//	SPI1->CR1|=1<<6; //SPI设备使能
//	
//	SPI1_Read_Write_Byte(0xff);//启动传输(主要作用：维持MOSI为高)		 
//}   
/*
 * 函数名: uint8_t MPU9250_Write_Reg
 * 描述  ：函数用于向9250的特定寄存器写入命令
 * 输入  ：寄存器的地址，命令
 * 输出  ：0：失败  1：成功
 */ 
u8 MPU6500_Write_Reg(uint8_t reg,uint8_t value)
{
	u8 status;
	MPU6500_CS=0;  //使能SPI传输
	status=SPI1_Read_Write_Byte(reg); //发送写命令+寄存器号
	SPI1_Read_Write_Byte(value);//写入寄存器值
	MPU6500_CS=1;  //禁止MPU9250
	return(status);//返回状态值
}

/*
 * 函数名: u8 MPU9250_Read_Reg
 * 描述  ：函数用于向9250读数据
 * 输入  ：寄存器的地址
 * 输出  ：从寄存器读得的数据
 */ 
u8 MPU6500_Read_Reg(uint8_t reg)
{
	u8 reg_val;
	MPU6500_CS=0;  //使能SPI传输
	SPI1_Read_Write_Byte(reg|0x80); //发送读命令+寄存器号
									//9250寄存器地址最大是0x7E，与上0x80,防止出错
	reg_val=SPI1_Read_Write_Byte(0xff);//读取寄存器值
	MPU6500_CS=1;  //禁止MPU9250
	return(reg_val);
}

/*
 * 函数名: u8 SPI1_ReadWriteByte
 * 描述  ：函数用于向9250读写数据
 * 输入  ：寄存器的地址
 * 输出  ：从寄存器读得的数据或者失败返回0
 */ 
//u8 SPI1_Read_Write_Byte(u8 TxData)
//{		
//	u16 retry=0;				 
//	while((SPI1->SR&1<<1)==0)//等待发送区空	
//	{
//		retry++;
//		if(retry>0XFFFE)return 0;
//	}			  
//	SPI1->DR=TxData;	 	  //发送一个byte 
//	retry=0;
//	while((SPI1->SR&1<<0)==0) //等待接收完一个byte  
//	{
//		retry++;
//		if(retry>0XFFFE)return 0;
//	}	  						    
//	return SPI1->DR;          //返回收到的数据				    
//}

u8 SPI1_Read_Write_Byte(u8 TxData)
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


