#ifndef __USART_H
#define __USART_H 
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	   
//REFER TO :正点原子@ALIENTEK
//技术论坛:www.openedv.com
////////////////////////////////////////////////////////////////////////////////// 

#if ___USART_PRINTF
	#include "stdio.h"	
#endif	  	

////////////串口1/////////////
#if __USART1
	void Usart1_init(u32 pclk2,u32 bound); 
#endif

////////////串口2/////////////
#if __USART2
	void Usart2_init(u32 pclk2,u32 bound); 
#endif

////////////串口3/////////////
#if __USART3
	void Usart3_init(u32 pclk2,u32 bound); 
#endif

////////////串口4/////////////
#if __UART4
	void Uart4_init(u32 pclk2,u32 bound); 
#endif

////////////串口5/////////////
#if __UART5
	void Uart5_init(u32 pclk2,u32 bound); 
#endif

////////////串口6/////////////
#if __USART6
	void Usart6_init(u32 pclk2,u32 bound); 
#endif

#endif	   
















