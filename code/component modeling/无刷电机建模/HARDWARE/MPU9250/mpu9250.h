#ifndef _MPU9250_H
#define _MPU9250_H

#include "sys.h"

#define Byte16(Type, ByteH, ByteL)  ((Type)((((u16)(ByteH))<<8) | ((u16)(ByteL))))

//#define MPU9250_CS(X)	(X==0)?GPIOA->BSRR&=0XFFEF:GPIOA->BSRR|=1<<4 //MPU9250片选信号PA4
//#define MPU9250_CS  PAout(4)//MPU9250片选信号PA4

		
//寄存器定义
#define SELF_TEST_X_GYRO	0X00
#define SELF_TEST_Y_GYRO	0X01
#define SELF_TEST_Z_GYRO	0X02

#define SELF_TEST_X_ACCEL	0X0D
#define SELF_TEST_Y_ACCEL	0X0E
#define SELF_TEST_Z_ACCEL	0X0F

#define XG_OFFSET_H			0X13
#define XG_OFFSET_L			0X14
#define YG_OFFSET_H			0X15
#define YG_OFFSET_L			0X16
#define ZG_OFFSET_H			0X17
#define ZG_OFFSET_L			0X18

#define SMPLRT_DIV			0X19 //陀螺仪采样率 典型值为0X07  1000/(1+7)=125HZ
#define CONFIG				0X1A //低通滤波器  典型值0x06 5hz
#define GYRO_CONFIG			0X1B //陀螺仪测量范围 0X18 正负2000度
#define ACCEL_CONFIG		0X1C //加速度计测量范围 0X18 正负16g
#define ACCEL_CONFIG2		0X1D //加速度计低通滤波器 0x06 5hz

#define LP_ACCEL_ODR		0X1E
#define WOM_THR				0X1F
#define FIFO_EN				0X23

#define ACCEL_XOUT_H		0X3B  //加速度计输出数据
#define ACCEL_XOUT_L		0X3C
#define ACCEL_YOUT_H		0X3D
#define ACCEL_YOUT_L		0X3E
#define ACCEL_ZOUT_H		0X3F
#define ACCEL_ZOUT_L		0X40

#define TEMP_OUT_H			0X41  //温度计输出数据
#define TEMP_OUT_L			0X42

#define GYRO_XOUT_H			0X43  //陀螺仪输出数据
#define GYRO_XOUT_L			0X44
#define GYRO_YOUT_H			0X45
#define GYRO_YOUT_L			0X46
#define GYRO_ZOUT_H			0X47
#define GYRO_ZOUT_L			0X48

#define MAG_XOUT_L          0X03
#define MAG_XOUT_H          0X04
#define MAG_YOUT_L          0X05
#define MAG_YOUT_H          0X06
#define MAG_ZOUT_L          0X07
#define MAG_ZOUT_H          0X08

#define PWR_MGMT_1			0X6B //电源管理1 典型值为0x00
#define PWR_MGMT_2			0X6C //电源管理2 典型值为0X00

#define WHO_AM_I			0X75 //器件ID MPU9250默认ID为0X71
//!!!!!!!!!!!!!!!!!!注意如果是6500地址为0x70，，如果是9250地址为0x75
#define WHO_AM_MAG			0X00 //器件ID MPU9250默认ID为0X71
#define USER_CTRL			0X6A //用户配置 当为0X10时使用SPI模式


void MPU9250_Date_Offset1(u16 cnt);
void MPU9250_Date_Offset2(u16 cnt);
void MPU9250_ReadValue(void);
u8 MPU9250_Init(void);
void SPI1_Init(void);
u8 MPU9250_Write_Reg(u8 reg,u8 value);
u8 MPU9250_Read_Reg(u8 reg);
u8 SPI1_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
#endif


