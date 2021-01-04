/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : crc16.h
 * Description : crc16 header file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-02-21
 ***********************************************************************/
#ifndef _CRC_H_
#define _CRC_H_

#include  "common.h"

//SYSCFG REG (PERI_CLKEN) CRC16  ±÷”—°‘Ò(test)
#define CRC16_CLKEN  	            (UINT32)0x1<<11

//CRC16 ∏¥Œª
#define CRC16_RESET  	            (UINT32)0x1<<11

/************************************************************************
 * function   : crc16_enable
 * Description: crc16 enable 
 * input : none
 * return: none
 ************************************************************************/
void crc16_enable(void);

/************************************************************************
 * function   : crc16_ccitt
 * Description: crc_test soft/hardware mode 
 * input : UINT8 crc_data[]
 *		   UINT32 len
 *		   UINT16 init_data
 * return: REG_CRC16_DATA
 ************************************************************************/
UINT16 crc16_ccitt(UINT8 crc_data[],UINT32 len,UINT16 init_data);

/************************************************************************
 * function   : crc_soft
 * Description: crc_soft calculation
 * input : UINT16 crc
 *         UINT8 data
 * return: crc&0xffff
 ************************************************************************/
UINT16 crc_soft(UINT16 crc,UINT8 data);

/************************************************************************
 * function   : crc16_ccitt_soft
 * Description: crc16_ccitt_soft
 * input : UINT8 crc_data[]
 * 		   UINT32 len
 * 		   UINT16 init_data
 * return: reg_crc
 ************************************************************************/
UINT16 crc16_ccitt_soft(UINT8 crc_data[],UINT32 len,UINT16 init_data);


#endif

