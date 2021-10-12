#ifndef __PID_H
#define __PID_H
#include "sys.h"
/*


*/
#define T  0.01		//����Ƶ��һ����100HZ��300HZ����

/*����ʽPID�㷨���ӿڲ����ṹ����*/
typedef struct 
{
	/*PID�㷨�ӿڱ����������ⲿ��ȡ���޸�PID�㷨������*/
	float Kp;     //����ϵ����һ����1��100��Χ��
	float Ki;     //����ϵ����һ����0.0001��0.01��Χ��
	float Kd;     //΢��ϵ����һ���ڼ���
	float ErrIMax;//����������
	float ErrIMin;//����������	

	float ErrNow;//��ǰ����Ҳ�ƻ���ƫ��趨ֵ��ȥ����ֵ
	float CtrOut;//���������

	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float ErrLast;//ǰһ�����ֵ
	float ErrP;
	float ErrI;
	float ErrD;
 
}PID_AbsoluteType;

/*����ʽPID�㷨���ӿڲ����ṹ����*/
typedef struct 
{
 /*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
 float Kp;     //����ϵ��
 float Ti;     //����ϵ������ʹ�û���ʱ��TIΪ�����
 float Td;     //΢��ϵ������ʹ��΢��ʱTD=0
 
 float ErrNow; //��ǰ����� Ҳ�ƻ���ƫ��趨ֵ��ȥ����ֵ
 float d_CtrOut;//�����������
 float CtrOut;//�������
 
 /*PID�㷨�ڲ���������ֵ�����޸�*/
 float ErrLast;
 float ErrPrev;
 
}PID_IncrementType;


typedef struct 
{
	float WAngle_X;
	float WAngle_Y;
	float WAngle_Z;
}WAng_XYZ;//���ٶ�

typedef struct 
{
	float Angle_X;
	float Angle_Y;
	float Angle_Z;
}Angle_XYZ;//�Ƕ�


void Increment_PID(PID_IncrementType* PID);
void Absolute_PID(PID_AbsoluteType* PID);

		/**��̨����***/
void PID_Angle(Angle_XYZ Now_angle, Angle_XYZ Exp_angle);
void Motor_Drive(s16 To_Motor[3]);


/**�ٶȱջ�*/
//s16 SpeedControl(s16 SpeedTag,s16 SpeedNow);
//void OutToMotor1(s16 Control_value);
//void OutToMotor2(s16 Control_value);

#endif









