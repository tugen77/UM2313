/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : adc.c
 * Description : adc controller source file
 * Author(s)   : Chloe
 * version     : V1.0
 * Modify date : 2019-03-06
 ***********************************************************************/
#include "um321x_adc.h"

volatile UINT16 conver_data0 = 0;
volatile UINT16 conver_data3 = 0;
volatile UINT16 conver_data5 = 0;
volatile UINT16 adc_converte_val[40] = {0};
volatile UINT8 adc_rx_flag = 0;

/************************************************************************
 * function   : ADC_IRQHandler
 * Description: (ADC interrupt handle)
 * adc_recive_fifo or adc_recive_data mode 
 * input : none
 * return: none
 ************************************************************************/
void ADC_IRQHandler(void)
{
	/*接收到中断后，读取转换结果*/
	if(REG_ADC_GCR & ADC_RXFIFO_MODE)				//RX FIFO MODE
	{
		adc_receive_fifo_data();
	}
	else
	{
		adc_receive_data();							//NO RX FIFO MODE
	}
}


/************************************************************************
 * function   : adc_gpio_config
 * Description: adc gpio config 
 * GPIO 端口初始化: 输入输出，模拟，上下拉，推挽/开漏输出,时钟初始化
 * GPIO有6个模拟输入通道：PA1--AIN0 PA2--AIN1 PA3--AIN2 
						PB4--AIN4 PB5--AIN3 PC3--AIN5
 * input : none
 * return: none
 ************************************************************************/
void adc_gpio_config(void)
{
	REG_SCU_PERICLKEN |= (1<<16)| (1<<19);				//开启相关的GPIOA GPIOD外设时钟
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;
	REG_SCU_PADADS |= (1<<2);							//使用通道1：AIN1--PA2
	
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;
	REG_SCU_PADADS |= (1<<30);							//使用通道3：AIN3--PD6
	
}

/************************************************************************
 * function   : adc_single_mode_one_channel
 * Description: adc_single_mode_one_channel configuration
 * 软件启动的ADC单次转换测试：一通道
 * 能转换多条通道，但只能转换一次
 * input : none
 * return: none
 ************************************************************************/
void adc_single_mode_one_channel(void)
{
	UINT32 temp = 0;
	adc_gpio_config();												//ADC GPIO配置
					
	REG_SCU_PERICLKEN |= ADC_CLKEN;									//开启ADC时钟
	REG_SCU_PERIRESET |= ADC_RESET;									//ADC复位
					
	REG_ADC_GCR &= ~ADC_PD_ON;				
	REG_ADC_GCR &= ~ADC_RST;				
				
	temp = ADC_SINGLE_MODE \
			| ADC_CLK_ICD | ADC_RCLR_EN \
			| ADC_RXFIFO_MODE;										//使能RX FIFO模式，rxtlf位置0能让RX FIFO在有至少一个有效数据时即可触发中断
	REG_ADC_GCR |= temp; 											//ADC上电，连续转换模式,使用内部时钟分频器，使能ADC数据寄存器读清
					
//	REG_ADC_CDR = ADC_CLK_DIV_4;				
//	REG_ADC_COUNT = ADC_SWITCH_COUNT_0;								//四分频
	adc_rx_flag = 0;				
				
	REG_ADC_ICR = 0x30F;											//清除所有中断
	REG_ADC_IER |= ADC_IT_RX_FIFO_EN;								//使能RX FIFO中断

	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);

	adc_rx_flag = 0;
	memset(adc_converte_val,0,sizeof(adc_converte_val));			//接收数据清0

	REG_ADC_GCR |= ADC_EN;											//启动ADC
	temp = ADC_CH3_EN;												//选择待转换通道 PD6-AIN3
	REG_ADC_GCR |= temp;				
	delay_ms(1);				
	REG_ADC_GCR |= ADC_START_EN;									//ADC连续转换开始
}

/************************************************************************
 * function   : adc_single_mode_multi_channels
 * Description: adc_single_mode_multi_channels configuration
 * 软件启动的ADC单次转换测试：多通道
 * 能一次转换多条通道
 * input : none
 * return: none
 ************************************************************************/
void adc_single_mode_multi_channels(void)
{
	UINT32 temp = 0;
	adc_gpio_config();									   			//ADC GPIO配置
	
	REG_SCU_PERICLKEN |= ADC_CLKEN;						  			//开启ADC时钟
	REG_SCU_PERIRESET |= ADC_RESET;						  			//ADC复位
	
	REG_ADC_GCR &= ~ADC_PD_ON;
	REG_ADC_GCR &= ~ADC_RST;

	temp = ADC_SINGLE_MODE \
			| ADC_CLK_ICD | ADC_RCLR_EN \
			| ADC_RXFIFO_MODE;							  			//使能RX FIFO模式，rxtlf位置0能让RX FIFO在有至少一个有效数据时即可触发中断
	REG_ADC_GCR |= temp; 								  			//ADC上电，连续转换模式,使用内部时钟分频器，使能ADC数据寄存器读清
				
//	REG_ADC_CDR = ADC_CLK_DIV_4;			
//	REG_ADC_COUNT = ADC_SWITCH_COUNT_0;				      			//四分频
	adc_rx_flag = 0;			
			
	REG_ADC_ICR = 0x30F;							      			//清除所有中断
	REG_ADC_IER |= ADC_IT_RX_FIFO_EN;					  			//使能RX FIFO中断

	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);

	adc_rx_flag = 0;
	memset(adc_converte_val,0,sizeof(adc_converte_val));  			//接收数据清0
			
	REG_ADC_GCR |= ADC_EN;							      			//启动ADC
	temp = ADC_CH1_EN|ADC_CH3_EN;						  			//选择 通道1：AIN1--PA2 和 通道3：AIN3--PD6
	REG_ADC_GCR |= temp;			
	delay_ms(1);			
	REG_ADC_GCR |= ADC_START_EN;					      			//ADC连续转换开始
}

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
void adc_continuous_mode(void)
{
	UINT32 temp = 0;
	adc_gpio_config();											//ADC GPIO配置
	
	REG_SCU_PERICLKEN |= ADC_CLKEN;								//开启ADC时钟
	REG_SCU_PERIRESET |= ADC_RESET;								//ADC复位
	
	REG_ADC_GCR &= ~ADC_PD_ON;
	REG_ADC_GCR &= ~ADC_RST;

	temp = ADC_CONTINUOUS_MODE \
			| ADC_CLK_ICD | ADC_RCLR_EN \
			| ADC_RXFIFO_MODE;									//使能RX FIFO模式，rxtlf位置0能让RX FIFO在有至少一个有效数据时即可触发中断
	REG_ADC_GCR |= temp; 										//ADC上电，连续转换模式,使用内部时钟分频器，使能ADC数据寄存器读清
	
	
//	REG_ADC_CDR = ADC_CLK_DIV_4;								//四分频
	
	REG_ADC_COUNT = ADC_SWITCH_COUNT_0;	
	adc_rx_flag = 0;

	REG_ADC_ICR = 0x30F;										//清除所有中断
	REG_ADC_IER |= ADC_IT_RX_FIFO_EN;							//使能RX FIFO中断

	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);

	adc_rx_flag = 0;
	memset(adc_converte_val,0,sizeof(adc_converte_val));		//接收数据清0

	REG_ADC_GCR |= ADC_EN;										//启动ADC
	temp = ADC_CH3_EN;											//选择待转换通道 PD6-AIN3
	REG_ADC_GCR |= temp;			
	REG_ADC_GCR |= ADC_START_EN;								//ADC连续转换开始
	
}

/************************************************************************
 * function   : adc_receive_data
 * Description: (use in no rx_fifo mode)receive the adc converted 
 * data from data registers, clear interrupt, stop conversion
 * input : none
 * return: none
 ************************************************************************/
void adc_receive_data(void)
{
	
	/*接收到中断后，读取转换结果*/
	//if(REG_ADC0_DR & ADC_DATA_VALID)							//CH0有有效数据，这个是轮询操作用的，中断不用
	UINT32 temp = 0;
	temp = REG_ADC_GCR & 0xFF0000;
	if(temp & ADC_CH0_EN)
	{
		conver_data0 = REG_ADC0_DR & ADC_CHx_DATA;				//保存转换数据，读取数据寄存器后valid位和data自动清零（ADC_RCLR_EN时）
		REG_ADC_ICR |= ADC_IT_CH0_CLR;							//清除中断
	}
	
	if(temp & ADC_CH3_EN)
	{
		conver_data3 = REG_ADC3_DR & ADC_CHx_DATA;				//保存转换数据，读取数据寄存器后valid位和data自动清零（ADC_RCLR_EN时）
		REG_ADC_ICR |= ADC_IT_CH3_CLR;							//清除中断
	}
	if(!(REG_ADC_GCR & ADC_SINGLE_MODE))
	REG_ADC_GCR &= ~(ADC_EN | ADC_START_EN);					//停止ADC转换
}

