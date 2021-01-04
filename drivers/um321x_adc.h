/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : adc.h
 * Description : adc header file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-04-10
 ***********************************************************************/
#ifndef _ADC_H_
#define _ADC_H_

#include  "common.h"

/******ADC REGISTER BIT DESCRIPTION**********/

/******REG ADC_GCR********/
//ADC数据在EOC信号的边沿采样选择
#define ADC_DATA_SAMP_RISE_EDGE						(UINT32)(0<<24)
#define ADC_DATA_SAMP_FALL_EDGE						(UINT32)(1<<24)
																 
//ADC通道转换使能                                               
#define ADC_CH0_EN									(UINT32)(1<<16)
#define ADC_CH1_EN									(UINT32)(1<<17)
#define ADC_CH2_EN									(UINT32)(1<<18)
#define ADC_CH3_EN									(UINT32)(1<<19)


#define ADC_START_EN								(UINT32)(1<<10)	//开始ADC转换
#define ADC_RST										(UINT32)(1<<9)	//ADC重启
//#define ADC_PD_DOWN									(UINT32)1<<8	//ADC停电
#define ADC_PD_ON									(UINT32)(1<<8)	//ADC上电
#define ADC_CLK_ICD									(UINT32)(0<<6)	//使用内部时钟分频器产生ADC时钟
#define ADC_CLK_SCK									(UINT32)(1<<6)	//使用系统时钟产生ADC时钟
#define ADC_RCLR_EN									(UINT32)(1<<5)	//使能ADC数据寄存器清除
#define ADC_RXTLF_OVER_1							(UINT32)(0<<4)	//RX FIFO有多于1个有效数据
#define ADC_RXTLF_OVER_16							(UINT32)(1<<4)	//RX FIFO有多于16个有效数据
#define ADC_RXFIFO_MODE								(UINT32)(1<<3)	//使能RX FIFO
#define ADC_DMA_MODE								(UINT32)(1<<2)	//DMA能读取RX FIFO数据
#define ADC_CPU_MODE								(UINT32)(0<<2)	//CPU能读取TX/RX FIFO数据
#define ADC_CONTINUOUS_MODE							(UINT32)(1<<1)	//ADC连续转换
#define ADC_SINGLE_MODE								(UINT32)(0<<1)	//ADC单次转换
#define ADC_EN										(UINT32)(1<<0)	//使能ADC

/*************REG ADCx_DR**************/
#define ADC_DATA_VALID								(UINT32)(1<<15)	//ADC通道数据有效
#define ADC_CHx_DATA								(UINT32)(0xFFF<<0)	//ADC通道转换数据

/*************REG ADC_CDR**************/
//adc_clk = fpclk / 2*(CLKDIV+1)
#define ADC_CLK_DIV									(UINT32)(0xFFFF<<0)	//ADC时钟分频系数
#define ADC_CLK_DIV_2								(UINT32)(0<<0)		//ADC时钟二分频
#define ADC_CLK_DIV_4								(UINT32)(1<<0)		//ADC时钟四分频

/************REG ADC_ISR****************/
#define ADC_IT_RX_FIFO_FULL							(UINT32)(1<<9)
#define ADC_IT_RX_FIFO_AVAILABLE					(UINT32)(1<<8)
#define ADC_IT_CH3_ACTIVE							(UINT32)(1<<3)
#define ADC_IT_CH2_ACTIVE							(UINT32)(1<<2)
#define ADC_IT_CH1_ACTIVE							(UINT32)(1<<1)
#define ADC_IT_CH0_ACTIVE							(UINT32)(1<<0)
															
/************REG ADC_IER****************/
#define ADC_IT_RX_FIFO_FULL_EN						(UINT32)(1<<9)
#define ADC_IT_RX_FIFO_EN							(UINT32)(1<<8)
#define ADC_IT_CH3_EN								(UINT32)(1<<3)
#define ADC_IT_CH2_EN								(UINT32)(1<<2)
#define ADC_IT_CH1_EN								(UINT32)(1<<1)
#define ADC_IT_CH0_EN								(UINT32)(1<<0)

/************REG ADC_ICR****************/
#define ADC_IT_RX_FIFO_FULL_CLR						(UINT32)(1<<9)
#define ADC_IT_RX_FIFO_CLR							(UINT32)(1<<8)
#define ADC_IT_CH3_CLR								(UINT32)(1<<3)
#define ADC_IT_CH2_CLR								(UINT32)(1<<2)
#define ADC_IT_CH1_CLR								(UINT32)(1<<1)
#define ADC_IT_CH0_CLR								(UINT32)(1<<0)

/********REG ADC_COUNT*****************/
//switch time =(adc_count+16) * ADC clock cycle time
//这个只能在ADC控制器使能前配置
#define ADC_SWITCH_COUNT							(UINT32)(0xFF<<0)
#define ADC_SWITCH_COUNT_0							(UINT32)(0<<0)

/********REG ADC_CSTAT*******/
#define ADC_RX_FIFO_EMPTY							(UINT32)(0<<0)
#define ADC_RX_FIFO_NO_EMPTY						(UINT32)(1<<0)

/*******REG ADC_SPW*****************/
#define ADC_SAMPCLK_WIDTH							 (UINT32)(0x7<<0)

//ADC复位(test)
#define ADC_RESET  	           						 (UINT32)(1<<14)

//SYSCFG REG (PERI_CLKEN) ADC 时钟选择(test)
#define ADC_CLKEN  	           						 (UINT32)(1<<14)


extern volatile UINT16 conver_data0;
extern volatile UINT16 conver_data3;
extern volatile UINT16 conver_data5;
extern volatile UINT16 adc_converte_val[40];
extern volatile UINT8 adc_rx_flag;

/************************************************************************
 * function   : adc_gpio_config
 * Description: adc gpio config 
 * GPIO 端口初始化: 输入输出，模拟，上下拉，推挽/开漏输出,时钟初始化
 * GPIO有6个模拟输入通道：PA1--AIN0 PA2--AIN1 PA3--AIN2 
						PB4--AIN4 PB5--AIN3 PC3--AIN5
 * input : none
 * return: none
 ************************************************************************/
void adc_gpio_config(void);

/************************************************************************
 * function   : adc_single_mode_one_channel
 * Description: adc_single_mode_one_channel configuration
 * 软件启动的ADC单次转换测试：一通道
 * 能转换多条通道，但只能转换一次
 * input : none
 * return: none
 ************************************************************************/
void adc_single_mode_one_channel(void);

/************************************************************************
 * function   : adc_single_mode_multi_channels
 * Description: adc_single_mode_multi_channels configuration
 * 软件启动的ADC单次转换测试：多通道
 * 能一次转换多条通道
 * input : none
 * return: none
 ************************************************************************/
void adc_single_mode_multi_channels(void);

/************************************************************************
 * function   : adc_continuous_mode
 * Description: adc_continuous_mode configuration
 * 软件启动的ADC连续转换测试
 * 能对多条通道进行循环转换
 * 循环转换模式里，转换后的数据会放到RX FIFO里
 * 寄存器RXREG是RX FIFO的入口，中断触发后读取RXREG寄存器
 * input : none
 * return: none
 ************************************************************************/
void adc_continuous_mode(void);

/************************************************************************
 * function   : adc_receive_data
 * Description: (use in no rx_fifo mode)receive the adc converted 
 * data from data registers, clear interrupt, stop conversion
 * input : none
 * return: none
 ************************************************************************/
void adc_receive_data(void);

#endif

