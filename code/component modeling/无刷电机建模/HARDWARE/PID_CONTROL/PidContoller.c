
#include "H_define.h"
/****************************
������������ѣ���С����˳���
���Ǳ�������֣�����ٰ�΢�ּ�
�����񵴺�Ƶ������������Ҫ�Ŵ�
����Ư���ƴ��壬����������С��
����ƫ��ظ���������ʱ�����½�
���߲������ڳ�������ʱ���ټӳ�
������Ƶ�ʿ죬�Ȱ�΢�ֽ�����
���������������΢��ʱ��Ӧ�ӳ�
����������������ǰ�ߺ��4��1
һ��������������������������
****************************/
//����ʽPID�㷨
void Increment_PID(PID_IncrementType* PID)
{
	 /*����ʽPID����*/
	 PID->d_CtrOut = PID->Kp * PID->ErrNow - PID->Ki * PID->ErrLast + PID->Kd * PID->ErrPrev;
	
	 PID->ErrPrev = PID->ErrLast; //�洢�������´μ���
	 PID->ErrLast = PID->ErrNow;  //

//	 PID->ctrOut += PID->dCtrOut;
}


//����ʽPID�㷨
void Absolute_PID(PID_AbsoluteType* PID)
{

	 PID->ErrP = PID->ErrNow;  //��ȡ���ڵ�������kp����

	 PID->ErrI += PID->ErrNow; //�þ��η���ֵ���ֽ��ƴ�����֣����ۼӵķ������䳤��������ki����

	  if( PID->ErrI > PID->ErrIMax)    //�Ի����޷���������ֻ��ֱ���
		  PID->ErrI = PID->ErrIMax;		//Max��Min������Ӧ���������ƥ�䣬���㵥���������ʱʹ�������ﵽ��ͺ����
	  else if(PID->ErrI < PID->ErrIMin)    
		  PID->ErrI = PID->ErrIMin;
	 
	 PID->ErrD = PID->ErrNow - PID->ErrLast;//һ�׺����ֽ��ƴ���΢�֣�����kd����
									//Ҫ��֤����ʱ���������㶨������������ȼ����������������
	 PID->ErrLast = PID->ErrNow;	//�������ڵ����
	 
	 PID->CtrOut = PID->Kp * PID->ErrP + PID->Ki * PID->ErrI + PID->Kd * PID->ErrD;//�������ʽPID���

}

#define Low_Pass 0.85

//extern volatile Angle_XYZ  Angle_Exp;///λ�û�����������Ƕ�

PID_AbsoluteType  PID_Pitch,PID_Roll;	//�⻷���Ƕ�PID��
//Pitch��Y���²��⻷һ�ŵ���� roll��X�ᣬ�ڻ����ŵ��
PID_AbsoluteType  PID_Pitch_Rate,PID_Roll_Rate;		//PID�ڻ������ٶ�PID��

WAng_XYZ  WAng_Proce;
WAng_XYZ  WAng_Proce_Last;

void PID_Double_Angle(WAng_XYZ  Now_WAng,  Angle_XYZ Now_angle, Angle_XYZ Exp_angle)
{
//	float Angle_Cycle_out[3]={0};//��������XYZ�ĽǶ��⻷���ֵ

	
	PID_Pitch.ErrNow=Now_angle.Angle_Y -Exp_angle.Angle_Y ;///���ڵ��ת����ȷ�����������ﻻ��
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
	
	Absolute_PID(&PID_Pitch);//ִ�о���ʽPID�㷨
	Absolute_PID(&PID_Roll);//ִ�о���ʽPID�㷨
//	Motor_Value[0]=(s16)PID_Pitch.CtrOut;
//	Motor_Value[1]=(s16)PID_Roll.CtrOut;	
	
///*********��������һ����ͨ��Dʹ��	
	WAng_Proce_Last.WAngle_X = WAng_Proce.WAngle_X;//	//������֮ǰ�ȴ洢
	WAng_Proce.WAngle_X= Low_Pass * WAng_Proce_Last.WAngle_X +(1- Low_Pass)* Now_WAng.WAngle_X;
//	//��ͨ�˲�

	WAng_Proce_Last.WAngle_Y = WAng_Proce.WAngle_Y;//	//������֮ǰ�ȴ洢	
	WAng_Proce.WAngle_Y= Low_Pass * WAng_Proce_Last.WAngle_Y +(1- Low_Pass)* Now_WAng.WAngle_Y;
//	//��ͨ�˲�

///�ڻ�
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
	
	Absolute_PID(&PID_Pitch_Rate);//ִ�о���ʽPID�㷨
	Absolute_PID(&PID_Roll_Rate);//ִ�о���ʽPID�㷨
	
	Motor_Value[0]=(s16)PID_Pitch_Rate.CtrOut;
	Motor_Value[1]=(s16)PID_Roll_Rate.CtrOut;	
}

void Motor_Drive(s16 To_Motor[3])
{
	u8 i=0;
	for(i=0;i<3;i++)//����޷���������λ
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
	
	if(To_Motor[0]>0)//���1
	{
			TIM8->CCR1=0;
			TIM8->CCR2=To_Motor[0];
	}
	else
	{		
			TIM8->CCR1=-To_Motor[0];
			TIM8->CCR2=0;
	}
	
	if(To_Motor[1]>0)//���2
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
///*****************************��������************************************************/
//		 
//		motor_yaw = (s16) PID_Yaw_Rate.Out;
//    if(!motor_en)
//			motor_yaw=0;
//	  Motor_PWM_Update(motor_yaw);
//		motor_pitch = -(s16)(PID_Pitch_Rate.Out);
//	  set_current(motor_pitch *5);
//}


///*
// * ��������PID_Init
// * ����  ��PID������ʼ������
// * ����  ����
// * ���  ����
// */ 
//void PID_Init(void)
//{
//	
//	PID_Yaw_Angle.P =55;		//65
//	PID_Yaw_Angle.I = 0.00;//0.05
//		
//���ٶȻ�	
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

//	//�ǶȻ�����
//	PID_Pitch_Angle.P =27;
//	PID_Pitch_Angle.I =0.05;//0.1��ʱ�򳬵���0.01��
//	PID_Pitch_Angle.D =0;
//	
//���ٶȻ�	
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

*****************************************����ٶȻ��ŷ�***********************************

PID_AbsoluteType SPEED_PID;//����PID�㷨�Ľṹ��

s16 SpeedControl(s16 SpeedTag,s16 SpeedNow)
{
	SPEED_PID.ErrNow = SpeedTag - SpeedNow;
	
	SPEED_PID.Kp=15; //д�����ϵ��Ϊ
	SPEED_PID.Ki=0.8; //д�����ϵ��Ϊ
	SPEED_PID.Kd=0;//д��΢��ϵ��Ϊ5
	SPEED_PID.ErrIMax=15000; //д������������Ϊ1000 
	SPEED_PID.ErrIMin=-15000;	//����Ϊ-1000
	Absolute_PID(&SPEED_PID);//ִ�о���ʽPID�㷨
	
	return  SPEED_PID.CtrOut;         //��ȡ����ֵ
}

void OutToMotor1(s16 Control_value)
{
		if(Control_value<0)
		{
			Control_value=-Control_value;
			if(Control_value>=3600)//����޷�
				Control_value=3600;
			
			TIM4->CCR1=Control_value;	
			TIM4->CCR2=0;			
		}
		else
		{
			if(Control_value>=3600)//����޷�
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
			if(Control_value>=3600)//����޷�
				Control_value=3600;
			TIM4->CCR3=0;	
			TIM4->CCR4=Control_value;	
					
		}
		else
		{
			if(Control_value>=3600)//����޷�
				Control_value=3600;
		
			TIM4->CCR3=Control_value;	
			TIM4->CCR4=0;				
		}
}
*************/





