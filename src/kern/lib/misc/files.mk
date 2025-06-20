#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBMISC_DIR			= ./lib/misc

KERN_CSRC				+= $(KERN_LIBMISC_DIR)/buffer.c

