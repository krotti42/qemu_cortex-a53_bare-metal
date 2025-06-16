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
 * Kernel lower (lower address) entry
 */

#define _ASM_ASSEMBLY_

#include <asm.h>

LOENTRY_S(_lo_start)
/**
 * EL3 (Secure monitor)
 */
4000:
    /**
     * Test if we are in EL3, jump if not
     */
    mrs x0, CurrentEL       /* Read CurrentEL */
    and x0, x0, #0xC        /* Mask EL bit field */
    asr x0, x0, #2          /* Shift right to test EL */
    cmp x0, #3              /* Test if we in EL3 */
    bne 4000f               /* Branch to EL2 setup if we are not in EL3 */

    /**
     * Disable MMU, I-Cache and D-Cache
     */
    mrs x0, SCTLR_EL3
    bic x0, x0, #(1 << 0)   /* Disable MMU */
    bic x0, x0, #(1 << 2)   /* Disable D-Cache */
    bic x0, x0, #(1 << 12)  /* Disable I-Cache */
    msr SCTLR_EL3, x0
    isb

    /**
     * Setup next lower exception level (EL2)
     */
    msr SCTLR_EL2, xzr
    msr HCR_EL2, xzr
    mrs x0, SCR_EL3
    orr x0, x0, #(1 << 10)  /* Next lower exception level is AArch64 */
    orr x0, x0, #(1 << 0)   /* EL1/EL0 are in Non-secure state */
    msr SCR_EL3, x0

    /**
     * Enter next lower exception level (EL2)
     */
    mov x0, xzr
    orr x0, x0, #(1 << 8)   /* Mask SError */
    orr x0, x0, #(1 << 7)   /* Mask IRQ */
    orr x0, x0, #(1 << 6)   /* Mask FIQ */
    mov x1, #0b01001        /* EL2 is in handler mode */
    orr x0, x0, x1
    msr SPSR_EL3, x0
    adr x0, 3000f
    msr ELR_EL3, x0
    eret

/**
 * EL2 (Hypervisor)
 */
4000:
    /**
     * Test if we are in EL2, jump if not
     */
    mrs x0, CurrentEL       /* Read CurrentEL */
    and x0, x0, #0xC        /* Mask EL bit field */
    asr x0, x0, #2          /* Shift right to test EL */
    cmp x0, #2              /* Test if we in EL2 */
    bne 3000f               /* Branch to EL1 setup if we are not in EL2 */

    /**
     * Disable MMU, I-Cache and D-Cache
     */
    mrs x0, SCTLR_EL2
    bic x0, x0, #(1 << 0)   /* Disable MMU */
    bic x0, x0, #(1 << 2)   /* Disable D-Cache */
    bic x0, x0, #(1 << 12)  /* Disable I-Cache */
    msr SCTLR_EL2, x0
    isb

    /**
     * Setup next lower exception level (EL1)
     */
    mrs x0, HCR_EL2
    orr x0, x0, #(1 << 31)  /* EL1 is AArch64 */
    msr HCR_EL2, x0
    mov x0, xzr
    orr x0, x0, #(1 << 29)  /* RES1 */
    orr x0, x0, #(1 << 28)  /* RES1 */
    orr x0, x0, #(1 << 23)  /* RES1 */
    orr x0, x0, #(1 << 22)  /* RES1 */
    orr x0, x0, #(1 << 20)  /* RES1 */
    orr x0, x0, #(1 << 11)  /* RES1 */
    orr x0, x0, #(1 << 4)   /* Enable SP alignment check for EL0 */
    orr x0, x0, #(1 << 3)   /* Enable SP alignment check for EL1 */
    orr x0, x0, #(1 << 1)   /* Enable alignment fault check */
    msr SCTLR_EL1, x0

    /**
     * Setup counter access for EL1
     */
    mrs x0, CNTHCTL_EL2
    orr x0, x0, #(1 << 0)
    orr x0, x0, #(1 << 1)
    msr CNTHCTL_EL2, x0
    msr CNTVOFF_EL2, xzr

    /**
     * Enter next lower exception level (EL1)
     */
    mov x0, xzr
    orr x0, x0, #(1 << 8)   /* Mask SError */
    orr x0, x0, #(1 << 7)   /* Mask IRQ */
    orr x0, x0, #(1 << 6)   /* Mask FIQ */
    mov x1, #0b101          /* EL1 is in handler mode */
    orr x0, x0, x1
    msr SPSR_EL2, x0
    adr x0, 3000f
    msr ELR_EL2, x0
    eret

/**
 * EL1 (Kernel)
 */
3000:
    /**
     * Setup EL1 stack pointer
     */
    msr SPsel, #1           /* Select EL1 stack */
    ldr x0, =_stack_lo_e    /* Load stack address (defined in linker script) */
    mov sp, x0              /* Setup stack pointer */

    mrs x0, SCTLR_EL1       /* Read SCTLR_EL1 register */
    bic x0, x0, #(1 << 0)   /* Disable MMU */
    bic x0, x0, #(1 << 2)   /* Disable D-Cache */
    bic x0, x0, #(1 << 12)  /* Disable I-Cache */
    msr SCTLR_EL1, x0       /* Write SCTLR_EL1 register */
    isb

    /**
     * Setup basic TLB's for MMU and enable the MMU
     */
    bl lo_tlb_kern_zero
    bl lo_tlb_user_zero
    bl lo_tlb_mem_type
    bl lo_tlb_kern_setup
    bl lo_tlb_user_setup
    bl lo_tlb_setup
    bl lo_mmu_enable

    /**
     * Jump to higher half kernel
     */
2000:
    ldr x0, =_start
    br x0

    /**
     * Should never be reached
     */
1000:
    b 1000b
LOENTRY_E(_lo_start)
