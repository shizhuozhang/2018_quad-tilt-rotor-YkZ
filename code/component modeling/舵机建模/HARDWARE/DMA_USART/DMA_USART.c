#include "H_define.h"


u8 D_6050[32];
u8 D_6050_ANGLE[6];
u8 D_6050_WANG[6];

//cndtr:数据数量
//cpar:外设地址
//cmar:存储地址
void DMA1_Channel3_Init(u16 cndtr,u32 cpar,u32 cmar)  //usart3
{
	RCC->AHBENR|=1<<0;			//开启DMA1时钟
	delay_ms(5);				//等待DMA时钟稳定
	DMA1_Channel3->CPAR=cpar; 	 	//DMA1 外设地址 
	DMA1_Channel3->CMAR=cmar; 	//DMA1,存储器地址
	DMA1_Channel3->CNDTR=cndtr;    	//DMA1,传输数据量
	DMA1_Channel3->CCR=0X00000000;	//复位
	DMA1_Channel3->CCR|=0<<4;  		//从外设读
	DMA1_Channel3->CCR|=1<<5;  		//普通模式
	DMA1_Channel3->CCR|=0<<6; 		//外设地址非增量模式
	DMA1_Channel3->CCR|=1<<7; 	 	//存储器增量模式
	DMA1_Channel3->CCR|=0<<8; 	 	//外设数据宽度为8位
	DMA1_Channel3->CCR|=0<<10; 		//存储器数据宽度8位
	DMA1_Channel3->CCR|=1<<12; 		//中等优先级
	DMA1_Channel3->CCR|=0<<14; 		//非存储器到存储器模式
	DMA1_Channel3->CCR|=1<<1;			//允许TC中断
	DMA1_Channel3->CCR|=1<<0;			//通道开启
	MY_NVIC_Init(1,0,DMA1_Channel3_IRQn,2);
}

//cndtr:数据数量
//cpar:外设地址
//cmar:存储地址
void DMA1_Channel6_Init(u16 cndtr,u32 cpar,u32 cmar)   //usart2
{
	RCC->AHBENR|=1<<0;			//开启DMA1时钟
	delay_ms(5);				//等待DMA时钟稳定
	DMA1_Channel6->CPAR=cpar; 	 	//DMA1 外设地址 
	DMA1_Channel6->CMAR=cmar; 	//DMA1,存储器地址
	DMA1_Channel6->CNDTR=cndtr;    	//DMA1,传输数据量
	DMA1_Channel6->CCR=0X00000000;	//复位
	DMA1_Channel6->CCR|=0<<4;  		//从外设读
	DMA1_Channel6->CCR|=1<<5;  		//普通模式
	DMA1_Channel6->CCR|=0<<6; 		//外设地址非增量模式
	DMA1_Channel6->CCR|=1<<7; 	 	//存储器增量模式
	DMA1_Channel6->CCR|=0<<8; 	 	//外设数据宽度为8位
	DMA1_Channel6->CCR|=0<<10; 		//存储器数据宽度8位
	DMA1_Channel6->CCR|=1<<12; 		//中等优先级
	DMA1_Channel6->CCR|=0<<14; 		//非存储器到存储器模式
	DMA1_Channel6->CCR|=1<<1;			//允许TC中断
	DMA1_Channel6->CCR|=1<<0;			//通道开启
	MY_NVIC_Init(1,3,DMA1_Channel6_IRQn,2);
}



void  DMA1_Channel3_IRQHandler()//dma1中断  usart3
{
	if(DMA1->ISR&(1<<9))//传输完成
	{
		DMA1->IFCR|=1<<9;//清除标志位
	}	
}

u8 sign_usrt2=0;
u8 Dma1_C6_Close=0;

volatile WAng_XYZ   WAng_Now;
volatile Angle_XYZ  Angle_Now; 
volatile Angle_XYZ  Acce_Now;
extern u8 GYRO_Flag;
void  DMA1_Channel6_IRQHandler()//dma1中断
{
	if(DMA1->ISR&(1<<21))//传输完成
	{
		DMA1->IFCR|=1<<21;//清除标志位
		if((0X51!=D_6050[0])||(0X52!=D_6050[11])||(0X53!=D_6050[22]))//
		{
			DMA1_Channel6->CCR&=~(1<<0);			//通道开启
			Dma1_C6_Close=1;
		}
		else
		{
//			Update_Acce();		
//			Update_WAng();
			Update_Angle();
			sign_usrt2=1;
			if(GYRO_Flag==0)
				printf("%f\r\n",Angle_Now.Angle_Z);
		}
	}
	
}

void Update_Acce()//串口读取6050数据包并解算////标志位sign_usrt2
{
	Acce_Now.Angle_X= ((short)(D_6050[2]<<8| D_6050[1]))/32768.0*16*G;  //-Angle_Init[0]X轴滚转角（x 轴）除去初始偏置
	Acce_Now.Angle_Y= ((short)(D_6050[4]<<8| D_6050[3]))/32768.0*16*G;  //-Angle_Init[1]Y轴俯仰角（y 轴）
	Acce_Now.Angle_Z= ((short)(D_6050[6]<<8| D_6050[5]))/32768.0*16*G;  //-Angle_Init[2]Z轴俯仰角（y 轴）
}

void Update_Angle()//串口读取6050数据包并解算////标志位sign_usrt2
{
	Angle_Now.Angle_X= -(((short)(D_6050[24]<<8| D_6050[23]))/32768.0*180)-Angle_Init[0];  //X轴滚转角（x 轴）除去初始偏置
	Angle_Now.Angle_Y= -(((short)(D_6050[26]<<8| D_6050[25]))/32768.0*180)-Angle_Init[1];  //Y轴俯仰角（y 轴）
	Angle_Now.Angle_Z= -(((short)(D_6050[28]<<8| D_6050[27]))/32768.0*180)-Angle_Init[2];	//Z轴俯仰角（y 轴）
}

void Update_WAng()//串口读取6050数据包并解算////标志位sign_usrt2
{
	WAng_Now.WAngle_X = ((short)(D_6050[13]<<8| D_6050[12]))/32768.0*2000;  //X轴角速度
	WAng_Now.WAngle_Y = ((short)(D_6050[15]<<8| D_6050[14]))/32768.0*2000; //Y轴角速度
	WAng_Now.WAngle_Z = ((short)(D_6050[17]<<8| D_6050[16]))/32768.0*2000; //Z轴角速度
}

