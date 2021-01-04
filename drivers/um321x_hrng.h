/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : hrng.h
 * Description : hrng  header file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-02-21
 ***********************************************************************/
#ifndef __HRNG_H__
#define __HRNG_H__
#include "common.h"
#include "types.h"

void rand_init(UINT32 seed);
	
UINT8 get_rand8(void);

UINT16 get_rand16(void);
UINT32 get_hrng32(void);
void rand_test(void);

#endif



