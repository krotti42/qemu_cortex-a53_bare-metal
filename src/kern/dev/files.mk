#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_DEV_DIR				= ./dev

KERN_CSRC				+= $(KERN_DEV_DIR)/dev_init.c

include $(KERN_DEV_DIR)/intc/files.mk
include $(KERN_DEV_DIR)/serial/files.mk
