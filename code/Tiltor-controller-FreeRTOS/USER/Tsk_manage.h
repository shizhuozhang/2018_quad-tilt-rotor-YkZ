#ifndef __TSK_MANAGE_H 
#define __TSK_MANAGE_H  

#include "stm32f4xx_conf.h"
#include "FreeRTOS.h"
#include "task.h"


/*ע�⣺
1����������ȼ�������Խ�����ȼ�Խ��
2�������ջ��С������Ϊ��λ��STM32��һ���ֵ���4�ֽ�
*/

/***********ң�����źŴ�������**********/
#define SBUS_data_PRIO		5	//ң�����źŴ����������ȼ�
#define SBUS_data_SIZE 		150  //ң�����źŴ��������ջ��С	

/***********AHRS�źŴ�������**********/
#define AHRS_data_PRIO		6	//�������ȼ�
#define AHRS_data_SIZE 		150  //�����ջ��С

/***********����**********/
#define Debug_task_PRIO		1//�������ȼ�
#define Debug_task_SIZE 		100//�����ջ��С	

extern TaskHandle_t SBUS_data_Handler;	//ң�����źŴ���������
extern TaskHandle_t AHRS_data_Handler;	//AHRS�źŴ���������


/**********************����ʹ�ܳ�ʼ����������**************************/
void Creat_All_Task(void);
void SBUS_data_Analy(void *pvParameters);//ң�����źŴ���������
void AHRS_data_Analy(void *pvParameters);//AHRS�źŴ���������
void For_Debug(void *pvParameters);//����״̬���������////����ʱʹ��
#endif






