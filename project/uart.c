#include "common.h"

unsigned char uartData[32], uartIndex;

void uartReceving(unsigned char data);

/*******************************************************************
* Function		: GTIMER0_IRQHandler
* Description	: GTIMER0_IRQHandler
* Input			: none
* Output		: none
* Return		: none
********************************************************************/
void GTIMER0_IRQHandler(void)
{
 /*溢出中断测试*/
	REG_GTIM0_CR &= ~(1<<0);										/* 关闭定时器 */
	
	REG_GTIM0_CIF = 0xFF;							             /* 清除中断 */

	uart0Putchar(0x99);
}

/*******************************************************************
* Function		: gtimer0_interrupt_test
* Description	: gtimer0_interrupt_test
* Input			: UINT32 arr
*				  UINT16 div
* Return		: none
********************************************************************/
void gtimer0_interrupt_test(UINT32 arr,UINT16 div)
{
	//gtimer0定时器中断 arr=32000000,div=0;不分频，定时计数1S，T=arr/(hclk/2^div); 
	
	/* gtimer0定时器中断方式 */
	REG_SCU_PERICLKEN |= (1<<9);									/* 开启GTimer时钟使能 */
	REG_SCU_PERIRESET |= (1<<9);									/* GTimer正常工作 */
	REG_GTIM0_CR &= ~(1<<0);										/* 关闭定时器 */
	REG_GTIM0_CR |= (1<<4);											/* 确定计数方向 */
	REG_GTIM0_CR |= (1<<5);											/* 边沿对其模式 */
	
	REG_GTIM0_ARR = arr;										    /* 自动重载值ARR */
	REG_GTIM_PSC |= (div<<0*3);										/* 预分频因子 */
	
	REG_GTIM0_CIF = 0xFF;											/* 清除定时器更新中断标志 */
	REG_GTIM0_CR &= ~(1<<3);										/* 开启定时器更新中断 */
	REG_GTIM0_CR |= (2<<1);											/* 选择模式：循环模式 */
	REG_GTIM0_CR |= (1<<0);											/* 使能定时器 */
	REG_GTIM_ICMODE = 0x05;
	NVIC_ClearPendingIRQ(GTIMER0_IRQn);
	NVIC_EnableIRQ(GTIMER0_IRQn);
	
}

void uart0Init(unsigned long baudrate)
{
	uartIndex = 0;
	
//	gtimer0_interrupt_test(32000000,0);
	uart0_init(baudrate);
}

void uart0Putchar(unsigned char ch)
{
	uart0_send_byte(ch);
}

void UART0_IRQHandler(void)
{
	unsigned char regStatus, ch;

	regStatus = REG_UART0_ISR;
			
	if(regStatus & 0x20) {      // Rx int 
		while((REG_UART0_ISR & 0x20)== 0x20){
			ch = REG_UART0_RDR;
			gtimer0_interrupt_test(320000,0);
			
			uartReceving(ch);
		}
		REG_UART0_ISR &= ~(1<<5);	//清除FIFO_NE非空标志位
	} else if(regStatus & 0x02) { // Tx int 发送中断
		REG_UART0_ISR &= ~(1<<1);	//清除发送完成标志位
	} else {
		REG_UART0_ISR = 0x00; //  清除中断状态
	}
}

void uartReceving(unsigned char data)
{
	;
}




