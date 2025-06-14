##
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_LIBK_STDLIB_DIR			= ./lib/k/stdlib

KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/abort.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/abs.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/atoi.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/atol.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/atoll.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/bsearch.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/calloc.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/div.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/free.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/labs.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/ldiv.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/llabs.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/lldiv.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/malloc.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/qsort.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/rand.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/realloc.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/srand.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/strto_helper.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/strtol.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/strtoll.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/strtoul.c
KERN_CSRC				+= $(KERN_LIBK_STDLIB_DIR)/strtoull.c
