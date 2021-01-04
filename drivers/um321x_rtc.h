/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : rtc.h
 * Description : rtc driver header file
 * Author(s)   : Will
 * version     : V1.0
 * Modify date : 2019-12-09
 ***********************************************************************/
#ifndef _RTC_H_
#define _RTC_H_

#include  "common.h"

#define RTC_RESET  	            (UINT32)(0x1<<13)		//RTC正常工作
#define RTC_CLKEN  	            (UINT32)(0x1<<13)		//RTC时钟使能

extern volatile UINT8 rtc_int_flag;
/************************************************************************
 * function   : rtc_init
 * Description: init rtc counter
 * input : none
 * return: none
 ************************************************************************/
void rtc_init(void);

/************************************************************************
 * function   : rtc_load
 * Description: set the rtc counter load value
 * 设置RTC计时器加载值
 * input : load value
 * return: none
 ************************************************************************/
void rtc_set_load(UINT32 load);

/************************************************************************
 * function   : rtc_set_alarm
 * Description: config the rtc alarm,use rtc_update to valid
 * 配置RTC计时器闹钟
 * input : alarm value
 * return: none
 ************************************************************************/
void rtc_set_alarm(UINT32 value);

/************************************************************************
 * function   : rtc_update
 * Description: valid/enable the rtc update
 * 配置RTC更新（使能）
 * input : none
 * return: none
 ************************************************************************/
void rtc_update(void);

#endif

