#include "H_define.h"


volatile u8	mpu9250_buf[20];		//spi读取MPU6000后存放数据
u8 	offset_flag = 0;						//校准模式标志位，为0未进行校准，为1进行校准

S_INT16_XYZ	MPU9250_Acc_Offset	=	{0,0,0};		
S_INT16_XYZ	MPU9250_Gyro_Offset	=	{0,0,0};	
S_INT16_XYZ MPU9250_Acc = {0,0,0};
S_INT16_XYZ MPU9250_Gyro = {0,0,0};
S_INT16_XYZ MPU9250_Magn = {0,0,0};

float	mpu9250_tempreature = 0;
s16 mpu9250_tempreature_temp = 0;
s16 mpu9250_tempreature_Offset = 0;

/*
 * 函数名: MPU9250_Date_Offset
 * 描述  ：函数用于向9250读取数据的初始化偏移值
 * 输入  ：需要求取多少个值的平均值的数量
 * 输出  ：无
 */ 
S_INT32_XYZ Temp_Gyro , Temp_Acc;
void MPU9250_Date_Offset1(u16 cnt)
{
	
	u16 i = 0;
	
	Temp_Gyro.X =	0;
	Temp_Gyro.Y =	0;
	Temp_Gyro.Z =	0;
	
	
	offset_flag = 1;//进入MPU6500校准模式
	for(i = cnt; i > 0; i--)
	{
	    delay_ms(1);
		MPU9250_ReadValue();
		Temp_Gyro.X	+=	MPU9250_Gyro.X;
		Temp_Gyro.Y	+=	MPU9250_Gyro.Y;
		Temp_Gyro.Z	+=	MPU9250_Gyro.Z;

	}
	
	MPU9250_Gyro_Offset.X	= Temp_Gyro.X	/	cnt;
	MPU9250_Gyro_Offset.Y	= Temp_Gyro.Y	/	cnt;
	MPU9250_Gyro_Offset.Z =	Temp_Gyro.Z	/	cnt;

	offset_flag = 0;//退出MPU9250校准模式
}

void MPU9250_Date_Offset2(u16 cnt)
{
	
	u16 i = 0;
	
	Temp_Acc.X = 0;
	Temp_Acc.Y = 0;
	Temp_Acc.Z = 0;
	
	offset_flag = 1;//进入MPU6500校准模式
	for(i = cnt; i > 0; i--)
	{
		delay_ms(1);
    MPU9250_ReadValue();
		
		Temp_Acc.X	+=	MPU9250_Acc.X;
		Temp_Acc.Y	+=	MPU9250_Acc.Y;		
		Temp_Acc.Z	+=	MPU9250_Acc.Z;


	}
	MPU9250_Acc_Offset.X 	=	Temp_Acc.X	/	cnt;
	MPU9250_Acc_Offset.Y 	=	Temp_Acc.Y	/	cnt;
	MPU9250_Acc_Offset.Z  =	Temp_Acc.Z	/	cnt;	
	offset_flag = 0;//退出MPU9250校准模式
}

/*
 * 函数名: MPU9250_ReadValue
 * 描述  ：函数用于向9250读取三轴加速度计和三轴陀螺仪的数据
 * 输入  ：无
 * 输出  ：无
 */ 
void MPU9250_ReadValue(void)
{
	uint8_t i;
	
	MPU9250_CS=0; 																//使能SPI传输
  
	SPI1_ReadWriteByte(ACCEL_XOUT_H|0x80); 				//从加速度计的寄存器开始进行读取陀螺仪和加速度计的值//发送读命令+寄存器号
	
	for(i	=	0;i	<	14;i++)													//一共读取14字节的数据
	{
		mpu9250_buf[i]	=	SPI1_ReadWriteByte(0xff);	//输入0xff,因为slave不识别
	}	
	
	if(offset_flag == 0)
	{
	  MPU9250_Acc.X = Byte16(s16, mpu9250_buf[0],  mpu9250_buf[1]) - MPU9250_Acc_Offset.X;
		MPU9250_Acc.Y = Byte16(s16, mpu9250_buf[2],  mpu9250_buf[3]) - MPU9250_Acc_Offset.Y;
		MPU9250_Acc.Z = Byte16(s16, mpu9250_buf[4],  mpu9250_buf[5]);
		MPU9250_Gyro.X = Byte16(s16, mpu9250_buf[8],  mpu9250_buf[9]) - MPU9250_Gyro_Offset.X;
		MPU9250_Gyro.Y = Byte16(s16, mpu9250_buf[10],  mpu9250_buf[11]) - MPU9250_Gyro_Offset.Y;
		MPU9250_Gyro.Z = Byte16(s16, mpu9250_buf[12],  mpu9250_buf[13]) - MPU9250_Gyro_Offset.Z;
//陀螺仪加死区                           
		if(( -3	<	MPU9250_Gyro.X ) && (MPU9250_Gyro.X < 3) ) MPU9250_Gyro.X = 0;
		if(( -3	<	MPU9250_Gyro.Y ) && (MPU9250_Gyro.Y < 3) ) MPU9250_Gyro.Y = 0;
		if(( -3	<	MPU9250_Gyro.Z ) && (MPU9250_Gyro.Z < 3) ) MPU9250_Gyro.Z = 0;
	}
	else if(offset_flag)  //MPU6000处于校准模式
	{
		MPU9250_Acc.X = Byte16(s16, mpu9250_buf[0],  mpu9250_buf[1]);
		MPU9250_Acc.Y = Byte16(s16, mpu9250_buf[2],  mpu9250_buf[3]);
		MPU9250_Acc.Z = Byte16(s16, mpu9250_buf[4],  mpu9250_buf[5]);
		MPU9250_Gyro.X = Byte16(s16, mpu9250_buf[8],  mpu9250_buf[9]);
		MPU9250_Gyro.Y = Byte16(s16, mpu9250_buf[10],  mpu9250_buf[11]);
		MPU9250_Gyro.Z = Byte16(s16, mpu9250_buf[12],  mpu9250_buf[13]);
	}
	MPU9250_CS=1;  		//禁止SPI传输
}

/*
 * 函数名: MPU9250_Init
 * 描述  ：用于初始化9250并完成量程等的配置
 * 输入  ：无
 * 输出  ：0：初始化失败 1：初始化成功
 */ 
u8	ID;
u8 MPU9250_Init(void)
{
	SPI1_Init();					
 	ID = MPU9250_Read_Reg(WHO_AM_I);
	if(ID == 0x73)													//正确读取到6000的地址
	{		
		MPU9250_Write_Reg(PWR_MGMT_1,0X00);   //电源管理,复位MPU6000
		delay_ms(10);
		MPU9250_Write_Reg(PWR_MGMT_1,0X01);   //选择时钟源
		delay_ms(10);
		MPU9250_Write_Reg(USER_CTRL,0X10);  	//设置为ＳＰＩ模式
		delay_ms(10);
		MPU9250_Write_Reg(PWR_MGMT_2,0X00);   //使能加速度计和陀螺仪
		delay_ms(100);
		MPU9250_Write_Reg(CONFIG,0X01);		//低通滤波器 0x06 92hz (3.9ms delay) fs=1khz
		delay_ms(10);
		MPU9250_Write_Reg(SMPLRT_DIV,0X00);		//采样率1000/(1+0)=1000HZ
		delay_ms(10);
		MPU9250_Write_Reg(GYRO_CONFIG,0X18);  //陀螺仪测量范围 0X18 正负2000度
		delay_ms(10);
		MPU9250_Write_Reg(ACCEL_CONFIG,0x10); //加速度计测量范围 0X00 正负8g
		delay_ms(10);
		MPU9250_Write_Reg(ACCEL_CONFIG2,0x00);//加速度计速率1khz 滤波器460hz (1.94ms delay)
		delay_ms(10);
		
		return 1;
	}
	else
		return 0;
}

/*
 * 函数名: SPI1_Init
 * 描述  ：初始化连接9250的spi1的IO口
 * 输入  ：无
 * 输出  ：无
 */ 
void SPI1_Init(void)
{
	
	RCC->APB2ENR|=1<<2;       //PORTA时钟使能 	 
	RCC->APB2ENR|=1<<12;      //SPI1时钟使能 
		   
	//这里只针对SPI口初始化
	GPIOA->CRL&=0X0000FFFF; 
	GPIOA->CRL|=0X00030000;//PA4推挽输出 	    
	GPIOA->CRL|=0XBBB00000;//PA5.6.7推挽复用输出 	    
	GPIOA->ODR|=0XF<<5;    //PA5.6.7上拉
	
	MPU9250_CS=1;		
	SPI1->CR1|=0<<6; //SPI设备禁用
	
	SPI1->CR1|=0<<10;//全双工模式	
	SPI1->CR1|=1<<9; //软件nss管理
	SPI1->CR1|=1<<8; //决定nss上的电平 /////////////////////////////////////////

	SPI1->CR1|=1<<2; //SPI主机
	SPI1->CR1|=0<<11;//8bit数据格式	
	SPI1->CR1|=1<<1; //空闲模式下SCK为1 CPOL=1
	SPI1->CR1|=1<<0; //数据采样从第2个时间边沿开始,CPHA=1  
	SPI1->CR1|=3<<3; //Fsck=Fcpu/16
	SPI1->CR1|=0<<7; //MSB   
	SPI1->CR1|=1<<13; //使能CRC校验	
	SPI1->CRCPR|=7; //CRC计算时用到的多项式
	
	SPI1->CR1|=1<<6; //SPI设备使能
	
	SPI1_ReadWriteByte(0xff);//启动传输(主要作用：维持MOSI为高)		 
}   

/*
 * 函数名: uint8_t MPU9250_Write_Reg
 * 描述  ：函数用于向9250的特定寄存器写入命令
 * 输入  ：寄存器的地址，命令
 * 输出  ：0：失败  1：成功
 */ 
u8 MPU9250_Write_Reg(uint8_t reg,uint8_t value)
{
	u8 status;
	MPU9250_CS=0;  //使能SPI传输
	status=SPI1_ReadWriteByte(reg); //发送写命令+寄存器号
	SPI1_ReadWriteByte(value);//写入寄存器值
	MPU9250_CS=1;  //禁止MPU9250
	return(status);//返回状态值
}

/*
 * 函数名: u8 MPU9250_Read_Reg
 * 描述  ：函数用于向9250读数据
 * 输入  ：寄存器的地址
 * 输出  ：从寄存器读得的数据
 */ 
u8 MPU9250_Read_Reg(uint8_t reg)
{
	u8 reg_val;
	MPU9250_CS=0;  //使能SPI传输
	SPI1_ReadWriteByte(reg|0x80); //发送读命令+寄存器号
									//9250寄存器地址最大是0x7E，与上0x80,防止出错
	reg_val=SPI1_ReadWriteByte(0xff);//读取寄存器值
	MPU9250_CS=1;  //禁止MPU9250
	return(reg_val);
}

/*
 * 函数名: u8 SPI1_ReadWriteByte
 * 描述  ：函数用于向9250读写数据
 * 输入  ：寄存器的地址
 * 输出  ：从寄存器读得的数据或者失败返回0
 */ 
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

