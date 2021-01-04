/*
 * generic gcc linker script for UM3213
 * Eric Qiu <jmqiu@icwiser.com>.
 *
 * License: Public Domain
 */

MEMORY
{
    /* NXP UM3213 */
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00008000 /* 32 Kbytes */
    RAM (rwx) :  ORIGIN = 0x20000000, LENGTH = 0x00002000 /* 8 Kbyte */
}

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        KEEP(*(.after_vectors))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    .data : AT (_etext)
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > RAM

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM
}
