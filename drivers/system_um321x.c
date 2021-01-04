/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : system_um321x.c
 * Description : system config source file (for example: clock config.....)
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-04-10
 ***********************************************************************/
#include  "system_um321x.h"

UINT32 SystemCoreClock = 0;   //core时钟，HCLK  (uint:Hz)
UINT32 SRCClock = 32000000;   //源时钟,clk_src, (uint:Hz)
UINT32 PCLK = 0;     		  //APB时钟/PCLK,外设时钟 (uint:Hz)
UINT32 RCLClock = 32000;   	  //RCL时钟,clk_src, (uint:Hz)

/************************************************************************
 * function   : clock_init
 * Description: clock init, initil several clock variables
 * input : 
 		   uint32_t system_clk_mhz: expected system core clock
 * return: none
 ************************************************************************/
void clock_init(UINT32 system_clk_hz)
{
	UINT8 wait_time=0;
	UINT8 i,regdata;
	UINT8 div=0;
	UINT32 temp,rch32m,rcl32k;
	
	SRCClock = 32000000;
	RCLClock = 32000;
	
	div=SRCClock/system_clk_hz;
	
	REG_SCU_CTRLPROTECT = 0xA5A55A5A;				 //清除SYSCTRL0的写保护
	temp = REG_SCU_CTRL0 & (~(3<<17));
	temp &= ~(3<<9);
	REG_SCU_CTRL0 = temp|CLK_DIV_RCH|CLK_DIV_APB;	//RCH时钟源和APB分频配置

	REG_SCU_CTRLPROTECT = 0xA5A55A5A;		 		//清除SYSCTRL0的写保护
	REG_SCU_CTRL0 = (REG_SCU_CTRL0&(~(7<<6)))|((div-1)<<6);	//HCLK分频配置
	
	REG_SCU_CTRLPROTECT = 0xA5A55A5A;		 		//清除SYSCTRL0的写保护
	REG_SCU_CTRL0 |= 1<<0;					 		//RCH时钟使能
	while((REG_SCU_OSCCTRL&0x400) == 0x00);  		//等待时钟稳定
	
	REG_SCU_CTRLPROTECT = 0xA5A55A5A;		 		//清除SYSCTRL0的写保护
	REG_SCU_CTRL0 &= ~(1<<14);				 		//系统时钟来源为系统高速时钟
	
	REG_SCU_CTRLPROTECT = 0xA5A55A5A;				//清除SYSCTRL0的写保护
	REG_SCU_CTRL0 &= ~(1<<13);				 		//高频时钟选择内部高速时钟RCH
				 
	//系统时钟频率
	rch32m = (*(volatile UINT32 *)(0x00010034));
	if ((rch32m <= 34000000) && (rch32m >= 30000000))
		SystemCoreClock = rch32m;	
	else
		SystemCoreClock = system_clk_hz;
	
	div = 1;
	regdata = ((REG_SCU_CTRL0>>9)&0x03);
	for(i=0; i<regdata; i++)
	{
		div = div*2;	
	}
	
    PCLK = SystemCoreClock/div;		
	
	//RCL时钟频率
	rcl32k = (*(volatile UINT32 *)(0x00010038));
	rcl32k = rcl32k/100;
	if ((rcl32k <= 34000) && (rcl32k >= 30000)) 
		RCLClock = rcl32k;
	
	
	/*EFC配置*/
	REG_SCU_PERICLKEN |= (1<<20);
	REG_EFC_CTRL = (REG_EFC_CTRL &(~(0x0f<<3))) | (wait_time << 3);
	
	/*默认上拉配置*/
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A; //清除IO写保护 
	REG_SCU_PADPU = 0xFC7C300F; 
	REG_SCU_IOCTRLPROTECT = 0xffffffff; //开启IO写保护
}

/************************************************************************
 * function   : SystemInit
 * Description: SystemInit
 * input : none
 * return: none
 ************************************************************************/
void SystemInit(void)
{
    clock_init(FCLK);
//	delay_init(SystemCoreClock);
}

void SystemCoreClockUpdate(void)
{
    //SystemCoreClock=FCLK;
}

UINT32 SystemCoreClockGet(UINT32 system_clk_hz)
{
	UINT32		rch32m, SystemClock;
	
	rch32m = (*(volatile UINT32 *)(0x00010034));
	if ((rch32m <= 34000000) && (rch32m >= 30000000))
		SystemClock = rch32m;	
	else
		SystemClock = system_clk_hz;
	
	return SystemClock;
}
