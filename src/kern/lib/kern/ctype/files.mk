#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBKERN_CTYPE_DIR		= ./lib/kern/ctype

KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/isalnum.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/isalpha.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/isblank.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/iscntrl.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/isdigit.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/isgraph.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/islower.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/isprint.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/ispunct.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/isspace.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/isupper.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/isxdigit.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/tolower.c
KERN_CSRC			+= $(KERN_LIBKERN_CTYPE_DIR)/toupper.c

