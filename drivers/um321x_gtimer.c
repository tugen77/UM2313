/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : um_gtimer.c
 * Description : um_gtimer source file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-02-21
 ***********************************************************************/
#include "um321x_gtimer.h"

/*******************************************************************
* Function		: GTIMER0_IRQHandler
* Description	: GTIMER0_IRQHandler
* Input			: none
* Output		: none
* Return		: none
********************************************************************/
void GTIMER0_IRQHandler(void)
{
#ifdef gtimer_interrupt											 /*溢出中断测试*/
	REG_GTIM0_CIF = 0xFF;							             /* 清除中断 */
//	static int a=0;
//	printfS("timer0=%d\r\n",a++);
#endif	
#ifdef gtimer_capture                                            /* 输入捕获*/
	REG_GTIM_CCIF |= (3<<0);
//	printfS("ch0=%d    ch2=%d\r\n",REG_GTIM_CH0_CR,REG_GTIM_CH2_CR);
#endif	
	
}

/*******************************************************************
* Function		: gtimer0_interrupt_test
* Description	: gtimer0_interrupt_test
* Input			: UINT32 arr
*				  UINT16 div
* Return		: none
********************************************************************/
void gtimer0_interrupt_test(UINT32 arr,UINT16 div)
{
	/* gtimer0定时器中断方式 */
	REG_SCU_PERICLKEN |= (1<<9);									/* 开启GTimer时钟使能 */
	REG_SCU_PERIRESET |= (1<<9);									/* GTimer正常工作 */
	REG_GTIM0_CR &= ~(1<<0);										/* 关闭定时器 */
	REG_GTIM0_CR |= (1<<4);											/* 确定计数方向 */
	REG_GTIM0_CR |= (1<<5);											/* 边沿对其模式 */
	
	REG_GTIM0_ARR = arr;										    /* 自动重载值ARR */
	REG_GTIM_PSC |= (div<<0*3);										/* 预分频因子 */
	
	REG_GTIM0_CIF = 0xFF;											/* 清除定时器更新中断标志 */
	REG_GTIM0_CR &= ~(1<<3);										/* 开启定时器更新中断 */
	REG_GTIM0_CR |= (2<<1);											/* 选择模式：循环模式 */
	REG_GTIM0_CR |= (1<<0);											/* 使能定时器 */
	REG_GTIM_ICMODE = 0x05;
	NVIC_ClearPendingIRQ(GTIMER0_IRQn);
	NVIC_EnableIRQ(GTIMER0_IRQn);
	
}

/*******************************************************************
* Function		: gtimer0_pwm_out_test
* Description	: gtimer0_pwm_out_test
* Input			: UINT32 arr
*				  UINT16 div
				  UINT32 duty
* Return		: none
********************************************************************/
void gtimer0_pwm_out_test(UINT32 arr,UINT16 div,UINT32 duty)
{
	/* gtimer0 PWM输出测试*/
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A; 						/* 清除IO写保护 */
	
	REG_SCU_PERICLKEN |= (1<<9);									/* 开启GTimer时钟使能 */
	REG_SCU_PERIRESET |= (1<<9);									/* GTimer正常工作 */
	
	REG_SCU_PERICLKEN |= (1<<16);									/* 开启GPIOA时钟使能 */
	REG_SCU_PERIRESET |= (1<<16);									/* GPIOA正常工作 */
	
	REG_SCU_PASEL = 0x00;
	REG_SCU_PASEL |= (2<<4);										/* PA1复用为TIM0_TOG */
	REG_SCU_PASEL |= (2<<8);										/* PA2复用为TIM0_TOG反向输出 */
	REG_SCU_IOCTRLPROTECT = 0xFFFFFFFF; 							/* IO写保护 */
	
	REG_GTIM0_CR &= ~(1<<0);										/* 关闭定时器 */
	REG_GTIM0_CR &= ~(1<<4);										/* 确定计数方向 */
	REG_GTIM0_CR &= ~(1<<5);										/* 边沿对其模式 */
	REG_GTIM0_ARR = arr;									     	/* 自动重载值ARR */
	REG_GTIM_PSC |= (div<<0*3);										/* 预分频因子 */
	REG_GTIM0_CIF = 0xFF;											/* 清除定时器更新中断标志 */
	REG_GTIM0_CR &= ~(1<<3);										/* 开启定时器更新中断 */
	REG_GTIM0_CR |= (2<<1);											/* 选择模式：循环模式 */
	
	REG_GTIM_ICMODE = 0x05;											/* 选择通道模式 */
	REG_GTIM_PCR |= (1<<0);											/* 使能PWM中断 */
	REG_GTIM_C0PR = duty;											/* 比较寄存器（占空比） */
	
	REG_GTIM0_CR |= (1<<0);											/* 使能定时器 */
	
	NVIC_ClearPendingIRQ(GTIMER0_IRQn);
	NVIC_EnableIRQ(GTIMER0_IRQn);
}

/*******************************************************************
* Function		: gtimer0_capture_counter_test
* Description	: gtimer0_capture_counter_test
* Input			: UINT16 div
* Return		: none
********************************************************************/
void gtimer0_capture_counter_test(UINT16 div)
{
	/* gtimer0 输入捕获 */
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A; 							/* 清除IO写保护 */
	REG_SCU_PERICLKEN |= (1<<9);									/* 开启GTimer时钟使能 */
	REG_SCU_PERIRESET |= (1<<9);									/* GTimer正常工作 */
	
	REG_SCU_PERICLKEN |= (1<<19);									/* 开启GPIOD时钟使能 */
	REG_SCU_PERIRESET |= (1<<19);									/* GPIOD正常工作 */
	
	REG_SCU_PDSEL &= ~(7<<16);
	REG_SCU_PDSEL |= (2<<16);										/* PD4复用为TIM0_EXT */
	REG_SCU_IOCTRLPROTECT = 0xFFFFFFFF; 							/* IO写保护 */
	
	REG_GTIM_PSC |= (div<<0*3);										/* 预分频因子 */
	REG_GTIM_ICMODE = 0x00;											/* 选择通道模式 */
	REG_GTIM_CCR = 0x00;
	REG_GTIM_CCR |= (1<<3);											/* 使能CH0输入捕获 */
	REG_GTIM_CCR |= (1<<0);											/* 使能CH0输入捕获 */
	
	REG_GTIM0_CR |= (1<<0);											/* 使能定时器 */
	
	NVIC_ClearPendingIRQ(GTIMER0_IRQn);
	NVIC_EnableIRQ(GTIMER0_IRQn);
	
}



