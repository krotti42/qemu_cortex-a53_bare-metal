#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBK_SETJMP_DIR			= ./lib/k/setjmp

KERN_CSRC				+= $(KERN_LIBK_SETJMP_DIR)/longjmp.c
KERN_CSRC				+= $(KERN_LIBK_SETJMP_DIR)/setjmp.c
