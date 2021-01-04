/***********************************************************************
 * Copyright (c)  2019, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : um_wdt.h
 * Description : wdt driver header file
 * Author(s)   : yanhaihua
 * version     : V1.0
 * Modify date : 2019-02-28
 ***********************************************************************/
#ifndef __WDT_H__
#define __WDT_H__

#include "common.h"

#define WDT_LOCK_VALUE							0x55555555
#define WDT_UNLOCK_VALUE						0x1ACCE551

#define WDT_MODE_RESET							0
#define WDT_MODE_INT							1

extern volatile UINT8 wdt_int_flag;

/*******************************************************************
* Function		: wdt_int
* Description	: wdt_int
* Input			: UINT32 load_value:wdt load value, UINT8 mode:int/reset
* Output		: none
* Return		: none
********************************************************************/
void wdt_init(UINT32 load_value,UINT8 mode);

/*******************************************************************
* Function		: wdt_feed_dog
* Description	: wdt_feed_dog
* Input			: UINT32 load_value:wdt load value
* Output		: none
* Return		: none
********************************************************************/
void wdt_feed(UINT32 load_value);

#endif
