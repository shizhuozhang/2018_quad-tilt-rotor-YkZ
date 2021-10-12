//////////////////////////////////////////////////////////////////////////////////	 
//REFER TO:正点原子@ALIENTEK
//技术论坛:www.openedv.com
//////////////////////////////////////////////////////////////////////////////////  
#include "Tsk_manage.h"

/******任务句柄定义*******/
TaskHandle_t SBUS_data_Handler;	//遥控器信号处理任务句柄
TaskHandle_t AHRS_data_Handler;	//AHRS信号处理任务句柄
TaskHandle_t Debugtask_Handler;	//任务句柄

/******调试任务相关的变量声明*******/
char RunTimeInfo[400];		//保存任务运行时间信息
volatile unsigned long long FreeRTOSRunTimeTicks;

//    taskENTER_CRITICAL();           //进入临界区
//    taskEXIT_CRITICAL();            //退出临界区

void Creat_All_Task(void)
{
	/*******创建遥控器信号处理任务 ******/
	xTaskCreate((TaskFunction_t )SBUS_data_Analy,    	
                (const char*    )"SBUS_data_task",   	
                (uint16_t       )SBUS_data_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )SBUS_data_PRIO,	
                (TaskHandle_t*  )&SBUS_data_Handler); 
				
    /******创建AHRS信号处理任务*******/
    xTaskCreate((TaskFunction_t )AHRS_data_Analy,     
                (const char*    )"AHRS_data_task",   
                (uint16_t       )AHRS_data_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )AHRS_data_PRIO,
                (TaskHandle_t*  )&AHRS_data_Handler);
				
    /*******创建调试测试任务******/
    xTaskCreate((TaskFunction_t )For_Debug,     
                (const char*    )"Debug_task",   
                (uint16_t       )Debug_task_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )Debug_task_PRIO,
                (TaskHandle_t*  )&Debugtask_Handler);   
}

u8 Sbus_OK=0;
volatile u8 Dma1_T1_Close=1;//开始时关着的，有数据再开启	
//遥控器信号处理任务函数 
void SBUS_data_Analy(void *pvParameters)
{
	u8 i=0;
	u32 value=pdFALSE;
	while(1)
    {       	
//	printf("num1=%d\r\n",num1);	
		value=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);//等待任务通知，死等 
//		printf("SBUS Value= %d\r\n",value);		
		if(value!=0)			//获取信号量成功???????为什么是等于2
		{
			SBUS_data_Pro();
			
//			for(i=0;i<10;i++)
//				printf("channel %d:%d\r\n",i,ControL_Data[i]);
//			printf("ok\r\n");
			
			Sbus_OK=1;//遥控数据接收到
			Dma1_T1_Close=1;
		}			
		LED0=~LED0;		
        vTaskDelay(1);//延时不可过长，否则会卡，不知为何
    }
}  

u8 Ahrs_OK=0;
volatile u8 Dma1_T5_Close=1;
//AHRS信号处理任务函数
void AHRS_data_Analy(void *pvParameters)
{	
	u8 i=0;
	u32 value=pdFALSE;
	while(1)
    {	
//		printf("num2=%d\r\n",num2);	
		printf("AHRS Value= %d\r\n",value);		
		value=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);//等待任务通知，死等 
	
		
		if(value!=0)			//获取信号量成功
		{
			if(AHRS_data_Pro())		//AHRS模块的跟新频率是100HZ	
			{
				Ahrs_OK=1;
//				printf("yaw%.2f  pitch%.2f  roll%.2f\r\n",Att_Angle.yaw,Att_Angle.pitch,Att_Angle.roll);
			}
			Ahrs_Flag1=1;
			Dma1_T5_Close=1;		
		}
		LED1=~LED1;		
        vTaskDelay(1);//延时不可过长，否则会卡，不知为何
    }
}

//调试使用的测试任务
void For_Debug(void *pvParameters)
{
	u8 key=0;
	UBaseType_t AHRS_High_mark;
	UBaseType_t SBUS_High_mark;	
	
//	vTaskList(InfoBuffer);			//获取所有任务的信息,太占内存了
//	printf("%s\r\n",InfoBuffer);	//通过串口打印所有任务的信息

	while(1)
	{	
		key=KEY_Scan();
		
		if(key==KEY1_PRES)
		{
			memset(RunTimeInfo,0,400);				//信息缓冲区清零
			vTaskGetRunTimeStats(RunTimeInfo);		//获取任务运行时间信息
			printf("任务名\t\t\t运行时间\t运行所占百分比\r\n");
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

//初始化TIM3使其为FreeRTOS的时间统计提供时基
void ConfigureTimeForRunTimeStats(void)
{
	FreeRTOSRunTimeTicks=0;
	TIM7_Init(50-1,84-1);
}













