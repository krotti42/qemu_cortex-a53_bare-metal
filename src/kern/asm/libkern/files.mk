#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_ASM_LIBKERN_DIR			= ./asm/libkern

KERN_ASRC				+= $(KERN_ASM_LIBKERN_DIR)/longjmp.S
KERN_ASRC				+= $(KERN_ASM_LIBKERN_DIR)/setjmp.S

