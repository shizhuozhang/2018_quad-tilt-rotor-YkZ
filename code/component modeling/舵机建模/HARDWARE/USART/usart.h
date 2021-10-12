#ifndef __USART_H
#define __USART_H

#include "sys.h"

#if ___USART_PRINTF
	#include "stdio.h"	
#endif
 

////////////����1/////////////
#if __USART1
	void usart1(u32 pclk2,u32 bound);
#endif
/////////////////////////////

////////////����2/////////////
#if __USART2
	void usart2(u32 pclk1,u32 bound);
#endif
/////////////////////////////

////////////����3/////////////
#if __USART3
	void usart3(u32 pclk1,u32 bound);
#endif
/////////////////////////////

#endif	   
















