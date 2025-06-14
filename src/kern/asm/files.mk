#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_ASM_DIR			= ./asm

KERN_ASRC			+= $(KERN_ASM_DIR)/locore.S
KERN_ASRC			+= $(KERN_ASM_DIR)/mmu.S
KERN_ASRC			+= $(KERN_ASM_DIR)/start.S
KERN_ASRC			+= $(KERN_ASM_DIR)/cache.S
KERN_ASRC			+= $(KERN_ASM_DIR)/crt0.S
KERN_ASRC			+= $(KERN_ASM_DIR)/vector.S
KERN_ASRC			+= $(KERN_ASM_DIR)/user.S
KERN_ASRC			+= $(KERN_ASM_DIR)/intr.S

include $(KERN_ASM_DIR)/libk/files.mk
