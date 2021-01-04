/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : crc16.c
 * Description : crc16 source file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-02-21
 ***********************************************************************/
#include "um321x_crc16.h"

/************************************************************************
 * function   : crc16_enable
 * Description: crc16 enable 
 * input : none
 * return: none
 ************************************************************************/
void crc16_enable(void)
{
	//开启CRC时钟
	REG_SCU_PERICLKEN |= CRC16_CLKEN;
	//SCU复位控制寄存器
	REG_SCU_PERIRESET |= CRC16_RESET;
}

/************************************************************************
 * function   : crc16_ccitt
 * Description: crc_test soft/hardware mode 
 * input : UINT8 crc_data[]
 *		   UINT32 len
 *		   UINT16 init_data
 * return: REG_CRC16_DATA
 ************************************************************************/
//CRC-CCITT=X16+X12+X5+1
UINT16 crc16_ccitt(UINT8 crc_data[],UINT32 len,UINT16 init_data)
{
	UINT32 i;
	REG_CRC16_INIT = init_data;
//	printf("init = %x\n",REG_CRC16_INIT);
//	printf("ctrl = %x\n",REG_CRC16_CTRL);

	for( i = 0; i < len; i++ )
	{
		REG_CRC16_DATA = crc_data[i];	
	}
	return REG_CRC16_DATA;
}

/************************************************************************
 * function   : crc_soft
 * Description: crc_soft calculation
 * input : UINT16 crc
 *         UINT8 data
 * return: crc&0xffff
 ************************************************************************/
//+余数初始值  +结果异或值
UINT16 crc_soft(UINT16 crc,UINT8 data)
{
	UINT8 i;
	crc = crc ^ (int)data <<8;//被除数对齐,变成16位
	for(i=0;i<8;i++)
	{
		if((crc&0x8000) == 0x8000)
		{
			crc = crc << 1 ^0x1021;
		}
		else
		{
			crc = crc << 1;
		}
	}
	return crc&0xffff;
}

/************************************************************************
 * function   : crc16_ccitt_soft
 * Description: crc16_ccitt_soft
 * input : UINT8 crc_data[]
 * 		   UINT32 len
 * 		   UINT16 init_data
 * return: reg_crc
 ************************************************************************/
UINT16 crc16_ccitt_soft(UINT8 crc_data[],UINT32 len,UINT16 init_data)
{
	UINT32 i;

	UINT16 reg_crc;

	reg_crc = init_data;

	for( i = 0; i < len; i++ )
	{
		//REG_CRC16_DATA = crc_data[i];
		reg_crc = crc_soft(reg_crc,crc_data[i]);	
	}

	return reg_crc;
}

