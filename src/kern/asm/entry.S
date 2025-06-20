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
 * Kernel higher half (high address) entry
 */

#define _ASM_ASSEMBLY_

#include <asm.h>

.text

ENTRY_S(_start)
    /**
     * Setup EL1 handler stack pointer
     */
    msr SPsel, #1           /* Select handler stack */
    ldr x0, =_stack_el1_e   /* Load stack address (defined in linker script) */
    mov sp, x0              /* Setup stack pointer */

    /**
     * Setup EL1 thread stack pointer
     */
    msr SPsel, #0           /* Select thread stack */
    ldr x0, =_stack_el0_e   /* Load stack address (defined in linker script) */
    mov sp, x0              /* Setup stack pointer */

    /**
     * Disable interrupts
     */
    bl intr_disable

    /**
     * Setup basic vector table and enable interrupts
     */
    bl vector_set
    bl intr_enable

    /**
     * Clean and invalidate caches, then enable them
     */
    bl cpu_icache_inval
    bl cpu_dcache_l1_inval
    bl cpu_dcache_l2_inval
    mrs x0, SCTLR_EL1       /* Read SCTLR_EL1 register */
    orr x0, x0, #(1 << 2)   /* Enable D-Cache */
    orr x0, x0, #(1 << 12)  /* Enable I-Cache */
    msr SCTLR_EL1, x0       /* Write SCTLR_EL1 register */
    isb

    /**
     * Don't trap access from Advanced SIMD and floating-point
     * registers in EL1 and EL0.
     *
     * NOTE:
     * Without the compiler switch '-mgeneral-regs-only' the
     * compiler GCC uses these registers in some cases
     * (variadic arguments as example).
     */
    mrs x0, CPACR_EL1
    mov x1, #3              /* Access from EL1 and EL0 not trapped */
    lsl x1, x1, #20
    orr x0, x0, x1
    msr CPACR_EL1, x0
    isb

    /**
     * Zero .bss for C runtime
     */
    bl zero_bss

    /**
     * Jump to kernel main
     */
    bl kern_main

    /**
    * Should never be reached
    */
1000:
    b 1000b

ENTRY_E(_start)

.end
