#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_DIR				= .

include $(KERN_DIR)/asm/files.mk
include $(KERN_DIR)/lib/files.mk

KERN_CSRC				+= $(KERN_DIR)/kern_main.c
