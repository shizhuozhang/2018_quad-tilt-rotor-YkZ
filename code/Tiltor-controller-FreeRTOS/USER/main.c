/*调试完成时应删除调试任务并关闭相关的宏定义
	1、去掉ASSERT断言	configASSERT(x)
	2、运行时间宏定义	configGENERATE_RUN_TIME_STATS
*/
#include "Tsk_manage.h"

int main(void)
{ 
	Init1();		        //硬件底层初始化	
	Creat_All_Task();        //创建全部的任务 
    vTaskStartScheduler();   //开启任务调度
}
 



