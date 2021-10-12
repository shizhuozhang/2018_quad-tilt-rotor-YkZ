#include "H_define.h"

volatile S_INT16_XYZ Acc_Avg;			 //�����˲�����ٶȼ�ֵ
volatile S_FLOAT_XYZ Acc_Angle;    //���ٶȼƼ�����ĽǶ�
volatile S_FLOAT_XYZ Angle;        //�����ںϼ�����ĽǶ�
volatile S_INT16_XYZ Acc_Buf[FILTER_LENGTH] = {0};

/*
 * ��������Acc_Flitter
 * ����  �����ٶȼ�Ԥ�˲�
 *                     ������С���˹���/�����˲�
 *			1������洢ȫ�����ݣ�ȡ��һ��۲����ݱ���Թ���һ�β���
 *				�Ҷ��ܹ���һ��������������ɣ�������С��ռ�ô洢�ռ�С
 *			2������һ����ʵʱ��������
 * ����  ����
 * ���  ����
 */ 
void	Acc_Flitter()
{
	static u8 filter_cnt	=	0;
	static u8 cnt;
	S_INT32_XYZ	Temp;
	
	Temp.X = 0;
	Temp.Y = 0;
	Temp.Z = 0;
	
	Acc_Buf[filter_cnt].X = MPU6500_Acc.X;
	Acc_Buf[filter_cnt].Y	= MPU6500_Acc.Y;
	Acc_Buf[filter_cnt].Z = MPU6500_Acc.Z;
	
	filter_cnt++;
	
	for(cnt	=	0;cnt <	FILTER_LENGTH;cnt++)
	{
		Temp.X += Acc_Buf[cnt].X;
		Temp.Y += Acc_Buf[cnt].Y;
		Temp.Z += Acc_Buf[cnt].Z;
	}
	Acc_Avg.X = Temp.X / FILTER_LENGTH;
	Acc_Avg.Y = Temp.Y / FILTER_LENGTH;
	Acc_Avg.Z = Temp.Z / FILTER_LENGTH;
	
	if(filter_cnt	==	FILTER_LENGTH)	filter_cnt = 0;
}

/*
 * ��������Prepare_Data
 * ����  ����ȡMPU6500ԭʼ���ݣ����ٶȼ�Ԥ�˲�
 * ����  ��Now_Angle����ǰ��̬��Exp_Angle��������̬
 * ���  ����
 */ 
void Prepare_Data(void)
{
	MPU6500_ReadValue(); //��ȡMPU6500ԭʼֵ
	Acc_Flitter();		 	 //���ٶȼ�Ԥ�˲�
}

float ex_int = 0, ey_int = 0, ez_int = 0;   //X��Y��Z��ı������
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;    //������Ԫ��
float q0_yaw = 1, q1_yaw = 0, q2_yaw = 0, q3_yaw = 0;    //�ֲ�Mahony�㷨���޵ش��������Yaw�����㲻�˴��Ŷ�Ҫ�������

/*
 * ��������IMU_Update
 * ����  ����̬���ݸ���
 * ����  ����
 * ���  ����
 */ 
void IMU_Update(void)
{
  float norm;	
	float gx = MPU6500_Gyro.X	*	GYRO_GR,gy = MPU6500_Gyro.Y	*	GYRO_GR,gz = MPU6500_Gyro.Z	*	GYRO_GR;
	float ax = Acc_Avg.X,ay = Acc_Avg.Y,az = Acc_Avg.Z;
	
	float q0q0 = q0 * q0;
  float q0q1 = q0 * q1;
  float q0q2 = q0 * q2;
  float q1q1 = q1 * q1;
  float q1q3 = q1 * q3;
  float q2q2 = q2	* q2;
  float q2q3 = q2	*	q3;
  float q3q3 = q3	*	q3;	
	float vx, vy, vz;
  float ex, ey, ez;
	
	float	q0_yawq0_yaw = q0_yaw * q0_yaw;
	float	q1_yawq1_yaw = q1_yaw * q1_yaw;
	float	q2_yawq2_yaw = q2_yaw * q2_yaw;
	float	q3_yawq3_yaw = q3_yaw * q3_yaw;
	float	q1_yawq2_yaw = q1_yaw * q2_yaw;
	float	q0_yawq3_yaw = q0_yaw * q3_yaw;
	
//**************************Yaw�����******************************
	
	//Yaw����Ԫ�ص�΢�ַ���
  q0_yaw = q0_yaw + (-q1_yaw * gx - q2_yaw * gy - q3_yaw * gz) * SAMPLE_HALF_T;
  q1_yaw = q1_yaw + (q0_yaw * gx + q2_yaw * gz - q3_yaw * gy) * SAMPLE_HALF_T;
  q2_yaw = q2_yaw + (q0_yaw * gy - q1_yaw * gz + q3_yaw * gx) * SAMPLE_HALF_T;
  q3_yaw = q3_yaw + (q0_yaw * gz + q1_yaw * gy - q2_yaw * gx) * SAMPLE_HALF_T;
	
	//�淶��Yaw����Ԫ��
  norm = sqrt(q0_yawq0_yaw + q1_yawq1_yaw + q2_yawq2_yaw + q3_yawq3_yaw);
  q0_yaw = q0_yaw / norm;
  q1_yaw = q1_yaw / norm;
  q2_yaw = q2_yaw / norm;
  q3_yaw = q3_yaw / norm;
	
  
	if(ax * ay * az	== 0)
	return ;
	
	//�淶�����ٶȼ�ֵ
  norm = sqrt(ax * ax + ay * ay + az * az); 
  ax = ax / norm;
  ay = ay / norm;
  az = az / norm;
	
	//�����������������/��Ǩ
  vx = 2 * (q1q3 - q0q2);											
  vy = 2 * (q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3 ;
	
  //�������������õ���־������
  ex = (ay * vz - az * vy) ;      
  ey = (az * vx - ax * vz) ;
  ez = (ax * vy - ay * vx) ;

	//��������PI����
  ex_int = ex_int + ex * IMU_KI;			
  ey_int = ey_int + ey * IMU_KI;
  ez_int = ez_int + ez * IMU_KI;

  //У��������
  gx = gx + IMU_KP * ex + ex_int;					
  gy = gy + IMU_KP * ey + ey_int;
  gz = gz + IMU_KP * ez + ez_int;			
			
	//��Ԫ�ص�΢�ַ���
  q0 = q0 + (-q1 * gx - q2	*	gy - q3	*	gz)	*	SAMPLE_HALF_T;
  q1 = q1 + (q0	*	gx + q2	*	gz - q3	*	gy)	*	SAMPLE_HALF_T;
  q2 = q2 + (q0	*	gy - q1	*	gz + q3	*	gx)	*	SAMPLE_HALF_T;
  q3 = q3 + (q0	*	gz + q1	*	gy - q2	*	gx)	*	SAMPLE_HALF_T;

  //�淶��Pitch��Roll����Ԫ��
  norm = sqrt(q0q0 + q1q1 + q2q2 + q3q3);
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;
	
	//���ŷ����
	Angle.X = atan2(2 * q2q3 + 2 * q0q1, -2 * q1q1 - 2 * q2q2 + 1) * 57.3f;
	Angle.Y = asin(-2 * q1q3 + 2 * q0q2) * 57.3f;
	Angle.Z = atan2(2 * q1_yawq2_yaw + 2 * q0_yawq3_yaw, -2 * q2_yawq2_yaw - 2 * q3_yawq3_yaw + 1)	* 57.3f;

}


/*
 * ��������AHRS_Date_Init
 * ����  ���������ݳ�ʼ��
 * ����  ����
 * ���  ����
 */ 
void AHRS_Date_Init(void)
{	
	int cnt;
	
	for(cnt	=	0;cnt	<	FILTER_LENGTH;cnt++)
	{
		Acc_Buf[cnt].X = 0;
		Acc_Buf[cnt].Y = 0;
		Acc_Buf[cnt].Z = 0;
	}
  	
	q0 = 1;
	q1 = 0;
	q2 = 0;
	q3 = 0;
	
	q0_yaw = 1;
	q1_yaw = 0;
	q2_yaw = 0;
	q3_yaw = 0;
	
	Angle.X = 0;
	Angle.Y = 0;
	Angle.Z = 0;
	
}













