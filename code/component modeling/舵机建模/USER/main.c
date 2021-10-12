#include "H_define.h"


#define Init_S1 3000
extern u16 time_num;
float Angle_Init[3]={0.0,0.0,0.0};
float Angle_Sum[3]={0.0};
	u8 GYRO_Flag=1;
int main()
{

	u8 Num=0;//陀螺仪初始化
	
	Init1();
	
	TIM4->CCR1=Init_S1;  
	delay_ms(1000);
	
    while(1)
	{					
		if(sign_usrt2)
		{	
			if(Num>100)
			{
				GYRO_Flag=0;
				Num=100;
				Angle_Init[0]=(float)(Angle_Sum[0]/100);
				Angle_Init[1]=(float)(Angle_Sum[1]/100);	
				Angle_Init[2]=(float)(Angle_Sum[2]/100);
				printf("%f  %f  %f \r\n",Angle_Init[0],Angle_Init[1],Angle_Init[2]);	
				printf("ok\r\n");	
				TIM3->CR1|=1<<0;//使能计数器				
			}
			
			if(GYRO_Flag)
			{
				Num++;	
				Angle_Sum[0]+=Angle_Now.Angle_X;
				Angle_Sum[1]+=Angle_Now.Angle_Y;
				Angle_Sum[2]+=Angle_Now.Angle_Z;
			}	
					
			
			sign_usrt2=0;	
			
		
		}
	}
}








