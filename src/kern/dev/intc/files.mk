#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_DEV_INTC_DIR			= ./dev/intc

KERN_CSRC				+= $(KERN_DEV_INTC_DIR)/arm_gicv2.c
