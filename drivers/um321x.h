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
#define REG_EFC_CTRL    							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x00))		/* EFC 控制寄存器 */
#define REG_EFC_SEC    								(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x04))		/* EFC 写擦安全寄存器 */
#define REG_EFC_STATUS    							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x08))		/* EFC 状态寄存器 */
#define REG_EFC_INTSTATUS   						(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x0C))		/* EFC 中断状态寄存器 */
#define REG_EFC_INEN   								(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x10))		/* EFC 中断使能寄存器 */
#define REG_EFC_HALFUS   							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x14))		/* EFC 时间标尺寄存器 */
#define REG_EFC_RCHTRIM   							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x20))		/* EFC RCH TRIM 寄存器 */
#define REG_EFC_RCLTRIM   							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x24))		/* EFC RCL TRIM 寄存器 */
#define REG_EFC_LDOTRIM   							(*(volatile unsigned int *)(EFC_BASE_ADDR + 0x28))		/* EFC LDO TRIM 寄存器 */

/*------------------------------------------------- UART0 -------------------------------------------------*/
#define UART0_BASE_ADDR								0x40000000
#define REG_UART0_ISR								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x00))	/* UART0 中断状态寄存器 */
#define REG_UART0_IER								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x04))	/* UART0 中断使能寄存器 */
#define REG_UART0_CR								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x08))	/* UART0 控制寄存器 */
#define REG_UART0_TDR								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x0C))	/* UART0 发送数据寄存器 */
#define REG_UART0_RDR								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x0C))	/* UART0 接收数据寄存器 */
#define REG_UART0_BRPL								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x10))	/* UART0 波特率参数低位寄存器 */
#define REG_UART0_BRPH								(*(volatile unsigned int *)(UART0_BASE_ADDR + 0x14))	/* UART0 波特率参数高位寄存器 */

/*------------------------------------------------ LPUART -------------------------------------------------*/
#define LPUART_BASE_ADDR							0x40000400
#define REG_LPUART_LPURXD							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x00))	/* LPUART 接收数据寄存器 */
#define REG_LPUART_LPUTXD							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x04))	/* LPUART 发送数据寄存器 */
#define REG_LPUART_LPUSTA							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x08))	/* LPUART 状态寄存器 */
#define REG_LPUART_LPUCON							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x0C))	/* LPUART 控制寄存器 */
#define REG_LPUART_LPUIF							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x10))	/* LPUART 中断标志寄存器 */
#define REG_LPUART_LPUBAUD							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x14))	/* LPUART 波特率寄存器 */
#define REG_LPUART_LPUEN							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x18))	/* LPUART 接收使能寄存器 */
#define REG_LPUART_COMPARE							(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x1C))	/* LPUART 数据匹配寄存器 */
#define REG_LPUART_MODU								(*(volatile unsigned int *)(LPUART_BASE_ADDR + 0x20))	/* LPUART 波特率调制控制寄存器 */

/*------------------------------------------------- SPI0 --------------------------------------------------*/
#define SPI0_BASE_ADDR								0x40000800
#define REG_SPI0_SPICR          					(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x00))		/* SPI0 配置寄存器 */
#define REG_SPI0_SPICS0            					(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x04))		/* SPI0 主模式控制寄存器0 */
#define REG_SPI0_SPICS1             				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x08))		/* SPI0 主模式控制寄存器1 */
#define REG_SPI0_SPIOPCR            				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x14))		/* SPI0 过程控制寄存器 */
#define REG_SPI0_SPIIE          					(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x18))		/* SPI0 中断控制寄存器 */
#define REG_SPI0_SPIIF          					(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x1C))		/* SPI0 中断标志寄存器 */
#define REG_SPI0_SPITXBUF           				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x20))		/* SPI0 发送缓存寄存器 */
#define REG_SPI0_SPIRXBUF           				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x24))		/* SPI0 接收缓存寄存器 */
#define REG_SPI0_DMA_SPIRX_LEV      				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x28))		/* SPI0 DMA接收设置寄存器 */
#define REG_SPI0_DMA_SPITX_LEV      				(*(volatile unsigned int *)(SPI0_BASE_ADDR + 0x2C))		/* SPI0 DMA发送设置寄存器 */

/*------------------------------------------------- GTIMER ------------------------------------------------*/
#define GTIMER_BASE_ADDR							0x40000C00
#define REG_GTIM0_ARR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x00))	/* Timer0 加载寄存器 */
#define REG_GTIM0_CNT								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x04))	/* Timer0 计数寄存器 */
#define REG_GTIM0_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x08))	/* Timer0 控制寄存器 */
#define REG_GTIM0_IF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x0C))	/* Timer0 中断状态寄存器 */
#define REG_GTIM0_CIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x10))	/* Timer0 中断清除寄存器 */
#define REG_GTIM1_ARR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x14))	/* Timer1 加载寄存器 */
#define REG_GTIM1_CNT								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x18))	/* Timer1 计数寄存器 */
#define REG_GTIM1_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x1C))	/* Timer1 控制寄存器 */
#define REG_GTIM1_IF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x20))	/* Timer1 中断状态寄存器 */
#define REG_GTIM1_CIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x24))	/* Timer1 中断清除寄存器 */
#define REG_GTIM2_ARR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x28))	/* Timer2 加载寄存器 */
#define REG_GTIM2_CNT								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x2C))	/* Timer2 计数寄存器 */
#define REG_GTIM2_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x30))	/* Timer2 控制寄存器 */
#define REG_GTIM2_IF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x34))	/* Timer2 中断状态寄存器 */
#define REG_GTIM2_CIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x38))	/* Timer2 中断清除寄存器 */
#define REG_GTIM3_ARR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x3C))	/* Timer3 加载寄存器 */
#define REG_GTIM3_CNT								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x40))	/* Timer3 计数寄存器 */
#define REG_GTIM3_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x44))	/* Timer3 控制寄存器 */
#define REG_GTIM3_IF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x48))	/* Timer3 中断状态寄存器 */
#define REG_GTIM3_CIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x4C))	/* Timer3 中断清除寄存器 */
#define REG_GTIM_PSC								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x50))	/* 定时器预分频寄存器 */
#define REG_GTIM_ICMODE								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x54))	/* 工作模式控制寄存器 */
#define REG_GTIM_CCR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x58))	/* 输入捕获模式控制寄存器 */
#define REG_GTIM_CCIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x5C))	/* 输入捕获模式中断状态寄存器 */
#define REG_GTIM_CH0_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x60))	/* Channel0输入捕获模式counter寄存器 */
#define REG_GTIM_CH2_CR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x64))	/* Channel2输入捕获模式counter寄存器 */
#define REG_GTIM_PCR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x68))	/* PWM控制寄存器 */
#define REG_GTIM_CPIF								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x6C))	/* PWM中断状态寄存器 */
#define REG_GTIM_C0PR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x70))	/* PWM0比较寄存器 */
#define REG_GTIM_C1PR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x74))	/* PWM1比较寄存器 */
#define REG_GTIM_C2PR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x78))	/* PWM2比较寄存器 */
#define REG_GTIM_C3PR								(*(volatile unsigned int *)(GTIMER_BASE_ADDR + 0x7C))	/* PWM3比较寄存器 */

/*------------------------------------------------- LPTIMER -----------------------------------------------*/
#define LPTIMER_BASE_ADDR							0x40001000
#define REG_LPTIM_LPTCFG							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x00))	/* LPTIM 配置寄存器 */
#define REG_LPTIM_LPTCNT							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x04))	/* LPTIM 计数寄存器 */
#define REG_LPTIM_LPTCMP							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x08))	/* LPTIM 比较值寄存器 */
#define REG_LPTIM_LPTTARGET							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x0C))	/* LPTIM 目标值寄存器 */
#define REG_LPTIM_LPTIE								(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x10))	/* LPTIM 中断使能寄存器 */
#define REG_LPTIM_LPTIF								(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x14))	/* LPTIM 中断标志寄存器 */
#define REG_LPTIM_LPTCTRL							(*(volatile unsigned int *)(LPTIMER_BASE_ADDR + 0x18))	/* LPTIM 控制寄存器 */

/*------------------------------------------------- RTC ---------------------------------------------------*/
#define RTC_BASE_ADDR								0x40001400
#define REG_RTC_DR                  				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x00))		/* RTC 数据寄存器 */
#define REG_RTC_MR                  				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x04))		/* RTC 匹配寄存器 */
#define REG_RTC_LR                  				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x08))		/* RTC 加载值寄存器 */
#define REG_RTC_CR                  				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x0C))		/* RTC 控制寄存器 */
#define REG_RTC_IMSC             					(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x10))		/* RTC 中断屏蔽/清除寄存器 */
#define REG_RTC_RIS                 				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x14))		/* RTC 原始中断状态寄存器 */
#define REG_RTC_MIS             					(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x18))		/* RTC 屏蔽中断状态寄存器 */
#define REG_RTC_ICR                 				(*(volatile unsigned int *)(RTC_BASE_ADDR + 0x1C))		/* RTC 中断清除寄存器 */

/*------------------------------------------------- CRC ---------------------------------------------------*/
#define CRC16_BASE_ADDR								0x40001800
#define REG_CRC16_DATA              				(*(volatile unsigned int *)(CRC16_BASE_ADDR + 0x00))	/* CRC数据寄存器 */
#define REG_CRC16_INIT              				(*(volatile unsigned int *)(CRC16_BASE_ADDR + 0x04))	/* CRC初始值寄存器 */
#define REG_CRC16_CTRL              				(*(volatile unsigned int *)(CRC16_BASE_ADDR + 0x08))	/* CRC控制寄存器 */

/*------------------------------------------------- ADC ---------------------------------------------------*/
#define ADC_BASE_ADDR								0x40001C00
#define REG_ADC_GCR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x00))		/*ADC 总控寄存器 */
#define REG_ADC0_DR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x04))		/*ADC 通道0数据寄存器 */
#define REG_ADC1_DR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x08))		/*ADC 通道1数据寄存器 */
#define REG_ADC2_DR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x0C))		/*ADC 通道2数据寄存器 */
#define REG_ADC3_DR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x10))		/*ADC 通道3数据寄存器 */
#define REG_ADC_CDR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x24))		/*ADC 时钟分频寄存器 */
#define REG_ADC_ISR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x28))		/*ADC 中断状态寄存器 */
#define REG_ADC_IER                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x2C))		/*ADC 中断使能寄存器 */
#define REG_ADC_ICR                  				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x30))		/*ADC 中断清除寄存器 */
#define REG_ADC_COUNT                				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x34))		/*ADC 转换间隔寄存器 */
#define REG_ADC_RXREG                				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x38))		/*ADC 接收数据寄存器 */
#define REG_ADC_CSTAT                				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x3C))		/*ADC 状态寄存器 */
#define REG_ADC_SPW		             				(*(volatile unsigned int *)(ADC_BASE_ADDR + 0x40))		/*ADC 采样时钟脉宽寄存器 */

/*------------------------------------------------- SYSREG ------------------------------------------------*/
#define SCU_BASE_ADDR								0x40002000
#define REG_SCU_CTRL0								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x00))		/* 系统控制寄存器0 */
#define REG_SCU_CTRL1								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x04))		/* 系统控制寄存器1 */
#define REG_SCU_CTRLPROTECT							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x08))		/* 系统控制保护寄存器 */
#define REG_SCU_OSCCTRL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x0C))		/* 时钟控制寄存器 */
#define REG_SCU_PERICLKEN							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x10))		/* 外围模块时钟寄存器 */
#define REG_SCU_RESETFLAG							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x20))		/* 复位标识寄存器 */
#define REG_SCU_PERIRESET							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x24))		/* 外围模块复位控制寄存器 */
#define REG_SCU_EXTRESETCTRL						(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x28))		/* 外部复位滤波控制寄存器 */
#define REG_SCU_PASEL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x30))		/* 端口PA功能配置寄存器 */
#define REG_SCU_PBSEL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x34))		/* 端口PB功能配置寄存器 */
#define REG_SCU_PCSEL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x38))		/* 端口PC功能配置寄存器 */
#define REG_SCU_PDSEL								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x3C))		/* 端口PD功能配置寄存器 */
#define REG_SCU_PADADS								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x40))		/* 端口数模配置寄存器 */
#define REG_SCU_PADDR								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x44))		/* 端口驱动能力配置寄存器 */
#define REG_SCU_PADPU								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x48))		/* 端口上拉配置寄存器 */
#define REG_SCU_PADPD								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x4C))		/* 端口下拉配置寄存器 */
#define REG_SCU_PADOD								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x50))		/* 端口开漏输出配置寄存器 */
#define REG_SCU_PADCS								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x54))		/* 端口输入类型配置寄存器 */
#define REG_SCU_PADIE								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x58))		/* 端口输入配置寄存器 */
#define REG_SCU_IOCTRLPROTECT						(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x5C))		/* IO控制保护寄存器 */
#define REG_SCU_IOWACKINTRCLR						(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x60))		/* STOP模式下唤醒IO选择寄存器 */
#define REG_SCU_LVDCFG								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x64))		/* LVD控制寄存器 */
#define REG_SCU_GPIOCFG								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x70))		/* 端口辅助功能寄存器 */
#define REG_SCU_EXTRSTSEL							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x74))		/* 外部复位端口选择寄存器 */
#define REG_SCU_STOPMODESEL							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x78))		/* 停止模式选择寄存器 */
#define REG_SCU_REMAP								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x7C))		/* REMAP寄存器 */
#define REG_SCU_VECTOROFFSET						(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x80))		/* 中断向量地址重映射寄存器 */
#define REG_SCU_HRNGCR								(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x84))		/* 随机数控制寄存器 */
#define REG_SCU_HRNGSEED							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x88))		/* 随机数种子寄存器 */
#define REG_SCU_HRNGDATA							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x8C))		/* 随机数数据寄存器 */	
#define REG_SCU_BUZZERCR							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0x90))		/* 蜂鸣器控制寄存器/BUZERCR */
#define REG_SCU_RESERVE0							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0xA0))		/* 保留寄存器0 */
#define REG_SCU_RESERVE1							(*(volatile unsigned int *)(SCU_BASE_ADDR + 0xA4))		/* 保留寄存器1 */

/*------------------------------------------------- WDT ---------------------------------------------------*/
#define WDT_BASE_ADDR								0x40002400
#define REG_WDT_LOAD								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x00))		/* WDT 装载寄存器 */
#define REG_WDT_CNT									(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x04))		/* WDT 计数寄存器 */
#define REG_WDT_CTRL								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x08))		/* WDT 控制寄存器 */
#define REG_WDT_CLR									(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x0C))		/* WDT 清除寄存器 */
#define REG_WDT_INTRAW								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x10))		/* WDT RAW中断状态寄存器 */
#define REG_WDT_MINTS								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x14))		/* WDT MASK中断状态寄存器 */
#define REG_WDT_STALL								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x18))		/* WDT STALL寄存器 */
#define REG_WDT_LOCK								(*(volatile unsigned int *)(WDT_BASE_ADDR + 0x1C))		/* WDT LOCK寄存器 */

/*------------------------------------------------- UART1 -------------------------------------------------*/
#define UART1_BASE_ADDR								0x40003000
#define REG_UART1_RBR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x00))	/* UART1 接收缓冲寄存器 */
#define REG_UART1_THR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x00))	/* UART1 发送缓冲寄存器 */
#define REG_UART1_DLL								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x00))	/* UART1 波特率分频低位寄存器 */	
#define REG_UART1_DLH								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x04))	/* UART1 波特率分频高位寄存器 */
#define REG_UART1_IER								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x04))	/* UART1 中断使能寄存器 */
#define REG_UART1_IIR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x08))	/* UART1 中断状态寄存器 */
#define REG_UART1_FCR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x08))	/* UART1 FIFO控制寄存器 */
#define REG_UART1_LCR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x0C))	/* UART1 LINE控制寄存器 */
#define REG_UART1_MCR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x10))	/* UART1 流控制寄存器 */
#define REG_UART1_LSR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x14))	/* UART1 LINE中断状态寄存器 */
#define REG_UART1_MSR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x18))	/* UART1 流状态寄存器 */	
#define REG_UART1_USR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x7C))	/* UART1 状态寄存器 */
#define REG_UART1_TFL								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x80))	/* UART1 发送FIFO数据个数寄存器 */	
#define REG_UART1_RFL								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0x84))	/* UART1 接收FIFO数据个数寄存器 */	
#define REG_UART1_DLF								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0xC0))	/* UART1 小数分频寄存器 */
#define REG_UART1_RAR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0xC4))	/* UART1 接收地址匹配寄存器 */
#define REG_UART1_TAR								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0xC8))	/* UART1 发送地址匹配寄存器 */
#define REG_UART1_LCRE								(*(volatile unsigned int *)(UART1_BASE_ADDR + 0xCC))	/* UART1 LINE控制扩展寄存器 */

/*------------------------------------------------- GPIO --------------------------------------------------*/
#define GPIOA										0
#define GPIOB										1
#define GPIOC										2
#define GPIOD										3
#define GPIO_BASE_ADDR(x)							(0x40004000 + 0x0400 * (x))
#define REG_GPIO_DIR(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x00))	/* GPIO 数据方向寄存器 */
#define REG_GPIO_SET(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x08))	/* GPIO 输出置位寄存器 */
#define REG_GPIO_CLR(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x0C))	/* GPIO 输出清零寄存器 */
#define REG_GPIO_ODATA(x)							(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x10))	/* GPIO 输出引脚映射寄存器 */
#define REG_GPIO_IDATA(x)							(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x14))	/* GPIO 输入引脚映射寄存器 */
#define REG_GPIO_IEN(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x18))	/* GPIO 中断使能寄存器 */
#define REG_GPIO_IS(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x1C))	/* GPIO 中断触发模式寄存器 */
#define REG_GPIO_IBE(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x20))	/* GPIO 中断触发模式寄存器 */
#define REG_GPIO_IEV(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x24))	/* GPIO 中断触发模式寄存器 */
#define REG_GPIO_IC(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x28))	/* GPIO 中断状态清除寄存器 */
#define REG_GPIO_RIS(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x2C))	/* GPIO 原始中断状态寄存器 */
#define REG_GPIO_MIS(x)								(*(volatile unsigned int *)(GPIO_BASE_ADDR(x) + 0x30))	/* GPIO 屏蔽后中断状态寄存器 */

/*------------------------------------------------- I2C ---------------------------------------------------*/
#define I2C_BASE_ADDR								0x40005000
#define REG_I2C_CR                  				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x00))		/* I2C 配置寄存器 */
#define REG_I2C_CLR                 				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x04))		/* I2C 配置清除寄存器 */
#define REG_I2C_STAT                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x08))		/* I2C 状态寄存器 */
#define REG_I2C_DATA                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x0C))		/* I2C 数据寄存器 */
#define REG_I2C_CCR                 				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x10))		/* I2C 波特率配置寄存器 */
#define REG_I2C_SAD0                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x14))		/* I2C SLAVE地址寄存器0 */
#define REG_I2C_SADM0               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x18))		/* I2C SLAVE地址屏蔽寄存器0 */
#define REG_I2C_XSAD0               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x1C))		/* I2C SLAVE 扩展地址寄存器 */
#define REG_I2C_XSADM0              				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x20))		/* I2C SLAVE 扩展地址屏蔽寄存器 */
#define REG_I2C_SRST                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x24))		/* I2C 复位寄存器 */
#define REG_I2C_SAD1                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x28))		/* I2C SLAVE地址寄存器1 */
#define REG_I2C_SADM1               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x2C))		/* I2C SLAVE地址屏蔽寄存器1 */
#define REG_I2C_SAD2                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x30))		/* I2C SLAVE地址寄存器2 */
#define REG_I2C_SADM2               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x34))		/* I2C SLAVE地址屏蔽寄存器2 */
#define REG_I2C_SAD3                				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x38))		/* I2C SLAVE地址寄存器3 */
#define REG_I2C_SADM3               				(*(volatile unsigned int *)(I2C_BASE_ADDR + 0x3C))		/* I2C SLAVE地址屏蔽寄存器3 */
	
/*------------------------------------------------- SPI1 --------------------------------------------------*/
#define SPI1_BASE_ADDR								0x40006000
#define REG_SPI1_SPICR          					(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x00))		/* SPI1 配置寄存器 */
#define REG_SPI1_SPICS0            					(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x04))		/* SPI1 主模式控制寄存器0 */
#define REG_SPI1_SPIOPCR            				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x14))		/* SPI1 过程控制寄存器 */
#define REG_SPI1_SPIIE          					(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x18))		/* SPI1 中断控制寄存器 */
#define REG_SPI1_SPIIF          					(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x1c))		/* SPI1 中断标志寄存器 */
#define REG_SPI1_SPITXBUF           				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x20))		/* SPI1 接收缓存寄存器 */
#define REG_SPI1_SPIRXBUF           				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x24))		/* SPI1 接收缓存寄存器 */
#define REG_SPI1_DMA_SPIRX_LEV      				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x28))		/* SPI1 DMA接收设置寄存器 */
#define REG_SPI1_DMA_SPITX_LEV      				(*(volatile unsigned int *)(SPI1_BASE_ADDR + 0x2C))		/* SPI1 DMA发送设置寄存器 */
	
/*------------------------------------------------- DMA ---------------------------------------------------*/
#define DMACH0                          			0
#define DMACH1                           			1
#define DMA_BASE_ADDR								0x40020000 

#define REG_DMA_SAR(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x00))	/* DMA源地址寄存器 */
#define REG_DMA_DAR(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x08))	/* DMA目的地址寄存器 */
#define REG_DMA_CTLL(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x18))	/* DMA控制寄存器低32位 */	
#define REG_DMA_CTLH(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x1C))	/* DMA控制寄存器高32位 */															
#define REG_DMA_CFGL(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x40))	/* DMA设置寄存器低32位 */	
#define REG_DMA_CFGH(x)								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x0058 * (x) + 0x44))	/* DMA设置寄存器高32位 */
	
#define REG_DMA_RAWTFR								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2C0))				/* DMA原始传输中断寄存器 */
#define REG_DMA_RAWBLOCK							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2C8))				/* DMA原始Block传输中断寄存器 */
#define REG_DMA_RAWSRCTRAN							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2D0))				/* DMA原始源传输中断寄存器 */
#define REG_DMA_RAWDSTTRAN							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2D8))				/* DMA原始目标传输中断寄存器 */
#define REG_DMA_RAWERR								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2E0))				/* DMA错误中断寄存器 */
#define REG_DMA_STATUSTFR							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2E8))				/* DMA传输中断状态寄存器 */
#define REG_DMA_STATUSBLOCK							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2F0))				/* DMA Block传输中断状态寄存器 */	
#define REG_DMA_STATUSSRCTRAN						(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x2F8))				/* DMA 源传输中断状态寄存器 */	
#define REG_DMA_STATUSDSTTRAN						(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x300))				/* DMA 目标传输中断状态寄存器 */
#define REG_DMA_STATUSERR							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x308))				/* DMA 错误中断状态寄存器 */	
#define REG_DMA_MASKTFR								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x310))				/* DMA 传输中断屏蔽寄存器 */
#define REG_DMA_MASKBLOCK							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x318))				/* DMA Block传输中断屏蔽寄存器 */
#define REG_DMA_MASKSRCTRAN							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x320))				/* DMA 源传输中断屏蔽寄存器 */
#define REG_DMA_MASKDSTTRAN							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x328))				/* DMA 目标传输中断屏蔽寄存器 */
#define REG_DMA_MASKERR								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x330))				/* DMA 错误中断屏蔽寄存器 */
#define REG_DMA_CLEARTFR							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x338))				/* DMA 传输中断清除寄存器 */
#define REG_DMA_CLEARBLOCK							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x340))				/* DMA Block传输中断清除寄存器*/
#define REG_DMA_CLEARSRCTRAN						(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x348))				/* DMA 源传输中断清除寄存器*/
#define REG_DMA_CLEARDSTTRAN						(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x350))				/* DMA 目标传输中断清除寄存器*/
#define REG_DMA_CLEARERR							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x358))				/* DMA 错误中断清除寄存器*/
#define REG_DMA_STATUSINT							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x360))				/* DMA 中断状态寄存器*/
#define REG_DMA_REQSRC								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x368))				/* DMA 源传输Req信号软件握手寄存器*/
#define REG_DMA_REQDST								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x370))				/* DMA 源传输Req信号软件握手寄存器*/
#define REG_DMA_SGLREQSRC							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x378))				/* DMA 源传输Single信号软件握手寄存器*/
#define REG_DMA_SGLREQDST							(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x380))				/* DMA 目标传输Single信号软件握手寄存器*/
#define REG_DMA_LSTSRC								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x388))				/* DMA 源传输Last信号软件握手寄存器*/	
#define REG_DMA_LSTDST								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x390))				/* DMA 目标传输Last信号软件握手寄存器*/	
#define REG_DMA_DMACFG								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x398))				/* DMA 模块使能寄存器*/
#define REG_DMA_CHEN								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x3A0))				/* DMA 通道使能寄存器*/
#define REG_DMA_DMATEST								(*(volatile UINT32 *)(DMA_BASE_ADDR + 0x3B0))				/* DMA 测试模式寄存器*/
	
/*------------------------------------------------- System Tick -------------------------------------------*/
#define SYSTICK_BASE_ADDR							0xE000E010
#define REG_SYSTICK_CSR          					(*(volatile unsigned int *)(SYSTICK_BASE_ADDR + 0x00))	/* SysTick控制和状态寄存器 */
#define REG_SYSTICK_RVR          					(*(volatile unsigned int *)(SYSTICK_BASE_ADDR + 0x04))	/* SysTick重载值寄存器 */
#define REG_SYSTICK_CVR          					(*(volatile unsigned int *)(SYSTICK_BASE_ADDR + 0x08))	/* SysTick当前值寄存器 */

#endif
