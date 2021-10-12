#include "H_define.h"

#define SAMPLE_HALF_T 0.0005f    //采样周期的一半，单位：s
#define FILTER_LENGTH 35		//滑动滤波窗口长度

#define GYRO_G 	0.0610361f		//角速度变成度/S   此参数对应陀螺2000度每秒  Gyro_G=1/16.375=0.0610687
#define GYRO_GR	0.0010653f		//角速度变成弧度/S	此参数对应陀螺2000度每秒

#define IMU_KP 1.5f     		//比例
#define IMU_KI 0.0005f 			//积分

volatile S_INT16_XYZ Acc_Avg;		//滑动滤波后加速度计值
volatile S_FLOAT_XYZ Acc_Angle;    //加速度计计算出的角度
volatile S_FLOAT_XYZ Angle;        //数据融合计算出的角度
volatile S_INT16_XYZ Acc_Buf[FILTER_LENGTH] = {0};

//extern volatile S_FLOAT_XYZ Angle;
extern S_INT16_XYZ MPU9250_Acc;
extern S_INT16_XYZ MPU9250_Gyro;
extern S_INT16_XYZ MPU9250_Acc_Offset;	
/*
 * 函数名：Acc_Flitter
 * 描述  ：加速度计预滤波
 *                     递推最小二乘估计/滑动滤波
 *			1：无需存储全部数据，取得一组观测数据便可以估计一次参数
 *				且都能够在一个采样周期内完成，计算量小，占用存储空间小
 *			2：具有一定的实时处理能力
 * 输入  ：无
 * 输出  ：无
 */ 
void	Acc_Flitter()
{
	static u8 filter_cnt	=	0;
	u8 cnt;
	S_INT32_XYZ	Temp;
	
	Temp.X = 0;
	Temp.Y = 0;
	Temp.Z = 0;
	
	Acc_Buf[filter_cnt].X = MPU9250_Acc.X;
	Acc_Buf[filter_cnt].Y	= MPU9250_Acc.Y;
	Acc_Buf[filter_cnt].Z = MPU9250_Acc.Z;
	
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
 * 函数名：Prepare_Data
 * 描述  ：读取MPU6500原始数据；加速度计预滤波
 * 输入  ：Now_Angle：当前姿态；Exp_Angle：期望姿态
 * 输出  ：无
 */ 
void Prepare_Data(void)
{
	MPU9250_ReadValue(); //读取MPU6500原始值
	Acc_Flitter();		 	 //加速度计预滤波
}



float ex_int = 0, ey_int = 0, ez_int = 0;   //X、Y、Z轴的比例误差
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;    //定义四元素
float q0_yaw = 1, q1_yaw = 0, q2_yaw = 0, q3_yaw = 0;    //弥补Mahony算法在无地磁情况解算Yaw轴满足不了大扰动要求的现象

/*
 * 函数名：IMU_Update
 * 描述  ：姿态数据更新
 * 输入  ：无
 * 输出  ：无
 */ 


float yaw_real;//由于四元素算得的角度会在180到-180之间跳变，所以用这么一个数实现连续的角度测量
float yaw_real_num;//计算圈数
float yaw_last;
float yaw_c;
void IMU_Update(void)
{
  float norm;	
	float gx = MPU9250_Gyro.X	*	GYRO_GR,gy = MPU9250_Gyro.Y	*	GYRO_GR,gz = MPU9250_Gyro.Z	*	GYRO_GR;
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
	 
	if(ax * ay * az	== 0)
	return ;
	
	//加速度归一
  norm = sqrt(ax * ax + ay * ay + az * az); 
  ax = ax / norm;
  ay = ay / norm;
  az = az / norm;
	
	//估计重力方向和流量/变迁
  vx = 2 * (q1q3 - q0q2);											
  vy = 2 * (q0q1 + q2q3);
  vz = q0q0 - q1q1 - q2q2 + q3q3 ;
	
  //向量外积再相减得到差分就是误差
  ex = (ay * vz - az * vy) ;      
  ey = (az * vx - ax * vz) ;
  ez = (ax * vy - ay * vx) ;

	//对误差进行PI计算
  ex_int = ex_int + ex * IMU_KI;			
  ey_int = ey_int + ey * IMU_KI;
  ez_int = ez_int + ez * IMU_KI;

  //校正陀螺仪
  gx = gx + IMU_KP * ex + ex_int;					
  gy = gy + IMU_KP * ey + ey_int;
  gz = gz;			
			
	//四元素的微分方程
  q0 = q0 + (-q1 * gx - q2	*	gy - q3	*	gz)	*	SAMPLE_HALF_T;
  q1 = q1 + (q0	*	gx + q2	*	gz - q3	*	gy)	*	SAMPLE_HALF_T;
  q2 = q2 + (q0	*	gy - q1	*	gz + q3	*	gx)	*	SAMPLE_HALF_T;
  q3 = q3 + (q0	*	gz + q1	*	gy - q2	*	gx)	*	SAMPLE_HALF_T;

  //规范化Pitch、Roll轴四元数
  norm = sqrt(q0q0 + q1q1 + q2q2 + q3q3);
  q0 = q0 / norm;
  q1 = q1 / norm;
  q2 = q2 / norm;
  q3 = q3 / norm;
	
	//求解欧拉角
	Angle.X = atan2(2 * q2q3 + 2 * q0q1, -2 * q1q1 - 2 * q2q2 + 1) * 57.3;
	Angle.Y = asin(-2 * q1q3 + 2 * q0q2) * 57.3;
	yaw_c = atan2(2 * q1*q2 + 2 * q0*q3, -2 * q2*q2 - 2 * q3q3 + 1)	* 57.3;
	//计算获得的角度在180度的时候会跳变到-180度
	if(yaw_c-yaw_last>300)//从-180跳变到180
	 yaw_real_num-=1;//计算获得的圈数减去一
	if(yaw_c-yaw_last<-300)//从180跳变到-180
		yaw_real_num+=1;
	 Angle.Z=360.0*yaw_real_num+yaw_c;
	 yaw_last=yaw_c;
}


//extern volatile S_FLOAT_XYZ Exp_Angle;

/*
 * 函数名：AHRS_Date_Init
 * 描述  ：航姿数据初始化
 * 输入  ：无
 * 输出  ：无
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
	
//	Exp_Angle.X = 0;
//	Exp_Angle.Y = 0;
//	Exp_Angle.Z = 0;
}













