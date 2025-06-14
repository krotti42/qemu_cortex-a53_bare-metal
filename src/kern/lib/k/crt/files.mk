#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBK_CRT_DIR			= ./lib/k/crt

KERN_CSRC				+= $(KERN_LIBK_CRT_DIR)/crti.c
KERN_CSRC				+= $(KERN_LIBK_CRT_DIR)/crtn.c
