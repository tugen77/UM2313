//
// gcc startup for LPC810
// Kamal Mostafa <kamal@whence.com>
//
// License: mixed
// - simple crt0 and statically allocated stack (Kamal Mostafa; Public Domain)
// - Note: empty boilerplate ISR routines from cr_startup_lpc8xx.c
//


#if defined (__USE_CMSIS)
#include "um321x.h"
#endif


//*****************************************************************************
//
// Allocated stack space
//
//*****************************************************************************
#define STACKSIZE 64

static unsigned int StackMem[STACKSIZE];
#define _pStackTop ((void *)((unsigned int)StackMem + sizeof(StackMem)))

//*****************************************************************************

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************

WEAK void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
//*****************************************************************************
void GPIO_PA_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO_PB_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO_PC_IRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO_PD_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void GTIMER0_IRQHandler(void) ALIAS(IntDefaultHandler);
void GTIMER1_IRQHandler(void) ALIAS(IntDefaultHandler);
void GTIMER2_IRQHandler(void) ALIAS(IntDefaultHandler);
void GTIMER3_IRQHandler(void) ALIAS(IntDefaultHandler);
void LPTIMER_IRQHandler(void) ALIAS(IntDefaultHandler);
void WDT_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC_IRQHandler(void) ALIAS(IntDefaultHandler);
void LVD_IRQHandler(void) ALIAS(IntDefaultHandler);
void FLASH_IRQHandler(void) ALIAS(IntDefaultHandler);

//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
	// Core Level - CM0plus
    _pStackTop, //&_vStackTop,		// The initial stack pointer
    ResetISR,				// The reset handler
    NMI_Handler,			// The NMI handler
    HardFault_Handler,			// The hard fault handler
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    SVC_Handler,			// SVCall handler
    0,					// Reserved
    0,					// Reserved
    PendSV_Handler,			// The PendSV handler
    SysTick_Handler,			// The SysTick handler

	// Chip Level - LPC8xx
    GPIO_PA_IRQHandler,                         // GPIO_PA_IRQHandler
    GPIO_PB_IRQHandler,                         // GPIO_PB_IRQHandler
    GPIO_PC_IRQHandler,                                       // GPIO_PC_IRQHandler
    GPIO_PD_IRQHandler,                        // GPIO_PD_IRQHandler
    DMA_IRQHandler,                        // DMA_IRQHandler
    0,                        // Reserved
    UART0_IRQHandler,                                       // UART0_IRQHandler
    LPUART_IRQHandler,                                       // LPUART_IRQHandler
    UART1_IRQHandler,                          // UART1_IRQHandler
    I2C_IRQHandler,                          // I2C_IRQHandler
    SPI0_IRQHandler,                          // SPI0_IRQHandler
    SPI1_IRQHandler,                          // SPI1_IRQHandler
    0,                          // PIO1 (0:11)
    0,                          // Brown Out Detect
    GTIMER0_IRQHandler,                                       // GTIMER0_IRQHandler
    GTIMER1_IRQHandler,                          // GTIMER1_IRQHandler
    GTIMER2_IRQHandler,                                       // GTIMER2_IRQHandler
    GTIMER3_IRQHandler,                                       // GTIMER3_IRQHandler
    LPTIMER_IRQHandler,                                       // LPTIMER_IRQHandler
    0,                                       // Reserved
    0,                                       // Reserved
    0,                                       // Reserved
    WDT_IRQHandler,                                       // WDT_IRQHandler
    RTC_IRQHandler,                                       // RTC_IRQHandler
    ADC_IRQHandler,                      // ADC_IRQHandler
    0,                      // PIO INT1
    0,                      // PIO INT2
    0,                      // PIO INT3
    LVD_IRQHandler,                      // LVD_IRQHandler
    0,                      // PIO INT5
    FLASH_IRQHandler,                      // FLASH_IRQHandler
    0,                      // PIO INT7

}; /* End of g_pfnVectors */


//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple C runtime environment.
//*****************************************************************************

extern unsigned int _etext;
extern unsigned int _data;
extern unsigned int _edata;
extern unsigned int _bss;
extern unsigned int _ebss;

// Simple gcc-compatible C runtime init
static inline void
crt0(void)
{
    unsigned int *src, *dest, *dend;
    // copy the data section
    src  = (unsigned int *)(&_etext);
    dest = (unsigned int *)(&_data);
    dend = (unsigned int *)(&_edata);
    while (dest < dend)
	*(dest++) = *(src++);
    // blank the bss section
    dest = (unsigned int *)(&_bss);
    dend = (unsigned int *)(&_ebss);
    while (dest < dend)
	*(dest++) = 0;
}

__attribute__ ((section(".after_vectors")))
void
ResetISR(void)
{
#ifdef __USE_CMSIS
    SystemInit();
#endif
    crt0();
    main();
    while (1) ;	// hang if main returns
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void SVC_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void)
{
    while(1)
    {
    }
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void)
{
    while(1)
    {
    }
}

