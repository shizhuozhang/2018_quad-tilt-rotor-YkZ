#include "H_define.h"

volatile u8 AHRS_DATA[42];

SINT16_XYZ ACC_DAC_DATA={0};//���ٶȼƵ�ֱ���������
SINT16_XYZ GYRO_DAC_DATA={0};//�����ǵ�ֱ���������
SINT16_XYZ MAG_DAC_DATA={0};//�شżƵ�ֱ���������
volatile POSE  Att_Angle={0.0f};
float Tempr=0.0f;//�¶�
u16 Press;//��ѹ
//********************************���´�����****************************/
u8 AHRS_data_Pro(void)//����ͨ��Э�����IMU����
{
	u8 i=0;
	u8 CRC_Flag1=0;
	u8 CRC_Flag2=0;
	u16 Checksum=0;
	s16 temp=0;
	
	for(i=0;i<16;i++)//��һ��У��λ֮ǰ��16�����ݣ�AHRS_DATA[0:15]
		Checksum+=AHRS_DATA[i];
	if((Checksum%256)==AHRS_DATA[16]) //ȡ����8λ��У��
		CRC_Flag1=1;//Checksum successful
	else
		CRC_Flag1=0; //Checksum error
	
	Checksum=0;	
	for(i=0;i<20;i++)//�ڶ���У��λ֮ǰ��ȥ��һ�����ݺ���ʼ�����ֽڣ���20�����ݣ�AHRS_DATA[20:39]
		Checksum+=AHRS_DATA[i+20];
	if((Checksum%256)==AHRS_DATA[40]) //ȡ����8λ��У��
		CRC_Flag2=1;//Checksum successful
	else
		CRC_Flag2=0; //Checksum error	
	
	if(CRC_Flag1&&CRC_Flag2)	//���ж������Ƿ���ȷ
	{
		temp |= (s16)(((u16)AHRS_DATA[2]<<8)| AHRS_DATA[3]);
		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.yaw=(float)(temp / 10.0f); //ƫ����
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[4]<<8)| AHRS_DATA[5]);
		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.pitch=(float)(temp / 10.0f); //������
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[6]<<8)| AHRS_DATA[7]);
		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.roll=(float)(temp / 10.0f); //��ת��
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[8]<<8)| AHRS_DATA[9]);
		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.alt=(float)(temp / 10.0f); //�߶�
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[10]<<8)| AHRS_DATA[11]);
		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.alt=(float)(temp / 10.0f); //�¶�
		
		temp = 0;
		temp |= (s16)(((u16)AHRS_DATA[12]<<8)| AHRS_DATA[13]);
		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
			temp = 0-(temp&0x7fff);
		else
			temp = (temp&0x7fff);
		Att_Angle.alt=(float)(temp / 10.0f); //��ѹ
		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[22]<<8)| AHRS_DATA[23]);
//		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		ACC_DAC_DATA.X= temp ; //X����ļ��ٶ�ADCֵ
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[24]<<8)| AHRS_DATA[25]);
//		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		ACC_DAC_DATA.Y= temp ; //Y����ļ��ٶ�ADCֵ
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[26]<<8)| AHRS_DATA[27]);
//		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		ACC_DAC_DATA.Z= temp ; //Z����ļ��ٶ�ADCֵ
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[28]<<8)| AHRS_DATA[29]);
//		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		GYRO_DAC_DATA.X= temp ; //	X����Ľ��ٶ�ADCֵ

//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[30]<<8)| AHRS_DATA[31]);
//		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		GYRO_DAC_DATA.Y= temp ; //	Y����Ľ��ٶ�ADCֵ
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[32]<<8)| AHRS_DATA[33]);
//		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		GYRO_DAC_DATA.Z= temp ; //	Z����Ľ��ٶ�ADCֵ
		
		//�شż���ʱ����Ҫ
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[34]<<8)| AHRS_DATA[35]);
//		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		MAG_DAC_DATA.X= temp ; //	X����ĵشż�ADCֵ
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[36]<<8)| AHRS_DATA[37]);
//		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		MAG_DAC_DATA.Y= temp ; //	Y����ĵشż�ADCֵ
//		
//		temp = 0;
//		temp |= (s16)(((u16)AHRS_DATA[38]<<8)| AHRS_DATA[39]);
//		if(temp&0x8000)//����Э��涨����Ϊ��ֵ�����������λ��1�������λ�Ƿ���λ
//			temp = 0-(temp&0x7fff);
//		else
//			temp = (temp&0x7fff);
//		MAG_DAC_DATA.Z= temp ; //	Z����ĵشż�ADCֵ
		
		return 1;//�������
	}
	else
		return 0;//����ʧ��
}
	


