#include "stm32f4xx_conf.h"

volatile u8 SBUS_DATA[25];
volatile u16 ChanneL_Data[10]={0};//遥控器是9通道的
volatile s16 ControL_Data[10]={0}; //数据解算后存到C数组
//********************************以下为遥控器的处理函数****************************/
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
	
	/*通道1-4，9，10对应连续变化的模拟量*/
	ControL_Data[0]=ChanneL_Data[0]-1000;//各通道的中值是1000，范围是300～1700；
	ControL_Data[1]=ChanneL_Data[1]-1000;//各通道的中值是1000，范围是300～1700；
	ControL_Data[2]=ChanneL_Data[2]-300;//通道3是油门，只有正值
	if(ControL_Data[2]<0)
		ControL_Data[2]=0;//防止异常出现
	ControL_Data[3]=ChanneL_Data[3]-1000;//各通道的中值是1000，范围是300～1700；
	ControL_Data[8]=ChanneL_Data[8]-1000;//各通道的中值是1000，范围是300～1700；
	ControL_Data[9]=ChanneL_Data[9]-1000;//各通道的中值是1000，范围是300～1700；	
	
	/*通道5-8为开关量，其中5，8有两个档位，记为0，1；6，7有三个档位，记为-1，0，1*/
	if(ChanneL_Data[4]>1000)	
		ControL_Data[4]=1;//通道5拨到下面是1690左右，记为1
	else
		ControL_Data[4]=0;//通道5拨到上面是310左右，记为0
	
	if(ChanneL_Data[7]>1000)	
		ControL_Data[7]=1;//通道8拨到下面是1690左右，记为1
	else
		ControL_Data[7]=0;//通道8拨到上面是310左右，记为0
	
	if(ChanneL_Data[5]>1300)	
		ControL_Data[5]=1;//通道6拨到下面是1690左右，记为1
	else if(ChanneL_Data[5]<700)
		ControL_Data[5]=-1;//通道6拨到上面是310左右，记为-1
	else 
		ControL_Data[5]=0;//通道6拨到中间是1000左右，记为0
	
	if(ChanneL_Data[6]>1300)	
		ControL_Data[6]=1;//通道7拨到下面是1690左右，记为1
	else if(ChanneL_Data[6]<700)
		ControL_Data[6]=-1;//通道7拨到上面是310左右，记为-1
	else 
		ControL_Data[6]=0;//通道7拨到中间是1000左右，记为0
}



