/***********************************************************************
 * Copyright (c)  2019, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : um_wdt.c
 * Description : wdt driver source file
 * Author(s)   : Will
 * version     : V1.0
 * Modify date : 2019-12-09
 ***********************************************************************/
#include "um321x_wdt.h"

UINT32 g_wdt_load = 0;
volatile UINT8 wdt_int_flag = 0;


/*******************************************************************
* Function		: WDT_IRQHandler
* Description	: WDT_IRQHandler
* Input			: none
* Output		: none
* Return		: none
********************************************************************/
void WDT_IRQHandler(void)											
{ 
//	printfS("wdt interrupt!!\r\n");
	
	REG_WDT_LOCK = WDT_UNLOCK_VALUE;
	REG_WDT_CLR = 0xFF;												/* �ж�����Ĵ��� */
	wdt_int_flag = 1;
	wdt_feed(320000);
	while((REG_WDT_CTRL & ((UINT32)1<<31)) == 0);
	REG_WDT_LOCK = WDT_LOCK_VALUE;	
	
}

/*******************************************************************
* Function		: wdt_int
* Description	: wdt_int
* Input			: UINT32 load_value:wdt load value, UINT8 mode:int/reset
* Output		: none
* Return		: none
********************************************************************/
void wdt_init(UINT32 load_value,UINT8 mode)
{
	g_wdt_load = load_value;
	
	REG_SCU_PERICLKEN |= (1<<12);									/* ����WDTʱ��ʹ�� */
	REG_SCU_PERIRESET |= (1<<12);									/* WDT�������� */
	
	REG_WDT_LOCK = WDT_UNLOCK_VALUE;								/* �����Ĵ��� */
	REG_WDT_STALL |= (0x0<<16);                                     /* ��������Ƶ  Time = ((clkdiv + 1 )*load)/32k (s) */
	
	REG_WDT_LOAD = g_wdt_load;										/* װ�ؼĴ��� */
	
	if(mode == WDT_MODE_RESET)
	{
		REG_WDT_CTRL |= (1<<1);										/* ʹ�ܸ�λ����,�üĴ���ֻ��һ���Բ�������Ҫ�ȴ���Ч֮���ټ������� */
	}
	else
	{
		REG_WDT_CTRL |= (1<<0);										/* ʹ���ж�,�üĴ���ֻ��һ���Բ�������Ҫ�ȴ���Ч֮���ټ������� */
		NVIC_ClearPendingIRQ(WDT_IRQn);
		NVIC_EnableIRQ(WDT_IRQn);
	}
	
	while((REG_WDT_CTRL & ((UINT32)1<<31)) == 0);

	REG_WDT_LOCK = WDT_LOCK_VALUE;									/* �����Ĵ��� */
}

/*******************************************************************
* Function		: wdt_feed_dog
* Description	: wdt_feed_dog
* Input			: UINT32 load_value:wdt load value
* Output		: none
* Return		: none
********************************************************************/
void wdt_feed(UINT32 load_value)
{
	REG_WDT_LOCK = WDT_UNLOCK_VALUE;								/* �����Ĵ��� */
	REG_WDT_LOAD = load_value;										/* ι��-д������ֵ */
	while((REG_WDT_CTRL & ((UINT32)1<<31)) == 0);
	
	REG_WDT_LOCK = WDT_LOCK_VALUE;									/* �����Ĵ��� */
}

