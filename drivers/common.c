/***********************************************************************
 * Copyright (c)  2017 - 2020, Unicmicro Co.,Ltd .
 * All rights reserved.
 * Filename    : common.c
 * Description : conmmon source file
 * Author(s)   : Dan
 * version     : V1.0
 * Modify date : 2019-02-21
 ***********************************************************************/
#include  "common.h"
UINT32 g_data_buf[512];
static UINT8  fac_us = 0;							//us延时倍乘数			   
static UINT16 fac_ms = 0;							//ms延时倍乘数
#ifdef DEBUG
/************************************************************************
 * function   : printf_buff_byte
 * Description: printf data block by byte
 * input :
 *         UINT8* buff: buff
 *         UINT32 length: byte length
 * return: none
 ************************************************************************/
void printf_buff_byte(UINT8* buff, UINT32 length)
{
	UINT32 i;
	for(i=0; i<length; i++)
	{
		printf("%.2x ",buff[i]);	
	}
	printf("\n");
}

/************************************************************************
 * function   : printf_buff_word
 * Description: printf data block by word
 * input :
 *         UINT8* buff: buff
 *         UINT32 length: word length
 * return: none
 ************************************************************************/
void printf_buff_word(UINT32* buff, UINT32 length)
{
	UINT32 i;

	for(i=0; i<length; i++)
	{
		printf("%.8x ",buff[i]);	
	}
	printf("\n");
}

#endif

/*******************************************************************
* Function		: delay_init
* Description	: 初始化延迟函数 SYSTICK的时钟固定为系统时钟
* Input			: SYSCLK:系统时钟频率
* 				fosc=1/T   T=1/fosc ,fosc为系统的频率。
* 				1.当系统时钟频率为高速时钟RCH、XTH时:
*   			  如果SYSCLK时钟频率为：32MHz，每次计数的时间为：T=1/32MHz,
*   			  1秒钟需要计数次数为：1/（每次的时间)=1/(1/32MHz)=32 000 000次。
*   			  所以定时1ms需要计数32000次，1us需要32次。
* 				2.当系统时钟频率为低速时钟RCL、XTL时，us计数无效。
*   			  如果SYSCLK时钟频率为：32KHz，每次计数的时间为：T=1/32KHz,
*   			  1秒钟需要计数次数为：1/（每次的时间)=1/(1/32KHz)=32 000次。
*   			  所以定时1ms需要计数32次，1us计数无效。 
* Output		: none
* Return		: none
********************************************************************/						    
void delay_init(UINT32 system_clk_hz)	
{
 	UINT8 system_clk_mhz;
	UINT8 system_clk_khz;
	
	system_clk_mhz = 0;
	system_clk_khz = 0;
	
	if(system_clk_hz > 1000000) //MHz
	{
		system_clk_mhz = system_clk_hz/1000000;   	// 单位转换
		REG_SYSTICK_CSR |= (1<<2);					// SysTick使用系统时钟	 
		fac_us = system_clk_mhz;					// fac_us代表1us所用时钟个数,SysTick时钟来源于系统时钟
		fac_ms = (UINT16)fac_us*1000;				// 代表每个ms需要的SysTick时钟数   		
	}
	else
	{
		system_clk_khz = system_clk_hz/1000;   		// 单位转换
		REG_SYSTICK_CSR |= (1<<2);					// SysTick使用系统时钟	 
		fac_ms = system_clk_khz;					// 代表每个ms需要的SysTick时钟数 
	}

}	

/*******************************************************************
* Function		: delay_us
* Description	: delay n us
* Input			: UINT32 nus注意:nus的值,不要大于838860us(系统时钟SYSCLK最大为32MHz，每计数一次时间为1/32 us,嘀嗒计时最大值为(2^24)*(1/32)us=524288us,最大值即2^24/fac_us)
* Output		: none
* Return		: none
********************************************************************/
void delay_us(UINT32 nus)
{		
	UINT32 temp;
	REG_SYSTICK_RVR = nus*fac_us-1; 				// 时间加载	  		 
	REG_SYSTICK_CVR = 0x00;        				    // 清空计数器
	REG_SYSTICK_CSR = 0x01 ;      					// 开始倒数 
	do
	{
		temp = REG_SYSTICK_CSR;
	}while((temp&0x01)&&!(temp&(1<<16)));		// 等待时间到达  
	REG_SYSTICK_CSR = 0x00;      	 				// 关闭计数器
	REG_SYSTICK_CVR = 0X00;       					// 清空计数器 
}

/*******************************************************************
* Function		: delay_xms
* Description	: delay x ms
* Input			: SysTick->LOAD为24位寄存器,所以,最大延时为:nms<=524.288ms(系统时钟SYSCLK最大为32MHz，每计数一次时间为1/32 us,嘀嗒计时最大值为(2^24)*(1/32)us=524288us =524.288ms)
* Output		: none
* Return		: none
********************************************************************/
void delay_xms(UINT16 nms)
{	 		  	  
	UINT32 temp;	
	REG_SYSTICK_RVR = (UINT32)nms*fac_ms-1;		// 时间加载(SysTick->LOAD为24bit，最大计数为2的24次方)
	REG_SYSTICK_CVR = 0x00;           			// 清空计数器
	REG_SYSTICK_CSR = 0x01 ;          			// 开始倒数  
	do
	{
		temp = REG_SYSTICK_CSR;
	}while((temp&0x01)&&!(temp&(1<<16)));		// 等待时间到达  
	
	REG_SYSTICK_CSR = 0x00;       				// 关闭计数器
	REG_SYSTICK_CVR = 0x00;     		  		// 清空计数器	  	    
}


/*******************************************************************
* Function		: delay_ms
* Description	: 延时nms 
* Input			: nms:0~65535
* Output		: none
* Return		: none
********************************************************************/
void delay_ms(UINT16 nms)
{	 	 
	UINT16 repeat,remain;

	repeat = nms/524;					// SysTick->LOAD为24位寄存器,所以,最大延时为:nms<=524.288ms
										//(系统时钟SYSCLK最大为32MHz，每计数一次时间为1/32 us,嘀嗒计时最大值为(2^24)*(1/32)us=524288us =524.288ms)
										//如果定时时间超过524ms，分多个524ms进行计数定时
	remain = nms%524;
	while(repeat)
	{
		delay_xms(524);
		repeat--;
	}
	
	if(remain)
	{
		delay_xms(remain);
	}
}

void delay(UINT32 count)
{
    while(count--);
}

//一个字内大小端转换
void reverse_DWORD(UINT32 *var)
{
    UINT8 *P = (UINT8 *)var;
    UINT8 tmp;

    tmp = P[0];
    P[0] = P[3];
    P[3] = tmp;
    tmp = P[1];
    P[1] = P[2];
    P[2] = tmp;
}

//整批数据前后大小端转换
void reverse_memory(UINT8 *buff, UINT32 length)
{
    UINT8 temp;
    UINT8 *buff_start = buff;
    UINT8 *buff_end = buff + length - 1;

    while(buff_end > buff_start)
    {
        temp = *buff_start;
        *buff_start++ = *buff_end;
        *buff_end-- = temp;
    }
}
