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
 * ARMv8 Generic Timer
 */

#define _ASM_ASSEMBLY_

#include <asm.h>

.text

FUNCTION_S(timer_get_freq)
    mrs x0, CNTFRQ_EL0
    ret
FUNCTION_E(timer_get_freq)

FUNCTION_S(timer_phys_enable)
    mov x0, xzr
    orr x0, x0, #(1 << 0)       /* Enable timer */
    msr CNTP_CTL_EL0, x0
    isb
    ret
FUNCTION_E(timer_phys_enable)

FUNCTION_S(timer_phys_set_compvalue)
    mrs x1, CNTP_CTL_EL0        /* Disable timer first */
    bic x1, x1, #(1 << 0)
    msr CNTP_CTL_EL0, x1
    msr CNTP_CVAL_EL0, x0       /* Set comparator value */
    mov x0, xzr                 /* Clear timer value */
    msr CNTP_TVAL_EL0, x0
    isb
    ret
FUNCTION_E(timer_phys_set_compvalue)

FUNCTION_S(timer_virt_enable)
    mov x0, xzr
    orr x0, x0, #(1 << 0)       /* Enable timer */
    msr CNTV_CTL_EL0, x0
    isb
    ret
FUNCTION_E(timer_virt_enable)

FUNCTION_S(timer_virt_set_compvalue)
    mrs x1, CNTV_CTL_EL0        /* Disable timer first */
    bic x1, x1, #(1 << 0)
    msr CNTV_CTL_EL0, x1
    msr CNTV_CVAL_EL0, x0       /* Set comparator value */
    mov x0, xzr                 /* Clear timer value */
    msr CNTV_TVAL_EL0, x0
    isb
    ret
FUNCTION_E(timer_virt_set_compvalue)

.end
