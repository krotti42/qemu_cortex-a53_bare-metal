#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBKERN_CRT_DIR			= ./lib/kern/crt

KERN_CSRC				+= $(KERN_LIBKERN_CRT_DIR)/crti.c
KERN_CSRC				+= $(KERN_LIBKERN_CRT_DIR)/crtn.c
