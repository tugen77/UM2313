#include "common.h"

/************************************************************************
 * function   : uart_set_baud_rate
 * Description: uart set baud rate
 * input : 
 *         UINT32 clk_hz: cpu frequency
 *         UINT32 baud_rate: Series rate
 * return: none
 ************************************************************************/
void uart0_set_baud_rate(UINT32 clk_hz, UINT32 baud_rate);

/************************************************************************
 * function   : uart_init
 * Description: uart initial for baud_rate
 * input : 
 *         UINT32 baud_rate: Series rate
 * return: none
 ************************************************************************/
void uart0_init(UINT32 baud_rate);

/************************************************************************
 * function   : outbyte
 * Description: uart out byte
 * input : 
 *         char c: out byte
 * return: none
 ************************************************************************/
void uart0_send_byte(UINT8 c);

/************************************************************************
 * function   : uart_send_bytes
 * Description: uart send bytes
 * input : 
 *         UINT8* buff: out buffer
 *         UINT32 length: buffer length
 * return: none
 ************************************************************************/
void uart0_send_bytes(UINT8 *buff, UINT32 length);

