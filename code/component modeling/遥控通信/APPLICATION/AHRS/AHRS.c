#include "H_define.h"

volatile u8 AHRS_DATA[42];

SINT16_XYZ ACC_DAC_DATA={0};//加速度计的直接输出数据
SINT16_XYZ GYRO_DAC_DATA={0};//陀螺仪的直接输出数据
SINT16_XYZ MAG_DAC_DATA={0};//地磁计的直接输出数据
volatile POSE  Att_Angle={0.0f};
float Tempr=0.0f;//温度
u16 Press;//气压
//********************************以下处理函数****************************/
u8 AHRS_data_Pro(void)//按照通信协议解算IMU数据
{
	u8 i=0;
	u8 CRC_Flag1=0;
	u8 CRC_Flag2=0;
	u16 Checksum=0;
	s16 temp=0;
	
	for(i=0;i<16;i++)//第一组校验位之前有16个数据，AHRS_DATA[0:15]
		Checksum+=AHRS_DATA[i];
	if((Checksum%256)==AHRS_DATA[16]) //取出低8位做校验
		CRC_Flag1=1;//Checksum successful
	else
		CRC_Flag1=0; //Checksum error
	
	Checksum=0;	
	for(i=0;i<20;i++)//第二组校验位之前除去第一组数据和起始两个字节，有20个数据，AHRS_DATA[20:39]
		Checksum+=AHRS_DATA[i+20];
	if((Checksum%256)==AHRS_DATA[40]) //取出低8位做校验
		CRC_Flag2=1;//Checksum successful
	else
		CRC_Flag2=0; //Checksum error	
	
	if(CRC_Flag1&&CRC_Flag2)	//先判断数据是否正确
	{
		temp |= (s16)(((u16)AHRS_DATA[2]<<8)| AHRS_DATA[3]);
		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.yaw=(float)(temp / 10.0f); //偏航角
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[4]<<8)| AHRS_DATA[5]);
		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.pitch=(float)(temp / 10.0f); //俯仰角
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[6]<<8)| AHRS_DATA[7]);
		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.roll=(float)(temp / 10.0f); //滚转角
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[8]<<8)| AHRS_DATA[9]);
		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.alt=(float)(temp / 10.0f); //高度
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[10]<<8)| AHRS_DATA[11]);
		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.alt=(float)(temp / 10.0f); //温度
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[12]<<8)| AHRS_DATA[13]);
		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.alt=(float)(temp / 10.0f); //气压
		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[22]<<8)| AHRS_DATA[23]);
//		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		ACC_DAC_DATA.X= temp ; //X轴向的加速度ADC值
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[24]<<8)| AHRS_DATA[25]);
//		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		ACC_DAC_DATA.Y= temp ; //Y轴向的加速度ADC值
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[26]<<8)| AHRS_DATA[27]);
//		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		ACC_DAC_DATA.Z= temp ; //Z轴向的加速度ADC值
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[28]<<8)| AHRS_DATA[29]);
//		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		GYRO_DAC_DATA.X= temp ; //	X轴向的角速度ADC值

//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[30]<<8)| AHRS_DATA[31]);
//		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		GYRO_DAC_DATA.Y= temp ; //	Y轴向的角速度ADC值
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[32]<<8)| AHRS_DATA[33]);
//		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		GYRO_DAC_DATA.Z= temp ; //	Z轴向的角速度ADC值
		
		//地磁计暂时不需要
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[34]<<8)| AHRS_DATA[35]);
//		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		MAG_DAC_DATA.X= temp ; //	X轴向的地磁计ADC值
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[36]<<8)| AHRS_DATA[37]);
//		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		MAG_DAC_DATA.Y= temp ; //	Y轴向的地磁计ADC值
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[38]<<8)| AHRS_DATA[39]);
//		if(temp&0x8000)//根据协议规定，若为负值，则数据最高位是1，即最高位是符号位
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		MAG_DAC_DATA.Z= temp ; //	Z轴向的地磁计ADC值
		
		return 1;//解析完成
	}
	else
		return 0;//解析失败
}
	


