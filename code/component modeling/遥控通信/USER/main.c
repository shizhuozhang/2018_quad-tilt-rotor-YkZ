#include "H_define.h"

int main(void)
{ 
	u8 t=0;
	Init1();
	Init2();
	while(1)
	{
		
		delay_ms(200);
		
		printf("tim8 %d %d %d %d\r\n",TIM8->CCR1,TIM8->CCR2,TIM8->CCR3,TIM8->CCR4);
		
		printf("tim3 %d %d %d %d\r\n",TIM3->CCR1,TIM3->CCR2,TIM3->CCR3,TIM3->CCR4);
		
//		if(sign_Adc1)
//		{
//			sign_Adc1=0;
//			Power_Monitor();
////			for(t=0;t<6;t++)
////			{
////				printf("%d %f %f %f\r\n",t,Voltage[t],Current[t],Walte[t]);
////			}
			printf("\r\n");
//		}	
//		if(sign_usrt2==1)
//		{
//			for(t=0;t<42;t++)
//			{
//				printf("%d   ",t);
//				printf("%x\r\n", AHRS_DATA[t]);
//			}
//			printf("OK\r\n");
//			
//			sign_usrt2=0;		
//		}
		
		
//		printf("t:%d\r\n",t);
////		LED0=~LED0;
////		LED1=~LED1;
//		delay_ms(200);
//		t++;
	}
}
