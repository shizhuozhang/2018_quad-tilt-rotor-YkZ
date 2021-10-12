#include "H_define.h"
#include "SBUS.h"

u16 ChanneL_Data[10]={0};//遥控器是9通道的
s16 ControL_Data[10]={0}; //数据解算后存到C数组
//u8 SBUS_OK=0;
	
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
}


/*
void DMA1_Channel3_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA1_IT_TC3)==SET)
	{
		//遥控	
		dr16_data.channel0=(dr16_rbuff[0]|(dr16_rbuff[1]<<8))&0x07ff;    // Channel 0 
		dr16_data.channel1=((dr16_rbuff[1]>>3)|(dr16_rbuff[2]<<5))&0x07ff; // Channel 1 
		dr16_data.channel2=((dr16_rbuff[2]>>6)|(dr16_rbuff[3]<< 2)|(dr16_rbuff[4]<<10))&0x07ff; // Channel 2 
		dr16_data.channel3=((dr16_rbuff[4]>>1)|(dr16_rbuff[5]<<7))&0x07ff; //Channel 3 
		//s按键对应：1 上  2 下 3 中
		dr16_data.s1=((dr16_rbuff[5]>>4)&0x000C)>>2; //s1 
		dr16_data.s2=((dr16_rbuff[5]>>4)&0x0003);   //s2	
		//键鼠信息
		dr16_data.mouse_x=dr16_rbuff[6]|(dr16_rbuff[7]<<8); //Mouse X 
		dr16_data.mouse_y=dr16_rbuff[8]|(dr16_rbuff[9]<<8); //Mouse Y 
		dr16_data.mouse_z=dr16_rbuff[10]|(dr16_rbuff[11]<<8); //Mouse Z 
		*********************************对鼠标数据进行处理**************************************************************
		dr16_data.mouse_x=dr16_data.mouse_x*(1+dr16_data.mouse_x*0.002);
		dr16_data.mouse_y=dr16_data.mouse_y*(1+dr16_data.mouse_y*0.002);
		dr16_data.mouse_z=dr16_data.mouse_z*(1+dr16_data.mouse_z*0.002);
		****************************************************************************************************************
		dr16_data.mouse_l=dr16_rbuff[12];  //Mouse Left 
		dr16_data.mouse_r=dr16_rbuff[13];  //Mouse Right 
		dr16_data.key_table=dr16_rbuff[14]|(dr16_rbuff[15]<<8); //Key table 
		
		
		//根据说明C0~4与channel0~4的对应关系如下：
		C[0]=(dr16_data.channel0-1024);
		C[1]=(dr16_data.channel1-1024);
		C[2]=(dr16_data.channel2-1024);
		C[3]=(dr16_data.channel3-1024);
//		C[0]=2188+(float)(dr16_data.channel0-1024)/660*722;
//		C[1]=2188-(float)(dr16_data.channel1-1024)/660*722;
//		C[2]=2188+(float)(dr16_data.channel2-1024)/660*722;
//		C[3]=2188+(float)(dr16_data.channel3-1024)/660*722;
//		//按键的数值：低：1016 高：2020 没有信号时：1518对应 定时器的数为：低：1462 高：2908 没有信号时：2185
		if(dr16_data.s1==1)
			C[4]=1;
		if(dr16_data.s1==2)
			C[4]=2;
		if(dr16_data.s1==3)
			C[4]=3;

		if(dr16_data.s2==1)
			C[5]=1;
		if(dr16_data.s2==2)
			C[5]=2;
		if(dr16_data.s2==3)
			C[5]=3;
	
		DBUS_OK=1;
		
		DMA_ClearFlag(DMA1_IT_TC3);			
	}
}
*/
