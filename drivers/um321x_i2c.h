/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : i2c.c
 * Description : i2c driver header file
 * Author(s)   : Chloe
 * version     : V1.0
 * Modify date : 2019-05-21
 ***********************************************************************/
#ifndef _I2C_H_
#define _I2C_H_

#include  "common.h"

/** generic error codes */
typedef enum en_result
{
    Ok                          = 0u,  ///< No error
    Error                       = 1u,  ///< Non-specific error code
    ErrorAddressAlignment       = 2u,  ///< Address alignment does not match
    ErrorAccessRights           = 3u,  ///< Wrong mode (e.g. user/system) mode is set
    ErrorInvalidParameter       = 4u,  ///< Provided parameter is not valid
    ErrorOperationInProgress    = 5u,  ///< A conflicting or requested operation is still in progress
    ErrorInvalidMode            = 6u,  ///< Operation not allowed in current mode
    ErrorUninitialized          = 7u,  ///< Module (or part of it) was not initialized properly
    ErrorBufferFull             = 8u,  ///< Circular buffer can not be written because the buffer is full
    ErrorTimeout                = 9u,  ///< Time Out error occurred (e.g. I2C arbitration lost, Flash time-out, etc.)
    ErrorNotReady               = 10u, ///< A requested final state is not reached
    OperationInProgress         = 11u  ///< Indicator for operation in progres
} en_result_t;

typedef enum en_i2c_func
{
    I2cMode_En  = 0, ///<I2C从机使能
    I2cStart_En = 1, ///<开始信号
    I2cStop_En  = 2, ///<结束信号
    I2cAck_En   = 3, ///<应答信号
	I2cIrq_En   = 4, ///<中断使能
}en_i2c_func_t;

#define I2C_MASTER  	       			 	1
#define I2C_SLAVE  	           			 	2

#define I2C_STANDARD_MODE  	            	0
#define I2C_FAST_MODE  	            		1
#define I2C_HIGH_MODE  	            		2

//SYSCFG REG (PERI_CLKEN) I2C 时钟选择(test)
#define I2C_CLKEN  	            	(UINT32)0x1<<15

//I2C复位(test)
#define I2C_RESET  	            	(UINT32)0x1<<15

//Slave Addr广播地址应答使能
#define I2C_SAD_GC  	           	(UINT32)1<<0

/*------------REG I2C_CR----------------*/
#define I2C_CR_GCAVAL  	           (UINT32)1<<8			//General Call使能
#define I2C_CR_IEN  	           (UINT32)1<<7			//I2C中断使能
#define I2C_CR_ENAB  	           (UINT32)1<<6			//I2C模块从模式使能位
#define I2C_CR_STA  	           (UINT32)1<<5			//发送START标志
#define I2C_CR_STP  	           (UINT32)1<<4			//发送STOP标志
#define I2C_CR_IFLG  	           (UINT32)1<<3			//中断标志位
#define I2C_CR_AAK  	           (UINT32)1<<2			//发送ACK标志
#define I2C_CR_SLAV10M  	       (UINT32)1<<1			//从模式时，收到的数据与SLAVE拓展地址寄存器中的数值相匹配
#define I2C_CR_SLAV7M	  	       (UINT32)1<<0			//从模式时，收到的数据与SLAVE地址寄存器中的数值相匹配

/*------------REG I2C_CCR----------------*/
#define I2C_CCR_CCRM  	           (UINT32)0x7F<<0	

/*------------REG I2C_STAT----------------*/
#define I2C_STAT_START_BIT_SENT  	    		(UINT32)0x08	//已发送START
#define I2C_STAT_RESTART_BIT_SENT  	    		(UINT32)0x10	//已发送RESTART
#define I2C_STAT_TX_ADDR 	         			(UINT32)0x18	//已发送SLAVE地址加写标志，并接收ACK
#define I2C_STAT_TX_DATA  	         			(UINT32)0x28
#define I2C_STAT_NAK_REC  	         			(UINT32)0x30
#define I2C_STAT_ID_LOST  	         			(UINT32)0x38
#define I2C_STAT_RX_ADDR  	         			(UINT32)0x40
#define I2C_STAT_RX_ADDR_NACK         			(UINT32)0x48
#define I2C_STAT_RX_DATA_ACK  	        		(UINT32)0x50
#define I2C_STAT_RX_DATA_NACK  	        		(UINT32)0x58
#define I2C_STAT_SLAVE_RX_DEVADDRW_ACK      	(UINT32)0x60
#define I2C_STAT_SLAVE_RX_DEVADDR_ACK      		(UINT32)0x68
#define I2C_STAT_SLAVE_RX_ADDR0			      	(UINT32)0x70
#define I2C_STAT_SLAVE_RX_ADDR0W	      		(UINT32)0x78
#define I2C_STAT_SLAVE_LRX_ADDR_ACK			    (UINT32)0x80
#define I2C_STAT_SLAVE_LRX_ADDR_NACK	      	(UINT32)0x88
#define I2C_STAT_SLAVE_LRX_ADDR0_ACK		    (UINT32)0x90
#define I2C_STAT_SLAVE_LRX_ADDR0_NACK      		(UINT32)0x98
#define I2C_STAT_SLAVE_RX_STP_RSTA      		(UINT32)0xA0
#define I2C_STAT_SLAVE_RX_ADDR_ACK      		(UINT32)0xA8
#define I2C_STAT_SLAVE_RX_ADDR0R		    	(UINT32)0xB0
#define I2C_STAT_SLAVE_TX_DATA_ACK	    		(UINT32)0xB8
#define I2C_STAT_SLAVE_TX_DATA_NACK	    		(UINT32)0xC0
#define I2C_STAT_SLAVE_TX_BYTE_ACK	    		(UINT32)0xC8
#define I2C_STAT_SECOND_ADD_ACK					(UINT32)0xe0
#define I2C_STAT_SECOND_ADD_NOTACK				(UINT32)0xe8

void i2c_speed(UINT8 speed);
UINT32 i2c_timeout_user_callback(UINT8 errcode);
en_result_t i2c_clr_func(en_i2c_func_t index_func);
en_result_t i2c_set_func(en_i2c_func_t index_func);
UINT8 i2c_get_status(void);
UINT8 i2c_get_irq(void);
UINT8 i2c_read_byte(void);
void i2c_init(UINT8 i2c_device);
en_result_t i2c_master_write_data(UINT8 DevAddr, UINT8 sAddr, UINT8* pBuffer, UINT8 NumByteToWrite);
en_result_t i2c_write_byte(UINT8 data_to_send);
en_result_t i2c_master_read_data_simple(UINT8 sAddr, UINT8* pBuffer, UINT8 NumByteToRead);
en_result_t i2c_master_write_data_10b(UINT16 sAddr, UINT8* pBuffer, UINT8 NumByteToWrite);
en_result_t i2c_master_read_data_simple_10b(UINT16 sAddr, UINT8* pBuffer, UINT8 NumByteToRead);

#endif

