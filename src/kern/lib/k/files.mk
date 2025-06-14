#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBK_DIR				= ./lib/k

CCFLAGS					+= -I $(KERN_LIBK_DIR)/include

KERN_CSRC				+= $(KERN_LIBK_DIR)/libk_errno.c
KERN_CSRC				+= $(KERN_LIBK_DIR)/libk_fini.c
KERN_CSRC				+= $(KERN_LIBK_DIR)/libk_init.c
KERN_CSRC				+= $(KERN_LIBK_DIR)/libk_malloc.c
KERN_CSRC				+= $(KERN_LIBK_DIR)/libk_ofmt.c
KERN_CSRC				+= $(KERN_LIBK_DIR)/libk_ofmt_int.c
KERN_CSRC				+= $(KERN_LIBK_DIR)/libk_rand.c

include $(KERN_LIBK_DIR)/ctype/files.mk
include $(KERN_LIBK_DIR)/setjmp/files.mk
include $(KERN_LIBK_DIR)/stdio/files.mk
include $(KERN_LIBK_DIR)/stdlib/files.mk
include $(KERN_LIBK_DIR)/string/files.mk
