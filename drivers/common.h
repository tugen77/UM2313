/***********************************************************************
 * Copyright (c)  2017 - 2019, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : common.h
 * Description : common header file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-02-21
 ***********************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

#include  "types.h"
//#include  "config.h"
#include  "um321x.h"
#include  "um321x_uart.h"
#include  "um321x_gpio.h"
//#include  "app.h"

#define SWAP(x)             ((((x) & 0xFF) << 8) | (((x) >> 8) & 0xFF))
#define max(a, b)		    (((a) > (b)) ? (a) : (b))
#define min(a, b)		    (((a) < (b)) ? (a) : (b))

void delay(UINT32 count);
void reverse_DWORD(UINT32 *var);
void reverse_memory(UINT8 *buff, UINT32 length);
void delay_init(UINT32 system_clk_hz);
void delay_us(UINT32 nus);
void delay_xms(UINT16 nms);
void delay_ms(UINT16 nms);
UINT8 addr_default_compare(UINT32 addr, UINT32 com_data);
UINT8 addr_write_compare(UINT32 addr, UINT32 wdata, UINT32 com_data);

#endif

