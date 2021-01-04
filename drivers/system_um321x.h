/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : system_um321x.h
 * Description : system config header file (for example: clock config.....)
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-04-10
 ***********************************************************************/
#ifndef __SYSTEM_UM321x_H__
#define __SYSTEM_UM321x_H__

#include  "common.h"

#define FCLK          32000000      //Ŀ��ʱ��

#ifdef __cplusplus
extern "C"
{
#endif

#define CLK_DIV_RCH    (0<<17)  //ʱ��Դ��Ƶ(0��ʾ����Ƶ��1��ʾ2��Ƶ)
#define CLK_DIV_APB    (0<<9)  //APB��Ƶ

extern UINT32 SystemCoreClock;   //coreʱ��  (uint:Hz)
extern UINT32 SRCClock;   		 //Դʱ��,clk_src, (uint:Hz)
extern UINT32 PCLK;    			 //APBʱ��/PCLK,����ʱ��  , (uint:Hz)
extern UINT32 RCLClock;   	     //RCLʱ��,clk_src, (uint:Hz)

/************************************************************************
 * function   : SystemInit
 * Description: SystemInit
 * input : none
 * return: none
 ************************************************************************/
extern void SystemInit(void);

/************************************************************************
 * function   : clock_init
 * Description: clock init, initil several clock variables
 * input :
 *         uint32_t system_clk_mhz: expected system core clock
 * return: none
 ************************************************************************/
//void clock_init(UINT32 system_clk_hz);

extern void SystemCoreClockUpdate(void);
	
extern UINT32 SystemCoreClockGet(UINT32 system_clk_hz);


#ifdef __cplusplus
}
#endif

#endif
