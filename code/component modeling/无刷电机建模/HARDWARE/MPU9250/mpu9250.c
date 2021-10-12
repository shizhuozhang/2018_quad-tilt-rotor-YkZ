#include "H_define.h"


volatile u8	mpu9250_buf[20];		//spi��ȡMPU6000��������
u8 	offset_flag = 0;						//У׼ģʽ��־λ��Ϊ0δ����У׼��Ϊ1����У׼

S_INT16_XYZ	MPU9250_Acc_Offset	=	{0,0,0};		
S_INT16_XYZ	MPU9250_Gyro_Offset	=	{0,0,0};	
S_INT16_XYZ MPU9250_Acc = {0,0,0};
S_INT16_XYZ MPU9250_Gyro = {0,0,0};
S_INT16_XYZ MPU9250_Magn = {0,0,0};

float	mpu9250_tempreature = 0;
s16 mpu9250_tempreature_temp = 0;
s16 mpu9250_tempreature_Offset = 0;

/*
 * ������: MPU9250_Date_Offset
 * ����  ������������9250��ȡ���ݵĳ�ʼ��ƫ��ֵ
 * ����  ����Ҫ��ȡ���ٸ�ֵ��ƽ��ֵ������
 * ���  ����
 */ 
S_INT32_XYZ Temp_Gyro , Temp_Acc;
void MPU9250_Date_Offset1(u16 cnt)
{
	
	u16 i = 0;
	
	Temp_Gyro.X =	0;
	Temp_Gyro.Y =	0;
	Temp_Gyro.Z =	0;
	
	
	offset_flag = 1;//����MPU6500У׼ģʽ
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

	offset_flag = 0;//�˳�MPU9250У׼ģʽ
}

void MPU9250_Date_Offset2(u16 cnt)
{
	
	u16 i = 0;
	
	Temp_Acc.X = 0;
	Temp_Acc.Y = 0;
	Temp_Acc.Z = 0;
	
	offset_flag = 1;//����MPU6500У׼ģʽ
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
	offset_flag = 0;//�˳�MPU9250У׼ģʽ
}

/*
 * ������: MPU9250_ReadValue
 * ����  ������������9250��ȡ������ٶȼƺ����������ǵ�����
 * ����  ����
 * ���  ����
 */ 
void MPU9250_ReadValue(void)
{
	uint8_t i;
	
	MPU9250_CS=0; 																//ʹ��SPI����
  
	SPI1_ReadWriteByte(ACCEL_XOUT_H|0x80); 				//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ//���Ͷ�����+�Ĵ�����
	
	for(i	=	0;i	<	14;i++)													//һ����ȡ14�ֽڵ�����
	{
		mpu9250_buf[i]	=	SPI1_ReadWriteByte(0xff);	//����0xff,��Ϊslave��ʶ��
	}	
	
	if(offset_flag == 0)
	{
	  MPU9250_Acc.X = Byte16(s16, mpu9250_buf[0],  mpu9250_buf[1]) - MPU9250_Acc_Offset.X;
		MPU9250_Acc.Y = Byte16(s16, mpu9250_buf[2],  mpu9250_buf[3]) - MPU9250_Acc_Offset.Y;
		MPU9250_Acc.Z = Byte16(s16, mpu9250_buf[4],  mpu9250_buf[5]);
		MPU9250_Gyro.X = Byte16(s16, mpu9250_buf[8],  mpu9250_buf[9]) - MPU9250_Gyro_Offset.X;
		MPU9250_Gyro.Y = Byte16(s16, mpu9250_buf[10],  mpu9250_buf[11]) - MPU9250_Gyro_Offset.Y;
		MPU9250_Gyro.Z = Byte16(s16, mpu9250_buf[12],  mpu9250_buf[13]) - MPU9250_Gyro_Offset.Z;
//�����Ǽ�����                           
		if(( -3	<	MPU9250_Gyro.X ) && (MPU9250_Gyro.X < 3) ) MPU9250_Gyro.X = 0;
		if(( -3	<	MPU9250_Gyro.Y ) && (MPU9250_Gyro.Y < 3) ) MPU9250_Gyro.Y = 0;
		if(( -3	<	MPU9250_Gyro.Z ) && (MPU9250_Gyro.Z < 3) ) MPU9250_Gyro.Z = 0;
	}
	else if(offset_flag)  //MPU6000����У׼ģʽ
	{
		MPU9250_Acc.X = Byte16(s16, mpu9250_buf[0],  mpu9250_buf[1]);
		MPU9250_Acc.Y = Byte16(s16, mpu9250_buf[2],  mpu9250_buf[3]);
		MPU9250_Acc.Z = Byte16(s16, mpu9250_buf[4],  mpu9250_buf[5]);
		MPU9250_Gyro.X = Byte16(s16, mpu9250_buf[8],  mpu9250_buf[9]);
		MPU9250_Gyro.Y = Byte16(s16, mpu9250_buf[10],  mpu9250_buf[11]);
		MPU9250_Gyro.Z = Byte16(s16, mpu9250_buf[12],  mpu9250_buf[13]);
	}
	MPU9250_CS=1;  		//��ֹSPI����
}

/*
 * ������: MPU9250_Init
 * ����  �����ڳ�ʼ��9250��������̵ȵ�����
 * ����  ����
 * ���  ��0����ʼ��ʧ�� 1����ʼ���ɹ�
 */ 
u8	ID;
u8 MPU9250_Init(void)
{
	SPI1_Init();					
 	ID = MPU9250_Read_Reg(WHO_AM_I);
	if(ID == 0x73)													//��ȷ��ȡ��6000�ĵ�ַ
	{		
		MPU9250_Write_Reg(PWR_MGMT_1,0X00);   //��Դ����,��λMPU6000
		delay_ms(10);
		MPU9250_Write_Reg(PWR_MGMT_1,0X01);   //ѡ��ʱ��Դ
		delay_ms(10);
		MPU9250_Write_Reg(USER_CTRL,0X10);  	//����Ϊ�ӣУ�ģʽ
		delay_ms(10);
		MPU9250_Write_Reg(PWR_MGMT_2,0X00);   //ʹ�ܼ��ٶȼƺ�������
		delay_ms(100);
		MPU9250_Write_Reg(CONFIG,0X01);		//��ͨ�˲��� 0x06 92hz (3.9ms delay) fs=1khz
		delay_ms(10);
		MPU9250_Write_Reg(SMPLRT_DIV,0X00);		//������1000/(1+0)=1000HZ
		delay_ms(10);
		MPU9250_Write_Reg(GYRO_CONFIG,0X18);  //�����ǲ�����Χ 0X18 ����2000��
		delay_ms(10);
		MPU9250_Write_Reg(ACCEL_CONFIG,0x10); //���ٶȼƲ�����Χ 0X00 ����8g
		delay_ms(10);
		MPU9250_Write_Reg(ACCEL_CONFIG2,0x00);//���ٶȼ�����1khz �˲���460hz (1.94ms delay)
		delay_ms(10);
		
		return 1;
	}
	else
		return 0;
}

/*
 * ������: SPI1_Init
 * ����  ����ʼ������9250��spi1��IO��
 * ����  ����
 * ���  ����
 */ 
void SPI1_Init(void)
{
	
	RCC->APB2ENR|=1<<2;       //PORTAʱ��ʹ�� 	 
	RCC->APB2ENR|=1<<12;      //SPI1ʱ��ʹ�� 
		   
	//����ֻ���SPI�ڳ�ʼ��
	GPIOA->CRL&=0X0000FFFF; 
	GPIOA->CRL|=0X00030000;//PA4������� 	    
	GPIOA->CRL|=0XBBB00000;//PA5.6.7���츴����� 	    
	GPIOA->ODR|=0XF<<5;    //PA5.6.7����
	
	MPU9250_CS=1;		
	SPI1->CR1|=0<<6; //SPI�豸����
	
	SPI1->CR1|=0<<10;//ȫ˫��ģʽ	
	SPI1->CR1|=1<<9; //���nss����
	SPI1->CR1|=1<<8; //����nss�ϵĵ�ƽ /////////////////////////////////////////

	SPI1->CR1|=1<<2; //SPI����
	SPI1->CR1|=0<<11;//8bit���ݸ�ʽ	
	SPI1->CR1|=1<<1; //����ģʽ��SCKΪ1 CPOL=1
	SPI1->CR1|=1<<0; //���ݲ����ӵ�2��ʱ����ؿ�ʼ,CPHA=1  
	SPI1->CR1|=3<<3; //Fsck=Fcpu/16
	SPI1->CR1|=0<<7; //MSB   
	SPI1->CR1|=1<<13; //ʹ��CRCУ��	
	SPI1->CRCPR|=7; //CRC����ʱ�õ��Ķ���ʽ
	
	SPI1->CR1|=1<<6; //SPI�豸ʹ��
	
	SPI1_ReadWriteByte(0xff);//��������(��Ҫ���ã�ά��MOSIΪ��)		 
}   

/*
 * ������: uint8_t MPU9250_Write_Reg
 * ����  ������������9250���ض��Ĵ���д������
 * ����  ���Ĵ����ĵ�ַ������
 * ���  ��0��ʧ��  1���ɹ�
 */ 
u8 MPU9250_Write_Reg(uint8_t reg,uint8_t value)
{
	u8 status;
	MPU9250_CS=0;  //ʹ��SPI����
	status=SPI1_ReadWriteByte(reg); //����д����+�Ĵ�����
	SPI1_ReadWriteByte(value);//д��Ĵ���ֵ
	MPU9250_CS=1;  //��ֹMPU9250
	return(status);//����״ֵ̬
}

/*
 * ������: u8 MPU9250_Read_Reg
 * ����  ������������9250������
 * ����  ���Ĵ����ĵ�ַ
 * ���  ���ӼĴ������õ�����
 */ 
u8 MPU9250_Read_Reg(uint8_t reg)
{
	u8 reg_val;
	MPU9250_CS=0;  //ʹ��SPI����
	SPI1_ReadWriteByte(reg|0x80); //���Ͷ�����+�Ĵ�����
									//9250�Ĵ�����ַ�����0x7E������0x80,��ֹ����
	reg_val=SPI1_ReadWriteByte(0xff);//��ȡ�Ĵ���ֵ
	MPU9250_CS=1;  //��ֹMPU9250
	return(reg_val);
}

/*
 * ������: u8 SPI1_ReadWriteByte
 * ����  ������������9250��д����
 * ����  ���Ĵ����ĵ�ַ
 * ���  ���ӼĴ������õ����ݻ���ʧ�ܷ���0
 */ 
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u16 retry=0;				 
	while((SPI1->SR&1<<1)==0)//�ȴ���������	
	{
		retry++;
		if(retry>0XFFFE)return 0;
	}			  
	SPI1->DR=TxData;	 	  //����һ��byte 
	retry=0;
	while((SPI1->SR&1<<0)==0) //�ȴ�������һ��byte  
	{
		retry++;
		if(retry>0XFFFE)return 0;
	}	  						    
	return SPI1->DR;          //�����յ�������				    
}

