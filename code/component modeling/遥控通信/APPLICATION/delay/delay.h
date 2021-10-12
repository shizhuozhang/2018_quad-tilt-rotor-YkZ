#ifndef __DELAY_H
#define __DELAY_H 			   
#include <sys.h>	  
//////////////////////////////////////////////////////////////////////////////////  
//使用SysTick的普通计数模式对延迟进行管理(支持ucosii)
//REFER TO :正点原子@ALIENTEK
//技术论坛:www.openedv.com
////////////////////////////////////////////////////////////////////////////////// 
#if __DELAY
	void delay_init(u8 SYSCLK);
	void delay_ms(u16 nms);
	void delay_us(u32 nus);
#endif

#endif





























