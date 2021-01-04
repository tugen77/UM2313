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


//ͨ����������/���ܽ�--����SYSCFGĳЩ�Ĵ�������(PAD_PD PAD_OD PAD_PU)
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
		
//��ƽ/�����жϴ���ģʽ
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

//SYSCFG REG (PERI_CLKEN) GPIO ʱ��ѡ��(test)
#define GPIOA_CLKEN  	            		(UINT32)(0x1<<16)
#define GPIOB_CLKEN  	            		(UINT32)(0x1<<17)
#define GPIOC_CLKEN  	            		(UINT32)(0x1<<18)
#define GPIOD_CLKEN  	            		(UINT32)(0x1<<19)
		
//GPIO��λ(test)
#define GPIOA_RESET  	            		(UINT32)(0x1<<16)
#define GPIOB_RESET  	            		(UINT32)(0x1<<17)
#define GPIOC_RESET  	            		(UINT32)(0x1<<18)
#define GPIOD_RESET  	            		(UINT32)(0x1<<19)
		
//SYSCFG REG�˿���ģ����
#define PA1_ADS_A  	            			(UINT32)		(1<<1)	//PA1Ϊģ��ӿ�
		
//GPIO���ù���(Px_SEL),xΪA,B,C,D
/*******Px_SEL************/

#define PIN_SEL(x)  			            (4*x)
		
//extern volatile UINT8 gpioa_it_flag;
//extern volatile UINT8 gpiob_it_flag;
//extern volatile UINT8 gpioc_it_flag;
//extern volatile UINT8 gpiod_it_flag;

/************************************************************************
 * function   : gpio_init
 * Description: gpio initial
 * GPIO��ʼ����������ʱ�ӣ�ģ���������������������������
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
*			UINT8 newstate     GPIO_DIR_OUT   �����GPIO_DIR_IN ����
 ************************************************************************/
void gpio_dir(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_in_enable
 * Description: gpio in enable
 * 
 * input : 	UINT8 gpio port 
 *			UINT8 gpio pin
*			UINT8 newstate     ENABLE ����ʹ�ܣ�DISABLE �����ֹ
 ************************************************************************/
void gpio_in_enable(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_config_pu
 * Description: set pullup function 
 * ����GPIO �˿�������
 * input : 	UINT8 gpio port     A,B,C,D�˿�
 *			UINT8 gpio pin		0~7
 *			UINT8 newstate 		1 ����ʹ�ܣ� 0 ������ֹ
 * return: none
 ************************************************************************/
void gpio_config_pu(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_config_pd
 * Description: set pulldown function 
 * ����GPIO �˿�������
 * input : 	UINT8 gpio port     A,B,C,D�˿�
 *			UINT8 gpio pin		0~7
 *			UINT8 newstate 		1 ����ʹ�ܣ� 0 ������ֹ
 * return: none
 ************************************************************************/
void gpio_config_pd(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_config_od
 * Description: set gpio output open drain 
 * ����GPIO �˿ڿ�©���
 * input : 	UINT8 gpio port     A,B,C,D�˿�
 *			UINT8 gpio pin		0~7
 *			UINT8 newstate 		1 ��©ʹ�ܣ� 0 ��©��ֹ
 * return: none
 ************************************************************************/
void gpio_config_od(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_getio
 * Description: get gpio pin value
 * GPIO�����ƽ��ȡ
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 * return: �ܽŵ�ƽ״̬
 ************************************************************************/
UINT8 gpio_getio(UINT8 port, UINT8 pin);

/************************************************************************
 * function   : gpio_setio
 * Description: gpio set 1
 * GPIO��ƽ���
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate : high 1��low 0
 * return: none
 ************************************************************************/
void gpio_setio(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_set_irq
 * Description: gpio interrupt configuration
 * GPIO�ж�ʹ�ܣ�ʧ��
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate : enable ʹ�ܣ�disable ʧ��
 * return: none
 ************************************************************************/
void gpio_set_irq(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_set_is
 * Description: set the interrupt sense of gpio pin
 * GPIO�жϴ�����������
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate:  0  ���ش�����1 ��ƽ����
 * return: none
 ************************************************************************/
void gpio_set_is(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_set_iev
 * Description: set the interrupt event of gpio pin
 * GPIO�жϸߵ͵�ƽ��������
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate: interrupt event
 * return: none
 ************************************************************************/
void gpio_set_iev(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_set_ibe
 * Description: set the interrupt both edge of gpio pin
 * GPIO�жϵ�˫�ߴ�������
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate: 0 �����ش�����1 ˫���ش���
 * return: none
 ************************************************************************/
void gpio_set_ibe(UINT8 port, UINT8 pin, UINT8 newstate);

/************************************************************************
 * function   : gpio_clr_irq
 * Description: clear the interrupt flag of gpio pin
 * GPIO�ж����
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 * return: none
 ************************************************************************/
void gpio_clr_irq(UINT8 port, UINT8 pin);

/************************************************************************
 * function   : gpio_original_irq
 * Description: get gpio raw interrupt status
 * GPIO��ԭʼ�ж�״̬
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 * return: status 0 ��Ӧ�������жϹ���1 ��Ӧ�������жϹ���
 ************************************************************************/
UINT8 gpio_original_irq(UINT8 port, UINT8 pin);


#endif

