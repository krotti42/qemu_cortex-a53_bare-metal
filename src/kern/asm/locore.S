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
 * Kernel low address startup
 */

#define _ASM_ASSEMBLY_

#include <asm.h>

LOENTRY_S(_lstart)
/**
 * EL3 (Secure monitor)
 */
4000:
    mrs x0, CurrentEL       /* Read CurrentEL */
    and x0, x0, #0xC        /* Mask EL bit field */
    asr x0, x0, #2          /* Shift right to test EL */
    cmp x0, #3              /* Test if we in EL3 */
    bne 3000f               /* Branch to EL2 setup if we are not in EL3 */



/**
 * EL2 (Hypervisor)
 */
3000:
    mrs x0, CurrentEL       /* Read CurrentEL */
    and x0, x0, #0xC        /* Mask EL bit field */
    asr x0, x0, #2          /* Shift right to test EL */
    cmp x0, #2              /* Test if we in EL2 */
    bne 2000f               /* Branch to EL1 setup if we are not in EL2 */

/**
 * EL1 (Kernel)
 */
2000:
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

    bl lo_tlb_kern_zero
    bl lo_tlb_user_zero
    bl lo_tlb_mem_type
    bl lo_tlb_kern_setup
    bl lo_tlb_user_setup
    bl lo_tlb_setup
    bl lo_mmu_enable

1000:
    ldr x0, =_start
    br x0
LOENTRY_E(_lstart)
