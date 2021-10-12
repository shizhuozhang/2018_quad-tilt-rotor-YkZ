#include "H_define.h"


u8 D_6050[32];
u8 D_6050_ANGLE[6];
u8 D_6050_WANG[6];

//cndtr:��������
//cpar:�����ַ
//cmar:�洢��ַ
void DMA1_Channel3_Init(u16 cndtr,u32 cpar,u32 cmar)  //usart3
{
	RCC->AHBENR|=1<<0;			//����DMA1ʱ��
	delay_ms(5);				//�ȴ�DMAʱ���ȶ�
	DMA1_Channel3->CPAR=cpar; 	 	//DMA1 �����ַ 
	DMA1_Channel3->CMAR=cmar; 	//DMA1,�洢����ַ
	DMA1_Channel3->CNDTR=cndtr;    	//DMA1,����������
	DMA1_Channel3->CCR=0X00000000;	//��λ
	DMA1_Channel3->CCR|=0<<4;  		//�������
	DMA1_Channel3->CCR|=1<<5;  		//��ͨģʽ
	DMA1_Channel3->CCR|=0<<6; 		//�����ַ������ģʽ
	DMA1_Channel3->CCR|=1<<7; 	 	//�洢������ģʽ
	DMA1_Channel3->CCR|=0<<8; 	 	//�������ݿ��Ϊ8λ
	DMA1_Channel3->CCR|=0<<10; 		//�洢�����ݿ��8λ
	DMA1_Channel3->CCR|=1<<12; 		//�е����ȼ�
	DMA1_Channel3->CCR|=0<<14; 		//�Ǵ洢�����洢��ģʽ
	DMA1_Channel3->CCR|=1<<1;			//����TC�ж�
	DMA1_Channel3->CCR|=1<<0;			//ͨ������
	MY_NVIC_Init(1,0,DMA1_Channel3_IRQn,2);
}

//cndtr:��������
//cpar:�����ַ
//cmar:�洢��ַ
void DMA1_Channel6_Init(u16 cndtr,u32 cpar,u32 cmar)   //usart2
{
	RCC->AHBENR|=1<<0;			//����DMA1ʱ��
	delay_ms(5);				//�ȴ�DMAʱ���ȶ�
	DMA1_Channel6->CPAR=cpar; 	 	//DMA1 �����ַ 
	DMA1_Channel6->CMAR=cmar; 	//DMA1,�洢����ַ
	DMA1_Channel6->CNDTR=cndtr;    	//DMA1,����������
	DMA1_Channel6->CCR=0X00000000;	//��λ
	DMA1_Channel6->CCR|=0<<4;  		//�������
	DMA1_Channel6->CCR|=1<<5;  		//��ͨģʽ
	DMA1_Channel6->CCR|=0<<6; 		//�����ַ������ģʽ
	DMA1_Channel6->CCR|=1<<7; 	 	//�洢������ģʽ
	DMA1_Channel6->CCR|=0<<8; 	 	//�������ݿ��Ϊ8λ
	DMA1_Channel6->CCR|=0<<10; 		//�洢�����ݿ��8λ
	DMA1_Channel6->CCR|=1<<12; 		//�е����ȼ�
	DMA1_Channel6->CCR|=0<<14; 		//�Ǵ洢�����洢��ģʽ
	DMA1_Channel6->CCR|=1<<1;			//����TC�ж�
	DMA1_Channel6->CCR|=1<<0;			//ͨ������
	MY_NVIC_Init(1,3,DMA1_Channel6_IRQn,2);
}



void  DMA1_Channel3_IRQHandler()//dma1�ж�  usart3
{
	if(DMA1->ISR&(1<<9))//�������
	{
		DMA1->IFCR|=1<<9;//�����־λ
	}	
}

u8 sign_usrt2=0;
u8 Dma1_C6_Close=0;

volatile WAng_XYZ   WAng_Now;
volatile Angle_XYZ  Angle_Now; 
volatile Angle_XYZ  Acce_Now;
extern u8 GYRO_Flag;
void  DMA1_Channel6_IRQHandler()//dma1�ж�
{
	if(DMA1->ISR&(1<<21))//�������
	{
		DMA1->IFCR|=1<<21;//�����־λ
		if((0X51!=D_6050[0])||(0X52!=D_6050[11])||(0X53!=D_6050[22]))//
		{
			DMA1_Channel6->CCR&=~(1<<0);			//ͨ������
			Dma1_C6_Close=1;
		}
		else
		{
//			Update_Acce();		
//			Update_WAng();
			Update_Angle();
			sign_usrt2=1;
			if(GYRO_Flag==0)
				printf("%f\r\n",Angle_Now.Angle_Z);
		}
	}
	
}

void Update_Acce()//���ڶ�ȡ6050���ݰ�������////��־λsign_usrt2
{
	Acce_Now.Angle_X= ((short)(D_6050[2]<<8| D_6050[1]))/32768.0*16*G;  //-Angle_Init[0]X���ת�ǣ�x �ᣩ��ȥ��ʼƫ��
	Acce_Now.Angle_Y= ((short)(D_6050[4]<<8| D_6050[3]))/32768.0*16*G;  //-Angle_Init[1]Y�ḩ���ǣ�y �ᣩ
	Acce_Now.Angle_Z= ((short)(D_6050[6]<<8| D_6050[5]))/32768.0*16*G;  //-Angle_Init[2]Z�ḩ���ǣ�y �ᣩ
}

void Update_Angle()//���ڶ�ȡ6050���ݰ�������////��־λsign_usrt2
{
	Angle_Now.Angle_X= -(((short)(D_6050[24]<<8| D_6050[23]))/32768.0*180)-Angle_Init[0];  //X���ת�ǣ�x �ᣩ��ȥ��ʼƫ��
	Angle_Now.Angle_Y= -(((short)(D_6050[26]<<8| D_6050[25]))/32768.0*180)-Angle_Init[1];  //Y�ḩ���ǣ�y �ᣩ
	Angle_Now.Angle_Z= -(((short)(D_6050[28]<<8| D_6050[27]))/32768.0*180)-Angle_Init[2];	//Z�ḩ���ǣ�y �ᣩ
}

void Update_WAng()//���ڶ�ȡ6050���ݰ�������////��־λsign_usrt2
{
	WAng_Now.WAngle_X = ((short)(D_6050[13]<<8| D_6050[12]))/32768.0*2000;  //X����ٶ�
	WAng_Now.WAngle_Y = ((short)(D_6050[15]<<8| D_6050[14]))/32768.0*2000; //Y����ٶ�
	WAng_Now.WAngle_Z = ((short)(D_6050[17]<<8| D_6050[16]))/32768.0*2000; //Z����ٶ�
}

