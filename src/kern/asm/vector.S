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

#define _ASM_ASSEMBLY_

#include <asm.h>

.section .isr_vector

SYMBOL(vector_el1_s)

/**
 * Kernel thread with SP_EL0
 */
    /**
     * Synchronous
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    msr SPsel, #0
    mov x1, sp                      /* Save SP for kernel thread */
    msr SPsel, #1
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_cel_sp0_sync
.balign 0x80
    /**
     * IRQ or vIRQ
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    msr SPsel, #0
    mov x1, sp                      /* Save SP for kernel thread */
    msr SPsel, #1
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_cel_sp0_irq
.balign 0x80
    /**
     * FIQ or vFIQ
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    msr SPsel, #0
    mov x1, sp                      /* Save SP for kernel thread */
    msr SPsel, #1
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_cel_sp0_fiq
.balign 0x80
    /**
     * SError or vSError
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    msr SPsel, #0
    mov x1, sp                      /* Save SP for kernel thread */
    msr SPsel, #1
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_cel_sp0_serr
.balign 0x80

/**
 * Kernel handler with SP_EL1
 */
    /**
     * Synchronous
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    mov x1, sp                      /* Save SP for kernel thread */
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_cel_sp1_sync
.balign 0x80
    /**
     * IRQ or vIRQ
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    mov x1, sp                      /* Save SP for kernel thread */
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_cel_sp1_irq
.balign 0x80
    /**
     * FIQ or vFIQ
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    mov x1, sp                      /* Save SP for kernel thread */
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_cel_sp1_fiq
.balign 0x80
    /**
     * SError or vSError
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    mov x1, sp                      /* Save SP for kernel thread */
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_cel_sp1_serr
.balign 0x80

/**
 * User thread AArch64
 */
    /**
     * Synchronous
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    mrs x1, SP_EL0                  /* Save SP for user thread */
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_lo64_sync
.balign 0x80
    /**
     * IRQ or vIRQ
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    mrs x1, SP_EL0                  /* Save SP for user thread */
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_lo64_irq
.balign 0x80
    /**
     * FIQ or vFIQ
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    mrs x1, SP_EL0                  /* Save SP for user thread */
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_lo64_fiq
.balign 0x80
    /**
     * SError or vSError
     */
    stp x29, x30, [sp, #-16]!       /* Save general all purpose registers */
    stp x27, x28, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x19, x20, [sp, #-16]!
    stp x17, x18, [sp, #-16]!
    stp x15, x16, [sp, #-16]!
    stp x13, x14, [sp, #-16]!
    stp x11, x12, [sp, #-16]!
    stp x9, x10, [sp, #-16]!
    stp x7, x8, [sp, #-16]!
    stp x5, x6, [sp, #-16]!
    stp x3, x4, [sp, #-16]!
    stp x1, x2, [sp, #-16]!
    mrs x1, SP_EL0                  /* Save SP for user thread */
    stp x1, x0, [sp, #-16]!
    mrs x0, SPSR_EL1                /* Save program status register */
    mrs x1, ELR_EL1                 /* Save exception link register */
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1                 /* Save fault address */
    mrs x1, ESR_EL1                 /* Save exception syndrome register */
    stp x1, x0, [sp, #-16]!
    b isr_lo64_serr
.balign 0x80

/**
 * User thread AArch32
 *
 * TODO
 */
    /**
     * Synchronous
     */
    stp w29, w30, [sp, #-8]!        /* Save general all purpose registers */
    stp w27, w28, [sp, #-8]!
    stp w25, w26, [sp, #-8]!
    stp w23, w24, [sp, #-8]!
    stp w21, w22, [sp, #-8]!
    stp w19, w20, [sp, #-8]!
    stp w17, w18, [sp, #-8]!
    stp w15, w16, [sp, #-8]!
    stp w13, w14, [sp, #-8]!
    stp w11, w12, [sp, #-8]!
    stp w9, w10, [sp, #-8]!
    stp w7, w8, [sp, #-8]!
    stp w5, w6, [sp, #-8]!
    stp w3, w4, [sp, #-8]!
    stp w1, w2, [sp, #-8]!
    stp wzr, w0, [sp, #-8]!
    mrs x0, SP_EL0
    stp xzr, x0, [sp, #-16]!
    mrs x0, SPSR_EL1
    mrs x1, ELR_EL1
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1
    mrs x1, ESR_EL1
    stp x1, x0, [sp, #-16]!
    b isr_lo32_sync
.balign 0x80
    /**
     * IRQ or vIRQ
     */
    stp w29, w30, [sp, #-8]!        /* Save general all purpose registers */
    stp w27, w28, [sp, #-8]!
    stp w25, w26, [sp, #-8]!
    stp w23, w24, [sp, #-8]!
    stp w21, w22, [sp, #-8]!
    stp w19, w20, [sp, #-8]!
    stp w17, w18, [sp, #-8]!
    stp w15, w16, [sp, #-8]!
    stp w13, w14, [sp, #-8]!
    stp w11, w12, [sp, #-8]!
    stp w9, w10, [sp, #-8]!
    stp w7, w8, [sp, #-8]!
    stp w5, w6, [sp, #-8]!
    stp w3, w4, [sp, #-8]!
    stp w1, w2, [sp, #-8]!
    stp wzr, w0, [sp, #-8]!
    mrs x0, SP_EL0
    stp xzr, x0, [sp, #-16]!
    mrs x0, SPSR_EL1
    mrs x1, ELR_EL1
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1
    mrs x1, ESR_EL1
    stp x1, x0, [sp, #-16]!
    b isr_lo32_irq
.balign 0x80
    /**
     * FIQ or vFIQ
     */
    stp w29, w30, [sp, #-8]!        /* Save general all purpose registers */
    stp w27, w28, [sp, #-8]!
    stp w25, w26, [sp, #-8]!
    stp w23, w24, [sp, #-8]!
    stp w21, w22, [sp, #-8]!
    stp w19, w20, [sp, #-8]!
    stp w17, w18, [sp, #-8]!
    stp w15, w16, [sp, #-8]!
    stp w13, w14, [sp, #-8]!
    stp w11, w12, [sp, #-8]!
    stp w9, w10, [sp, #-8]!
    stp w7, w8, [sp, #-8]!
    stp w5, w6, [sp, #-8]!
    stp w3, w4, [sp, #-8]!
    stp w1, w2, [sp, #-8]!
    stp wzr, w0, [sp, #-8]!
    mrs x0, SP_EL0
    stp xzr, x0, [sp, #-16]!
    mrs x0, SPSR_EL1
    mrs x1, ELR_EL1
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1
    mrs x1, ESR_EL1
    stp x1, x0, [sp, #-16]!
    b isr_lo32_fiq
.balign 0x80
    /**
     * SError or vSError
     */
    stp w29, w30, [sp, #-8]!        /* Save general all purpose registers */
    stp w27, w28, [sp, #-8]!
    stp w25, w26, [sp, #-8]!
    stp w23, w24, [sp, #-8]!
    stp w21, w22, [sp, #-8]!
    stp w19, w20, [sp, #-8]!
    stp w17, w18, [sp, #-8]!
    stp w15, w16, [sp, #-8]!
    stp w13, w14, [sp, #-8]!
    stp w11, w12, [sp, #-8]!
    stp w9, w10, [sp, #-8]!
    stp w7, w8, [sp, #-8]!
    stp w5, w6, [sp, #-8]!
    stp w3, w4, [sp, #-8]!
    stp w1, w2, [sp, #-8]!
    stp wzr, w0, [sp, #-8]!
    mrs x0, SP_EL0
    stp xzr, x0, [sp, #-16]!
    mrs x0, SPSR_EL1
    mrs x1, ELR_EL1
    stp x1, x0, [sp, #-16]!
    mrs x0, FAR_EL1
    mrs x1, ESR_EL1
    stp x1, x0, [sp, #-16]!
    b isr_lo32_serr
.balign 0x80

SYMBOL(vector_el1_e)

.text

/**
 * Kernel thread with SP_EL0
 */

/**
 * Synchronous
 */
ISR_S(isr_cel_sp0_sync)
    mov x0, sp
    bl intr_handler_kern_sp0_sync
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SPsel, #0
    mov sp, x1
    msr SPsel, #1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_cel_sp0_sync)

/**
 * IRQ or vIRQ
 */
ISR_S(isr_cel_sp0_irq)
    mov x0, sp
    bl intr_handler_kern_sp0_irq
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SPsel, #0
    mov sp, x1
    msr SPsel, #1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_cel_sp0_irq)

/**
 * FIQ or vFIQ
 */
ISR_S(isr_cel_sp0_fiq)
    mov x0, sp
    bl intr_handler_kern_sp0_fiq
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SPsel, #0
    mov sp, x1
    msr SPsel, #1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_cel_sp0_fiq)

/**
 * SError or vSError
 */
ISR_S(isr_cel_sp0_serr)
    mov x0, sp
    bl intr_handler_kern_sp0_serr
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SPsel, #0
    mov sp, x1
    msr SPsel, #1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_cel_sp0_serr)

/**
 * Kernel handler with SP_EL1
 */

/**
 * Synchronous
 */
ISR_S(isr_cel_sp1_sync)
    mov x0, sp
    bl intr_handler_kern_sp1_sync
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_cel_sp1_sync)

/**
 * IRQ or vIRQ
 */
ISR_S(isr_cel_sp1_irq)
    mov x0, sp
    bl intr_handler_kern_sp1_irq
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_cel_sp1_irq)

/**
 * FIQ or vFIQ
 */
ISR_S(isr_cel_sp1_fiq)
    mov x0, sp
    bl intr_handler_kern_sp1_fiq
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_cel_sp1_fiq)

/**
 * SError or vSError
 */
ISR_S(isr_cel_sp1_serr)
    mov x0, sp
    bl intr_handler_kern_sp1_serr
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_cel_sp1_serr)

/**
 * User thread AArch64
 */

/**
 * Synchronous
 */
ISR_S(isr_lo64_sync)
    mov x0, sp
    bl intr_handler_user64_sync
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SP_EL0, x1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_lo64_sync)

/**
 * IRQ or vIRQ
 */
ISR_S(isr_lo64_irq)
    mov x0, sp
    bl intr_handler_user64_irq
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SP_EL0, x1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_lo64_irq)

/**
 * FIQ or vFIQ
 */
ISR_S(isr_lo64_fiq)
    mov x0, sp
    bl intr_handler_user64_fiq
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SP_EL0, x1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_lo64_fiq)

/**
 * SError or vSError
 */
ISR_S(isr_lo64_serr)
    mov x0, sp
    bl intr_handler_user64_serr
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SP_EL0, x1
    add sp, sp, #48
    ldp x1, x2, [sp], #16
    ldp x3, x4, [sp], #16
    ldp x5, x6, [sp], #16
    ldp x7, x8, [sp], #16
    ldp x9, x10, [sp], #16
    ldp x11, x12, [sp], #16
    ldp x13, x14, [sp], #16
    ldp x15, x16, [sp], #16
    ldp x17, x18, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16
    eret
ISR_E(isr_lo64_serr)

/**
 * User thread AArch32
 */

/**
 * Synchronous
 */
ISR_S(isr_lo32_sync)
    mov x0, sp
    bl intr_handler_user32_sync
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SP_EL0, x1
    add sp, sp, #48
    ldp wzr, w0, [sp], #8
    ldp w1, w2, [sp], #8
    ldp w3, w4, [sp], #8
    ldp w5, w6, [sp], #8
    ldp w7, w8, [sp], #8
    ldp w9, w10, [sp], #8
    ldp w11, w12, [sp], #8
    ldp w13, w14, [sp], #8
    ldp w15, w16, [sp], #8
    ldp w17, w18, [sp], #8
    ldp w19, w20, [sp], #8
    ldp w21, w22, [sp], #8
    ldp w23, w24, [sp], #8
    ldp w25, w26, [sp], #8
    ldp w27, w28, [sp], #8
    ldp w29, w30, [sp], #8
    eret
ISR_E(isr_lo32_sync)

/**
 * IRQ or vIRQ
 */
ISR_S(isr_lo32_irq)
    mov x0, sp
    bl intr_handler_user32_irq
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SP_EL0, x1
    add sp, sp, #48
    ldp wzr, w0, [sp], #8
    ldp w1, w2, [sp], #8
    ldp w3, w4, [sp], #8
    ldp w5, w6, [sp], #8
    ldp w7, w8, [sp], #8
    ldp w9, w10, [sp], #8
    ldp w11, w12, [sp], #8
    ldp w13, w14, [sp], #8
    ldp w15, w16, [sp], #8
    ldp w17, w18, [sp], #8
    ldp w19, w20, [sp], #8
    ldp w21, w22, [sp], #8
    ldp w23, w24, [sp], #8
    ldp w25, w26, [sp], #8
    ldp w27, w28, [sp], #8
    ldp w29, w30, [sp], #8
    eret
ISR_E(isr_lo32_irq)

/**
 * FIQ or vFIQ
 */
ISR_S(isr_lo32_fiq)
    mov x0, sp
    bl intr_handler_user32_fiq
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SP_EL0, x1
    add sp, sp, #48
    ldp wzr, w0, [sp], #8
    ldp w1, w2, [sp], #8
    ldp w3, w4, [sp], #8
    ldp w5, w6, [sp], #8
    ldp w7, w8, [sp], #8
    ldp w9, w10, [sp], #8
    ldp w11, w12, [sp], #8
    ldp w13, w14, [sp], #8
    ldp w15, w16, [sp], #8
    ldp w17, w18, [sp], #8
    ldp w19, w20, [sp], #8
    ldp w21, w22, [sp], #8
    ldp w23, w24, [sp], #8
    ldp w25, w26, [sp], #8
    ldp w27, w28, [sp], #8
    ldp w29, w30, [sp], #8
    eret
ISR_E(isr_lo32_fiq)

/**
 * SError or vSError
 */
ISR_S(isr_lo32_serr)
    mov x0, sp
    bl intr_handler_user32_serr
    ldr x1, [x0]
    msr ELR_EL1, x1
    ldr x1, [x0, #8]
    msr SPSR_EL1, x1
    ldr x1, [x0, #16]
    msr SP_EL0, x1
    add sp, sp, #48
    ldp wzr, w0, [sp], #8
    ldp w1, w2, [sp], #8
    ldp w3, w4, [sp], #8
    ldp w5, w6, [sp], #8
    ldp w7, w8, [sp], #8
    ldp w9, w10, [sp], #8
    ldp w11, w12, [sp], #8
    ldp w13, w14, [sp], #8
    ldp w15, w16, [sp], #8
    ldp w17, w18, [sp], #8
    ldp w19, w20, [sp], #8
    ldp w21, w22, [sp], #8
    ldp w23, w24, [sp], #8
    ldp w25, w26, [sp], #8
    ldp w27, w28, [sp], #8
    ldp w29, w30, [sp], #8
    eret
ISR_E(isr_lo32_serr)

FUNCTION_S(vector_set)
    ldr x0, =_isr_vector_s
    msr VBAR_EL1, x0
    ret
FUNCTION_E(vector_set)

.end
