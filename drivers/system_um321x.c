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

UINT32 SystemCoreClock = 0;   //coreʱ�ӣ�HCLK  (uint:Hz)
UINT32 SRCClock = 32000000;   //Դʱ��,clk_src, (uint:Hz)
UINT32 PCLK = 0;     		  //APBʱ��/PCLK,����ʱ�� (uint:Hz)
UINT32 RCLClock = 32000;   	  //RCLʱ��,clk_src, (uint:Hz)

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
	
	REG_SCU_CTRLPROTECT = 0xA5A55A5A;				 //���SYSCTRL0��д����
	temp = REG_SCU_CTRL0 & (~(3<<17));
	temp &= ~(3<<9);
	REG_SCU_CTRL0 = temp|CLK_DIV_RCH|CLK_DIV_APB;	//RCHʱ��Դ��APB��Ƶ����

	REG_SCU_CTRLPROTECT = 0xA5A55A5A;		 		//���SYSCTRL0��д����
	REG_SCU_CTRL0 = (REG_SCU_CTRL0&(~(7<<6)))|((div-1)<<6);	//HCLK��Ƶ����
	
	REG_SCU_CTRLPROTECT = 0xA5A55A5A;		 		//���SYSCTRL0��д����
	REG_SCU_CTRL0 |= 1<<0;					 		//RCHʱ��ʹ��
	while((REG_SCU_OSCCTRL&0x400) == 0x00);  		//�ȴ�ʱ���ȶ�
	
	REG_SCU_CTRLPROTECT = 0xA5A55A5A;		 		//���SYSCTRL0��д����
	REG_SCU_CTRL0 &= ~(1<<14);				 		//ϵͳʱ����ԴΪϵͳ����ʱ��
	
	REG_SCU_CTRLPROTECT = 0xA5A55A5A;				//���SYSCTRL0��д����
	REG_SCU_CTRL0 &= ~(1<<13);				 		//��Ƶʱ��ѡ���ڲ�����ʱ��RCH
				 
	//ϵͳʱ��Ƶ��
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
	
	//RCLʱ��Ƶ��
	rcl32k = (*(volatile UINT32 *)(0x00010038));
	rcl32k = rcl32k/100;
	if ((rcl32k <= 34000) && (rcl32k >= 30000)) 
		RCLClock = rcl32k;
	
	
	/*EFC����*/
	REG_SCU_PERICLKEN |= (1<<20);
	REG_EFC_CTRL = (REG_EFC_CTRL &(~(0x0f<<3))) | (wait_time << 3);
	
	/*Ĭ����������*/
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A; //���IOд���� 
	REG_SCU_PADPU = 0xFC7C300F; 
	REG_SCU_IOCTRLPROTECT = 0xffffffff; //����IOд����
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
