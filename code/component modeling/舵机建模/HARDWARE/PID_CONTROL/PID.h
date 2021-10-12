#ifndef __PID_H
#define __PID_H
#include "sys.h"
/*


*/
#define T  0.01		//控制频率一般在100HZ～300HZ左右

/*绝对式PID算法，接口参数结构类型*/
typedef struct 
{
	/*PID算法接口变量，用于外部获取或修改PID算法的特性*/
	float Kp;     //比例系数，一般在1～100范围内
	float Ki;     //积分系数，一般在0.0001到0.01范围内
	float Kd;     //微分系数，一般在几百
	float ErrIMax;//误差积分上限
	float ErrIMin;//误差积分下限	

	float ErrNow;//当前的误差，也称基本偏差，设定值减去测量值
	float CtrOut;//控制量输出

	/*PID算法内部变量，其值不能修改*/
	float ErrLast;//前一次误差值
	float ErrP;
	float ErrI;
	float ErrD;
 
}PID_AbsoluteType;

/*增量式PID算法，接口参数结构类型*/
typedef struct 
{
 /*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
 float Kp;     //比例系数
 float Ti;     //积分系数，不使用积分时，TI为无穷大
 float Td;     //微分系数，不使用微分时TD=0
 
 float ErrNow; //当前的误差 也称基本偏差，设定值减去测量值
 float d_CtrOut;//控制增量输出
 float CtrOut;//控制输出
 
 /*PID算法内部变量，其值不能修改*/
 float ErrLast;
 float ErrPrev;
 
}PID_IncrementType;


typedef struct 
{
	float WAngle_X;
	float WAngle_Y;
	float WAngle_Z;
}WAng_XYZ;//角速度

typedef struct 
{
	float Angle_X;
	float Angle_Y;
	float Angle_Z;
}Angle_XYZ;//角度


void Increment_PID(PID_IncrementType* PID);
void Absolute_PID(PID_AbsoluteType* PID);

		/**云台控制***/
void PID_Angle(Angle_XYZ Now_angle, Angle_XYZ Exp_angle);
void Motor_Drive(s16 To_Motor[3]);


/**速度闭环*/
//s16 SpeedControl(s16 SpeedTag,s16 SpeedNow);
//void OutToMotor1(s16 Control_value);
//void OutToMotor2(s16 Control_value);

#endif









