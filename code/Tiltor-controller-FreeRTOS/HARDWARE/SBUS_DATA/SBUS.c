#include "stm32f4xx_conf.h"

volatile u8 SBUS_DATA[25];
volatile u16 ChanneL_Data[10]={0};//ң������9ͨ����
volatile s16 ControL_Data[10]={0}; //���ݽ����浽C����
//********************************����Ϊң�����Ĵ�����****************************/
void SBUS_data_Pro(void)
{
	ChanneL_Data[0]=(SBUS_DATA[1]|(((u16)SBUS_DATA[2])<<8))&0x07ff;
	ChanneL_Data[1]=((SBUS_DATA[2]>>3)|(((u16)SBUS_DATA[3])<<5))&0x07ff;
	ChanneL_Data[2]=((SBUS_DATA[3]>>6)|(((u16)SBUS_DATA[4])<<2)|(((u16)SBUS_DATA[5])<<10))&0x07ff; 
	ChanneL_Data[3]=((SBUS_DATA[5]>>1)|(((u16)SBUS_DATA[6])<<7))&0x07ff; 
	ChanneL_Data[4]=((SBUS_DATA[6]>>4)|(((u16)SBUS_DATA[7])<<4))&0x07ff; 
	ChanneL_Data[5]=((SBUS_DATA[7]>>7)|(((u16)SBUS_DATA[8])<<1)|(((u16)SBUS_DATA[9])<<9))&0x07ff; 	
	ChanneL_Data[6]=((SBUS_DATA[9]>>2)|(((u16)SBUS_DATA[10])<<6))&0x07ff; 	
	ChanneL_Data[7]=((SBUS_DATA[10]>>5)|(((u16)SBUS_DATA[11])<<3))&0x07ff; 
	ChanneL_Data[8]=(SBUS_DATA[12]|(((u16)SBUS_DATA[13])<<8))&0x07ff; 
	ChanneL_Data[9]=((SBUS_DATA[13]>>3)|(((u16)SBUS_DATA[14])<<5))&0x07ff;
	
	/*ͨ��1-4��9��10��Ӧ�����仯��ģ����*/
	ControL_Data[0]=ChanneL_Data[0]-1000;//��ͨ������ֵ��1000����Χ��300��1700��
	ControL_Data[1]=ChanneL_Data[1]-1000;//��ͨ������ֵ��1000����Χ��300��1700��
	ControL_Data[2]=ChanneL_Data[2]-300;//ͨ��3�����ţ�ֻ����ֵ
	if(ControL_Data[2]<0)
		ControL_Data[2]=0;//��ֹ�쳣����
	ControL_Data[3]=ChanneL_Data[3]-1000;//��ͨ������ֵ��1000����Χ��300��1700��
	ControL_Data[8]=ChanneL_Data[8]-1000;//��ͨ������ֵ��1000����Χ��300��1700��
	ControL_Data[9]=ChanneL_Data[9]-1000;//��ͨ������ֵ��1000����Χ��300��1700��	
	
	/*ͨ��5-8Ϊ������������5��8��������λ����Ϊ0��1��6��7��������λ����Ϊ-1��0��1*/
	if(ChanneL_Data[4]>1000)	
		ControL_Data[4]=1;//ͨ��5����������1690���ң���Ϊ1
	else
		ControL_Data[4]=0;//ͨ��5����������310���ң���Ϊ0
	
	if(ChanneL_Data[7]>1000)	
		ControL_Data[7]=1;//ͨ��8����������1690���ң���Ϊ1
	else
		ControL_Data[7]=0;//ͨ��8����������310���ң���Ϊ0
	
	if(ChanneL_Data[5]>1300)	
		ControL_Data[5]=1;//ͨ��6����������1690���ң���Ϊ1
	else if(ChanneL_Data[5]<700)
		ControL_Data[5]=-1;//ͨ��6����������310���ң���Ϊ-1
	else 
		ControL_Data[5]=0;//ͨ��6�����м���1000���ң���Ϊ0
	
	if(ChanneL_Data[6]>1300)	
		ControL_Data[6]=1;//ͨ��7����������1690���ң���Ϊ1
	else if(ChanneL_Data[6]<700)
		ControL_Data[6]=-1;//ͨ��7����������310���ң���Ϊ-1
	else 
		ControL_Data[6]=0;//ͨ��7�����м���1000���ң���Ϊ0
}



