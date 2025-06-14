#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

KERN_DIR			= ./asm

KERN_ASRC			+= $(KERN_DIR)/locore.S
KERN_ASRC			+= $(KERN_DIR)/mmu.S
KERN_ASRC			+= $(KERN_DIR)/start.S
KERN_ASRC			+= $(KERN_DIR)/cache.S
KERN_ASRC			+= $(KERN_DIR)/crt0.S
KERN_ASRC			+= $(KERN_DIR)/vector.S
KERN_ASRC			+= $(KERN_DIR)/user.S
KERN_ASRC			+= $(KERN_DIR)/intr.S
