/*�������ʱӦɾ���������񲢹ر���صĺ궨��
	1��ȥ��ASSERT����	configASSERT(x)
	2������ʱ��궨��	configGENERATE_RUN_TIME_STATS
*/
#include "Tsk_manage.h"

int main(void)
{ 
	Init1();		        //Ӳ���ײ��ʼ��	
	Creat_All_Task();        //����ȫ�������� 
    vTaskStartScheduler();   //�����������
}
 



