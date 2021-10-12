#ifndef __TSK_MANAGE_H 
#define __TSK_MANAGE_H  

#include "stm32f4xx_conf.h"
#include "FreeRTOS.h"
#include "task.h"


/*注意：
1、任务的优先级是数字越大，优先级越高
2、任务堆栈大小是以字为单位，STM32中一个字等于4字节
*/

/***********遥控器信号处理任务**********/
#define SBUS_data_PRIO		5	//遥控器信号处理任务优先级
#define SBUS_data_SIZE 		150  //遥控器信号处理任务堆栈大小	

/***********AHRS信号处理任务**********/
#define AHRS_data_PRIO		6	//任务优先级
#define AHRS_data_SIZE 		150  //任务堆栈大小

/***********任务**********/
#define Debug_task_PRIO		1//任务优先级
#define Debug_task_SIZE 		100//任务堆栈大小	

extern TaskHandle_t SBUS_data_Handler;	//遥控器信号处理任务句柄
extern TaskHandle_t AHRS_data_Handler;	//AHRS信号处理任务句柄


/**********************外设使能初始化函数声明**************************/
void Creat_All_Task(void);
void SBUS_data_Analy(void *pvParameters);//遥控器信号处理任务函数
void AHRS_data_Analy(void *pvParameters);//AHRS信号处理任务函数
void For_Debug(void *pvParameters);//运行状态监测任务函数////调试时使用
#endif






