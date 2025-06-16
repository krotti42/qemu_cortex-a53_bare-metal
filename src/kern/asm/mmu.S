/**
 *
 * QEMU Cortex-A53 (ARMv8-A) minimal bare-metal example
 *
 * Copyright (c) 2025 Johannes Krottmayer <github.krotti42@proton.me>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/**
 * Kernel basic translation lookup tables
 */

#define _ASM_ASSEMBLY_

#include <asm.h>

#define TBL_SIZE         4096    /* TLB size in bytes (512 entries) for 4K granule */

.section .tlb

SYMBOL(tlb_kern_lvl0)           /* 512*512GiB regions */
.space TBL_SIZE
SYMBOL(tlb_kern_lvl1)           /* First 2GiB region only for kernel */
.space TBL_SIZE
SYMBOL(tlb_kern_lvl2)           /* 146*2MiB regions for kernel at index 1 level 1 table */
.space TBL_SIZE
SYMBOL(tlb_user_lvl0)           /* 512GB regions */
.space TBL_SIZE
SYMBOL(tlb_user_lvl1)           /* 512*1GB regions for userspace */
.space TBL_SIZE

/**
 * Zero kernel level 0, level 1 and level 2 translation table
 */
LOFUNCTION_S(lo_tlb_kern_zero)
    /* Set all entries to invalid in level 0 table */
    adr x0, tlb_kern_lvl0
    mov x1, #256
1:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp x1, #0
    bne 1b
    /* Set all entries to invalid in level 1 table */
    adr x0, tlb_kern_lvl1
    mov x1, #256
2:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp x1, #0
    bne 2b
    /* Set all entries to invalid in level 2 table */
    adr x0, tlb_kern_lvl2
    mov x1, #256
3:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp x1, #0
    bne 3b
    ret
LOFUNCTION_E(lo_tlb_kern_zero)

/**
 * Zero userspace level 0 and level 1 translation table
 */
LOFUNCTION_S(lo_tlb_user_zero)
    /*Set all entries to invalid in level 0 table */
    adr x0, tlb_user_lvl0
    mov x1, #256
1:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp x1, #0
    bne 1b
    /* Set all entries to invalid in level 1 table */
    adr x0, tlb_user_lvl1
    mov x1, #256
2:
    str xzr, [x0], #8
    subs x1, x1, #1
    cmp x1, #0
    bne 2b
    ret
LOFUNCTION_E(lo_tlb_user_zero)

/**
 * Setup basic memory types
 *
 * Attr0 (byte0): Device nGnRnE memory
 * Attr1 (byte1): Normal Memory
 *
 * NOTE: For basic setup we don't need more.
 */
LOFUNCTION_S(lo_tlb_mem_type)
    mov x0, #0xFF00
    msr MAIR_EL1, x0
    isb
    ret
LOFUNCTION_E(lo_tlb_mem_type)

/**
 * Setup basic kernel translation table
 */
LOFUNCTION_S(lo_tlb_kern_setup)
    ldr x0, =tlb_kern_lvl0
    ldr x1, =tlb_kern_lvl1
    /**
     * Create table entry for level 1 table
     */
    orr x2, x1, #3          /* Entry is a valid table */
#if 0
    mov x3, #0x4            /* EL0 not permitted table */
    lsl x3, x3, #59
    orr x2, x2, x3
#endif
    str x2, [x0]            /* Store at index 0 in level 0 table */
    /**
     * Map first 1GiB block to 0xFFFF0000_00000000 (device memory)
     */
    mov x4, xzr             /* Address 0x000000000 (first 1GB block is device memory ) */
    lsr x5, x4, #30
    and x5, x5, #0x1FF
    lsl x4, x5, #30
    /**
     * Upper attributes:
     * UXN, PXN
     *
     * Lower attributes:
     * AttrIndx: 0 (Device memory)
     * SH: Outer shareable (0b10)
     * AF: Not accessed (0b1)
     */
    ldr x6, =0x60000000000601
    orr x4, x4, x6
    str x4, [x1, x5, lsl #3]

    /**
     * Create 2MiB table (level 2) at index 1 level 1 table
     *
     * 0xFFFF0000_40000000 size 1GiB
     */
    ldr x2, =tlb_kern_lvl2
    orr x3, x2, #3          /* Entry is a valid table */
    str x3, [x1, #8]        /* Store at index 1 in level 1 table */

    /**
     * First 8x2MiB are reserved for the DTB
     *
     * 0xFFFF0000_40000000 size 16MiB at PA 0x40000000
     *
     * Upper attributes:
     * UXN, PXN
     *
     * Lower attributes:
     * AttrIndx: 1 (Normal memory)
     * SH: Inner shareable (0b11)
     * AF: Not accessed (0b1)
     */
    mov x7, #8
    mov x4, #0x40000000
    ldr x6, =0x60000000000705
1:
    orr x5, x4, x6
    str x5, [x2], #8
    add x4, x4, #0x200000
    subs x7, x7, #1
    cmp x7, #0
    bne 1b

    /**
     * Kernel low core (2MiB)
     *
     * 0xFFFF0000_41000000 size 2MiB at PA 0x41000000
     *
     * Upper attributes:
     * none
     *
     * Lower attributes:
     * AttrIndx: 1 (Normal memory)
     * SH: Inner shareable (0b11)
     * AF: Not accessed (0b1)
     */
    ldr x6, =0x00000000000705
    orr x5, x4, x6
    add x4, x4, #0x200000
    str x5, [x2], #8

    /**
     * Kernel 128*2MiB
     *
     * * 0xFFFF0000_41200000 size 2MiB at PA 0x41200000
     *
     * 128MiB currently (defined in linker), but reserve additional 128MiB
     * for further use.
     *
     * Upper attributes:
     * none
     *
     * Lower attributes:
     * AttrIndx: 1 (Normal memory)
     * SH: Inner shareable (0b11)
     * AF: Not accessed (0b1)
     */
    mov x7, #128
    ldr x6, =0x00000000000705
2:
    orr x5, x4, x6
    str x5, [x2], #8
    add x4, x4, #0x200000
    subs x7, x7, #1
    cmp x7, #0
    bne 2b

    msr TTBR1_EL1, x0       /* Store level 0 table */
    isb
    ret
LOFUNCTION_E(lo_tlb_kern_setup)

/**
 * Setup basic userspace translation table
 *
 * NOTE: We setup specific table for userspace later in C code.
 */
LOFUNCTION_S(lo_tlb_user_setup)
    ldr x0, =tlb_user_lvl0
    ldr x1, =tlb_user_lvl1
    /**
     * Create table entry for level 1 table
     */
    orr x2, x1, #3          /* Entry is a valid table */
#if 0
    mov x3, #0x10           /* NS table */
    lsl x3, x3, #59
    orr x2, x2, x3
#endif
    str x2, [x0]            /* Store at index 0 in level 0 table */
    /**
     * Map first 1GiB block to 0x000000000_00000000 (device memory) first
     */
    mov x4, xzr             /* Address 0x000000000 (first 1GB block is device memory ) */
    mov x5, #0
    ldr x6, =0x60000000000601
    orr x4, x4, x6
    str x4, [x1, x5, lsl #3]

    /**
     * Map second 1GiB block to 0x000000000_40000000 (normal memory) first
     *
     * NOTE: We need this first to allow low kernel setup to run. If we
     * don't this and then enable the MMU then an higher exception is
     * thrown and further low kernel setup will not run. We unmap it
     * later in kernel main.
     */
    mov x4, #0x40000000
    mov x5, #1
    ldr x6, =0x00000000000705
    orr x4, x4, x6
    str x4, [x1, x5, lsl #3]

    msr TTBR0_EL1, x0
    isb
    ret
LOFUNCTION_E(lo_tlb_user_setup)

/**
 * Setup translation table control register
 *
 * Current setup:
 *
 * Intermediate Physical Address size (IPS, bits [34:32]):
 * - 48 bits - 256TiB (Value: 0b101)
 *
 * Granule size for the TTBR1_EL1 (TG1, bits [31:30]):
 * - 4KiB (Value: 0b10)
 *
 * Shareability attribute for TTBR1_EL1 (SH1, bits [29:28]):
 * - Inner Shareable (Value: 0b11)
 *
 * Outer cacheability attribute for TTBR1_EL1 (ORGN1, bits [27:26]):
 * - Normal memory, Outer Write-Back Read-Allocate Write-Allocate Cacheable (Value: 0b01)
 *
 * Inner cacheability attribute for TTBR1_EL1 (IRGN1, bits [25:24]):
 * - Normal memory, Inner Write-Back Read-Allocate Write-Allocate Cacheable (Value: 0b01)
 *
 * Translation table walk disable for translations using TTBR1_EL1 (EPD1, bit [23]):
 * - Perform translation table walks using TTBR1_EL1 (Value: 0b0)
 *
 * Selects whether TTBR0_EL1 or TTBR1_EL1 defines the ASID (A1, bit [22]):
 * - TTBR0_EL1.ASID defines the ASID (Value: 0b0)
 *
 * Size offset of the memory region addressed by TTBR1_EL1 (T1SZ, bits [21:16]):
 * - 48 bits (Value: 16 0b010000)
 *
 * Granule size for the TTBR0_EL1 (TG0, bits [15:14]):
 * - 4KiB (Value: 0b00)
 *
 * Shareability attribute for TTBR0_EL1 (SH0, bits [13:12]):
 * - Inner Shareable (Value: 0b11)
 *
 * Outer cacheability attribute for TTBR0_EL1 (ORGN0, bits [11:10]):
 * - Normal memory, Outer Write-Back Read-Allocate Write-Allocate Cacheable (Value: 0b01)
 *
 * Inner cacheability attribute for TTBR0_EL1 (IRGN0, bits [9:8]):
 * - Normal memory, Inner Write-Back Read-Allocate Write-Allocate Cacheable (Value: 0b01)
 *
 * Translation table walk disable for translations using TTBR0_EL1 (EPD0, bit [7]):
 * - Perform translation table walks using TTBR0_EL1 (Value: 0b0)
 *
 * Size offset of the memory region addressed by TTBR0_EL1 (T0SZ, bits [5:0]):
 * - 48 bits (Value: 16 0b010000)
 *
 */
LOFUNCTION_S(lo_tlb_setup)
    ldr x0, =0x5B5103510
    msr TCR_EL1, x0
    isb
    ret
LOFUNCTION_E(lo_tlb_setup)

/**
 * Enable MMU
 */
LOFUNCTION_S(lo_mmu_enable)
    tlbi vmalle1            /* Invalidate all MMU cached (old) TLB's */
    dsb sy
    isb
    mrs x0, SCTLR_EL1
    orr x0, x0, #1          /* Enable MMU */
    msr SCTLR_EL1, x0
    isb
    ret
LOFUNCTION_E(lo_mmu_enable)

.text

/**
 * Get kernel translation table level 0
 */
FUNCTION_S(mmu_tlb_kern_lvl0_get)
    mrs x0, TTBR1_EL1
    ret
FUNCTION_E(mmu_tlb_kern_lvl0_get)

/**
 * Get kernel translation table level 1
 */
FUNCTION_S(mmu_tlb_kern_lvl1_get)
    ldr x0, =tlb_kern_lvl1
    ret
FUNCTION_E(mmu_tlb_kern_lvl1_get)

/**
 * Get kernel translation table level 2
 */
FUNCTION_S(mmu_tlb_kern_lvl2_get)
    ldr x0, =tlb_kern_lvl2
    ret
FUNCTION_E(mmu_tlb_kern_lvl2_get)

/**
 * Get userspace translation table level 0
 */
FUNCTION_S(mmu_tlb_user_lvl0_get)
    mrs x0, TTBR0_EL1
    ret
FUNCTION_E(mmu_tlb_user_lvl0_get)

/**
 * Get userspace translation table level 1
 */
FUNCTION_S(mmu_tlb_user_lvl1_get)
    ldr x0, =tlb_user_lvl1
    ret
FUNCTION_E(mmu_tlb_user_lvl1_get)

/**
 * Invalidate MMU all cached TLB's
 */
FUNCTION_S(mmu_tlb_inval_all)
    tlbi vmalle1
    dsb sy
    isb
    ret
FUNCTION_E(mmu_tlb_inval_all)

.end
