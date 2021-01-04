/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : rtc.c
 * Description : rtc driver source file
 * Author(s)   : Will
 * version     : V1.0
 * Modify date : 2019-12-09
 ***********************************************************************/
#include "um321x_rtc.h"

volatile UINT8 rtc_int_flag = 0;

/************************************************************************
 * function   : RTC_IRQHandler
 * Description: RTC_IRQHandler
 * input : none
 * return: none
 ************************************************************************/
void RTC_IRQHandler(void)
{
	if(REG_RTC_MIS & (1<<0))
	{
		rtc_int_flag = 1;
		REG_RTC_ICR = (UINT32)(1<<0);			//����ж�
	}
}

/************************************************************************
 * function   : rtc_init
 * Description: init rtc counter
 * input : none
 * return: none
 ************************************************************************/
void rtc_init(void)
{
	REG_SCU_PERIRESET &= ~(RTC_RESET);   	//��λRTC���ɽ�RTC_DR��ֵ��Ϊ0���ⲿ��λ���ܸ�λ��RTC_DR��ֵ
	REG_SCU_PERIRESET |= RTC_RESET;			//���´�RTC
	
	NVIC_ClearPendingIRQ(RTC_IRQn);		
	NVIC_EnableIRQ(RTC_IRQn);

}


/************************************************************************
 * function   : rtc_set_load
 * Description: set the rtc counter load value
 * ����RTC��ʱ������ֵ
 * input : load value
 * return: none
 ************************************************************************/
void rtc_set_load(UINT32 load)
{
	REG_RTC_CR |= (1<<0);                     /* ������ʼ��ؼĴ�����ƥ��Ĵ��� */
	REG_RTC_LR = load;
	REG_RTC_CR &= ~(1<<0);                     /* ���Է��ʼ��ؼĴ�����ƥ��Ĵ��� */
	while(load != REG_RTC_DR)
	{
	}
}


/************************************************************************
 * function   : rtc_set_alarm
 * Description: config the rtc alarm,use rtc_update to valid
 * ����RTC��ʱ������
 * input : alarm value
 * return: none
 ************************************************************************/
void rtc_set_alarm(UINT32 value)
{
	REG_RTC_MR = value;						//ƥ��ֵ
	REG_RTC_ICR |= (UINT32)(1<<0);			//����ж�
	REG_RTC_IMSC |= (UINT32)(1<<0); 		//ʹ���ж�
}


/************************************************************************
 * function   : rtc_update
 * Description: valid/enable the rtc update
 * ����RTC���£�ʹ�ܣ�
 * input : none
 * return: none
 ************************************************************************/
void rtc_update(void)
{
	REG_RTC_CR |= (UINT32)(1<<0);
}
