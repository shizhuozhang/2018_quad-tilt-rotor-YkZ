
#include "H_define.h"
/****************************
参数整定找最佳，从小到大顺序查
先是比例后积分，最后再把微分加
曲线振荡很频繁，比例度盘要放大
曲线漂浮绕大湾，比例度盘往小扳
曲线偏离回复慢，积分时间往下降
曲线波动周期长，积分时间再加长
曲线振荡频率快，先把微分降下来
动差大来波动慢。微分时间应加长
理想曲线两个波，前高后低4比1
一看二调多分析，调节质量不会低
****************************/
//增量式PID算法
void Increment_PID(PID_IncrementType* PID)
{
	 /*增量式PID计算*/
	 PID->d_CtrOut = PID->Kp * PID->ErrNow - PID->Ki * PID->ErrLast + PID->Kd * PID->ErrPrev;
	
	 PID->ErrPrev = PID->ErrLast; //存储误差，用于下次计算
	 PID->ErrLast = PID->ErrNow;  //

//	 PID->ctrOut += PID->dCtrOut;
}


//绝对式PID算法
void Absolute_PID(PID_AbsoluteType* PID)
{

	 PID->ErrP = PID->ErrNow;  //读取现在的误差，用于kp控制

	 PID->ErrI += PID->ErrNow; //用矩形法数值积分近似代替积分，用累加的方法记忆长期误差，用于ki控制

	  if( PID->ErrI > PID->ErrIMax)    //对积分限幅，避免出现积分饱和
		  PID->ErrI = PID->ErrIMax;		//Max和Min的设置应与积分增益匹配，满足单独积分输出时使驱动器达到最低和最高
	  else if(PID->ErrI < PID->ErrIMin)    
		  PID->ErrI = PID->ErrIMin;
	 
	 PID->ErrD = PID->ErrNow - PID->ErrLast;//一阶后向差分近似代替微分，用于kd控制
									//要保证采样时间间隔基本恒定，设置最高优先级，否则会引入噪声
	 PID->ErrLast = PID->ErrNow;	//保存现在的误差
	 
	 PID->CtrOut = PID->Kp * PID->ErrP + PID->Ki * PID->ErrI + PID->Kd * PID->ErrD;//计算绝对式PID输出

}

#define Low_Pass 0.85

//extern volatile Angle_XYZ  Angle_Exp;///位置环输出的期望角度

PID_AbsoluteType  PID_Pitch,PID_Roll;	//外环：角度PID环
//Pitch绕Y轴下层外环一号电机， roll绕X轴，内环二号电机
PID_AbsoluteType  PID_Pitch_Rate,PID_Roll_Rate;		//PID内环：角速度PID环

WAng_XYZ  WAng_Proce;
WAng_XYZ  WAng_Proce_Last;

void PID_Double_Angle(WAng_XYZ  Now_WAng,  Angle_XYZ Now_angle, Angle_XYZ Exp_angle)
{
//	float Angle_Cycle_out[3]={0};//三个轴向XYZ的角度外环输出值

	
	PID_Pitch.ErrNow=Now_angle.Angle_Y -Exp_angle.Angle_Y ;///由于电机转向已确定，故在这里换向
	PID_Roll.ErrNow= Exp_angle.Angle_X - Now_angle.Angle_X;
	
	PID_Pitch.Kp=50;//60
	PID_Pitch.Ki=0.3;
	PID_Pitch.Kd=0;
	PID_Pitch.ErrIMax=1200;
	PID_Pitch.ErrIMin=-1200;
	
	PID_Roll.Kp=37;
	PID_Roll.Ki=0.225;
	PID_Roll.Kd=0;
	PID_Roll.ErrIMax=1200;
	PID_Roll.ErrIMin=-1200;
	
	Absolute_PID(&PID_Pitch);//执行绝对式PID算法
	Absolute_PID(&PID_Roll);//执行绝对式PID算法
//	Motor_Value[0]=(s16)PID_Pitch.CtrOut;
//	Motor_Value[1]=(s16)PID_Roll.CtrOut;	
	
///*********阻尼项做一个低通给D使用	
	WAng_Proce_Last.WAngle_X = WAng_Proce.WAngle_X;//	//更新数之前先存储
	WAng_Proce.WAngle_X= Low_Pass * WAng_Proce_Last.WAngle_X +(1- Low_Pass)* Now_WAng.WAngle_X;
//	//低通滤波

	WAng_Proce_Last.WAngle_Y = WAng_Proce.WAngle_Y;//	//更新数之前先存储	
	WAng_Proce.WAngle_Y= Low_Pass * WAng_Proce_Last.WAngle_Y +(1- Low_Pass)* Now_WAng.WAngle_Y;
//	//低通滤波

///内环
	PID_Pitch_Rate.ErrNow=PID_Pitch.CtrOut+WAng_Proce.WAngle_Y*0.0610351;
	PID_Roll_Rate.ErrNow=PID_Roll.CtrOut+WAng_Proce.WAngle_X*0.0610351;
	
	PID_Pitch_Rate.Kp=1.3;//1.0
	PID_Pitch_Rate.Ki=0;
	PID_Pitch_Rate.Kd=0;
	PID_Pitch_Rate.ErrIMax=100;
	PID_Pitch_Rate.ErrIMin=-100;
	
	PID_Roll_Rate.Kp=1.2;//1.0
	PID_Roll_Rate.Ki=0;
	PID_Roll_Rate.Kd=0;
	PID_Roll_Rate.ErrIMax=100;
	PID_Roll_Rate.ErrIMin=-100;
	
	Absolute_PID(&PID_Pitch_Rate);//执行绝对式PID算法
	Absolute_PID(&PID_Roll_Rate);//执行绝对式PID算法
	
	Motor_Value[0]=(s16)PID_Pitch_Rate.CtrOut;
	Motor_Value[1]=(s16)PID_Roll_Rate.CtrOut;	
}

void Motor_Drive(s16 To_Motor[3])
{
	u8 i=0;
	for(i=0;i<3;i++)//输出限幅和死区限位
	{
		if(To_Motor[i]>0)
		{
			if(To_Motor[i]>3580)
				To_Motor[i]=3580;
			else if(To_Motor[i]<120)	
				To_Motor[i]+=120;
		}
		
		if(To_Motor[i]<0)
		{
			if(To_Motor[i]<-3580)
				To_Motor[i]=-3580;
			else if(To_Motor[i]>-120)	
					To_Motor[i]-=120;
		}
	
	}
	
	if(To_Motor[0]>0)//电机1
	{
			TIM8->CCR1=0;
			TIM8->CCR2=To_Motor[0];
	}
	else
	{		
			TIM8->CCR1=-To_Motor[0];
			TIM8->CCR2=0;
	}
	
	if(To_Motor[1]>0)//电机2
	{
			TIM8->CCR3=0;
			TIM8->CCR4=To_Motor[1];
	}
	else
	{
			TIM8->CCR3=-To_Motor[1];
			TIM8->CCR4=0;
	}		
}


	
///*****************************************************************************/	
//	
///*****************************输出给电机************************************************/
//		 
//		motor_yaw = (s16) PID_Yaw_Rate.Out;
//    if(!motor_en)
//			motor_yaw=0;
//	  Motor_PWM_Update(motor_yaw);
//		motor_pitch = -(s16)(PID_Pitch_Rate.Out);
//	  set_current(motor_pitch *5);
//}


///*
// * 函数名：PID_Init
// * 描述  ：PID参数初始化函数
// * 输入  ：无
// * 输出  ：无
// */ 
//void PID_Init(void)
//{
//	
//	PID_Yaw_Angle.P =55;		//65
//	PID_Yaw_Angle.I = 0.00;//0.05
//		
//角速度环	
//	
//	PID_Yaw_Rate.P = 1.1;//1.2
//	PID_Yaw_Rate.I = 0;

//	
//	PID_Yaw_Angle.Pout = 0;
//	PID_Yaw_Angle.Iout = 0;
//	PID_Yaw_Angle.Dout = 0;
//		
//	
//	PID_Yaw_Rate.Pout = 0;
//	PID_Yaw_Rate.Iout = 0;
//	PID_Yaw_Rate.Dout = 0;

//	//角度环参数
//	PID_Pitch_Angle.P =27;
//	PID_Pitch_Angle.I =0.05;//0.1的时候超调有0.01度
//	PID_Pitch_Angle.D =0;
//	
//角速度环	
//	PID_Pitch_Rate.P =-8;
//	PID_Pitch_Rate.I =0;
//	PID_Pitch_Rate.D =0;
// 
//	PID_Pitch_Angle.Pout = 0;
//	PID_Pitch_Angle.Iout = 0;
//	PID_Pitch_Angle.Dout = 0;
//	
//	PID_Pitch_Rate.Pout = 0;
//	PID_Pitch_Rate.Iout = 0;
//	PID_Pitch_Rate.Dout = 0;
//}
					




/***********************************************************************************

*****************************************电机速度环伺服***********************************

PID_AbsoluteType SPEED_PID;//定义PID算法的结构体

s16 SpeedControl(s16 SpeedTag,s16 SpeedNow)
{
	SPEED_PID.ErrNow = SpeedTag - SpeedNow;
	
	SPEED_PID.Kp=15; //写入比例系数为
	SPEED_PID.Ki=0.8; //写入积分系数为
	SPEED_PID.Kd=0;//写入微分系数为5
	SPEED_PID.ErrIMax=15000; //写入误差积分上限为1000 
	SPEED_PID.ErrIMin=-15000;	//下限为-1000
	Absolute_PID(&SPEED_PID);//执行绝对式PID算法
	
	return  SPEED_PID.CtrOut;         //读取控制值
}

void OutToMotor1(s16 Control_value)
{
		if(Control_value<0)
		{
			Control_value=-Control_value;
			if(Control_value>=3600)//输出限幅
				Control_value=3600;
			
			TIM4->CCR1=Control_value;	
			TIM4->CCR2=0;			
		}
		else
		{
			if(Control_value>=3600)//输出限幅
				Control_value=3600;
						
			TIM4->CCR1=0;	
			TIM4->CCR2=Control_value;
		}
}

void OutToMotor2(s16 Control_value)
{
		if(Control_value<0)
		{
			Control_value=-Control_value;
			if(Control_value>=3600)//输出限幅
				Control_value=3600;
			TIM4->CCR3=0;	
			TIM4->CCR4=Control_value;	
					
		}
		else
		{
			if(Control_value>=3600)//输出限幅
				Control_value=3600;
		
			TIM4->CCR3=Control_value;	
			TIM4->CCR4=0;				
		}
}
*************/





