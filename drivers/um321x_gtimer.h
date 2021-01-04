/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : um_gtimer.h
 * Description : um_gtimer header file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-02-21
 ***********************************************************************/
#ifndef __GTIMER_H__
#define __GTIMER_H__

#include "common.h"

//#define gtimer_interrupt         //溢出中断
#define gtimer_capture             //输入捕获


/*******************************************************************
* Function		: gtimer0_pwm_out_test
* Description	: gtimer0_pwm_out_test
* Input			: UINT32 arr
*				  UINT16 div
				  UINT32 duty
* Return		: none
********************************************************************/
void gtimer0_pwm_out_test(UINT32 arr,UINT16 div,UINT32 duty);

/*******************************************************************
* Function		: gtimer0_interrupt_test
* Description	: gtimer0_interrupt_test
* Input			: UINT32 arr
*				  UINT16 div
* Return		: none
********************************************************************/
void gtimer0_interrupt_test(UINT32 arr,UINT16 div);

/*******************************************************************
* Function		: gtimer0_capture_counter_test
* Description	: gtimer0_capture_counter_test
* Input			: UINT16 div
* Return		: none
********************************************************************/
void gtimer0_capture_counter_test(UINT16 div);


#endif
