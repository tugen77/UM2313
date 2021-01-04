/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : uart.c
 * Description : uart driver source file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-04-10
 ***********************************************************************/
#include  "um321x_uart.h"

#if 0
/************************************************************************
 * function   : UART_IRQHandler
 * Description: uart interrupt handling
 * input : none
 * return: none
 ************************************************************************/
void UART0_IRQHandler(void)
{
	UINT8 temp;

	temp = REG_UART0_ISR;
		
	if(temp & 0x20)       // Rx int 
	{
		while((REG_UART0_ISR & 0x20)== 0x20)
		{
			uart0_rx_buf[rx_count] = REG_UART0_RDR;
			rx_count++;
		    rx_flag = 1;
		}
		REG_UART0_ISR &= ~(1<<5);	//清除FIFO_NE非空标志位
	}
	else if(temp & 0x02)  // Tx int 发送中断
	{
		tx_flag = 1;
		REG_UART0_ISR &= ~(1<<1);	//清除发送完成标志位
	}
	else
	{
		REG_UART0_ISR = 0x00; //  清除中断状态
	}
	
}
#endif 

/************************************************************************
 * function   : uart_init
 * Description: uart initial for  baud_rate
 * input : 
 *         UINT32 baud_rate: Series rate
 * return: none
 ************************************************************************/
void uart0_init(UINT32 baud_rate)
{
	UINT32 uart_clk_hz;
//	uart_clk_hz = PCLK;	
	uart_clk_hz = SystemCoreClockGet(FCLK);	
	
	REG_SCU_PERICLKEN |= (1<<0);		//开UART时钟使能	
	REG_SCU_PERIRESET |= (1<<0);		//UART正常工作
	
	REG_SCU_IOCTRLPROTECT = 0xA5A55A5A; //清除IO写保护
	
	REG_SCU_PASEL = (REG_SCU_PASEL&(~(7<<4)))|(1<<4);		//PA1复用为UART0_RX
	REG_SCU_PDSEL = (REG_SCU_PDSEL&(~(7<<20)))|(1<<20);		//PD5复用为UART0_TX	
	
	REG_SCU_IOCTRLPROTECT = 0xffffffff; //开启IO写保护
	while((REG_SCU_IOCTRLPROTECT & 0x01) == 0x01)      //读IO控制保护寄存器的写使能状态
		REG_SCU_IOCTRLPROTECT = 0xffffffff; //开启IO写保护

	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);
	
	REG_UART0_ISR = 0x00; 		//中断状态清除
	
#ifdef UART_Tx_INT_MODE			//发送采用中断方式
	REG_UART_IER = 0x22;        //接收FIFO非空中断使能，发送完成中断使能,enable Rx/Tx_INT,disable else int
#else							//发送采用查询方式
	REG_UART0_IER = 0x20;        //接收FIFO非空中断使能，发送完成中断不使能,enable Rx_INT,disable Tx_INT and else int	
#endif	

	REG_UART0_CR = 0x04; 		//清除接收FIFO中数据和指针
	REG_UART0_CR = 0x00;
	
	REG_UART0_CR = 0x0a; 		//无奇偶校验,发送数据使能
	
	uart0_set_baud_rate(uart_clk_hz, baud_rate);		//设置波特率
}

/************************************************************************
 * function   : uart_set_baud_rate
 * Description: uart set baud rate
 * input : 
 *         UINT32 clk_hz: cpu frequency
 *         UINT32 baud_rate: Series rate
 * return: none
 ************************************************************************/
void uart0_set_baud_rate(UINT32 clk_hz, UINT32 baud_rate)
{
//1.计算波特率高、低位；
//2.设置波特率寄存器
	
	UINT16 temp;
	UINT8 MSbyte, LSbyte;

	temp = clk_hz / baud_rate;

	MSbyte = temp >> 8;
	LSbyte = temp;
	
	REG_UART0_BRPH = MSbyte;
	REG_UART0_BRPL = LSbyte;
}


/************************************************************************
 * function   : outbyte
 * Description: uart out byte
 * input : 
 *         char c: out byte
 * return: none
 ************************************************************************/
void uart0_send_byte(UINT8 c)
{
//	1.输出一个字符
	UINT16 timeout;
	timeout = 65535;
	
	REG_UART0_TDR = c;
	
#ifdef UART0_Tx_INT_MODE		//中断方式
	while(!tx_flag);
	tx_flag = 0;
#else						//查询方式
	while((REG_UART0_ISR & 0x02) != 0x02) //等待数据发送完
		if((timeout--)==0)   //超时等待退出
			break;
	REG_UART0_ISR &= ~(1<<1);			   //清除发送完成标志位
#endif	
}

/************************************************************************
 * function   : uart_send_bytes
 * Description: uart send bytes
 * input : 
 *         UINT8* buff: out buffer
 *         UINT32 length: buffer length
 * return: none
 ************************************************************************/
void uart0_send_bytes(UINT8 *buff, UINT32 length)
{
	UINT32 i;

	for(i = 0; i < length; i++)
		uart0_send_byte(*buff++);
}


