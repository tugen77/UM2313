/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : i2c.c
 * Description : i2c source file
 * Author(s)   : Chloe
 * version     : V1.0
 * Modify date : 2019-05-22
 ***********************************************************************/

#include "um321x_i2c.h"
/************************************************************************
 * function   : i2c_init
 * Description: i2c pin init, config interruption
 * input : device type: slave or master
 * return: none
 ************************************************************************/
void i2c_init(UINT8 i2c_device)
{
	//����I2Cʱ��
	REG_SCU_PERICLKEN |= I2C_CLKEN;
	//SCU��λ���ƼĴ���
	REG_SCU_PERIRESET |= I2C_RESET;	
	REG_I2C_SRST = 1;

	REG_SCU_PDSEL|=(REG_SCU_PDSEL&(~(7<<16)))|(3<<16);      //PD4 SCL
	REG_SCU_PASEL|=(REG_SCU_PASEL&(~(7<<8)))|(4<<8);        //PA2 SDA

	//����������
	i2c_speed(I2C_STANDARD_MODE);			//I2C ����ģʽ��1 Mbit��
	
	//I2C�ж�ʹ��
	i2c_set_func(I2cIrq_En);
	REG_I2C_CR |= I2C_CR_GCAVAL;		//General Call����ʹ��λ
}

/************************************************************************
 * function   : i2c_speed
 * Description: i2c_speed
 * input : I2Cģʽ�����棬���� �� ����
 * return: rdata: none
 ************************************************************************/
void i2c_speed(UINT8 speed)
{
	switch(speed)
	{
		case I2C_STANDARD_MODE:
			REG_I2C_CCR&=~(3<<4);
			REG_I2C_CCR&=~(3<<0);
		
			REG_I2C_CCR|=(3<<4); // 100K
			REG_I2C_CCR|=(3<<0);
			break;
		
		case I2C_FAST_MODE:
			REG_I2C_CCR&=~(2<<4); //400K
			REG_I2C_CCR&=~(2<<0);
		
			REG_I2C_CCR|=(1<<4); //400K
			REG_I2C_CCR|=(3<<0);
			break;
		
		case I2C_HIGH_MODE:
			REG_I2C_CCR&=~(0<<4); // 1M
			REG_I2C_CCR&=~(2<<0);
		
			REG_I2C_CCR&=~(0<<4); // 1M
			REG_I2C_CCR|=(2<<0);
			break;	
		
		default:
			 break;
	}
}

/************************************************************************
 * function   : i2c_get_irq
 * Description: i2c_get_irq
 * input : none
 * return: IRQ_trigger
 ************************************************************************/
UINT8 i2c_get_irq(void)
{
	UINT8 irq_flag = 0;
	irq_flag = (REG_I2C_CR & I2C_CR_IFLG) >> 3;
	return irq_flag;
}

/************************************************************************
 * function   : i2c_get_status
 * Description: i2c_get_status
 * input : none
 * return: status_flag
 ************************************************************************/
UINT8 i2c_get_status(void)
{
	UINT8 status_flag = 0;
	status_flag = REG_I2C_STAT;
	return status_flag;
}

/************************************************************************
 * function   : i2c_set_func
 * Description: i2c_set_func
 * input : START,STOP,ACK����ʹ�ܣ��ӻ�ģʽʹ��
 * return: en_result_t
 ************************************************************************/
en_result_t i2c_set_func(en_i2c_func_t index_func)
{
	en_result_t set_result = Error;
	switch(index_func)
	{
		case I2cMode_En:
			REG_I2C_CR |= I2C_CR_ENAB;
			break;
		case I2cStart_En:
            REG_I2C_CR |= I2C_CR_STA;
            break;
        case I2cStop_En:
            REG_I2C_CR |= I2C_CR_STP;
            break;
        case I2cAck_En:
            REG_I2C_CR |= I2C_CR_AAK;
            break;
		case I2cIrq_En:
            REG_I2C_CR |= I2C_CR_IEN;
            break;
		default:
            return ErrorInvalidParameter;
	}
	set_result = Ok;
	return set_result;
}

/************************************************************************
 * function   : i2c_clr_func
 * Description: i2c_clr_func
 * input : START,STOP,ACK����ʹ�ܣ��ӻ�ģʽʹ�ܽ�ֹ
 * return: en_result_t
 ************************************************************************/
en_result_t i2c_clr_func(en_i2c_func_t index_func)
{
	en_result_t clr_result = Error;
	switch(index_func)
	{
		case I2cMode_En:
			REG_I2C_CLR |= I2C_CR_ENAB;
			break;
		case I2cStart_En:
            REG_I2C_CLR |= I2C_CR_STA;
            break;
        case I2cStop_En:
            REG_I2C_CLR |= I2C_CR_STP;
            break;
        case I2cAck_En:
            REG_I2C_CLR |= I2C_CR_AAK;
            break;
		case I2cIrq_En:
            REG_I2C_CLR |= I2C_CR_IEN;
            break;
		default:
            return ErrorInvalidParameter;
	}
	clr_result = Ok;
	return clr_result;
}

/************************************************************************
 * function   : i2c_write_byte
 * Description: i2c_write_byte
 * input : ���͵����ݣ�1 Byte��
 * return: rdata: none
 ************************************************************************/
en_result_t i2c_write_byte(UINT8 data_to_send)
{
	en_result_t send_result = Error;

	REG_I2C_DATA = data_to_send;
	
	send_result = Ok;
	return send_result;
}

/************************************************************************
 * function   : i2c_read_byte
 * Description: i2c_read_byte
 * input : none
 * return: rdata: �������ݣ�1 Byte��
 ************************************************************************/
UINT8 i2c_read_byte(void)
{
	UINT8 rdata = 0;
	rdata = REG_I2C_DATA;
	return rdata;
}

/************************************************************************
 * function   : i2c_master_write_data
 * Description: i2c_master_write_data
 * input : DevAddr�����豸7λ�ڴ��ַ sAddr�����豸��ַ pBuffer���������ݻ����� NumByteToWrite
 * return: en_result_t
 ************************************************************************/
en_result_t i2c_master_write_data(UINT8 DevAddr, UINT8 sAddr, UINT8* pBuffer, UINT8 NumByteToWrite)
{
	en_result_t enRet = Error;
	UINT8 i=0, status;
	UINT8 flag_stp = 0;
	
	//1.��������START��־
 	i2c_set_func(I2cStart_En);
	while(1)
	{
		while(i2c_get_irq() == 0);
		status = i2c_get_status();
		switch(status)
		{
			case I2C_STAT_START_BIT_SENT:

										i2c_clr_func(I2cStart_En);
										i2c_write_byte(sAddr);		//2.���ʹ��豸��ַ��д��
										break;
			case I2C_STAT_TX_ADDR:
										i2c_write_byte(DevAddr);	//3.���ʹ��豸�ڴ��ַ
										i2c_write_byte(pBuffer[i++]);	//4.ѭ����������
										break;
			case I2C_STAT_TX_DATA:
										if(i==NumByteToWrite)
										{
											flag_stp = 1;
										}
										else
										{
											i2c_write_byte(pBuffer[i++]);	//4.ѭ����������
										}
										break;
			case I2C_STAT_ID_LOST:
										i2c_set_func(I2cStart_En);
										break;
			case I2C_STAT_NAK_REC:
										i2c_set_func(I2cStop_En);
										break;
			default:
										i2c_set_func(I2cStart_En);		//��������״̬�����·�����ʼ����
										break;
		}
		if(flag_stp)
		{
			i2c_set_func(I2cStop_En);
			REG_I2C_CLR |= I2C_CR_IFLG;		//���жϱ�־
			break;
		}
		REG_I2C_CLR |= I2C_CR_IFLG;		//���жϱ�־
		}
		enRet = Ok;
		return enRet;
}

/************************************************************************
 * function   : i2c_master_read_data
 * Description: i2c_master_read_data
 * input : sAddr�����豸��ַ pBuffer���������ݻ����� NumByteToRead
 * return: en_result_t
 ************************************************************************/
en_result_t i2c_master_read_data_simple(UINT8 sAddr, UINT8* pBuffer, UINT8 NumByteToRead)
{
	en_result_t enRet = Error;
	UINT8 i=0, status;
	
	//1.��������START��־
	i2c_set_func(I2cStart_En);
	while(1)
	{
		while(i2c_get_irq() == 0);
		status = i2c_get_status();
		
		switch(status)
		{
			case I2C_STAT_START_BIT_SENT:
										i2c_clr_func(I2cStart_En);
										i2c_write_byte(sAddr|0x01);		//4.���ʹ��豸��ַ(��)
										break;
			case I2C_STAT_RX_ADDR:				//5.ACK����
										if(NumByteToRead>1)
										{
											i2c_set_func(I2cAck_En);	//����������ݴ���1Byte,�������һ��Byte����ACK�ź�
										}
										break;
			case I2C_STAT_RX_DATA_ACK:			//6.��������
										pBuffer[i++] = i2c_read_byte();
										if(i == NumByteToRead - 1)		//�����ڶ���Byte���ֹACKʹ�ܷ��ͣ����һ���ֽں󲻷���ACK
										{
											i2c_clr_func(I2cAck_En);
										}
										break;
			case I2C_STAT_RX_DATA_NACK:
										pBuffer[i++] = i2c_read_byte();
										i2c_set_func(I2cStop_En);		//7.������Ϸ���STOP
										break;
			case I2C_STAT_ID_LOST:
										i2c_set_func(I2cStart_En);
										break;
			case I2C_STAT_RX_ADDR_NACK:
										i2c_set_func(I2cStop_En);
										i2c_set_func(I2cStart_En);
										break;
			case I2C_STAT_NAK_REC:
										i2c_set_func(I2cStop_En);
										break;
			default:
										i2c_set_func(I2cStart_En);		//��������״̬�����·�����ʼ����
										break;
		}
		
		REG_I2C_CLR |= I2C_CR_IFLG;		//���жϱ�־
		if(i == NumByteToRead)
		{
			break;
		}
	}
		enRet = Ok;
		return enRet;
}

/************************************************************************
 * function   : i2c_master_write_data
 * Description: i2c_master_write_data
 * input : sAddr��10λ���豸��ַ pBuffer���������ݻ����� NumByteToWrite
 * return: en_result_t
 ************************************************************************/
en_result_t i2c_master_write_data_10b(UINT16 sAddr, UINT8* pBuffer, UINT8 NumByteToWrite)
{
	en_result_t enRet = Error;
	UINT8 i=0, status, j=0;
	UINT8 indicator1_10b = 0xF0, indicator2_10b;
	UINT8 flag_stp=0;
	
	indicator2_10b = (UINT8)sAddr;
	indicator1_10b |= (UINT8)((sAddr >> 7) & 0x06);
	
	//1.��������START��־
 	i2c_set_func(I2cStart_En);
	while(1)
	{
	while(i2c_get_irq() == 0);
	status = i2c_get_status();
		
	switch(status)
	{
		case I2C_STAT_START_BIT_SENT:
									i2c_clr_func(I2cStart_En);
									i2c_write_byte(indicator1_10b);			//2.���ʹ��豸��ַ��һbyte��д��
									break;
		case I2C_STAT_TX_ADDR:
									if(j<1)
									{
									i2c_write_byte(indicator2_10b);			//3.���ʹ��豸��ַ�ڶ�byte��д��
									j++;
									}
									break;
		case I2C_STAT_SECOND_ADD_ACK:                       				 //SECONG RECIVE 
									i2c_write_byte(pBuffer[i++]);			//4.ѭ����������
									break;
		case I2C_STAT_TX_DATA:
									if(i==NumByteToWrite)
									{
										flag_stp = 1;
									}
									else
									{
										i2c_write_byte(pBuffer[i++]);			//4.ѭ����������
									}
									break;
		case I2C_STAT_ID_LOST:
									i2c_set_func(I2cStart_En);
		break;
		case I2C_STAT_NAK_REC:
									i2c_set_func(I2cStop_En);
									break;
		default:
									i2c_set_func(I2cStart_En);					//��������״̬�����·�����ʼ����
									break;
		}
		if(flag_stp)
		{
			i2c_set_func(I2cStop_En);
			REG_I2C_CLR |= I2C_CR_IFLG;		//���жϱ�־
			break;
		}
		REG_I2C_CLR |= I2C_CR_IFLG;		//���жϱ�־
	}
	enRet = Ok;
    return enRet;
}

/************************************************************************
 * function   : i2c_master_read_data
 * Description: i2c_master_read_data
 * input : sAddr��10λ���豸��ַ pBuffer���������ݻ����� NumByteToRead
 * return: en_result_t
 ************************************************************************/
en_result_t i2c_master_read_data_simple_10b(UINT16 sAddr, UINT8* pBuffer, UINT8 NumByteToRead)
{
	en_result_t enRet = Error;
	UINT8 i=0, status,j=0;
	UINT8 indicator1_10b = 0xF0, indicator2_10b;
	indicator2_10b = (UINT8)sAddr;
	indicator1_10b |= (UINT8)((sAddr >> 7) & 0x06);
	//1.��������START��־
	i2c_set_func(I2cStart_En);
	while(1)
	{
		while(i2c_get_irq() == 0);
		status = i2c_get_status();

		switch(status)
		{
			case I2C_STAT_START_BIT_SENT:
											i2c_clr_func(I2cStart_En);
											i2c_write_byte(indicator1_10b);			//2.���ʹ��豸��ַ��һbyte��д��
											break;
			case I2C_STAT_TX_ADDR:
											if(j<1)
											{
												i2c_write_byte(indicator2_10b);			//3.���ʹ��豸��ַ�ڶ�byte��д��
												j++;
											}

											break;

			case I2C_STAT_SECOND_ADD_ACK:
											i2c_set_func(I2cStart_En);
											break;

			case I2C_STAT_RESTART_BIT_SENT:
											i2c_clr_func(I2cStart_En);
											i2c_write_byte(indicator1_10b | 0x01);			//2.���ʹ��豸��ַ��һbyte������
											break;
			case I2C_STAT_RX_ADDR:								//3.ACK����
											if(NumByteToRead>1)
											{
											i2c_set_func(I2cAck_En);					    //����������ݴ���1Byte,�������һ��Byte����ACK�ź�
											}
											break;
			case I2C_STAT_RX_DATA_ACK:							//6.��������
											pBuffer[i++] = i2c_read_byte();
											if(i == NumByteToRead - 1)						//�����ڶ���Byte���ֹACKʹ�ܷ��ͣ����һ���ֽں󲻷���ACK
											{
											i2c_clr_func(I2cAck_En);
											}
											break;
			case I2C_STAT_RX_DATA_NACK:
											pBuffer[i++] = i2c_read_byte();
											i2c_set_func(I2cStop_En);						//7.������Ϸ���STOP
											break;
			case I2C_STAT_ID_LOST:
											i2c_set_func(I2cStart_En);
											break;
			case I2C_STAT_RX_ADDR_NACK:
											i2c_set_func(I2cStop_En);
											i2c_set_func(I2cStart_En);
											break;
			case I2C_STAT_NAK_REC:
											i2c_set_func(I2cStop_En);
											break;
			default:
											i2c_set_func(I2cStart_En);						//��������״̬�����·�����ʼ����
											break;
			}
		
			REG_I2C_CLR |= I2C_CR_IFLG;		//���жϱ�־
			if(i == NumByteToRead)
			{
				break;
			}
	}
	enRet = Ok;
	return enRet;
}

//I2C���жϴ�����
void I2C_IRQHandler(void)
{
	//����IO�жϴ������
	printfS("i2c_master IT!\n");
	//�ж����
}

