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
static UINT8  fac_us = 0;							//us��ʱ������			   
static UINT16 fac_ms = 0;							//ms��ʱ������
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
* Description	: ��ʼ���ӳٺ��� SYSTICK��ʱ�ӹ̶�Ϊϵͳʱ��
* Input			: SYSCLK:ϵͳʱ��Ƶ��
* 				fosc=1/T   T=1/fosc ,foscΪϵͳ��Ƶ�ʡ�
* 				1.��ϵͳʱ��Ƶ��Ϊ����ʱ��RCH��XTHʱ:
*   			  ���SYSCLKʱ��Ƶ��Ϊ��32MHz��ÿ�μ�����ʱ��Ϊ��T=1/32MHz,
*   			  1������Ҫ��������Ϊ��1/��ÿ�ε�ʱ��)=1/(1/32MHz)=32 000 000�Ρ�
*   			  ���Զ�ʱ1ms��Ҫ����32000�Σ�1us��Ҫ32�Ρ�
* 				2.��ϵͳʱ��Ƶ��Ϊ����ʱ��RCL��XTLʱ��us������Ч��
*   			  ���SYSCLKʱ��Ƶ��Ϊ��32KHz��ÿ�μ�����ʱ��Ϊ��T=1/32KHz,
*   			  1������Ҫ��������Ϊ��1/��ÿ�ε�ʱ��)=1/(1/32KHz)=32 000�Ρ�
*   			  ���Զ�ʱ1ms��Ҫ����32�Σ�1us������Ч�� 
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
		system_clk_mhz = system_clk_hz/1000000;   	// ��λת��
		REG_SYSTICK_CSR |= (1<<2);					// SysTickʹ��ϵͳʱ��	 
		fac_us = system_clk_mhz;					// fac_us����1us����ʱ�Ӹ���,SysTickʱ����Դ��ϵͳʱ��
		fac_ms = (UINT16)fac_us*1000;				// ����ÿ��ms��Ҫ��SysTickʱ����   		
	}
	else
	{
		system_clk_khz = system_clk_hz/1000;   		// ��λת��
		REG_SYSTICK_CSR |= (1<<2);					// SysTickʹ��ϵͳʱ��	 
		fac_ms = system_clk_khz;					// ����ÿ��ms��Ҫ��SysTickʱ���� 
	}

}	

/*******************************************************************
* Function		: delay_us
* Description	: delay n us
* Input			: UINT32 nusע��:nus��ֵ,��Ҫ����838860us(ϵͳʱ��SYSCLK���Ϊ32MHz��ÿ����һ��ʱ��Ϊ1/32 us,��઼�ʱ���ֵΪ(2^24)*(1/32)us=524288us,���ֵ��2^24/fac_us)
* Output		: none
* Return		: none
********************************************************************/
void delay_us(UINT32 nus)
{		
	UINT32 temp;
	REG_SYSTICK_RVR = nus*fac_us-1; 				// ʱ�����	  		 
	REG_SYSTICK_CVR = 0x00;        				    // ��ռ�����
	REG_SYSTICK_CSR = 0x01 ;      					// ��ʼ���� 
	do
	{
		temp = REG_SYSTICK_CSR;
	}while((temp&0x01)&&!(temp&(1<<16)));		// �ȴ�ʱ�䵽��  
	REG_SYSTICK_CSR = 0x00;      	 				// �رռ�����
	REG_SYSTICK_CVR = 0X00;       					// ��ռ����� 
}

/*******************************************************************
* Function		: delay_xms
* Description	: delay x ms
* Input			: SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:nms<=524.288ms(ϵͳʱ��SYSCLK���Ϊ32MHz��ÿ����һ��ʱ��Ϊ1/32 us,��઼�ʱ���ֵΪ(2^24)*(1/32)us=524288us =524.288ms)
* Output		: none
* Return		: none
********************************************************************/
void delay_xms(UINT16 nms)
{	 		  	  
	UINT32 temp;	
	REG_SYSTICK_RVR = (UINT32)nms*fac_ms-1;		// ʱ�����(SysTick->LOADΪ24bit��������Ϊ2��24�η�)
	REG_SYSTICK_CVR = 0x00;           			// ��ռ�����
	REG_SYSTICK_CSR = 0x01 ;          			// ��ʼ����  
	do
	{
		temp = REG_SYSTICK_CSR;
	}while((temp&0x01)&&!(temp&(1<<16)));		// �ȴ�ʱ�䵽��  
	
	REG_SYSTICK_CSR = 0x00;       				// �رռ�����
	REG_SYSTICK_CVR = 0x00;     		  		// ��ռ�����	  	    
}


/*******************************************************************
* Function		: delay_ms
* Description	: ��ʱnms 
* Input			: nms:0~65535
* Output		: none
* Return		: none
********************************************************************/
void delay_ms(UINT16 nms)
{	 	 
	UINT16 repeat,remain;

	repeat = nms/524;					// SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:nms<=524.288ms
										//(ϵͳʱ��SYSCLK���Ϊ32MHz��ÿ����һ��ʱ��Ϊ1/32 us,��઼�ʱ���ֵΪ(2^24)*(1/32)us=524288us =524.288ms)
										//�����ʱʱ�䳬��524ms���ֶ��524ms���м�����ʱ
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

//һ�����ڴ�С��ת��
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

//��������ǰ���С��ת��
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
