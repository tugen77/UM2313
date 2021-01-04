/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : gpio.c
 * Description : gpio source file
 * Author(s)   : Chloe\Troy
 * version     : V1.0
 * Modify date : 2019-02-27
 ***********************************************************************/
#include "um321x_gpio.h"


#if 0
volatile UINT8 gpioa_it_flag = 0;
volatile UINT8 gpiob_it_flag = 0;
volatile UINT8 gpioc_it_flag = 0;
volatile UINT8 gpiod_it_flag = 0;

/************************************************************************
 * function   : GPIO_PA_IRQHandler
 * Description: GPIO_PA_IRQHandler
 * GPIOA�жϴ�����
 * input : 	none
 * return:  none
 ************************************************************************/
void GPIO_PA_IRQHandler(void)
{
	UINT8 regdata;
	UINT8 pinvalue;
	
	gpioa_it_flag = ~gpioa_it_flag;
	
	pinvalue = 0;
	regdata = REG_GPIO_RIS(GPIOA);
	
	while(regdata!= 1)
	{
		regdata = regdata/2;
		pinvalue ++;
	}
	
	gpio_clr_irq(GPIOA, pinvalue);								//�ж����
}

/************************************************************************
 * function   : GPIO_PB_IRQHandler
 * Description: GPIO_PB_IRQHandler
 * GPIOB�жϴ�����
 * input : 	none
 * return:  none  
 ************************************************************************/
void GPIO_PB_IRQHandler(void)
{
	UINT8 regdata;
	UINT8 pinvalue;
	
	gpiob_it_flag = 1;
	
	pinvalue = 0;
	regdata = REG_GPIO_RIS(GPIOB);
	
	while(regdata!= 1)
	{
		regdata = regdata/2;
		pinvalue ++;
	}
	
	gpio_clr_irq(GPIOB, pinvalue);								//�ж����
}

/************************************************************************
 * function   : GPIO_PC_IRQHandler
 * Description: GPIO_PC_IRQHandler
 * GPIOC�жϴ�����
 * input : 	none
 * return:  none 
 ************************************************************************/
void GPIO_PC_IRQHandler(void)
{
	UINT8 regdata;
	UINT8 pinvalue;
	
	gpiob_it_flag = 1;
	
	pinvalue = 0;
	regdata = REG_GPIO_RIS(GPIOC);
	
	while(regdata!= 1)
	{
		regdata = regdata/2;
		pinvalue ++;
	}
	
	gpio_clr_irq(GPIOC, pinvalue);								//�ж����
}

/************************************************************************
 * function   : GPIO_PD_IRQHandler
 * Description: GPIO_PD_IRQHandler
 * GPIOD�жϴ�����
 * input : 	none
 * return:  none
 ************************************************************************/
void GPIO_PD_IRQHandler(void)
{	
	UINT8 regdata;
	UINT8 pinvalue;
	
	gpiob_it_flag = 1;
	
	pinvalue = 0;
	regdata = REG_GPIO_RIS(GPIOD);
	
	while(regdata!= 1)
	{
		regdata = regdata/2;
		pinvalue ++;
	}
	
	gpio_clr_irq(GPIOD, pinvalue);								//�ж����
}
#endif

/************************************************************************
 * function   : gpio_init
 * Description: gpio initial
 * GPIO��ʼ����������ʱ�ӣ�ģ����������
 * input : 	UINT8 gpio port 
 *			UINT8 gpio pin
 ************************************************************************/
void gpio_init(UINT8 port, UINT8 pin)
{
	//����GPIOʱ�ӣ�GPIOģ����������,�˿�ΪGPIO
	
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;			//���IOд����
	
	if(port == GPIOA)
	{
		REG_SCU_PERICLKEN |= GPIOA_CLKEN;
		REG_SCU_PERIRESET |= GPIOA_RESET;	
		
		REG_SCU_PASEL &= ~(0x7<<(4*pin));
		REG_SCU_PASEL |= (0<<(4*pin));
		
	}
	else if(port == GPIOB)
	{
		REG_SCU_PERICLKEN |= GPIOB_CLKEN;
		REG_SCU_PERIRESET |= GPIOB_CLKEN;	
		
		REG_SCU_PBSEL &= ~(0x7<<(4*pin));
		REG_SCU_PBSEL |= (0<<(4*pin));
		
	}
	else if(port == GPIOC)
	{
		REG_SCU_PERICLKEN |= GPIOC_CLKEN;
		REG_SCU_PERIRESET |= GPIOC_RESET;	
		
		REG_SCU_PCSEL &= ~(0x7<<(4*pin));
		REG_SCU_PCSEL |= (0<<(4*pin));
	
	}
	else if(port == GPIOD)
	{
		REG_SCU_PERICLKEN |= GPIOD_CLKEN;
		REG_SCU_PERIRESET |= GPIOD_RESET;	
		
		REG_SCU_PDSEL &= ~(0x7<<(4*pin));
		REG_SCU_PDSEL |= (0<<(4*pin));

	}
	
	REG_SCU_IOCTRLPROTECT = 0xffffffff; //����IOд����
	

}
/************************************************************************
 * function   : gpio_dir
 * Description: gpio_dir
 * 
 * input : 	UINT8 gpio port 
 *			UINT8 gpio pin
*			UINT8 newstate     GPIO_DIR_OUT   �����GPIO_DIR_IN ����
 ************************************************************************/
void gpio_dir(UINT8 port, UINT8 pin, UINT8 newstate)
{	

	if(newstate)     //GPIO_DIR_OUT
	{
		REG_GPIO_DIR(port) |= (1 << pin);
	}
    else		     //GPIO_DIR_IN
    {
        REG_GPIO_DIR(port) &= (~(1 << pin));	
    }

}
/************************************************************************
 * function   : gpio_in_enable
 * Description: gpio in enable
 * 
 * input : 	UINT8 gpio port 
 *			UINT8 gpio pin
*			UINT8 newstate     ENABLE ����ʹ�ܣ�DISABLE �����ֹ
 ************************************************************************/
void gpio_in_enable(UINT8 port, UINT8 pin, UINT8 newstate)
{
	if(newstate)
	{
		//����ʹ��
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;			//���IOд����
		REG_SCU_PADIE |= (1<<(port*8+pin));
		REG_SCU_IOCTRLPROTECT = 0xffffffff; 		//����IOд����
	}
	else
	{
		//�����ֹ
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;			//���IOд����
		REG_SCU_PADIE &= ~(1<<(port*8+pin));
		REG_SCU_IOCTRLPROTECT = 0xffffffff; 		//����IOд����
	}
}
/************************************************************************
 * function   : gpio_config_pu
 * Description: set pullup function 
 * ����GPIO �˿�������
 * input : 	UINT8 gpio port     A,B,C,D�˿�
 *			UINT8 gpio pin		0~7
 *			UINT8 newstate 		1 ����ʹ�ܣ� 0 ������ֹ
 * return: none
 ************************************************************************/
void gpio_config_pu(UINT8 port, UINT8 pin, UINT8 newstate)
{
	if(newstate)
	{
		//����ʹ��
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;			//���IOд����
		REG_SCU_PADPU |= (1<<(port*8+pin));
		REG_SCU_IOCTRLPROTECT = 0xffffffff; 		//����IOд����
	}
	else
	{
		//������ֹ
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;			//���IOд����
		REG_SCU_PADPU &= ~(1<<(port*8+pin));
		REG_SCU_IOCTRLPROTECT = 0xffffffff; 		//����IOд����
	}		
}
/************************************************************************
 * function   : gpio_config_pd
 * Description: set pulldown function 
 * ����GPIO �˿�������
 * input : 	UINT8 gpio port     A,B,C,D�˿�
 *			UINT8 gpio pin		0~7
 *			UINT8 newstate 		1 ����ʹ�ܣ� 0 ������ֹ
 * return: none
 ************************************************************************/
void gpio_config_pd(UINT8 port, UINT8 pin, UINT8 newstate)
{
	if(newstate)
	{
		//����ʹ��
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;			//���IOд����
		REG_SCU_PADPD |= (1<<(port*8+pin));
		REG_SCU_IOCTRLPROTECT = 0xffffffff; 		//����IOд����
	}
	else
	{
		//������ֹ
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;			//���IOд����
		REG_SCU_PADPD &= ~(1<<(port*8+pin));
		REG_SCU_IOCTRLPROTECT = 0xffffffff; 		//����IOд����
	}		
}

/************************************************************************
 * function   : gpio_config_od
 * Description: set gpio output open drain 
 * ����GPIO �˿ڿ�©���
 * input : 	UINT8 gpio port     A,B,C,D�˿�
 *			UINT8 gpio pin		0~7
 *			UINT8 newstate 		1 ��©ʹ�ܣ� 0 ��©��ֹ
 * return: none
 ************************************************************************/
void gpio_config_od(UINT8 port, UINT8 pin, UINT8 newstate)
{
	if(newstate)
	{
		//��©���ʹ��
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;			//���IOд����
		REG_SCU_PADOD |= (1<<(port*8+pin));
		REG_SCU_IOCTRLPROTECT = 0xffffffff; 		//����IOд����
	}
	else
	{
		//��©�����ֹ
		REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;			//���IOд����
		REG_SCU_PADOD &= ~(1<<(port*8+pin));
		REG_SCU_IOCTRLPROTECT = 0xffffffff; 		//����IOд����
	}	
}
/************************************************************************
 * function   : gpio_getio
 * Description: get gpio pin value
 * GPIO�����ƽ��ȡ
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 * return: �ܽŵ�ƽ״̬
 ************************************************************************/
UINT8 gpio_getio(UINT8 port, UINT8 pin)
{
    return (REG_GPIO_IDATA(port) >> pin) & 0x01;	
}


/************************************************************************
 * function   : gpio_setio
 * Description: gpio set 1
 * GPIO��ƽ���
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate : high 1��low 0
 * return: none
 ************************************************************************/
void gpio_setio(UINT8 port, UINT8 pin, UINT8 newstate)
{
	if(newstate)
	{
	    REG_GPIO_SET(port) |= 1 << pin;
	}
	else
	{
	    REG_GPIO_CLR(port) |= 1 << pin;
	}
}
/************************************************************************
 * function   : gpio_set_irq
 * Description: gpio interrupt configuration
 * GPIO�ж�ʹ�ܣ�ʧ��
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate : enable ʹ�ܣ�disable ʧ��
 * return: none
 ************************************************************************/
void gpio_set_irq(UINT8 port, UINT8 pin, UINT8 newstate)
{
	if(newstate)
	{
		REG_GPIO_IEN(port) |= (1 << pin);
	}
	else
	{
	    REG_GPIO_IEN(port) &= (~(1 << pin));
	}	
	
}

/************************************************************************
 * function   : gpio_set_is
 * Description: set the interrupt sense of gpio pin
 * GPIO�жϴ�����������
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate:  0  ���ش�����1 ��ƽ����
 * return: none
 ************************************************************************/
void gpio_set_is(UINT8 port, UINT8 pin, UINT8 newstate)
{
    if (newstate == GPIO_IS_EDGE)
    {
        REG_GPIO_IS(port) &= (~(1 << pin));		//���ش���
    }
    else
    {
        REG_GPIO_IS(port) |= (1 << pin);		//��ƽ����
    }
}

/************************************************************************
 * function   : gpio_set_iev
 * Description: set the interrupt event of gpio pin
 * GPIO�жϸߵ͵�ƽ��������
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate: interrupt event
 * return: none
 ************************************************************************/
void gpio_set_iev(UINT8 port, UINT8 pin, UINT8 newstate)
{
    if (newstate == GPIO_IEV_FALLEDGEORLOWLEVEL)
    {
        REG_GPIO_IEV(port) &= (~(1 << pin));				//�½���/�͵�ƽ
    }
    else
    {
        REG_GPIO_IEV(port) |= (1 << pin);					//������/�ߵ�ƽ
    }
}
/************************************************************************
 * function   : gpio_set_ibe
 * Description: set the interrupt both edge of gpio pin
 * GPIO�жϵ�˫�ߴ�������
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 *		   UINT8 newstate: 0 �����ش�����1 ˫���ش���
 * return: none
 ************************************************************************/
void gpio_set_ibe(UINT8 port, UINT8 pin, UINT8 newstate)
{
    if (newstate == GPIO_IBE_SINGLE)
    {
        REG_GPIO_IBE(port) &= (~(1 << pin));		//����
    }
    else
    {
        REG_GPIO_IBE(port) |= (1 << pin);			//˫��
    }
}

/************************************************************************
 * function   : gpio_clr_irq
 * Description: clear the interrupt flag of gpio pin
 * GPIO�ж����
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 * return: none
 ************************************************************************/
void gpio_clr_irq(UINT8 port, UINT8 pin)
{
    REG_GPIO_IC(port) |= (1 << pin);			//���ж�	
}

/************************************************************************
 * function   : gpio_original_irq
 * Description: get gpio raw interrupt status
 * GPIO��ԭʼ�ж�״̬
 * input : UINT8 port: gpio port    
 *		   UINT8 pin : gpio pin
 * return: status 0 ��Ӧ�������жϹ���1 ��Ӧ�������жϹ���
 ************************************************************************/
UINT8 gpio_original_irq(UINT8 port, UINT8 pin)
{
	return (REG_GPIO_RIS(port) >> pin) & 0x01;
}

