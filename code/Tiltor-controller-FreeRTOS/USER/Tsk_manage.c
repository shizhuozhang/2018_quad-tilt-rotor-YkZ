//////////////////////////////////////////////////////////////////////////////////	 
//REFER TO:����ԭ��@ALIENTEK
//������̳:www.openedv.com
//////////////////////////////////////////////////////////////////////////////////  
#include "Tsk_manage.h"

/******����������*******/
TaskHandle_t SBUS_data_Handler;	//ң�����źŴ���������
TaskHandle_t AHRS_data_Handler;	//AHRS�źŴ���������
TaskHandle_t Debugtask_Handler;	//������

/******����������صı�������*******/
char RunTimeInfo[400];		//������������ʱ����Ϣ
volatile unsigned long long FreeRTOSRunTimeTicks;

//    taskENTER_CRITICAL();           //�����ٽ���
//    taskEXIT_CRITICAL();            //�˳��ٽ���

void Creat_All_Task(void)
{
	/*******����ң�����źŴ������� ******/
	xTaskCreate((TaskFunction_t )SBUS_data_Analy,    	
                (const char*    )"SBUS_data_task",   	
                (uint16_t       )SBUS_data_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )SBUS_data_PRIO,	
                (TaskHandle_t*  )&SBUS_data_Handler); 
				
    /******����AHRS�źŴ�������*******/
    xTaskCreate((TaskFunction_t )AHRS_data_Analy,     
                (const char*    )"AHRS_data_task",   
                (uint16_t       )AHRS_data_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )AHRS_data_PRIO,
                (TaskHandle_t*  )&AHRS_data_Handler);
				
    /*******�������Բ�������******/
    xTaskCreate((TaskFunction_t )For_Debug,     
                (const char*    )"Debug_task",   
                (uint16_t       )Debug_task_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Debug_task_PRIO,
                (TaskHandle_t*  )&Debugtask_Handler);   
}

u8 Sbus_OK=0;
volatile u8 Dma1_T1_Close=1;//��ʼʱ���ŵģ��������ٿ���	
//ң�����źŴ��������� 
void SBUS_data_Analy(void *pvParameters)
{
	u8 i=0;
	u32 value=pdFALSE;
	while(1)
    {       	
//	printf("num1=%d\r\n",num1);	
		value=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);//�ȴ�����֪ͨ������ 
//		printf("SBUS Value= %d\r\n",value);		
		if(value!=0)			//��ȡ�ź����ɹ�???????Ϊʲô�ǵ���2
		{
			SBUS_data_Pro();
			
//			for(i=0;i<10;i++)
//				printf("channel %d:%d\r\n",i,ControL_Data[i]);
//			printf("ok\r\n");
			
			Sbus_OK=1;//ң�����ݽ��յ�
			Dma1_T1_Close=1;
		}			
		LED0=~LED0;		
        vTaskDelay(1);//��ʱ���ɹ���������Ῠ����֪Ϊ��
    }
}  

u8 Ahrs_OK=0;
volatile u8 Dma1_T5_Close=1;
//AHRS�źŴ���������
void AHRS_data_Analy(void *pvParameters)
{	
	u8 i=0;
	u32 value=pdFALSE;
	while(1)
    {	
//		printf("num2=%d\r\n",num2);	
		printf("AHRS Value= %d\r\n",value);		
		value=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);//�ȴ�����֪ͨ������ 
	
		
		if(value!=0)			//��ȡ�ź����ɹ�
		{
			if(AHRS_data_Pro())		//AHRSģ��ĸ���Ƶ����100HZ	
			{
				Ahrs_OK=1;
//				printf("yaw%.2f  pitch%.2f  roll%.2f\r\n",Att_Angle.yaw,Att_Angle.pitch,Att_Angle.roll);
			}
			Ahrs_Flag1=1;
			Dma1_T5_Close=1;		
		}
		LED1=~LED1;		
        vTaskDelay(1);//��ʱ���ɹ���������Ῠ����֪Ϊ��
    }
}

//����ʹ�õĲ�������
void For_Debug(void *pvParameters)
{
	u8 key=0;
	UBaseType_t AHRS_High_mark;
	UBaseType_t SBUS_High_mark;	
	
//	vTaskList(InfoBuffer);			//��ȡ�����������Ϣ,̫ռ�ڴ���
//	printf("%s\r\n",InfoBuffer);	//ͨ�����ڴ�ӡ�����������Ϣ

	while(1)
	{	
		key=KEY_Scan();
		
		if(key==KEY1_PRES)
		{
			memset(RunTimeInfo,0,400);				//��Ϣ����������
			vTaskGetRunTimeStats(RunTimeInfo);		//��ȡ��������ʱ����Ϣ
			printf("������\t\t\t����ʱ��\t������ռ�ٷֱ�\r\n");
			printf("%s\r\n",RunTimeInfo);	
		}
		
		if(key==KEY2_PRES)
		{
			SBUS_High_mark=uxTaskGetStackHighWaterMark(SBUS_data_Handler); 
			printf("SBUS_High_mark=%d\r\n",SBUS_High_mark);
		
			AHRS_High_mark=uxTaskGetStackHighWaterMark(AHRS_data_Handler); 
			printf("AHRS_High_mark=%d\r\n",AHRS_High_mark);
		}		
        vTaskDelay(100);
	}
}

//��ʼ��TIM3ʹ��ΪFreeRTOS��ʱ��ͳ���ṩʱ��
void ConfigureTimeForRunTimeStats(void)
{
	FreeRTOSRunTimeTicks=0;
	TIM7_Init(50-1,84-1);
}













