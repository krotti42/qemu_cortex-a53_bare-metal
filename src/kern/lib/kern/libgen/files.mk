#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBKERN_LIBGEN_DIR			= ./lib/kern/libgen

KERN_CSRC				+= $(KERN_LIBKERN_LIBGEN_DIR)/basename.c
KERN_CSRC				+= $(KERN_LIBKERN_LIBGEN_DIR)/dirname.c
