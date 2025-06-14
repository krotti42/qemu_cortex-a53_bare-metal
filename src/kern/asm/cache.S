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
 * Kernel cache maintenance functions
 */

#define _ASM_ASSEMBLY_

#include <asm.h>

.text

/**
 * Clean and invalidate instruction cache
 */
FUNCTION_S(cpu_icache_inval)
    ic IALLUIS
    dsb sy
    isb
    ret
FUNCTION_E(cpu_icache_inval)

/**
 * Clean and invalidate level 1 data cache
 */
FUNCTION_S(cpu_dcache_l1_inval)
    mov x0, xzr
    msr CSSELR_EL1, x0
    mrs x4, CCSIDR_EL1
    and x1, x4, #0x7
    add x1, x1, #0x4
    ldr x3, =0x7FFF
    and x2, x3, x4, lsr #13
    ldr x3, =0x3FF
    and x3, x3, x4, lsr #3
    clz w4, w3
    mov x5, #0
1:
    mov x6, #0
2:
    lsl x7, x5, x4
    orr x7, x0, x7
    lsl x8, x6, x1
    orr x7, x7, x8
    dc CISW, x7
    add x6, x6, #1
    cmp x6, x2
    ble 2b
    add x5, x5, #1
    cmp x5, x3
    ble 1b
    dsb sy
    isb
    ret
FUNCTION_E(cpu_dcache_l1_inval)

/**
 * Clean and invalidate level 2 data cache
 */
FUNCTION_S(cpu_dcache_l2_inval)
    mov x0, xzr
    orr x0, x0, #(1 << 1)
    msr CSSELR_EL1, x0
    mrs x4, CCSIDR_EL1
    and x1, x4, #0x7
    add x1, x1, #0x4
    ldr x3, =0x7FFF
    and x2, x3, x4, lsr #13
    ldr x3, =0x3FF
    and x3, x3, x4, lsr #3
    clz w4, w3
    mov x5, #0
1:
    mov x6, #0
2:
    lsl x7, x5, x4
    orr x7, x0, x7
    lsl x8, x6, x1
    orr x7, x7, x8
    dc CISW, x7
    add x6, x6, #1
    cmp x6, x2
    ble 2b
    add x5, x5, #1
    cmp x5, x3
    ble 1b
    dsb sy
    isb
    ret
FUNCTION_E(cpu_dcache_l2_inval)

.end
