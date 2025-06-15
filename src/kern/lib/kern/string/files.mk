#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBK_STRING_DIR		= ./lib/kern/string

KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/memchr.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/memcmp.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/memcpy.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/memmove.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/memset.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strcat.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strchr.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strcmp.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strcpy.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strcspn.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strerror.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strlen.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strncat.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strncmp.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strncpy.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strpbrk.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strrchr.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strspn.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strstr.c
KERN_CSRC			+= $(KERN_LIBK_STRING_DIR)/strtok.c
