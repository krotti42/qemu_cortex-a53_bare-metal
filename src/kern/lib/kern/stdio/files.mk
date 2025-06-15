#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBKERN_STDIO_DIR			= ./lib/kern/stdio

KERN_CSRC				+= $(KERN_LIBKERN_STDIO_DIR)/sprintf.c
KERN_CSRC				+= $(KERN_LIBKERN_STDIO_DIR)/vsprintf.c
