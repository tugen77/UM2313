/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : hrng.c
 * Description : hrng driver source file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-04-10
 ***********************************************************************/
#include "um321x_hrng.h"

UINT32 RandSeed;

/************************************************************************
 * function   : rand_init
 * Description: rand_init
 * input : none
 * return: none
 ************************************************************************/
void rand_init(UINT32 seed)
{
	RandSeed = seed;
}
/************************************************************************
 * function   : get_rand16
 * Description: get_rand16 numbers
 * input : none
 * return:RandSeed
 ************************************************************************/
UINT16 get_rand16(void)
{
	RandSeed = (RandSeed*16807+1)%65536;
	return RandSeed;
}
/************************************************************************
 * function   : get_rand8
 * Description: get_rand8 numbers
 * input : none
 * return: get_rand16()&0xff
 ************************************************************************/
UINT8 get_rand8(void)
{
	return get_rand16()&0xff;
}
/************************************************************************
 * function   : get_hrng32
 * Description: get_hrng32 numbers
 * input : none
 * return: ((get_rand16()<<16)|get_rand16())
 ************************************************************************/
UINT32 get_hrng32(void)
{
	return ((get_rand16()<<16)|get_rand16());
}
/************************************************************************
 * function   : rand_test
 * Description: rand numbers  test
 * input : none
 * return: none
 ************************************************************************/
void rand_test(void)
{
	UINT32 i;
	rand_init(1234);
	for(i = 0; i < 32;i++)
	{
		printf("rand = 0x%4x\n", get_rand16());
	}
}
