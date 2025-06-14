#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBK_STDIO_DIR			= ./lib/k/stdio

KERN_CSRC				+= $(KERN_LIBK_STDIO_DIR)/sprintf.c
KERN_CSRC				+= $(KERN_LIBK_STDIO_DIR)/vsprintf.c
