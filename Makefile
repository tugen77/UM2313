#
# gcc Makefile for UM3213
# Eric Qiu <jmqiu@icwiser.com>
#
# License: Public Domain
#

CROSS = arm-none-eabi-
CPU = -mthumb -mcpu=cortex-m0plus -MD
FPU = # -mfloat-abi=soft

FILENAME = um3213
LINKERSCRIPT = um321x.ld

CFLAGS = -Wall -g -std=c99 -Os

#CFLAGS+= -Os --specs=nano.specs -ffunction-sections -fdata-sections -fno-builtin
CFLAGS += -mlittle-endian -mcpu=cortex-m0 -mthumb 
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections

CC = ${CROSS}gcc
LD = ${CROSS}ld
OBJCOPY = ${CROSS}objcopy
SIZE = ${CROSS}size

# use these on the $(LD) line, as needed:
LIBM = "${shell ${CC} ${CFLAGS} --print-file-name=libm.a}"
LIBC = "${shell ${CC} ${CFLAGS} --print-file-name=libc.a}"
LIBGCC = "${shell ${CC} ${CFLAGS} --print-libgcc-file-name}"

CFLAGS += $(CPU) $(FPU)
LDFLAGS += --gc-sections


INC += -ICMSIS/Include -Idrivers -Iproject
CFLAGS += $(INC) -D__USE_CMSIS # -DCLOCK_SETUP=1

BLINKY_OBJS = drivers/startup_um321x.o \
	      drivers/system_um321x.o \
	      drivers/common.o \
	      drivers/um321x_gpio.o  \
	      drivers/um321x_uart.o #\
	      drivers/um321x_crc16.o \
	      drivers/um321x_hrng.o \
	      drivers/um321x_gtimer.o \
	      drivers/um321x_rtc.o \
	      drivers/um321x_wdt.o 

BLINKY_OBJS += project/main.o \
	       project/uart.o

all: $(FILENAME).bin

$(FILENAME).axf: $(BLINKY_OBJS)
	@$(LD) -o $@ $(LDFLAGS) -T drivers/$(LINKERSCRIPT) $(BLINKY_OBJS) $(LIBGCC)
	-@echo ""
	@$(SIZE) $(FILENAME).axf

clean:
	@rm -f drivers/*.o drivers/*.d project/*.o project/*.d
	@rm -f $(FILENAME).axf $(FILENAME).hex $(FILENAME).bin

%.bin:%.axf
	-@echo ""
	-@echo "Generating $(FILENAME).hex"
	@$(OBJCOPY) --strip-unneeded -O ihex $(FILENAME).axf $(FILENAME).hex
	-@echo "Generating $(FILENAME).bin"
	@$(OBJCOPY) --strip-unneeded -O binary $(FILENAME).axf $(FILENAME).bin


