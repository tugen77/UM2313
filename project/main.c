/**************************************************************************/
/*!
    @file     main.c

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2020, Eric Qiu (jmqiu@icwiser.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#include "common.h"
#include "uart.h"


int main(void)
{	
	gpio_init(GPIOC, PIN1);						//PD6 时钟初始化，模块正常工作
	gpio_dir(GPIOC, PIN1, GPIO_DIR_OUT);			//PD6 配置为输出
	gpio_config_od(GPIOC, PIN1, DISABLE);			//PD6 开漏输出禁止，默认推挽输出
	
	gpio_init(GPIOC, PIN6);						//PD6 时钟初始化，模块正常工作
	gpio_dir(GPIOC, PIN6, GPIO_DIR_OUT);			//PD6 配置为输出
	gpio_config_od(GPIOC, PIN6, DISABLE);			//PD6 开漏输出禁止，默认推挽输出
	
	gpio_setio(GPIOC, PIN1, HIGH);
	gpio_setio(GPIOC, PIN6, HIGH);
		
	uart0Init(9600);
	
	while(1) {
		gpio_setio(GPIOC, PIN1, LOW);
		gpio_setio(GPIOC, PIN6, LOW);
		
//		uart0Putchar(qq);
		
		delay_xms(500);
		
		gpio_setio(GPIOC, PIN1, HIGH);
		gpio_setio(GPIOC, PIN6, HIGH);
		
//		uart0Putchar(qq);
		
		delay_xms(500);
	}
	
  return 0;
}






