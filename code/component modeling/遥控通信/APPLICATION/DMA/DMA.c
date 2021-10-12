#include "H_define.h"

/*
//DMAx的各通道配置
//这里的传输形式是固定的,从外设->存储器模式/8位数据宽度/存储器增量模式
//使用时根据不同的情况来修改
//DMA_Streamx:DMA数据流,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMA通道选择,范围:0~7
//par:外设地址
//mar:存储器地址
//ndtr:数据传输量  
void DMA_Config_Temp(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr)
{ 
	DMA_TypeDef *DMAx;
	u8 streamx;
	if((u32)DMA_Streamx>(u32)DMA2)//得到当前stream是属于DMA2还是DMA1
	{
		DMAx=DMA2;
		RCC->AHB1ENR|=1<<22;//DMA2时钟使能 
	}else 
	{
		DMAx=DMA1; 
 		RCC->AHB1ENR|=1<<21;//DMA1时钟使能 
	}
	while(DMA_Streamx->CR&0X01);//等待DMA可配置 
	streamx=(((u32)DMA_Streamx-(u32)DMAx)-0X10)/0X18;		//得到stream通道号
 	if(streamx>=6)DMAx->HIFCR|=0X3D<<(6*(streamx-6)+16);	//清空之前该stream上的所有中断标志
	else if(streamx>=4)DMAx->HIFCR|=0X3D<<6*(streamx-4);    //清空之前该stream上的所有中断标志
	else if(streamx>=2)DMAx->LIFCR|=0X3D<<(6*(streamx-2)+16);//清空之前该stream上的所有中断标志
	else DMAx->LIFCR|=0X3D<<6*streamx;						//清空之前该stream上的所有中断标志
	
	DMA_Streamx->PAR=par;		//DMA外设地址
	DMA_Streamx->M0AR=mar;		//DMA 存储器0地址
	DMA_Streamx->NDTR=ndtr;		//DMA 数据传输量
	DMA_Streamx->CR=0;			//先全部复位CR寄存器值 
	DMA_Streamx->CR|=(u32)chx<<25;//通道选择
	
	DMA_Streamx->CR|=0<<6;		//外设到存储器模式//0是从外设到存储器，1是存储器到外设，2是存储器到存储器
	DMA_Streamx->CR|=0<<8;		//非循环模式(即使用普通模式)
	DMA_Streamx->CR|=0<<9;		//外设非增量模式
	DMA_Streamx->CR|=1<<10;		//存储器增量模式
	DMA_Streamx->CR|=0<<11;		//外设数据长度:8位
	DMA_Streamx->CR|=0<<13;		//存储器数据长度:8位
	DMA_Streamx->CR|=1<<16;		//中等优先级0是低，1是中，2是高，3是非常高
	DMA_Streamx->CR|=0<<21;		//外设突发单次传输
	DMA_Streamx->CR|=0<<23;		//存储器突发单次传输
//	DMA_Streamx->FCR=0X21;	//FIFO控制寄存器？？？？？？？？？？
	DMA_Streamx->CR|=1<<4;		//传输完成中断使能	
	MY_NVIC_Init(0,0,DMA1_Stream0_IRQn,2);//需要根据需要修改中断矢量号
	
	DMA_Streamx->CR&=~(1<<0); 	//关闭DMA传输 
	while(DMA_Streamx->CR&0X1);	//确保DMA可以被设置  
	DMA_Streamx->CR|=1<<0;		//开启DMA传输
} 
void  DMA1_Stream0_IRQHandler()//数据流X0-3的传输完成中断服务函数
{
	if(DMA1->LISR&(1<<5))//传输完成标志位，数据流0-3对应5，11，21，27
	{
		DMA1->LIFCR &=~(1<<5);//清除标志位
		
	}
}
void  DMA1_Stream4_IRQHandler()//数据流X4-7的传输完成中断服务函数
{
	if(DMA1->HISR&(1<<5))//传输完成标志位，数据流4-7对应5，11，21，27
	{
		DMA1->HIFCR &=~(1<<5);//清除标志位
		
	}
}
*/

/*串口接收外部数据包，通过DMA直接传输到内存*/
#if __DMA_USART3
//DMA_Streamx:DMA数据流,DMAX_StreamX
//chx:DMA通道选择,范围:0~7
//USART1_RX:DMA2_Stream5,CH4；USART2_RX:DMA1_Stream5,CH4；USART3_RX:DMA1_Stream1,CH4；
//UART4_RX:DMA1_Stream2,CH4；UART5_RX:DMA1_Stream0,CH4；USART6_RX:DMA2_Stream1,CH5；
//par:外设地址
//mar:存储器地址
//ndtr:数据传输量  
//rank：不同串口的传输优先级,有效值0-3
void DMA_Config_USART3(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr,u8 rank)
{ 
	DMA_TypeDef *DMAx;
	u8 streamx;
	if((u32)DMA_Streamx>(u32)DMA2)//得到当前stream是属于DMA2还是DMA1
	{
		DMAx=DMA2;
		RCC->AHB1ENR|=1<<22;//DMA2时钟使能 
	}else 
	{
		DMAx=DMA1; 
 		RCC->AHB1ENR|=1<<21;//DMA1时钟使能 
	}
	while(DMA_Streamx->CR&0X01);//等待DMA可配置 
	streamx=(((u32)DMA_Streamx-(u32)DMAx)-0X10)/0X18;		//得到stream通道号
 	if(streamx>=6)DMAx->HIFCR|=0X3D<<(6*(streamx-6)+16);	//清空之前该stream上的所有中断标志
	else if(streamx>=4)DMAx->HIFCR|=0X3D<<6*(streamx-4);    //清空之前该stream上的所有中断标志
	else if(streamx>=2)DMAx->LIFCR|=0X3D<<(6*(streamx-2)+16);//清空之前该stream上的所有中断标志
	else DMAx->LIFCR|=0X3D<<6*streamx;						//清空之前该stream上的所有中断标志
	
	DMA_Streamx->PAR=par;		//DMA外设地址
	DMA_Streamx->M0AR=mar;		//DMA 存储器0地址
	DMA_Streamx->NDTR=ndtr;		//DMA 数据传输量
	DMA_Streamx->CR=0;			//先全部复位CR寄存器值 
	DMA_Streamx->CR|=(u32)chx<<25;//通道选择
	
	DMA_Streamx->CR|=0<<6;		//外设到存储器模式//0是从外设到存储器，1是存储器到外设，2是存储器到存储器
	DMA_Streamx->CR|=1<<8;		//循环模式
	DMA_Streamx->CR|=0<<9;		//外设非增量模式
	DMA_Streamx->CR|=1<<10;		//存储器增量模式
	DMA_Streamx->CR|=0<<11;		//外设数据长度:8位
	DMA_Streamx->CR|=0<<13;		//存储器数据长度:8位
	DMA_Streamx->CR|=rank<<16;		//中等优先级0是低，1是中，2是高，3是非常高
//	DMA_Streamx->CR|=0<<21;		//外设突发单次传输
//	DMA_Streamx->CR|=0<<23;		//存储器突发单次传输
//	DMA_Streamx->FCR=0X21;	//FIFO控制寄存器？？？？？？？？？？
	DMA_Streamx->CR|=1<<4;		//传输完成中断使能
	
	MY_NVIC_Init(0,1,DMA1_Stream1_IRQn,2);//需要根据需要修改中断矢量号

	DMA_Streamx->CR&=~(1<<0); 	//关闭DMA传输 
//	while(DMA_Streamx->CR&0X1);	//确保DMA可以被设置  
//	DMA_Streamx->CR|=1<<0;		//开启DMA传输
} 

u8 Sbus_OK=0;
volatile u8 Dma1_T1_Close=1;//开始时关着的，有数据再开启
void  DMA1_Stream1_IRQHandler()//数据流X0-3的传输完成中断服务函数
{
	if(DMA1->LISR&(1<<11))//传输完成标志位，数据流0-3对应5，11，21，27
	{	
		DMA1->LIFCR|=1<<11;//清除标志位
		if(0!=SBUS_DATA[24])	//0X0F!=SBUS_DATA[0])||
			Sbus_OK=0;
		else
		{
			SBUS_data_Pro();
			Sbus_OK=1;//遥控数据接收到
		}
		USART3->CR3&=~(1<<6);    //DMA禁止接受
		DMA1_Stream1->CR&=~(1<<0); 	//关闭DMA传输 		
		Dma1_T1_Close=1;
	}
}
#endif

#if __DMA_USART2
void DMA_Config_USART2(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr,u8 rank)
{ 
	DMA_TypeDef *DMAx;
	u8 streamx;
	if((u32)DMA_Streamx>(u32)DMA2)//得到当前stream是属于DMA2还是DMA1
	{
		DMAx=DMA2;
		RCC->AHB1ENR|=1<<22;//DMA2时钟使能 
	}else 
	{
		DMAx=DMA1; 
 		RCC->AHB1ENR|=1<<21;//DMA1时钟使能 
	}
	while(DMA_Streamx->CR&0X01);//等待DMA可配置 
	streamx=(((u32)DMA_Streamx-(u32)DMAx)-0X10)/0X18;		//得到stream通道号
 	if(streamx>=6)DMAx->HIFCR|=0X3D<<(6*(streamx-6)+16);	//清空之前该stream上的所有中断标志
	else if(streamx>=4)DMAx->HIFCR|=0X3D<<6*(streamx-4);    //清空之前该stream上的所有中断标志
	else if(streamx>=2)DMAx->LIFCR|=0X3D<<(6*(streamx-2)+16);//清空之前该stream上的所有中断标志
	else DMAx->LIFCR|=0X3D<<6*streamx;						//清空之前该stream上的所有中断标志
	
	DMA_Streamx->PAR=par;		//DMA外设地址
	DMA_Streamx->M0AR=mar;		//DMA 存储器0地址
	DMA_Streamx->NDTR=ndtr;		//DMA 数据传输量
	DMA_Streamx->CR=0;			//先全部复位CR寄存器值 
	DMA_Streamx->CR|=(u32)chx<<25;//通道选择
	
	DMA_Streamx->CR|=0<<6;		//外设到存储器模式//0是从外设到存储器，1是存储器到外设，2是存储器到存储器
	DMA_Streamx->CR|=1<<8;		//循环模式
	DMA_Streamx->CR|=0<<9;		//外设非增量模式
	DMA_Streamx->CR|=1<<10;		//存储器增量模式
	DMA_Streamx->CR|=0<<11;		//外设数据长度:8位
	DMA_Streamx->CR|=0<<13;		//存储器数据长度:8位
	DMA_Streamx->CR|=rank<<16;		//中等优先级0是低，1是中，2是高，3是非常高
	DMA_Streamx->CR|=0<<21;		//外设突发单次传输
//	DMA_Streamx->CR|=0<<23;		//存储器突发单次传输
//	DMA_Streamx->FCR=0X21;	//FIFO控制寄存器？？？？？？？？？？
	DMA_Streamx->CR|=1<<4;		//传输完成中断使能
	
	MY_NVIC_Init(0,2,DMA1_Stream5_IRQn,2);//需要根据需要修改中断矢量号

	DMA_Streamx->CR&=~(1<<0); 	//关闭DMA传输 
//	while(DMA_Streamx->CR&0X1);	//确保DMA可以被设置  
//	DMA_Streamx->CR|=1<<0;		//开启DMA传输
} 
u8 Ahrs_OK=0;
volatile u8 Dma1_T5_Close=1;

void  DMA1_Stream5_IRQHandler()//数据流X4-7的传输完成中断服务函数
{
	if(DMA1->HISR&(1<<11))//传输完成标志位，数据流4-7对应5，11，21，27
	{
		DMA1->HIFCR|=1<<11;//清除标志位
		
		Ahrs_Flag1=1;//传输完一组数据后，开启下一组数据的帧头校验
		
		USART2->CR3&=~(1<<6);    //DMA禁止接受
		DMA1_Stream5->CR&=~(1<<0); 	//关闭DMA传输,在USART2接收中断函数中开启 		
		Dma1_T5_Close=1;
		
		if((0X12==AHRS_DATA[0])&&(0XA1==AHRS_DATA[1])&&(0XAA==AHRS_DATA[41]))			
		{							//再次判断帧标识字节和结尾校验
			if(AHRS_data_Pro())			
				Ahrs_OK=1;
			else
				Ahrs_OK=0;
		}
	}
}
#endif


volatile u16 ADC1_DATA[6]={0};
volatile u16 ADC_SUM[6]={0};
volatile u16 ADC_AVE[6]={0};
volatile float Voltage[6]={0.0};//采到的电压值，
volatile float Current[5]={0.0};//其中总电流和四路电机的电流，电流电压的转换关系是40mv/A
volatile float Walte[5]={0.0};//总功率和四路电机的功率
u8 sign_Adc1=0;

//DMA2 Stream0,ch0对应ADC1,DMA2 Stream1,ch2对应ADC3,DMA2 Stream2,ch2对应ADC2
#if __DMA_ADC1

void DMA_Config_ADC1(DMA_Stream_TypeDef *DMA_Streamx,u8 chx,u32 par,u32 mar,u16 ndtr,u8 rank)
{ 
	DMA_TypeDef *DMAx;
	u8 streamx;
	if((u32)DMA_Streamx>(u32)DMA2)//得到当前stream是属于DMA2还是DMA1
	{
		DMAx=DMA2;
		RCC->AHB1ENR|=1<<22;//DMA2时钟使能 
	}else 
	{
		DMAx=DMA1; 
 		RCC->AHB1ENR|=1<<21;//DMA1时钟使能 
	}
	while(DMA_Streamx->CR&0X01);//等待DMA可配置 
	streamx=(((u32)DMA_Streamx-(u32)DMAx)-0X10)/0X18;		//得到stream通道号
 	if(streamx>=6)DMAx->HIFCR|=0X3D<<(6*(streamx-6)+16);	//清空之前该stream上的所有中断标志
	else if(streamx>=4)DMAx->HIFCR|=0X3D<<6*(streamx-4);    //清空之前该stream上的所有中断标志
	else if(streamx>=2)DMAx->LIFCR|=0X3D<<(6*(streamx-2)+16);//清空之前该stream上的所有中断标志
	else DMAx->LIFCR|=0X3D<<6*streamx;						//清空之前该stream上的所有中断标志
	
	DMA_Streamx->PAR=par;		//DMA外设地址
	DMA_Streamx->M0AR=mar;		//DMA 存储器0地址
	DMA_Streamx->NDTR=ndtr;		//DMA 数据传输量
	
	DMA_Streamx->CR=0;			//先全部复位CR寄存器值 
	DMA_Streamx->CR|=(u32)chx<<25;//通道选择
//	DMA_Streamx->CR|=1<<21;		//外设突发单次传输
	DMA_Streamx->CR|=(u32)rank<<16;		//中等优先级0是低，1是中，2是高，3是非常高
	
	DMA_Streamx->CR|=1<<13;		//存储器数据长度:16位
	DMA_Streamx->CR|=1<<11;		//外设数据长度:16位	
	DMA_Streamx->CR|=1<<10;		//存储器增量模式	
//	DMA_Streamx->CR|=1<<9;		//外设非增量模式
	DMA_Streamx->CR|=1<<8;		//循环模式	
//	DMA_Streamx->CR|=1<<6;		//外设到存储器模式//0是从外设到存储器，1是存储器到外设，2是存储器到存储器
	DMA_Streamx->CR|=1<<4;		//传输完成中断使能	
	MY_NVIC_Init(3,3,DMA2_Stream0_IRQn,2);//需要根据需要修改中断矢量号	
	
//	DMA_Streamx->FCR=0X21;	//FIFO控制寄存器？？？？？？？？？？

//	DMA_Streamx->CR&=~(1<<0); 	//关闭DMA传输 
	while(DMA_Streamx->CR&0X1);	//确保DMA可以被设置  
	DMA_Streamx->CR|=1<<0;		//开启DMA传输
	
	ADC1->CR2|=1<<30;	   	//开启ADC规则转换
} 


void  DMA2_Stream0_IRQHandler()//数据流X0-3的传输完成中断服务函数
{
	u8 i=0;
	static u8 t=0;
	if(DMA2->LISR&(1<<5))//传输完成标志位，数据流0-3对应5，11，21，27
	{
		DMA2->LIFCR|=1<<5;//清除标志位
		for(i=0;i<6;i++)
			ADC_SUM[i]+=ADC1_DATA[i];
		t++;
		
		if(t>7)
		{
			t=0;
			for(i=0;i<6;i++)
			{
				ADC_AVE[i]=ADC_SUM[i]/8;//取8次均值		
				ADC_SUM[i]=0;				
			}		
			sign_Adc1=1;
		}	
	}
}

u8 PowerOff_Flag=0;
void Power_Monitor(void)
{
	u8 i=0;
	for(i=0;i<6;i++)
		Voltage[i]=(float)(ADC_AVE[i]*3.3f/4095);//转换为电压值					
	
	Voltage[5]=(float)(Voltage[5]*43/10);//根据电阻的分压情况计算电池电压
	if(Voltage[5]<11.7f)
		PowerOff_Flag=1;
	
	for(i=1;i<5;i++)
		Current[i]=(float)((float)(Voltage[i-1]-2.5f)/0.04f);//各个电机电流
	Current[0]=Current[1]+Current[2]+Current[3]+Current[4];//总电流
	
	for(i=1;i<5;i++)
		Walte[i]=(float)(Voltage[5]*Current[i]);//电池电压乘以电流
	Walte[0]=Walte[1]+Walte[2]+Walte[3]+Walte[4];//发动机总功率
}	
#endif


