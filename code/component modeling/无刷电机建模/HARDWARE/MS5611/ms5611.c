#include "ms5611.h"
#include "ms5611_spi.h"
#include "delay.h"
#include "math.h"

s32 ref_pressure;//参考气压
s32 ref_altitude;//参考海拔

MS5611_DATA MS5611_Date = {0};

/*
 * 函数名: MS5611_Init
 * 描述  ：用于初始化MS5611
 * 输入  ：无
 * 输出  ：无
 */ 
void MS5611_Init(void)
{
	SPI2_Init();
	Delay_Ms(5);
	MS5611_CS(0);  //使能MS5611的SPI传输
  SPI2_ReadWriteByte(MS5611_RESET);
	Delay_Ms(5);
	MS5611_CS(1);  //失能MS5611的SPI传输
	MS5611_PROM_READ();
	MS5611_Altitude_Offset(100);
}

/*
 * 函数名: MS5611_PROM_READ
 * 描述  ：从PROM读取出厂校准数据
 * 输入  ：无
 * 输出  ：无
 */ 
void MS5611_PROM_READ(void)
{
  MS5611_Date.C1 = SPI2_ReadWrite_16bits(MS5611_PROM_COEFF_1);
  MS5611_Date.C2 = SPI2_ReadWrite_16bits(MS5611_PROM_COEFF_2);
  MS5611_Date.C3 = SPI2_ReadWrite_16bits(MS5611_PROM_COEFF_3);
  MS5611_Date.C4 = SPI2_ReadWrite_16bits(MS5611_PROM_COEFF_4);
  MS5611_Date.C5 = SPI2_ReadWrite_16bits(MS5611_PROM_COEFF_5);
  MS5611_Date.C6 = SPI2_ReadWrite_16bits(MS5611_PROM_COEFF_6); 
}


/*
 * 函数名: MS5611_getPressure
 * 描述  ：通过MS5611模块得到气压值
 * 输入  ：气压分辨率系数
 * 输出  ：无
 */ 

void MS5611_PressureADC_Conversion(void)
{
	MS5611_CS(0);  //使能MS5611的SPI传输 
  SPI2_ReadWriteByte(MS5611_D1_OSR_4096);
	MS5611_CS(1);  //失能MS5611的SPI传输	
}

void MS5611_Pressure_Calculate(void)
{
  MS5611_Date.D1 = MS5611_SPI_read_ADC();//获得气压值
  MS5611_Date.P = (MS5611_Date.D1 * MS5611_Date.SENS / 2097152 - MS5611_Date.OFF) / 32768;
}


void MS5611_TemperatureADC_Conversion(void)
{
	MS5611_CS(0);  //使能MS5611的SPI传输 
  SPI2_ReadWriteByte(MS5611_D2_OSR_4096);
	MS5611_CS(1);  //失能MS5611的SPI传输	
}

/*
 * 函数名: MS5611_getTemperature
 * 描述  ：通过MS5611模块得到温度值
 * 输入  ：温度分辨率系数
 * 输出  ：无
 */ 


void MS5611_Temperature_Calculate(void)    
{
  MS5611_Date.D2 = MS5611_SPI_read_ADC();	
  MS5611_Date.dT = MS5611_Date.D2 - (((u32)MS5611_Date.C5) << 8);
  MS5611_Date.TEMP = 2000 + MS5611_Date.dT * MS5611_Date.C6 / 8388608;
	MS5611_Temp_Compensation();
	//MS5611_SecondOrder_Temp_Compensation();
}

//MS5611二阶温度补偿
void MS5611_SecondOrder_Temp_Compensation(void)    
{
	double temp;
	
	MS5611_Date.OFF = (u32)MS5611_Date.C2 * 65536 + ((u32)MS5611_Date.C4 * MS5611_Date.dT) / 128;
  MS5611_Date.SENS = (u32)MS5611_Date.C1 * 32768 + ((u32)MS5611_Date.C3 * MS5611_Date.dT) / 256;
	
	if(MS5611_Date.TEMP < 2000)//如果MS5611温度小于20摄氏度
	{
		MS5611_Date.TEMP2 = (MS5611_Date.dT * MS5611_Date.dT) / 2147483648U;
		temp = (MS5611_Date.TEMP - 2000)^2;
		MS5611_Date.OFF2 = 2.5 * temp;//OFF2 = 5 * (TEMP – 2000)^2 / 2
		MS5611_Date.SENS2 = 1.25 * temp;//SENS2 = 5 * (TEMP – 2000)^2/ 2
		
		if(MS5611_Date.TEMP < -1500)//如果MS5611温度小于-15摄氏度
		{
			temp = (MS5611_Date.TEMP + 1500)^2;
			MS5611_Date.OFF2 += 7 * temp;
			MS5611_Date.SENS2 += 5.5 * temp;
		}
	}
	else//如果MS5611温度大于20摄氏度
	{
		MS5611_Date.TEMP2 = 0;
		MS5611_Date.OFF2 = 0;
		MS5611_Date.SENS2 = 0;
	}
 
	MS5611_Date.TEMP = MS5611_Date.TEMP - MS5611_Date.TEMP2;
	MS5611_Date.OFF -= MS5611_Date.OFF2;
	MS5611_Date.SENS -= MS5611_Date.SENS2;
}

void MS5611_Temp_Compensation(void)    
{
	MS5611_Date.OFF = (u32)MS5611_Date.C2 * 65536 + ((u32)MS5611_Date.C4 * MS5611_Date.dT) / 128;
  MS5611_Date.SENS = (u32)MS5611_Date.C1 * 32768 + ((u32)MS5611_Date.C3 * MS5611_Date.dT) / 256;
	
}
/*
 * 函数名: MS5611_Altitude_Calculate
 * 描述  ：根据大气压算出海拔高?
 * 输入  ：无
 * 输出  ：海拔高度
 */ 

float altitude; 

float MS5611_Altitude_Calculate(void)                             
{      
  altitude = 44330 * (1 - pow((MS5611_Date.P) / 101325.0, 0.190295));
 // height = (altitude - ref_altitude) * 100;
	//height = 10*(ref_pressure-MS5611_Date.P);//单位厘米	
	return (altitude);
}


void MS5611_Altitude_Offset(u16 cnt)                             
{
	static double temp;
	u16 i = 0;
	
  for(i = cnt; i > 0; i--)
	{
		MS5611_TemperatureADC_Conversion();
		Delay_Ms(12);
		MS5611_Temperature_Calculate();
		MS5611_PressureADC_Conversion();
		Delay_Ms(12);
		MS5611_Pressure_Calculate();
		
		temp += MS5611_Date.P;
	}	
		
  ref_pressure = temp / cnt;
	ref_altitude = 44330 * (1 - pow((ref_pressure) / 101325.0, 0.190295));
}


/*
 * 函数名: get_height
 * 描述  ：近似的计算高度
 * 输入  ：无
 * 输出  ：相对初始地面的近似高度值
 */ 
#define  filter_num 25//定义的滑动窗口的大小

float ms5611[filter_num]={0};
static u8 filter_cnt=0;
float Vz=0;
float height_last;
float get_height()//要减去初始值
{    
		 	u8 i;
	    float height;//作为返回值，返回高度数据，单位为cm
	    float  height_final;
      float sum;//气压值的初始值
      height=10*(ref_pressure-MS5611_Date.P);//单位厘米	
	    ms5611[filter_cnt]=height;
	    filter_cnt++;
	
	    for(i=0;i<filter_num;i++)
	    {
			   sum+=ms5611[i];
			}

			height_final=sum/filter_num;//滑动均值
			sum=0;
			 Vz=((height_final-height_last));
			height_last=height_final;
			if( filter_cnt==filter_num)
				filter_cnt=0;
			return  height_final;
}


/*
 * 函数名: SPI2_Init
 * 描述  ：用于初始化连接ms5611的spi接口
 * 输入  ：无
 * 输出  ：无
 */ 
void SPI2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); //使能SPI1时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //狹PU9250片选信号
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;         //上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);     //初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                             //复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                           //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                                       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                             //上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);                                         //初始化   
	
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);  
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);  
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);  
	//这里只针对SPI口初始化
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,ENABLE);  //复位SPI2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,DISABLE); //停止复位SPI2

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                    //设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                //设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//时钟悬空低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                 //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                        //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//42M/128=328.125KHZ定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	                          //CRC值计算的多项式
	SPI_Init(SPI2, &SPI_InitStructure);                                 //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI2, ENABLE);   //使能SPI外设

	SPI2_ReadWriteByte(0xff);//启动传输		 	 

}

/*
 * 函数名: uint8_t MS5611_Write_Reg
 * 描述  ：用于写单个寄存器的值
 * 输入  ：无
 * 输出  ：status：返回状态值
 */ 
uint8_t MS5611_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;
	MS5611_CS(0);  //使能SPI传输
	SPI2_ReadWriteByte(reg); //发送写命令+寄存器号
	SPI2_ReadWriteByte(value);//写入寄存器值
	MS5611_CS(1);  //禁止MPU9250
	return(status);//返回状态值
}


/*
 * 函数名: MS5611_Read_Reg
 * 描述  ：用于写单个寄存器的值
 * 输入  ：无
 * 输出  ：status：返回状态值
 */ 
uint8_t MS5611_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;
	MS5611_CS(0);  //使能SPI传输
	SPI2_ReadWriteByte(reg|0x80); //发送读命令+寄存器号
	reg_val=SPI2_ReadWriteByte(0xff);//读取寄存器值
	MS5611_CS(1);  //禁止MPU9250
	return(reg_val);
}

/*
 * 函数名: uint8_t SPI2_ReadWriteByte
 * 描述  ：函数用于向ms5611读写数据
 * 输入  ：寄存器的地址
 * 输出  ：从寄存器读得的数据或者失败返回0
 */ 
uint8_t SPI2_ReadWriteByte(uint8_t TxData)
{		
	uint8_t retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据					    
}

/*
 * 函数名: u16  SPI2_ReadWrite_16bits
 * 描述  ：SPI2 读写两个字节
 * 输入  ：地址
 * 输出  ：读取到的16位数据
 */ 

u16  SPI2_ReadWrite_16bits(unsigned char addr)
{
  unsigned char byteH,byteL;
  unsigned int return_value;
	
  MS5611_CS(0);  //使能SPI传输 
  SPI2_ReadWriteByte(addr);
  byteH = SPI2_ReadWriteByte(0);
  byteL = SPI2_ReadWriteByte(0);
  MS5611_CS(1);  //禁止MPU9250
  return_value = ((unsigned int)byteH<<8) | (byteL);
	
  return(return_value);    
}

/*
 * 函数名: long MS5611_SPI_read_ADC
 * 描述  ：函数用于向ms5611温度原始数据或者气压原始数据
 * 输入  ：无
 * 输出  ：读回的数据
 */ 
long MS5611_SPI_read_ADC(void)
{
  unsigned char byteH,byteM,byteL;
  long return_value;
  
  MS5611_CS(0);  //使能SPI传输 
  SPI2_ReadWriteByte(MS5611_ADC_READ);
  byteH = SPI2_ReadWriteByte(0);
  byteM = SPI2_ReadWriteByte(0);
  byteL = SPI2_ReadWriteByte(0);
  MS5611_CS(1);  //使能SPI传输 
  return_value = (((long)byteH)<<16) | (((long)byteM)<<8) | (byteL);
  return(return_value);
}



