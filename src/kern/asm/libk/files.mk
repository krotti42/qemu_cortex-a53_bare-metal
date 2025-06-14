#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_ASM_LIBK_DIR			= ./asm/libk

KERN_ASRC				+= $(KERN_ASM_LIBK_DIR)/longjmp.S
KERN_ASRC				+= $(KERN_ASM_LIBK_DIR)/setjmp.S

