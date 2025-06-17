#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_DEV_SERIAL_DIR			= ./dev/serial

KERN_CSRC				+= $(KERN_DEV_SERIAL_DIR)/pl011_uart.c
