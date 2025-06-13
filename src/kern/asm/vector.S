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
 * EL1 Current Exception level with SP_EL0
 */
/* Synchronous */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mrs x0, ESR_EL1             /* Exception syndrome */
    mrs x1, FAR_EL1             /* Exception fault address */
    b isr_cel_spel0_sync
.balign 0x80
/* IRQ or vIRQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_cel_spel0_irq
.balign 0x80
/* FIQ or vFIQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_cel_spel0_fiq
.balign 0x80
/* SError or vSError */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    mrs x0, ESR_EL1
    mrs x1, FAR_EL1
    b isr_cel_spel0_serr
.balign 0x80
/**
 * EL1 Current Exception level with SP_ELx
 */
/* Synchronous */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_cel_spel1_sync
.balign 0x80
/* IRQ or vIRQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_cel_spel1_irq
.balign 0x80
/* FIQ or vFIQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_cel_spel1_fiq
.balign 0x80
/* SError or vSError */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_cel_spel1_serr
.balign 0x80
/**
 * EL1 Lower Exception level AArch64
 */
/* Synchronous */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_l64_sync
.balign 0x80
/* IRQ or vIRQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_l64_irq
.balign 0x80
/* FIQ or vFIQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_l64_fiq
.balign 0x80
/* SError or vSError */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_l64_serr
.balign 0x80
/**
 * EL1 Lower Exception level AArch32
 */
/* Synchronous */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_l32_sync
.balign 0x80
/* IRQ or vIRQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_l32_irq
.balign 0x80
/* FIQ or vFIQ */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_l32_fiq
.balign 0x80
/* SError or vSError */
    stp x29, x30, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
    b isr_l32_serr
.balign 0x80
SYMBOL(vector_el1_e)

.text

/**
 * EL1 Current Exception level with SP_EL0 ISR's
 */
ISR_S(isr_cel_spel0_sync)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_cel_spel0_sync)

ISR_S(isr_cel_spel0_irq)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_cel_spel0_irq)

ISR_S(isr_cel_spel0_fiq)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_cel_spel0_fiq)

ISR_S(isr_cel_spel0_serr)
    mrs x0, ESR_EL1
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_cel_spel0_serr)

/**
 * EL1 Current Exception level with SP_EL1 ISR's
 */
ISR_S(isr_cel_spel1_sync)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_cel_spel1_sync)

ISR_S(isr_cel_spel1_irq)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_cel_spel1_irq)

ISR_S(isr_cel_spel1_fiq)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_cel_spel1_fiq)

ISR_S(isr_cel_spel1_serr)
    mrs x0, ESR_EL1
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_cel_spel1_serr)

/**
 * EL1 Lower Exception level AArch64 ISR's
 */
ISR_S(isr_l64_sync)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_l64_sync)

ISR_S(isr_l64_irq)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_l64_irq)

ISR_S(isr_l64_fiq)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_l64_fiq)

ISR_S(isr_l64_serr)
    mrs x0, ESR_EL1
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_l64_serr)

/**
 * EL1 Lower Exception level AArch32 ISR's
 */
ISR_S(isr_l32_sync)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_l32_sync)

ISR_S(isr_l32_irq)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_l32_irq)

ISR_S(isr_l32_fiq)
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_l32_fiq)

ISR_S(isr_l32_serr)
    mrs x0, ESR_EL1
1:
    nop
    nop
    nop
    nop
    b 1b
ISR_E(isr_l32_serr)

FUNCTION_S(vector_set)
    ldr x0, =_isr_vector_s
    msr VBAR_EL1, x0
    ret
FUNCTION_E(vector_set)

.end
