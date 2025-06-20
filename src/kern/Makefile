#
# QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
#

TARGET_KERN		= kern

# Cross compile
ifeq ($(CROSS_COMPILE),)
CROSS_COMPILE		= aarch64-none-elf-
endif

# Generic shell commands
RM			= rm -rf
CP			= cp -Rf

# Toolchain
AS			= $(CROSS_COMPILE)gcc
CC			= $(CROSS_COMPILE)gcc
LD			= $(CROSS_COMPILE)gcc

ASFLAGS			+= -Wa,-march=armv8-a
ASFLAGS			+= -Wa,-mcpu=cortex-a53
ASFLAGS			+= -Wa,-mlittle-endian

# C compiler flags
CCFLAGS			+= -g
CCFLAGS			+= -Wall
CCFLAGS			+= -Wextra
CCFLAGS			+= -pedantic
CCFLAGS			+= -std=c99
CCFLAGS			+= -nostdlib
CCFLAGS			+= -nostartfiles
CCFLAGS			+= -nodefaultlibs
CCFLAGS			+= -ffreestanding
CCFLAGS			+= -ffunction-sections
CCFLAGS			+= -fdata-sections
CCFLAGS			+= -fno-delete-null-pointer-checks
CCFLAGS			+= -march=armv8-a
CCFLAGS			+= -mcpu=cortex-a53+nofp+nosimd
CCFLAGS			+= -mtune=cortex-a53
CCFLAGS			+= -mfix-cortex-a53-835769
CCFLAGS			+= -mfix-cortex-a53-843419
CCFLAGS			+= -mcmodel=small
CCFLAGS			+= -mgeneral-regs-only
CCFLAGS			+= -I ./include

# GNU ld flags
LDFLAGS			+= -Wl,-n
LDFLAGS			+= -Wl,--build-id=none
LDFLAGS			+= -Wl,--gc-sections
LDFLAGS			+= -Wl,-nostdlib
LDFLAGS			+= -T ./ld/kern.ld
LDFLAGS			+= -Wl,-Map $(TARGET_KERN).map
LDFLAGS			+= -Wl,--no-warn-rwx-segments
LDFLAGS			+= -Wl,--fix-cortex-a53-835769
LDFLAGS			+= -Wl,--fix-cortex-a53-843419=full

include ./files.mk

KERN_AOBJ		+= $(KERN_ASRC:.S=.o)
KERN_COBJ		+= $(KERN_CSRC:.c=.o)

all: kern

# Link object files
kern: $(KERN_AOBJ) $(KERN_COBJ)
	@echo "   [CCLD] $(TARGET_KERN).elf"
	@$(LD) $(CCFLAGS) $(LDFLAGS) -o $(TARGET_KERN).elf $(KERN_AOBJ) $(KERN_COBJ)

# Assemble assembly sources
$(KERN_AOBJ): %.o: %.S
	@echo "   [CCAS] $@"
	@$(AS) -c $(CCFLAGS) $(ASFLAGS) -o $@ $<

# Compile C sources
$(KERN_COBJ): %.o: %.c
	@echo "   [CC]   $@"
	@$(CC) -c $(CCFLAGS) -o $@ $<

.PHONY: clean
clean:
	@echo "   [CLEAN]"
	@$(RM) $(KERN_AOBJ)
	@$(RM) $(KERN_COBJ)
	@$(RM) $(TARGET_KERN).elf
	@$(RM) $(TARGET_KERN).map
