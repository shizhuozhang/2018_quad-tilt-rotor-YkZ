#include "H_define.h"

u8	mpu6500_buf[14];					//spi��ȡMPU6500��������
u8 offset_flag = 0;						//У׼ģʽ��־λ��Ϊ0δ����У׼��Ϊ1����У׼

S_INT16_XYZ	MPU6500_Acc_Offset	=	{0,0,0};		
S_INT16_XYZ	MPU6500_Gyro_Offset	=	{0,0,0};	
S_INT16_XYZ MPU6500_Acc = {0,0,0};
S_INT16_XYZ MPU6500_Gyro = {0,0,0};

float	mpu6500_tempreature = 0;
s16 mpu6500_tempreature_temp = 0;
s16 mpu6500_tempreature_Offset = 0;

/*
 * ��������MPU6500_Date_Offset
 * ����  ��MPU6500����У׼
 * ����  ��У׼����
 * ���  ����
 */ 
void MPU6500_Date_Offset(u16 cnt)
{
	static S_INT32_XYZ Temp_Gyro , Temp_Acc;
	int i = 0;
	
	Temp_Gyro.X =	0;
	Temp_Gyro.Y =	0;
	Temp_Gyro.Z =	0;
	
	Temp_Acc.X = 0;
	Temp_Acc.Y = 0;
	Temp_Acc.Z = 0;
	
	offset_flag = 1;//����MPU6500У׼ģʽ
	for(i = cnt; i > 0; i--)
	{
    MPU6500_ReadValue();
		
		Temp_Acc.X	+=	MPU6500_Acc.X;
		Temp_Acc.Y	+=	MPU6500_Acc.Y;		
		//Temp_Acc.Z	+=	MPU6500_Acc.Z;
		Temp_Gyro.X	+=	MPU6500_Gyro.X;
		Temp_Gyro.Y	+=	MPU6500_Gyro.Y;
		Temp_Gyro.Z	+=	MPU6500_Gyro.Z;

	}
	
	MPU6500_Acc_Offset.X 	=	Temp_Acc.X	/	cnt;
	MPU6500_Acc_Offset.Y 	=	Temp_Acc.Y	/	cnt;
	//MPU6500_Acc_Offset.Z  =	Temp_Acc.Z	/	cnt;	
	MPU6500_Gyro_Offset.X	= Temp_Gyro.X	/	cnt;
	MPU6500_Gyro_Offset.Y	= Temp_Gyro.Y	/	cnt;
	MPU6500_Gyro_Offset.Z =	Temp_Gyro.Z	/	cnt;

	offset_flag = 0;//�˳�MPU6500У׼ģʽ
}


/*
 * ��������MPU6500_ReadValue
 * ����  ����ȡMPU6500ԭʼ����
 * ����  ����
 * ���  ����
 */ 
void MPU6500_ReadValue(void)
{
	uint8_t i;
	
	MPU6500_CS=0; 																	//ʹ��SPI����

	SPI1_Read_Write_Byte(ACCEL_XOUT_H|0x80); 				//�Ӽ��ٶȼƵļĴ�����ʼ���ж�ȡ�����Ǻͼ��ٶȼƵ�ֵ//���Ͷ�����+�Ĵ�����
	
	for(i	=	0;i	<	14;i++)														//һ����ȡ14�ֽڵ�����
	{
		mpu6500_buf[i]	=	SPI1_Read_Write_Byte(0xff);	//����0xff,��Ϊslave��ʶ��
	}	
	if(offset_flag == 0)
	{
		MPU6500_Acc.X = BYTE16(s16, mpu6500_buf[0],  mpu6500_buf[1]) - MPU6500_Acc_Offset.X;
		MPU6500_Acc.Y = BYTE16(s16, mpu6500_buf[2],  mpu6500_buf[3]) - MPU6500_Acc_Offset.Y;
		MPU6500_Acc.Z = BYTE16(s16, mpu6500_buf[4],  mpu6500_buf[5]);
		MPU6500_Gyro.X = BYTE16(s16, mpu6500_buf[8],  mpu6500_buf[9]) - MPU6500_Gyro_Offset.X;
		MPU6500_Gyro.Y = BYTE16(s16, mpu6500_buf[10],  mpu6500_buf[11]) - MPU6500_Gyro_Offset.Y;
		MPU6500_Gyro.Z = BYTE16(s16, mpu6500_buf[12],  mpu6500_buf[13]) - MPU6500_Gyro_Offset.Z;
		
		mpu6500_tempreature_temp	=	BYTE16(s16, mpu6500_buf[6],  mpu6500_buf[7]);
		mpu6500_tempreature	=	(float)(35000+((521+mpu6500_tempreature_temp)*100)/34); // ԭ����ĸΪ340�����ڷ���*100����������1000����
		mpu6500_tempreature = mpu6500_tempreature/1000;                             
		if(( -4	<	MPU6500_Gyro.X ) && (MPU6500_Gyro.X < 4) ) MPU6500_Gyro.X = 0;
		if(( -4	<	MPU6500_Gyro.Y ) && (MPU6500_Gyro.Y < 4) ) MPU6500_Gyro.Y = 0;
		if(( -4	<	MPU6500_Gyro.Z ) && (MPU6500_Gyro.Z < 4) ) MPU6500_Gyro.Z = 0;
	}
	else if(offset_flag)  //MPU6500����У׼ģʽ
	{
		MPU6500_Acc.X = BYTE16(s16, mpu6500_buf[0],  mpu6500_buf[1]);
		MPU6500_Acc.Y = BYTE16(s16, mpu6500_buf[2],  mpu6500_buf[3]);
		MPU6500_Acc.Z = BYTE16(s16, mpu6500_buf[4],  mpu6500_buf[5]);
		MPU6500_Gyro.X = BYTE16(s16, mpu6500_buf[8],  mpu6500_buf[9]);
		MPU6500_Gyro.Y = BYTE16(s16, mpu6500_buf[10],  mpu6500_buf[11]);
		MPU6500_Gyro.Z = BYTE16(s16, mpu6500_buf[12],  mpu6500_buf[13]);
	}
	
	MPU6500_CS=1;  	    //��ֹSPI����
}

/*
 * ��������MPU6500_Init
 * ����  ��MPU6500��ʼ������
 * ����  ����
 * ���  ��0����ʼ��ʧ�� 1����ʼ���ɹ�
 */ 
u8 MPU6500_Init(void)
{
	SPI1_Init();																//MPU6500 IO�ں�SPI��ʼ��
	
	if(MPU6500_Read_Reg(WHO_AM_I) == 0x70)			//��ȷ��ȡ��6500�ĵ�ַ
	{		
		MPU6500_Write_Reg(PWR_MGMT_1,0X80);   		//��Դ����,��λMPU6500
		delay_ms(100);
		MPU6500_Write_Reg(SIGNAL_PATH_RESET,0X07);//�����ǡ����ٶȼơ��¶ȼƸ�λ
		delay_ms(100);
		MPU6500_Write_Reg(PWR_MGMT_1,0X01);   		//ѡ��ʱ��Դ
		MPU6500_Write_Reg(PWR_MGMT_2,0X00);   		//ʹ�ܼ��ٶȼƺ�������
		MPU6500_Write_Reg(CONFIG,0X02);						//��ͨ�˲��� 0x02 92hz (3.9ms delay) fs=1khz
		MPU6500_Write_Reg(SMPLRT_DIV,0X00);				//������1000/(1+0)=1000HZ
		MPU6500_Write_Reg(GYRO_CONFIG,0X18);  		//�����ǲ�����Χ 0X18 ����2000��
		MPU6500_Write_Reg(ACCEL_CONFIG,0x10); 		//���ٶȼƲ�����Χ 0X00 ����8g
		MPU6500_Write_Reg(ACCEL_CONFIG2,0x00);		//���ٶȼ�����1khz �˲���460hz (1.94ms delay)
		return 1;
	}
	else return 0;
}




