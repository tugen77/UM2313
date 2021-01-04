/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : rtc.c
 * Description : rtc driver source file
 * Author(s)   : Will
 * version     : V1.0
 * Modify date : 2019-12-09
 ***********************************************************************/
#include "um321x_rtc.h"

volatile UINT8 rtc_int_flag = 0;

/************************************************************************
 * function   : RTC_IRQHandler
 * Description: RTC_IRQHandler
 * input : none
 * return: none
 ************************************************************************/
void RTC_IRQHandler(void)
{
	if(REG_RTC_MIS & (1<<0))
	{
		rtc_int_flag = 1;
		REG_RTC_ICR = (UINT32)(1<<0);			//清除中断
	}
}

/************************************************************************
 * function   : rtc_init
 * Description: init rtc counter
 * input : none
 * return: none
 ************************************************************************/
void rtc_init(void)
{
	REG_SCU_PERIRESET &= ~(RTC_RESET);   	//复位RTC，可将RTC_DR的值归为0，外部复位不能复位掉RTC_DR的值
	REG_SCU_PERIRESET |= RTC_RESET;			//重新打开RTC
	
	NVIC_ClearPendingIRQ(RTC_IRQn);		
	NVIC_EnableIRQ(RTC_IRQn);

}


/************************************************************************
 * function   : rtc_set_load
 * Description: set the rtc counter load value
 * 设置RTC计时器加载值
 * input : load value
 * return: none
 ************************************************************************/
void rtc_set_load(UINT32 load)
{
	REG_RTC_CR |= (1<<0);                     /* 允许访问加载寄存器和匹配寄存器 */
	REG_RTC_LR = load;
	REG_RTC_CR &= ~(1<<0);                     /* 忽略访问加载寄存器和匹配寄存器 */
	while(load != REG_RTC_DR)
	{
	}
}


/************************************************************************
 * function   : rtc_set_alarm
 * Description: config the rtc alarm,use rtc_update to valid
 * 配置RTC计时器闹钟
 * input : alarm value
 * return: none
 ************************************************************************/
void rtc_set_alarm(UINT32 value)
{
	REG_RTC_MR = value;						//匹配值
	REG_RTC_ICR |= (UINT32)(1<<0);			//清除中断
	REG_RTC_IMSC |= (UINT32)(1<<0); 		//使能中断
}


/************************************************************************
 * function   : rtc_update
 * Description: valid/enable the rtc update
 * 配置RTC更新（使能）
 * input : none
 * return: none
 ************************************************************************/
void rtc_update(void)
{
	REG_RTC_CR |= (UINT32)(1<<0);
}
