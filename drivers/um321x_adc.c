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
	/*���յ��жϺ󣬶�ȡת�����*/
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
 * GPIO �˿ڳ�ʼ��: ���������ģ�⣬������������/��©���,ʱ�ӳ�ʼ��
 * GPIO��6��ģ������ͨ����PA1--AIN0 PA2--AIN1 PA3--AIN2 
						PB4--AIN4 PB5--AIN3 PC3--AIN5
 * input : none
 * return: none
 ************************************************************************/
void adc_gpio_config(void)
{
	REG_SCU_PERICLKEN |= (1<<16)| (1<<19);				//������ص�GPIOA GPIOD����ʱ��
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;
	REG_SCU_PADADS |= (1<<2);							//ʹ��ͨ��1��AIN1--PA2
	
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A;
	REG_SCU_PADADS |= (1<<30);							//ʹ��ͨ��3��AIN3--PD6
	
}

/************************************************************************
 * function   : adc_single_mode_one_channel
 * Description: adc_single_mode_one_channel configuration
 * ���������ADC����ת�����ԣ�һͨ��
 * ��ת������ͨ������ֻ��ת��һ��
 * input : none
 * return: none
 ************************************************************************/
void adc_single_mode_one_channel(void)
{
	UINT32 temp = 0;
	adc_gpio_config();												//ADC GPIO����
					
	REG_SCU_PERICLKEN |= ADC_CLKEN;									//����ADCʱ��
	REG_SCU_PERIRESET |= ADC_RESET;									//ADC��λ
					
	REG_ADC_GCR &= ~ADC_PD_ON;				
	REG_ADC_GCR &= ~ADC_RST;				
				
	temp = ADC_SINGLE_MODE \
			| ADC_CLK_ICD | ADC_RCLR_EN \
			| ADC_RXFIFO_MODE;										//ʹ��RX FIFOģʽ��rxtlfλ��0����RX FIFO��������һ����Ч����ʱ���ɴ����ж�
	REG_ADC_GCR |= temp; 											//ADC�ϵ磬����ת��ģʽ,ʹ���ڲ�ʱ�ӷ�Ƶ����ʹ��ADC���ݼĴ�������
					
//	REG_ADC_CDR = ADC_CLK_DIV_4;				
//	REG_ADC_COUNT = ADC_SWITCH_COUNT_0;								//�ķ�Ƶ
	adc_rx_flag = 0;				
				
	REG_ADC_ICR = 0x30F;											//��������ж�
	REG_ADC_IER |= ADC_IT_RX_FIFO_EN;								//ʹ��RX FIFO�ж�

	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);

	adc_rx_flag = 0;
	memset(adc_converte_val,0,sizeof(adc_converte_val));			//����������0

	REG_ADC_GCR |= ADC_EN;											//����ADC
	temp = ADC_CH3_EN;												//ѡ���ת��ͨ�� PD6-AIN3
	REG_ADC_GCR |= temp;				
	delay_ms(1);				
	REG_ADC_GCR |= ADC_START_EN;									//ADC����ת����ʼ
}

/************************************************************************
 * function   : adc_single_mode_multi_channels
 * Description: adc_single_mode_multi_channels configuration
 * ���������ADC����ת�����ԣ���ͨ��
 * ��һ��ת������ͨ��
 * input : none
 * return: none
 ************************************************************************/
void adc_single_mode_multi_channels(void)
{
	UINT32 temp = 0;
	adc_gpio_config();									   			//ADC GPIO����
	
	REG_SCU_PERICLKEN |= ADC_CLKEN;						  			//����ADCʱ��
	REG_SCU_PERIRESET |= ADC_RESET;						  			//ADC��λ
	
	REG_ADC_GCR &= ~ADC_PD_ON;
	REG_ADC_GCR &= ~ADC_RST;

	temp = ADC_SINGLE_MODE \
			| ADC_CLK_ICD | ADC_RCLR_EN \
			| ADC_RXFIFO_MODE;							  			//ʹ��RX FIFOģʽ��rxtlfλ��0����RX FIFO��������һ����Ч����ʱ���ɴ����ж�
	REG_ADC_GCR |= temp; 								  			//ADC�ϵ磬����ת��ģʽ,ʹ���ڲ�ʱ�ӷ�Ƶ����ʹ��ADC���ݼĴ�������
				
//	REG_ADC_CDR = ADC_CLK_DIV_4;			
//	REG_ADC_COUNT = ADC_SWITCH_COUNT_0;				      			//�ķ�Ƶ
	adc_rx_flag = 0;			
			
	REG_ADC_ICR = 0x30F;							      			//��������ж�
	REG_ADC_IER |= ADC_IT_RX_FIFO_EN;					  			//ʹ��RX FIFO�ж�

	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);

	adc_rx_flag = 0;
	memset(adc_converte_val,0,sizeof(adc_converte_val));  			//����������0
			
	REG_ADC_GCR |= ADC_EN;							      			//����ADC
	temp = ADC_CH1_EN|ADC_CH3_EN;						  			//ѡ�� ͨ��1��AIN1--PA2 �� ͨ��3��AIN3--PD6
	REG_ADC_GCR |= temp;			
	delay_ms(1);			
	REG_ADC_GCR |= ADC_START_EN;					      			//ADC����ת����ʼ
}

/************************************************************************
 * function   : adc_continuous_mode
 * Description: adc_continuous_mode configuration
 * ���������ADC����ת������
 * �ܶԶ���ͨ������ѭ��ת��
 * ѭ��ת��ģʽ�ת��������ݻ�ŵ�RX FIFO��
 * �Ĵ���RXREG��RX FIFO����ڣ��жϴ������ȡRXREG�Ĵ���
 * input : none
 * return: none
 ************************************************************************/
void adc_continuous_mode(void)
{
	UINT32 temp = 0;
	adc_gpio_config();											//ADC GPIO����
	
	REG_SCU_PERICLKEN |= ADC_CLKEN;								//����ADCʱ��
	REG_SCU_PERIRESET |= ADC_RESET;								//ADC��λ
	
	REG_ADC_GCR &= ~ADC_PD_ON;
	REG_ADC_GCR &= ~ADC_RST;

	temp = ADC_CONTINUOUS_MODE \
			| ADC_CLK_ICD | ADC_RCLR_EN \
			| ADC_RXFIFO_MODE;									//ʹ��RX FIFOģʽ��rxtlfλ��0����RX FIFO��������һ����Ч����ʱ���ɴ����ж�
	REG_ADC_GCR |= temp; 										//ADC�ϵ磬����ת��ģʽ,ʹ���ڲ�ʱ�ӷ�Ƶ����ʹ��ADC���ݼĴ�������
	
	
//	REG_ADC_CDR = ADC_CLK_DIV_4;								//�ķ�Ƶ
	
	REG_ADC_COUNT = ADC_SWITCH_COUNT_0;	
	adc_rx_flag = 0;

	REG_ADC_ICR = 0x30F;										//��������ж�
	REG_ADC_IER |= ADC_IT_RX_FIFO_EN;							//ʹ��RX FIFO�ж�

	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);

	adc_rx_flag = 0;
	memset(adc_converte_val,0,sizeof(adc_converte_val));		//����������0

	REG_ADC_GCR |= ADC_EN;										//����ADC
	temp = ADC_CH3_EN;											//ѡ���ת��ͨ�� PD6-AIN3
	REG_ADC_GCR |= temp;			
	REG_ADC_GCR |= ADC_START_EN;								//ADC����ת����ʼ
	
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
	
	/*���յ��жϺ󣬶�ȡת�����*/
	//if(REG_ADC0_DR & ADC_DATA_VALID)							//CH0����Ч���ݣ��������ѯ�����õģ��жϲ���
	UINT32 temp = 0;
	temp = REG_ADC_GCR & 0xFF0000;
	if(temp & ADC_CH0_EN)
	{
		conver_data0 = REG_ADC0_DR & ADC_CHx_DATA;				//����ת�����ݣ���ȡ���ݼĴ�����validλ��data�Զ����㣨ADC_RCLR_ENʱ��
		REG_ADC_ICR |= ADC_IT_CH0_CLR;							//����ж�
	}
	
	if(temp & ADC_CH3_EN)
	{
		conver_data3 = REG_ADC3_DR & ADC_CHx_DATA;				//����ת�����ݣ���ȡ���ݼĴ�����validλ��data�Զ����㣨ADC_RCLR_ENʱ��
		REG_ADC_ICR |= ADC_IT_CH3_CLR;							//����ж�
	}
	if(!(REG_ADC_GCR & ADC_SINGLE_MODE))
	REG_ADC_GCR &= ~(ADC_EN | ADC_START_EN);					//ֹͣADCת��
}

