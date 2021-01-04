/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : gpio.c
 * Description : gpio driver header file
 * Author(s)   : Chloe
 * version     : V1.0
 * Modify date : 2019-02-27
 ***********************************************************************/
#ifndef _GPIO_H_
#define _GPIO_H_

#include  "common.h"


//通用数字输入/出管脚--用于SYSCFG某些寄存器配置(PAD_PD PAD_OD PAD_PU)
#define PA1	                    			1
#define PA2	                    			2
#define PA3	                    			3
#define PA4	                    			4
		
#define PB4	                    			12
#define PB5	                    			13
		
#define PC1	                    			17
#define PC2	                    			18
#define PC3	                    			19
#define PC4	                    			20
#define PC5	                    			21
#define PC6	                    			22
#define PC7	                    			23
		
#define PD1	                    			25
#define PD2	                    			26
#define PD3	                    			27
#define PD4	                    			28
#define PD5	                    			29
#define PD6	                    			30
#define PD7	                    			31
		
//PIN Number			
#define PIN1	                			1
#define PIN2	                			2
#define PIN3	                			3
#define PIN4	                			4
#define PIN5	                			5
#define PIN6	                			6
#define PIN7	                			7
		
//ST		ATE
#define ENABLE	        					1
#define DISABLE		       					0
		
//LE		VEL
#define HIGH	        					1
#define LOW		       						0
		
//DI		R
#define GPIO_DIR_IN  	            		0
#define GPIO_DIR_OUT  	            		1
		
//电平/边沿中断触发模式
#define GPIO_IS_EDGE                		0
#define GPIO_IS_LEVEL               		1
		
#define GPIO_IBE_SINGLE             		0
#define GPIO_IBE_DOUBLE             		1
		
#define GPIO_IEV_FALLEDGEORLOWLEVEL	        0
#define GPIO_IEV_RISEEDGEORHIGHLEVEL        1
		
#define GPIO_RIS_RAW_IT	        			1
#define GPIO_RIS_NO_RAW_IT          		0
		
#define GPIO_MODE_SOFTWARE	        		0
#define GPIO_MODE_HARDWARE          		1
		
#define GPIO_DB_ENABLE	        			1
#define GPIO_DB_DISABLE		        		0

//SYSCFG REG (PERI_CLKEN) GPIO 时钟选择(test)
#define GPIOA_CLKEN  	            		(UINT32)(0x1<<16)
#define GPIOB_CLKEN  	            		(UINT32)(0x1<<17)
#define GPIOC_CLKEN  	            		(UINT32)(0x1<<18)
#define GPIOD_CLKEN  	            		(UINT32)(0x1<<19)
		
//GPIO复位(test)
#define GPIOA_RESET  	            		(UINT32)(0x1<<16)
#define GPIOB_RESET  	            		(UINT32)(0x1<<17)
#define GPIOC_RESET  	            		(UINT32)(0x1<<18)
#define GPIOD_RESET  	            		(UINT32)(0x1<<19)
		
//SYSCFG REG端口数模配置
#define PA1_ADS_A  	            			(UINT32)		(1<<1)	//PA1为模拟接口
		
//GPIO复用功能(Px_SEL),x为A,B,C,D
/*******Px_SEL************/

#define PIN_SEL(x)  			            (4*x)
		
//extern volatile UINT8 gpioa_it_flag;
//extern volatile UINT8 gpiob_it_flag;
//extern volatile UINT8 gpioc_it_flag;
//extern volatile UINT8 gpiod_it_flag;

/************************************************************************
 * function   : gpio_init
 * Description: gpio initial
 * GPIO初始化，包括开时钟，模块正常工作，输入输出方向配置
 * input : 	UINT8 gpio port 
 *			UINT8 gpio pin
 ************************************************************************/
void gpio_init(UINT8 port, UINT8 pin);

/************************************************************************
 * function   : gpio_dir
 * Description: gpio_dir
 * 
 * input : 	UINT8 gpio port 
 *			UINT8 gpio pin
*			UINT8 newstate     GPIO_DIR_OUT   输出；GPIO_DIR_IN 输入
 ************************************************************************/
void gpio_dir(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_in_enable
 * Description: gpio in enable
 * 
 * input : 	UINT8 gpio port 
 *			UINT8 gpio pin
*			UINT8 newstate     ENABLE 输入使能；DISABLE 输入禁止
 ************************************************************************/
void gpio_in_enable(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_config_pu
 * Description: set pullup function 
 * 配置GPIO 端口上下拉
 * input : 	UINT8 gpio port     A,B,C,D端口
 *			UINT8 gpio pin		0~7
 *			UINT8 newstate 		1 上拉使能， 0 上拉禁止
 * return: none
 ************************************************************************/
void gpio_config_pu(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_config_pd
 * Description: set pulldown function 
 * 配置GPIO 端口上下拉
 * input : 	UINT8 gpio port     A,B,C,D端口
 *			UINT8 gpio pin		0~7
 *			UINT8 newstate 		1 下拉使能， 0 下拉禁止
 * return: none
 ************************************************************************/
void gpio_config_pd(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_config_od
 * Description: set gpio output open drain 
 * 配置GPIO 端口开漏输出
 * input : 	UINT8 gpio port     A,B,C,D端口
 *			UINT8 gpio pin		0~7
 *			UINT8 newstate 		1 开漏使能， 0 开漏禁止
 * return: none
 ************************************************************************/
void gpio_config_od(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_getio
 * Description: get gpio pin value
 * GPIO输入电平获取
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 * return: 管脚电平状态
 ************************************************************************/
UINT8 gpio_getio(UINT8 port, UINT8 pin);

/************************************************************************
 * function   : gpio_setio
 * Description: gpio set 1
 * GPIO电平输出
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate : high 1，low 0
 * return: none
 ************************************************************************/
void gpio_setio(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_set_irq
 * Description: gpio interrupt configuration
 * GPIO中断使能，失能
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate : enable 使能，disable 失能
 * return: none
 ************************************************************************/
void gpio_set_irq(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_set_is
 * Description: set the interrupt sense of gpio pin
 * GPIO中断触发类型配置
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate:  0  边沿触发，1 电平触发
 * return: none
 ************************************************************************/
void gpio_set_is(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_set_iev
 * Description: set the interrupt event of gpio pin
 * GPIO中断高低电平触发设置
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate: interrupt event
 * return: none
 ************************************************************************/
void gpio_set_iev(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_set_ibe
 * Description: set the interrupt both edge of gpio pin
 * GPIO中断单双边触发配置
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate: 0 单边沿触发，1 双边沿触发
 * return: none
 ************************************************************************/
void gpio_set_ibe(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_clr_irq
 * Description: clear the interrupt flag of gpio pin
 * GPIO中断清除
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 * return: none
 ************************************************************************/
void gpio_clr_irq(UINT8 port, UINT8 pin);

/************************************************************************
 * function   : gpio_original_irq
 * Description: get gpio raw interrupt status
 * GPIO读原始中断状态
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 * return: status 0 对应引脚无中断挂起，1 对应引脚有中断挂起
 ************************************************************************/
UINT8 gpio_original_irq(UINT8 port, UINT8 pin);


#endif

