#ifndef __AHRS_H
#define __AHRS_H

#include "sys.h"

#define SAMPLE_HALF_T 0.0005f     //�������ڵ�һ�룬��λ��s
#define FILTER_LENGTH 20					//�����˲����ڳ���

#define GYRO_G 	0.0610351f	//���ٶȱ�ɶ�/S   �˲�����Ӧ����2000��ÿ��  Gyro_G=1/16.375=0.0610687
#define GYRO_GR	0.0010653f	//���ٶȱ�ɻ���/S	�˲�����Ӧ����2000��ÿ��

#define IMU_KP 1.5f     					//����
#define IMU_KI 0.0005f 						//����

typedef struct
{
	float X;
	float Y;
	float Z;
}S_FLOAT_XYZ;

extern volatile S_FLOAT_XYZ Angle;

void Geographic_Coordinate_ReadValue(void);
void Prepare_Data(void);
void IMU_Update(void);
void AHRS_Date_Init(void);

#endif


