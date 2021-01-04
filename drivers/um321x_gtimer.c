/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : um_gtimer.c
 * Description : um_gtimer source file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-02-21
 ***********************************************************************/
#include "um321x_gtimer.h"

/*******************************************************************
* Function		: GTIMER0_IRQHandler
* Description	: GTIMER0_IRQHandler
* Input			: none
* Output		: none
* Return		: none
********************************************************************/
void GTIMER0_IRQHandler(void)
{
#ifdef gtimer_interrupt											 /*����жϲ���*/
	REG_GTIM0_CIF = 0xFF;							             /* ����ж� */
//	static int a=0;
//	printfS("timer0=%d\r\n",a++);
#endif	
#ifdef gtimer_capture                                            /* ���벶��*/
	REG_GTIM_CCIF |= (3<<0);
//	printfS("ch0=%d    ch2=%d\r\n",REG_GTIM_CH0_CR,REG_GTIM_CH2_CR);
#endif	
	
}

/*******************************************************************
* Function		: gtimer0_interrupt_test
* Description	: gtimer0_interrupt_test
* Input			: UINT32 arr
*				  UINT16 div
* Return		: none
********************************************************************/
void gtimer0_interrupt_test(UINT32 arr,UINT16 div)
{
	/* gtimer0��ʱ���жϷ�ʽ */
	REG_SCU_PERICLKEN |= (1<<9);									/* ����GTimerʱ��ʹ�� */
	REG_SCU_PERIRESET |= (1<<9);									/* GTimer�������� */
	REG_GTIM0_CR &= ~(1<<0);										/* �رն�ʱ�� */
	REG_GTIM0_CR |= (1<<4);											/* ȷ���������� */
	REG_GTIM0_CR |= (1<<5);											/* ���ض���ģʽ */
	
	REG_GTIM0_ARR = arr;										    /* �Զ�����ֵARR */
	REG_GTIM_PSC |= (div<<0*3);										/* Ԥ��Ƶ���� */
	
	REG_GTIM0_CIF = 0xFF;											/* �����ʱ�������жϱ�־ */
	REG_GTIM0_CR &= ~(1<<3);										/* ������ʱ�������ж� */
	REG_GTIM0_CR |= (2<<1);											/* ѡ��ģʽ��ѭ��ģʽ */
	REG_GTIM0_CR |= (1<<0);											/* ʹ�ܶ�ʱ�� */
	REG_GTIM_ICMODE = 0x05;
	NVIC_ClearPendingIRQ(GTIMER0_IRQn);
	NVIC_EnableIRQ(GTIMER0_IRQn);
	
}

/*******************************************************************
* Function		: gtimer0_pwm_out_test
* Description	: gtimer0_pwm_out_test
* Input			: UINT32 arr
*				  UINT16 div
				  UINT32 duty
* Return		: none
********************************************************************/
void gtimer0_pwm_out_test(UINT32 arr,UINT16 div,UINT32 duty)
{
	/* gtimer0 PWM�������*/
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A; 						/* ���IOд���� */
	
	REG_SCU_PERICLKEN |= (1<<9);									/* ����GTimerʱ��ʹ�� */
	REG_SCU_PERIRESET |= (1<<9);									/* GTimer�������� */
	
	REG_SCU_PERICLKEN |= (1<<16);									/* ����GPIOAʱ��ʹ�� */
	REG_SCU_PERIRESET |= (1<<16);									/* GPIOA�������� */
	
	REG_SCU_PASEL = 0x00;
	REG_SCU_PASEL |= (2<<4);										/* PA1����ΪTIM0_TOG */
	REG_SCU_PASEL |= (2<<8);										/* PA2����ΪTIM0_TOG������� */
	REG_SCU_IOCTRLPROTECT = 0xFFFFFFFF; 							/* IOд���� */
	
	REG_GTIM0_CR &= ~(1<<0);										/* �رն�ʱ�� */
	REG_GTIM0_CR &= ~(1<<4);										/* ȷ���������� */
	REG_GTIM0_CR &= ~(1<<5);										/* ���ض���ģʽ */
	REG_GTIM0_ARR = arr;									     	/* �Զ�����ֵARR */
	REG_GTIM_PSC |= (div<<0*3);										/* Ԥ��Ƶ���� */
	REG_GTIM0_CIF = 0xFF;											/* �����ʱ�������жϱ�־ */
	REG_GTIM0_CR &= ~(1<<3);										/* ������ʱ�������ж� */
	REG_GTIM0_CR |= (2<<1);											/* ѡ��ģʽ��ѭ��ģʽ */
	
	REG_GTIM_ICMODE = 0x05;											/* ѡ��ͨ��ģʽ */
	REG_GTIM_PCR |= (1<<0);											/* ʹ��PWM�ж� */
	REG_GTIM_C0PR = duty;											/* �ȽϼĴ�����ռ�ձȣ� */
	
	REG_GTIM0_CR |= (1<<0);											/* ʹ�ܶ�ʱ�� */
	
	NVIC_ClearPendingIRQ(GTIMER0_IRQn);
	NVIC_EnableIRQ(GTIMER0_IRQn);
}

/*******************************************************************
* Function		: gtimer0_capture_counter_test
* Description	: gtimer0_capture_counter_test
* Input			: UINT16 div
* Return		: none
********************************************************************/
void gtimer0_capture_counter_test(UINT16 div)
{
	/* gtimer0 ���벶�� */
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A; 							/* ���IOд���� */
	REG_SCU_PERICLKEN |= (1<<9);									/* ����GTimerʱ��ʹ�� */
	REG_SCU_PERIRESET |= (1<<9);									/* GTimer�������� */
	
	REG_SCU_PERICLKEN |= (1<<19);									/* ����GPIODʱ��ʹ�� */
	REG_SCU_PERIRESET |= (1<<19);									/* GPIOD�������� */
	
	REG_SCU_PDSEL &= ~(7<<16);
	REG_SCU_PDSEL |= (2<<16);										/* PD4����ΪTIM0_EXT */
	REG_SCU_IOCTRLPROTECT = 0xFFFFFFFF; 							/* IOд���� */
	
	REG_GTIM_PSC |= (div<<0*3);										/* Ԥ��Ƶ���� */
	REG_GTIM_ICMODE = 0x00;											/* ѡ��ͨ��ģʽ */
	REG_GTIM_CCR = 0x00;
	REG_GTIM_CCR |= (1<<3);											/* ʹ��CH0���벶�� */
	REG_GTIM_CCR |= (1<<0);											/* ʹ��CH0���벶�� */
	
	REG_GTIM0_CR |= (1<<0);											/* ʹ�ܶ�ʱ�� */
	
	NVIC_ClearPendingIRQ(GTIMER0_IRQn);
	NVIC_EnableIRQ(GTIMER0_IRQn);
	
}



