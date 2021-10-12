#include "ms5611.h"
#include "ms5611_spi.h"
#include "delay.h"
#include "math.h"

s32 ref_pressure;//�ο���ѹ
s32 ref_altitude;//�ο�����

MS5611_DATA MS5611_Date = {0};

/*
 * ������: MS5611_Init
 * ����  �����ڳ�ʼ��MS5611
 * ����  ����
 * ���  ����
 */ 
void MS5611_Init(void)
{
	SPI2_Init();
	Delay_Ms(5);
	MS5611_CS(0);  //ʹ��MS5611��SPI����
  SPI2_ReadWriteByte(MS5611_RESET);
	Delay_Ms(5);
	MS5611_CS(1);  //ʧ��MS5611��SPI����
	MS5611_PROM_READ();
	MS5611_Altitude_Offset(100);
}

/*
 * ������: MS5611_PROM_READ
 * ����  ����PROM��ȡ����У׼����
 * ����  ����
 * ���  ����
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
 * ������: MS5611_getPressure
 * ����  ��ͨ��MS5611ģ��õ���ѹֵ
 * ����  ����ѹ�ֱ���ϵ��
 * ���  ����
 */ 

void MS5611_PressureADC_Conversion(void)
{
	MS5611_CS(0);  //ʹ��MS5611��SPI���� 
  SPI2_ReadWriteByte(MS5611_D1_OSR_4096);
	MS5611_CS(1);  //ʧ��MS5611��SPI����	
}

void MS5611_Pressure_Calculate(void)
{
  MS5611_Date.D1 = MS5611_SPI_read_ADC();//�����ѹֵ
  MS5611_Date.P = (MS5611_Date.D1 * MS5611_Date.SENS / 2097152 - MS5611_Date.OFF) / 32768;
}


void MS5611_TemperatureADC_Conversion(void)
{
	MS5611_CS(0);  //ʹ��MS5611��SPI���� 
  SPI2_ReadWriteByte(MS5611_D2_OSR_4096);
	MS5611_CS(1);  //ʧ��MS5611��SPI����	
}

/*
 * ������: MS5611_getTemperature
 * ����  ��ͨ��MS5611ģ��õ��¶�ֵ
 * ����  ���¶ȷֱ���ϵ��
 * ���  ����
 */ 


void MS5611_Temperature_Calculate(void)    
{
  MS5611_Date.D2 = MS5611_SPI_read_ADC();	
  MS5611_Date.dT = MS5611_Date.D2 - (((u32)MS5611_Date.C5) << 8);
  MS5611_Date.TEMP = 2000 + MS5611_Date.dT * MS5611_Date.C6 / 8388608;
	MS5611_Temp_Compensation();
	//MS5611_SecondOrder_Temp_Compensation();
}

//MS5611�����¶Ȳ���
void MS5611_SecondOrder_Temp_Compensation(void)    
{
	double temp;
	
	MS5611_Date.OFF = (u32)MS5611_Date.C2 * 65536 + ((u32)MS5611_Date.C4 * MS5611_Date.dT) / 128;
  MS5611_Date.SENS = (u32)MS5611_Date.C1 * 32768 + ((u32)MS5611_Date.C3 * MS5611_Date.dT) / 256;
	
	if(MS5611_Date.TEMP < 2000)//���MS5611�¶�С��20���϶�
	{
		MS5611_Date.TEMP2 = (MS5611_Date.dT * MS5611_Date.dT) / 2147483648U;
		temp = (MS5611_Date.TEMP - 2000)^2;
		MS5611_Date.OFF2 = 2.5 * temp;//OFF2 = 5 * (TEMP �C 2000)^2 / 2
		MS5611_Date.SENS2 = 1.25 * temp;//SENS2 = 5 * (TEMP �C 2000)^2/ 2
		
		if(MS5611_Date.TEMP < -1500)//���MS5611�¶�С��-15���϶�
		{
			temp = (MS5611_Date.TEMP + 1500)^2;
			MS5611_Date.OFF2 += 7 * temp;
			MS5611_Date.SENS2 += 5.5 * temp;
		}
	}
	else//���MS5611�¶ȴ���20���϶�
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
 * ������: MS5611_Altitude_Calculate
 * ����  �����ݴ���ѹ������θ�?
 * ����  ����
 * ���  �����θ߶�
 */ 

float altitude; 

float MS5611_Altitude_Calculate(void)                             
{      
  altitude = 44330 * (1 - pow((MS5611_Date.P) / 101325.0, 0.190295));
 // height = (altitude - ref_altitude) * 100;
	//height = 10*(ref_pressure-MS5611_Date.P);//��λ����	
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
 * ������: get_height
 * ����  �����Ƶļ���߶�
 * ����  ����
 * ���  ����Գ�ʼ����Ľ��Ƹ߶�ֵ
 */ 
#define  filter_num 25//����Ļ������ڵĴ�С

float ms5611[filter_num]={0};
static u8 filter_cnt=0;
float Vz=0;
float height_last;
float get_height()//Ҫ��ȥ��ʼֵ
{    
		 	u8 i;
	    float height;//��Ϊ����ֵ�����ظ߶����ݣ���λΪcm
	    float  height_final;
      float sum;//��ѹֵ�ĳ�ʼֵ
      height=10*(ref_pressure-MS5611_Date.P);//��λ����	
	    ms5611[filter_cnt]=height;
	    filter_cnt++;
	
	    for(i=0;i<filter_num;i++)
	    {
			   sum+=ms5611[i];
			}

			height_final=sum/filter_num;//������ֵ
			sum=0;
			 Vz=((height_final-height_last));
			height_last=height_final;
			if( filter_cnt==filter_num)
				filter_cnt=0;
			return  height_final;
}


/*
 * ������: SPI2_Init
 * ����  �����ڳ�ʼ������ms5611��spi�ӿ�
 * ����  ����
 * ���  ����
 */ 
void SPI2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); //ʹ��SPI1ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //�MPU9250Ƭѡ�ź�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;         //����
  GPIO_Init(GPIOB, &GPIO_InitStructure);     //��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                                             //���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                                       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                             //����
  GPIO_Init(GPIOB, &GPIO_InitStructure);                                         //��ʼ��   
	
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_SPI2);  
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);  
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);  
	//����ֻ���SPI�ڳ�ʼ��
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,ENABLE);  //��λSPI2
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,DISABLE); //ֹͣ��λSPI2

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                    //����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//ʱ�����յ�
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                 //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                        //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//42M/128=328.125KHZ���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	                          //CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);                                 //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI2, ENABLE);   //ʹ��SPI����

	SPI2_ReadWriteByte(0xff);//��������		 	 

}

/*
 * ������: uint8_t MS5611_Write_Reg
 * ����  ������д�����Ĵ�����ֵ
 * ����  ����
 * ���  ��status������״ֵ̬
 */ 
uint8_t MS5611_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;
	MS5611_CS(0);  //ʹ��SPI����
	SPI2_ReadWriteByte(reg); //����д����+�Ĵ�����
	SPI2_ReadWriteByte(value);//д��Ĵ���ֵ
	MS5611_CS(1);  //��ֹMPU9250
	return(status);//����״ֵ̬
}


/*
 * ������: MS5611_Read_Reg
 * ����  ������д�����Ĵ�����ֵ
 * ����  ����
 * ���  ��status������״ֵ̬
 */ 
uint8_t MS5611_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;
	MS5611_CS(0);  //ʹ��SPI����
	SPI2_ReadWriteByte(reg|0x80); //���Ͷ�����+�Ĵ�����
	reg_val=SPI2_ReadWriteByte(0xff);//��ȡ�Ĵ���ֵ
	MS5611_CS(1);  //��ֹMPU9250
	return(reg_val);
}

/*
 * ������: uint8_t SPI2_ReadWriteByte
 * ����  ������������ms5611��д����
 * ����  ���Ĵ����ĵ�ַ
 * ���  ���ӼĴ������õ����ݻ���ʧ�ܷ���0
 */ 
uint8_t SPI2_ReadWriteByte(uint8_t TxData)
{		
	uint8_t retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
}

/*
 * ������: u16  SPI2_ReadWrite_16bits
 * ����  ��SPI2 ��д�����ֽ�
 * ����  ����ַ
 * ���  ����ȡ����16λ����
 */ 

u16  SPI2_ReadWrite_16bits(unsigned char addr)
{
  unsigned char byteH,byteL;
  unsigned int return_value;
	
  MS5611_CS(0);  //ʹ��SPI���� 
  SPI2_ReadWriteByte(addr);
  byteH = SPI2_ReadWriteByte(0);
  byteL = SPI2_ReadWriteByte(0);
  MS5611_CS(1);  //��ֹMPU9250
  return_value = ((unsigned int)byteH<<8) | (byteL);
	
  return(return_value);    
}

/*
 * ������: long MS5611_SPI_read_ADC
 * ����  ������������ms5611�¶�ԭʼ���ݻ�����ѹԭʼ����
 * ����  ����
 * ���  �����ص�����
 */ 
long MS5611_SPI_read_ADC(void)
{
  unsigned char byteH,byteM,byteL;
  long return_value;
  
  MS5611_CS(0);  //ʹ��SPI���� 
  SPI2_ReadWriteByte(MS5611_ADC_READ);
  byteH = SPI2_ReadWriteByte(0);
  byteM = SPI2_ReadWriteByte(0);
  byteL = SPI2_ReadWriteByte(0);
  MS5611_CS(1);  //ʹ��SPI���� 
  return_value = (((long)byteH)<<16) | (((long)byteM)<<8) | (byteL);
  return(return_value);
}



