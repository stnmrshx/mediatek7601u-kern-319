ifeq ($(KERNELRELEASE),)
KDIR ?= /lib/modules/`uname -r`/build
default:
	$(MAKE) -C $(KDIR) M=$$PWD
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
else
EXTRA_CFLAGS += -Werror -Wenum-compare
ccflags-y += -D__CHECK_ENDIAN__ 

obj-m := mt7601u.o

mt7601u-y := \
	src/usb.o src/main.o src/mcu.o src/trace.o src/dma.o src/core.o src/eeprom.o src/phy.o \
	src/mac.o src/util.o src/debugfs.o src/tx.o src/init.o

CFLAGS_trace.o := -I$(src)

endif
