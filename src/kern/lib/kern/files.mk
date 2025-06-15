#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBKERN_DIR			= ./lib/kern

CCFLAGS					+= -I $(KERN_LIBKERN_DIR)/include

KERN_CSRC				+= $(KERN_LIBKERN_DIR)/libkern_errno.c
KERN_CSRC				+= $(KERN_LIBKERN_DIR)/libkern_fini.c
KERN_CSRC				+= $(KERN_LIBKERN_DIR)/libkern_init.c
KERN_CSRC				+= $(KERN_LIBKERN_DIR)/libkern_malloc.c
KERN_CSRC				+= $(KERN_LIBKERN_DIR)/libkern_ofmt.c
KERN_CSRC				+= $(KERN_LIBKERN_DIR)/libkern_ofmt_int.c
KERN_CSRC				+= $(KERN_LIBKERN_DIR)/libkern_rand.c

include $(KERN_LIBKERN_DIR)/crt/files.mk
include $(KERN_LIBKERN_DIR)/ctype/files.mk
include $(KERN_LIBKERN_DIR)/libgen/files.mk
include $(KERN_LIBKERN_DIR)/setjmp/files.mk
include $(KERN_LIBKERN_DIR)/stdio/files.mk
include $(KERN_LIBKERN_DIR)/stdlib/files.mk
include $(KERN_LIBKERN_DIR)/string/files.mk
