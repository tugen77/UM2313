/***********************************************************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : um321x.h
 * Description : um321x addr header file
 * Author(s)   : yanhaihua
 * version     : V1.0
 * Modify date : 2020-04-08
 ***********************************************************************************************************/
#ifndef __UM321x_H__
#define __UM321x_H__
#include  "system_um321x.h"
/* --------------------  Configuration of the Cortex-M0 Processor and Core Peripherals  ------------------ */
#define __CM0_REV                 					0x0000U   												/* Core revision r0p0 */
#define __MPU_PRESENT             					0         												/* MPU present or not */
#define __VTOR_PRESENT            					0         												/* no VTOR present*/
#define __NVIC_PRIO_BITS          					2         												/* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    					0         												/* Set to 1 if different SysTick Config is used */

/* ------------------------------  Interrupt Number Definition  ------------------------------------------ */
typedef enum IRQn
{
	/* --------------------------  Cortex-M0 Processor Exceptions Numbers  ------------------------------- */
	NonMaskableInt_IRQn			  					= -14,      											/* 2 Non Maskable Interrupt */
	HardFault_IRQn                					= -13,      											/* 3 HardFault Interrupt */
	SVCall_IRQn                   					= -5,      												/* 11 SV Call Interrupt */
	PendSV_IRQn                   					= -2,      												/* 14 Pend SV Interrupt */
	SysTick_IRQn                  					= -1,      												/* 15 System Tick Interrupt */

	/* --------------------------  ARMCM0 Specific Interrupt Numbers  ------------------------------------ */
	GPIO_PA_IRQn				  					= 0,        											/* 0:  GPIO_PA_IRQHandler */
	GPIO_PB_IRQn				  					= 1,        											/* 1:  GPIO_PB_IRQHandler */
	GPIO_PC_IRQn				  					= 2,        											/* 2:  GPIO_PC_IRQHandler */
	GPIO_PD_IRQn		          					= 3,        											/* 3:  GPIO_PD_IRQHandler */
	DMA_IRQn		          	  					= 4,        											/* 4:  DMA_IRQHandler */
	UART0_IRQn                    					= 6,        											/* 6:  UART0_IRQHandler */
	LPUART_IRQn	                  					= 7,        											/* 7:  LPUART_IRQHandler */
	UART1_IRQn                    					= 8,        											/* 8:  UART1_IRQHandler */
	I2C_IRQn                      					= 9,        											/* 9:  I2C_IRQHandler */
	SPI0_IRQn                     					= 10,       											/* 10: SPI0_IRQHandler */
	SPI1_IRQn                     					= 11,       											/* 10: SPI1_IRQHandler */
	GTIMER0_IRQn		          					= 14,       											/* 14: GTIMER0_IRQHandler */
	GTIMER1_IRQn	              					= 15,       											/* 15: GTIMER1_IRQHandler */
	GTIMER2_IRQn	              					= 16,       											/* 16: GTIMER2_IRQHandler */
	GTIMER3_IRQn                  					= 17,       											/* 17: GTIMER3_IRQHandler */
	LPTIMER_IRQn                  					= 18,       											/* 18: LPTIMER_IRQHandler */
	WDT_IRQn                  	  					= 22,       											/* 22: WDT_IRQHandler */
	RTC_IRQn                  	  					= 23,       											/* 23: RTC_IRQHandler */
	ADC_IRQn                      					= 24,       											/* 24: ADC_IRQHandler */
	LVD_IRQn                 	  					= 28,       											/* 28: LVD_IRQHandler */
	FLASH_IRQn                    					= 30        											/* 30: FLASH_IRQHandler */
} IRQn_Type;

#include  "core_cm0.h"

/***********************************************************************************************************/
/*                            Device Specific Peripheral Section                                           */
/***********************************************************************************************************/

/*------------------------------------------------- EFC ---------------------------------------------------*/
#define EFC_BASE_ADDR								0x00011000
#define REG_EFC_CTRL    							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x00))		/* EFC ���ƼĴ��� */
#define REG_EFC_SEC    								(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x04))		/* EFC д����ȫ�Ĵ��� */
#define REG_EFC_STATUS    							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x08))		/* EFC ״̬�Ĵ��� */
#define REG_EFC_INTSTATUS   						(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x0C))		/* EFC �ж�״̬�Ĵ��� */
#define REG_EFC_INEN   								(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x10))		/* EFC �ж�ʹ�ܼĴ��� */
#define REG_EFC_HALFUS   							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x14))		/* EFC ʱ���߼Ĵ��� */
#define REG_EFC_RCHTRIM   							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x20))		/* EFC RCH TRIM �Ĵ��� */
#define REG_EFC_RCLTRIM   							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x24))		/* EFC RCL TRIM �Ĵ��� */
#define REG_EFC_LDOTRIM   							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x28))		/* EFC LDO TRIM �Ĵ��� */

/*------------------------------------------------- UART0 -------------------------------------------------*/
#define UART0_BASE_ADDR								0x40000000
#define REG_UART0_ISR								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x00))	/* UART0 �ж�״̬�Ĵ��� */
#define REG_UART0_IER								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x04))	/* UART0 �ж�ʹ�ܼĴ��� */
#define REG_UART0_CR								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x08))	/* UART0 ���ƼĴ��� */
#define REG_UART0_TDR								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x0C))	/* UART0 �������ݼĴ��� */
#define REG_UART0_RDR								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x0C))	/* UART0 �������ݼĴ��� */
#define REG_UART0_BRPL								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x10))	/* UART0 �����ʲ�����λ�Ĵ��� */
#define REG_UART0_BRPH								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x14))	/* UART0 �����ʲ�����λ�Ĵ��� */

/*------------------------------------------------ LPUART -------------------------------------------------*/
#define LPUART_BASE_ADDR							0x40000400
#define REG_LPUART_LPURXD							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x00))	/* LPUART �������ݼĴ��� */
#define REG_LPUART_LPUTXD							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x04))	/* LPUART �������ݼĴ��� */
#define REG_LPUART_LPUSTA							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x08))	/* LPUART ״̬�Ĵ��� */
#define REG_LPUART_LPUCON							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x0C))	/* LPUART ���ƼĴ��� */
#define REG_LPUART_LPUIF							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x10))	/* LPUART �жϱ�־�Ĵ��� */
#define REG_LPUART_LPUBAUD							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x14))	/* LPUART �����ʼĴ��� */
#define REG_LPUART_LPUEN							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x18))	/* LPUART ����ʹ�ܼĴ��� */
#define REG_LPUART_COMPARE							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x1C))	/* LPUART ����ƥ��Ĵ��� */
#define REG_LPUART_MODU								(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x20))	/* LPUART �����ʵ��ƿ��ƼĴ��� */

/*------------------------------------------------- SPI0 --------------------------------------------------*/
#define SPI0_BASE_ADDR								0x40000800
#define REG_SPI0_SPICR          					(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x00))		/* SPI0 ���üĴ��� */
#define REG_SPI0_SPICS0            					(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x04))		/* SPI0 ��ģʽ���ƼĴ���0 */
#define REG_SPI0_SPICS1             				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x08))		/* SPI0 ��ģʽ���ƼĴ���1 */
#define REG_SPI0_SPIOPCR            				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x14))		/* SPI0 ���̿��ƼĴ��� */
#define REG_SPI0_SPIIE          					(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x18))		/* SPI0 �жϿ��ƼĴ��� */
#define REG_SPI0_SPIIF          					(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x1C))		/* SPI0 �жϱ�־�Ĵ��� */
#define REG_SPI0_SPITXBUF           				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x20))		/* SPI0 ���ͻ���Ĵ��� */
#define REG_SPI0_SPIRXBUF           				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x24))		/* SPI0 ���ջ���Ĵ��� */
#define REG_SPI0_DMA_SPIRX_LEV      				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x28))		/* SPI0 DMA�������üĴ��� */
#define REG_SPI0_DMA_SPITX_LEV      				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x2C))		/* SPI0 DMA�������üĴ��� */

/*------------------------------------------------- GTIMER ------------------------------------------------*/
#define GTIMER_BASE_ADDR							0x40000C00
#define REG_GTIM0_ARR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x00))	/* Timer0 ���ؼĴ��� */
#define REG_GTIM0_CNT								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x04))	/* Timer0 �����Ĵ��� */
#define REG_GTIM0_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x08))	/* Timer0 ���ƼĴ��� */
#define REG_GTIM0_IF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x0C))	/* Timer0 �ж�״̬�Ĵ��� */
#define REG_GTIM0_CIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x10))	/* Timer0 �ж�����Ĵ��� */
#define REG_GTIM1_ARR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x14))	/* Timer1 ���ؼĴ��� */
#define REG_GTIM1_CNT								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x18))	/* Timer1 �����Ĵ��� */
#define REG_GTIM1_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x1C))	/* Timer1 ���ƼĴ��� */
#define REG_GTIM1_IF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x20))	/* Timer1 �ж�״̬�Ĵ��� */
#define REG_GTIM1_CIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x24))	/* Timer1 �ж�����Ĵ��� */
#define REG_GTIM2_ARR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x28))	/* Timer2 ���ؼĴ��� */
#define REG_GTIM2_CNT								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x2C))	/* Timer2 �����Ĵ��� */
#define REG_GTIM2_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x30))	/* Timer2 ���ƼĴ��� */
#define REG_GTIM2_IF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x34))	/* Timer2 �ж�״̬�Ĵ��� */
#define REG_GTIM2_CIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x38))	/* Timer2 �ж�����Ĵ��� */
#define REG_GTIM3_ARR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x3C))	/* Timer3 ���ؼĴ��� */
#define REG_GTIM3_CNT								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x40))	/* Timer3 �����Ĵ��� */
#define REG_GTIM3_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x44))	/* Timer3 ���ƼĴ��� */
#define REG_GTIM3_IF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x48))	/* Timer3 �ж�״̬�Ĵ��� */
#define REG_GTIM3_CIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x4C))	/* Timer3 �ж�����Ĵ��� */
#define REG_GTIM_PSC								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x50))	/* ��ʱ��Ԥ��Ƶ�Ĵ��� */
#define REG_GTIM_ICMODE								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x54))	/* ����ģʽ���ƼĴ��� */
#define REG_GTIM_CCR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x58))	/* ���벶��ģʽ���ƼĴ��� */
#define REG_GTIM_CCIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x5C))	/* ���벶��ģʽ�ж�״̬�Ĵ��� */
#define REG_GTIM_CH0_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x60))	/* Channel0���벶��ģʽcounter�Ĵ��� */
#define REG_GTIM_CH2_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x64))	/* Channel2���벶��ģʽcounter�Ĵ��� */
#define REG_GTIM_PCR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x68))	/* PWM���ƼĴ��� */
#define REG_GTIM_CPIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x6C))	/* PWM�ж�״̬�Ĵ��� */
#define REG_GTIM_C0PR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x70))	/* PWM0�ȽϼĴ��� */
#define REG_GTIM_C1PR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x74))	/* PWM1�ȽϼĴ��� */
#define REG_GTIM_C2PR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x78))	/* PWM2�ȽϼĴ��� */
#define REG_GTIM_C3PR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x7C))	/* PWM3�ȽϼĴ��� */

/*------------------------------------------------- LPTIMER -----------------------------------------------*/
#define LPTIMER_BASE_ADDR							0x40001000
#define REG_LPTIM_LPTCFG							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x00))	/* LPTIM ���üĴ��� */
#define REG_LPTIM_LPTCNT							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x04))	/* LPTIM �����Ĵ��� */
#define REG_LPTIM_LPTCMP							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x08))	/* LPTIM �Ƚ�ֵ�Ĵ��� */
#define REG_LPTIM_LPTTARGET							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x0C))	/* LPTIM Ŀ��ֵ�Ĵ��� */
#define REG_LPTIM_LPTIE								(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x10))	/* LPTIM �ж�ʹ�ܼĴ��� */
#define REG_LPTIM_LPTIF								(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x14))	/* LPTIM �жϱ�־�Ĵ��� */
#define REG_LPTIM_LPTCTRL							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x18))	/* LPTIM ���ƼĴ��� */

/*------------------------------------------------- RTC ---------------------------------------------------*/
#define RTC_BASE_ADDR								0x40001400
#define REG_RTC_DR                  				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x00))		/* RTC ���ݼĴ��� */
#define REG_RTC_MR                  				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x04))		/* RTC ƥ��Ĵ��� */
#define REG_RTC_LR                  				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x08))		/* RTC ����ֵ�Ĵ��� */
#define REG_RTC_CR                  				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x0C))		/* RTC ���ƼĴ��� */
#define REG_RTC_IMSC             					(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x10))		/* RTC �ж�����/����Ĵ��� */
#define REG_RTC_RIS                 				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x14))		/* RTC ԭʼ�ж�״̬�Ĵ��� */
#define REG_RTC_MIS             					(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x18))		/* RTC �����ж�״̬�Ĵ��� */
#define REG_RTC_ICR                 				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x1C))		/* RTC �ж�����Ĵ��� */

/*------------------------------------------------- CRC ---------------------------------------------------*/
#define CRC16_BASE_ADDR								0x40001800
#define REG_CRC16_DATA              				(*(volatile unsigned int *)(CRC16_BASE_ADDR + 0x00))	/* CRC���ݼĴ��� */
#define REG_CRC16_INIT              				(*(volatile unsigned int *)(CRC16_BASE_ADDR + 0x04))	/* CRC��ʼֵ�Ĵ��� */
#define REG_CRC16_CTRL              				(*(volatile unsigned int *)(CRC16_BASE_ADDR + 0x08))	/* CRC���ƼĴ��� */

/*------------------------------------------------- ADC ---------------------------------------------------*/
#define ADC_BASE_ADDR								0x40001C00
#define REG_ADC_GCR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x00))		/*ADC �ܿؼĴ��� */
#define REG_ADC0_DR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x04))		/*ADC ͨ��0���ݼĴ��� */
#define REG_ADC1_DR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x08))		/*ADC ͨ��1���ݼĴ��� */
#define REG_ADC2_DR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x0C))		/*ADC ͨ��2���ݼĴ��� */
#define REG_ADC3_DR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x10))		/*ADC ͨ��3���ݼĴ��� */
#define REG_ADC_CDR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x24))		/*ADC ʱ�ӷ�Ƶ�Ĵ��� */
#define REG_ADC_ISR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x28))		/*ADC �ж�״̬�Ĵ��� */
#define REG_ADC_IER                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x2C))		/*ADC �ж�ʹ�ܼĴ��� */
#define REG_ADC_ICR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x30))		/*ADC �ж�����Ĵ��� */
#define REG_ADC_COUNT                				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x34))		/*ADC ת������Ĵ��� */
#define REG_ADC_RXREG                				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x38))		/*ADC �������ݼĴ��� */
#define REG_ADC_CSTAT                				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x3C))		/*ADC ״̬�Ĵ��� */
#define REG_ADC_SPW		             				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x40))		/*ADC ����ʱ������Ĵ��� */

/*------------------------------------------------- SYSREG ------------------------------------------------*/
#define SCU_BASE_ADDR								0x40002000
#define REG_SCU_CTRL0								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x00))		/* ϵͳ���ƼĴ���0 */
#define REG_SCU_CTRL1								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x04))		/* ϵͳ���ƼĴ���1 */
#define REG_SCU_CTRLPROTECT							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x08))		/* ϵͳ���Ʊ����Ĵ��� */
#define REG_SCU_OSCCTRL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x0C))		/* ʱ�ӿ��ƼĴ��� */
#define REG_SCU_PERICLKEN							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x10))		/* ��Χģ��ʱ�ӼĴ��� */
#define REG_SCU_RESETFLAG							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x20))		/* ��λ��ʶ�Ĵ��� */
#define REG_SCU_PERIRESET							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x24))		/* ��Χģ�鸴λ���ƼĴ��� */
#define REG_SCU_EXTRESETCTRL						(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x28))		/* �ⲿ��λ�˲����ƼĴ��� */
#define REG_SCU_PASEL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x30))		/* �˿�PA�������üĴ��� */
#define REG_SCU_PBSEL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x34))		/* �˿�PB�������üĴ��� */
#define REG_SCU_PCSEL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x38))		/* �˿�PC�������üĴ��� */
#define REG_SCU_PDSEL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x3C))		/* �˿�PD�������üĴ��� */
#define REG_SCU_PADADS								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x40))		/* �˿���ģ���üĴ��� */
#define REG_SCU_PADDR								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x44))		/* �˿������������üĴ��� */
#define REG_SCU_PADPU								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x48))		/* �˿��������üĴ��� */
#define REG_SCU_PADPD								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x4C))		/* �˿��������üĴ��� */
#define REG_SCU_PADOD								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x50))		/* �˿ڿ�©������üĴ��� */
#define REG_SCU_PADCS								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x54))		/* �˿������������üĴ��� */
#define REG_SCU_PADIE								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x58))		/* �˿��������üĴ��� */
#define REG_SCU_IOCTRLPROTECT						(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x5C))		/* IO���Ʊ����Ĵ��� */
#define REG_SCU_IOWACKINTRCLR						(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x60))		/* STOPģʽ�»���IOѡ��Ĵ��� */
#define REG_SCU_LVDCFG								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x64))		/* LVD���ƼĴ��� */
#define REG_SCU_GPIOCFG								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x70))		/* �˿ڸ������ܼĴ��� */
#define REG_SCU_EXTRSTSEL							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x74))		/* �ⲿ��λ�˿�ѡ��Ĵ��� */
#define REG_SCU_STOPMODESEL							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x78))		/* ֹͣģʽѡ��Ĵ��� */
#define REG_SCU_REMAP								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x7C))		/* REMAP�Ĵ��� */
#define REG_SCU_VECTOROFFSET						(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x80))		/* �ж�������ַ��ӳ��Ĵ��� */
#define REG_SCU_HRNGCR								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x84))		/* ��������ƼĴ��� */
#define REG_SCU_HRNGSEED							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x88))		/* ��������ӼĴ��� */
#define REG_SCU_HRNGDATA							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x8C))		/* ��������ݼĴ��� */	
#define REG_SCU_BUZZERCR							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x90))		/* ���������ƼĴ���/BUZERCR */
#define REG_SCU_RESERVE0							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0xA0))		/* �����Ĵ���0 */
#define REG_SCU_RESERVE1							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0xA4))		/* �����Ĵ���1 */

/*------------------------------------------------- WDT ---------------------------------------------------*/
#define WDT_BASE_ADDR								0x40002400
#define REG_WDT_LOAD								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x00))		/* WDT װ�ؼĴ��� */
#define REG_WDT_CNT									(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x04))		/* WDT �����Ĵ��� */
#define REG_WDT_CTRL								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x08))		/* WDT ���ƼĴ��� */
#define REG_WDT_CLR									(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x0C))		/* WDT ����Ĵ��� */
#define REG_WDT_INTRAW								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x10))		/* WDT RAW�ж�״̬�Ĵ��� */
#define REG_WDT_MINTS								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x14))		/* WDT MASK�ж�״̬�Ĵ��� */
#define REG_WDT_STALL								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x18))		/* WDT STALL�Ĵ��� */
#define REG_WDT_LOCK								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x1C))		/* WDT LOCK�Ĵ��� */

/*------------------------------------------------- UART1 -------------------------------------------------*/
#define UART1_BASE_ADDR								0x40003000
#define REG_UART1_RBR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x00))	/* UART1 ���ջ���Ĵ��� */
#define REG_UART1_THR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x00))	/* UART1 ���ͻ���Ĵ��� */
#define REG_UART1_DLL								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x00))	/* UART1 �����ʷ�Ƶ��λ�Ĵ��� */	
#define REG_UART1_DLH								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x04))	/* UART1 �����ʷ�Ƶ��λ�Ĵ��� */
#define REG_UART1_IER								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x04))	/* UART1 �ж�ʹ�ܼĴ��� */
#define REG_UART1_IIR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x08))	/* UART1 �ж�״̬�Ĵ��� */
#define REG_UART1_FCR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x08))	/* UART1 FIFO���ƼĴ��� */
#define REG_UART1_LCR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x0C))	/* UART1 LINE���ƼĴ��� */
#define REG_UART1_MCR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x10))	/* UART1 �����ƼĴ��� */
#define REG_UART1_LSR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x14))	/* UART1 LINE�ж�״̬�Ĵ��� */
#define REG_UART1_MSR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x18))	/* UART1 ��״̬�Ĵ��� */	
#define REG_UART1_USR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x7C))	/* UART1 ״̬�Ĵ��� */
#define REG_UART1_TFL								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x80))	/* UART1 ����FIFO���ݸ����Ĵ��� */	
#define REG_UART1_RFL								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x84))	/* UART1 ����FIFO���ݸ����Ĵ��� */	
#define REG_UART1_DLF								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0xC0))	/* UART1 С����Ƶ�Ĵ��� */
#define REG_UART1_RAR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0xC4))	/* UART1 ���յ�ַƥ��Ĵ��� */
#define REG_UART1_TAR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0xC8))	/* UART1 ���͵�ַƥ��Ĵ��� */
#define REG_UART1_LCRE								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0xCC))	/* UART1 LINE������չ�Ĵ��� */

/*------------------------------------------------- GPIO --------------------------------------------------*/
#define GPIOA										0
#define GPIOB										1
#define GPIOC										2
#define GPIOD										3
#define GPIO_BASE_ADDR(x)							(0x40004000 + 0x0400 * (x))
#define REG_GPIO_DIR(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x00))	/* GPIO ���ݷ���Ĵ��� */
#define REG_GPIO_SET(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x08))	/* GPIO �����λ�Ĵ��� */
#define REG_GPIO_CLR(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x0C))	/* GPIO �������Ĵ��� */
#define REG_GPIO_ODATA(x)							(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x10))	/* GPIO �������ӳ��Ĵ��� */
#define REG_GPIO_IDATA(x)							(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x14))	/* GPIO ��������ӳ��Ĵ��� */
#define REG_GPIO_IEN(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x18))	/* GPIO �ж�ʹ�ܼĴ��� */
#define REG_GPIO_IS(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x1C))	/* GPIO �жϴ���ģʽ�Ĵ��� */
#define REG_GPIO_IBE(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x20))	/* GPIO �жϴ���ģʽ�Ĵ��� */
#define REG_GPIO_IEV(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x24))	/* GPIO �жϴ���ģʽ�Ĵ��� */
#define REG_GPIO_IC(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x28))	/* GPIO �ж�״̬����Ĵ��� */
#define REG_GPIO_RIS(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x2C))	/* GPIO ԭʼ�ж�״̬�Ĵ��� */
#define REG_GPIO_MIS(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x30))	/* GPIO ���κ��ж�״̬�Ĵ��� */

/*------------------------------------------------- I2C ---------------------------------------------------*/
#define I2C_BASE_ADDR								0x40005000
#define REG_I2C_CR                  				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x00))		/* I2C ���üĴ��� */
#define REG_I2C_CLR                 				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x04))		/* I2C ��������Ĵ��� */
#define REG_I2C_STAT                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x08))		/* I2C ״̬�Ĵ��� */
#define REG_I2C_DATA                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x0C))		/* I2C ���ݼĴ��� */
#define REG_I2C_CCR                 				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x10))		/* I2C ���������üĴ��� */
#define REG_I2C_SAD0                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x14))		/* I2C SLAVE��ַ�Ĵ���0 */
#define REG_I2C_SADM0               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x18))		/* I2C SLAVE��ַ���μĴ���0 */
#define REG_I2C_XSAD0               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x1C))		/* I2C SLAVE ��չ��ַ�Ĵ��� */
#define REG_I2C_XSADM0              				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x20))		/* I2C SLAVE ��չ��ַ���μĴ��� */
#define REG_I2C_SRST                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x24))		/* I2C ��λ�Ĵ��� */
#define REG_I2C_SAD1                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x28))		/* I2C SLAVE��ַ�Ĵ���1 */
#define REG_I2C_SADM1               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x2C))		/* I2C SLAVE��ַ���μĴ���1 */
#define REG_I2C_SAD2                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x30))		/* I2C SLAVE��ַ�Ĵ���2 */
#define REG_I2C_SADM2               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x34))		/* I2C SLAVE��ַ���μĴ���2 */
#define REG_I2C_SAD3                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x38))		/* I2C SLAVE��ַ�Ĵ���3 */
#define REG_I2C_SADM3               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x3C))		/* I2C SLAVE��ַ���μĴ���3 */
	
/*------------------------------------------------- SPI1 --------------------------------------------------*/
#define SPI1_BASE_ADDR								0x40006000
#define REG_SPI1_SPICR          					(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x00))		/* SPI1 ���üĴ��� */
#define REG_SPI1_SPICS0            					(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x04))		/* SPI1 ��ģʽ���ƼĴ���0 */
#define REG_SPI1_SPIOPCR            				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x14))		/* SPI1 ���̿��ƼĴ��� */
#define REG_SPI1_SPIIE          					(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x18))		/* SPI1 �жϿ��ƼĴ��� */
#define REG_SPI1_SPIIF          					(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x1c))		/* SPI1 �жϱ�־�Ĵ��� */
#define REG_SPI1_SPITXBUF           				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x20))		/* SPI1 ���ջ���Ĵ��� */
#define REG_SPI1_SPIRXBUF           				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x24))		/* SPI1 ���ջ���Ĵ��� */
#define REG_SPI1_DMA_SPIRX_LEV      				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x28))		/* SPI1 DMA�������üĴ��� */
#define REG_SPI1_DMA_SPITX_LEV      				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x2C))		/* SPI1 DMA�������üĴ��� */
	
/*------------------------------------------------- DMA ---------------------------------------------------*/
#define DMACH0                          			0
#define DMACH1                           			1
#define DMA_BASE_ADDR								0x40020000 

#define REG_DMA_SAR(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x00))	/* DMAԴ��ַ�Ĵ��� */
#define REG_DMA_DAR(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x08))	/* DMAĿ�ĵ�ַ�Ĵ��� */
#define REG_DMA_CTLL(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x18))	/* DMA���ƼĴ�����32λ */	
#define REG_DMA_CTLH(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x1C))	/* DMA���ƼĴ�����32λ */															
#define REG_DMA_CFGL(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x40))	/* DMA���üĴ�����32λ */	
#define REG_DMA_CFGH(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x44))	/* DMA���üĴ�����32λ */
	
#define REG_DMA_RAWTFR								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2C0))				/* DMAԭʼ�����жϼĴ��� */
#define REG_DMA_RAWBLOCK							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2C8))				/* DMAԭʼBlock�����жϼĴ��� */
#define REG_DMA_RAWSRCTRAN							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2D0))				/* DMAԭʼԴ�����жϼĴ��� */
#define REG_DMA_RAWDSTTRAN							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2D8))				/* DMAԭʼĿ�괫���жϼĴ��� */
#define REG_DMA_RAWERR								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2E0))				/* DMA�����жϼĴ��� */
#define REG_DMA_STATUSTFR							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2E8))				/* DMA�����ж�״̬�Ĵ��� */
#define REG_DMA_STATUSBLOCK							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2F0))				/* DMA Block�����ж�״̬�Ĵ��� */	
#define REG_DMA_STATUSSRCTRAN						(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2F8))				/* DMA Դ�����ж�״̬�Ĵ��� */	
#define REG_DMA_STATUSDSTTRAN						(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x300))				/* DMA Ŀ�괫���ж�״̬�Ĵ��� */
#define REG_DMA_STATUSERR							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x308))				/* DMA �����ж�״̬�Ĵ��� */	
#define REG_DMA_MASKTFR								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x310))				/* DMA �����ж����μĴ��� */
#define REG_DMA_MASKBLOCK							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x318))				/* DMA Block�����ж����μĴ��� */
#define REG_DMA_MASKSRCTRAN							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x320))				/* DMA Դ�����ж����μĴ��� */
#define REG_DMA_MASKDSTTRAN							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x328))				/* DMA Ŀ�괫���ж����μĴ��� */
#define REG_DMA_MASKERR								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x330))				/* DMA �����ж����μĴ��� */
#define REG_DMA_CLEARTFR							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x338))				/* DMA �����ж�����Ĵ��� */
#define REG_DMA_CLEARBLOCK							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x340))				/* DMA Block�����ж�����Ĵ���*/
#define REG_DMA_CLEARSRCTRAN						(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x348))				/* DMA Դ�����ж�����Ĵ���*/
#define REG_DMA_CLEARDSTTRAN						(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x350))				/* DMA Ŀ�괫���ж�����Ĵ���*/
#define REG_DMA_CLEARERR							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x358))				/* DMA �����ж�����Ĵ���*/
#define REG_DMA_STATUSINT							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x360))				/* DMA �ж�״̬�Ĵ���*/
#define REG_DMA_REQSRC								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x368))				/* DMA Դ����Req�ź�������ּĴ���*/
#define REG_DMA_REQDST								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x370))				/* DMA Դ����Req�ź�������ּĴ���*/
#define REG_DMA_SGLREQSRC							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x378))				/* DMA Դ����Single�ź�������ּĴ���*/
#define REG_DMA_SGLREQDST							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x380))				/* DMA Ŀ�괫��Single�ź�������ּĴ���*/
#define REG_DMA_LSTSRC								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x388))				/* DMA Դ����Last�ź�������ּĴ���*/	
#define REG_DMA_LSTDST								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x390))				/* DMA Ŀ�괫��Last�ź�������ּĴ���*/	
#define REG_DMA_DMACFG								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x398))				/* DMA ģ��ʹ�ܼĴ���*/
#define REG_DMA_CHEN								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x3A0))				/* DMA ͨ��ʹ�ܼĴ���*/
#define REG_DMA_DMATEST								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x3B0))				/* DMA ����ģʽ�Ĵ���*/
	
/*------------------------------------------------- System Tick -------------------------------------------*/
#define SYSTICK_BASE_ADDR							0xE000E010
#define REG_SYSTICK_CSR          					(*(volatile unsigned int *)(SYSTICK_BASE_ADDR + 0x00))	/* SysTick���ƺ�״̬�Ĵ��� */
#define REG_SYSTICK_RVR          					(*(volatile unsigned int *)(SYSTICK_BASE_ADDR + 0x04))	/* SysTick����ֵ�Ĵ��� */
#define REG_SYSTICK_CVR          					(*(volatile unsigned int *)(SYSTICK_BASE_ADDR + 0x08))	/* SysTick��ǰֵ�Ĵ��� */

#endif
