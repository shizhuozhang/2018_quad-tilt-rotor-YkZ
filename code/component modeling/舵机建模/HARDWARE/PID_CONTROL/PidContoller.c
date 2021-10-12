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
	 PID->d_CtrOut = PID->Kp*(1+T/PID->Ti+PID->Td/T)* PID->ErrNow 
					- PID->Kp*(1+2*PID->Td/T) * PID->ErrLast
					+ PID->Kp*(PID->Td/T) * PID->ErrPrev;//
	
	 PID->ErrPrev = PID->ErrLast; //�洢�������´μ���
	 PID->ErrLast = PID->ErrNow;  //

	 PID->CtrOut = PID->d_CtrOut;//PID->CtrOut += PID->d_CtrOut;
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

//#define Low_Pass 0.85

extern volatile Angle_XYZ  Angle_Exp;///λ�û�����������Ƕ�

PID_IncrementType  PID_Pitch,PID_Yaw;	//�⻷���Ƕ�PID��
//Pitch��Y���ϲ��ڵ����YAw��Z�ᣬ�²�����
s16 Motor_Value[2]={0,0};//���������ֵ����Χ1500-7500

void PID_Angle(Angle_XYZ Now_angle, Angle_XYZ Exp_angle)
{	
	PID_Pitch.ErrNow=Exp_angle.Angle_Y -Now_angle.Angle_Y;
	PID_Yaw.ErrNow= Exp_angle.Angle_Z - Now_angle.Angle_Z;
	
	PID_Pitch.Kp=19;//19,0.11
	PID_Pitch.Ti=0.12;/////tiaohao
	PID_Pitch.Td=0;
	
	PID_Yaw.Kp=19;
	PID_Yaw.Ti=0.18;
	PID_Yaw.Td=0;
	
	Increment_PID(&PID_Pitch);//ִ�о���ʽPID�㷨
	Increment_PID(&PID_Yaw);//ִ�о���ʽPID�㷨
	
	Motor_Value[1]=(s16)PID_Pitch.CtrOut;
	Motor_Value[0]=(s16)PID_Yaw.CtrOut;	
	
	Motor_Drive(Motor_Value);
}

void Motor_Drive(s16 To_Motor[2])
{
	u8 i=0;
	
	TIM4->CCR1-=To_Motor[0];//ƫ��yaw
	TIM4->CCR2-=To_Motor[1];//����pitch		
//����޷���������λ
	if((TIM4->CCR1)>6000)		
		TIM4->CCR1=6000;
	
	else if((TIM4->CCR1)<3000)		
		TIM4->CCR1=3000;
	
	if((TIM4->CCR2)>6000)		
		TIM4->CCR2=6000;
	
	else if((TIM4->CCR2)<3000)		
		TIM4->CCR2=3000;
}



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





