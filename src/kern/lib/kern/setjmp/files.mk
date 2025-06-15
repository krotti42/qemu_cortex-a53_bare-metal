#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBKERN_SETJMP_DIR			= ./lib/kern/setjmp

KERN_CSRC				+= $(KERN_LIBKERN_SETJMP_DIR)/longjmp.c
KERN_CSRC				+= $(KERN_LIBKERN_SETJMP_DIR)/setjmp.c
