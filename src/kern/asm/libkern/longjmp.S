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

.text

FUNCTION_S(_l_longjmp)
    /* Restore floating-point register (callee saved register) */
    ldp q8, q9, [x0, #0]
    ldp q10, q11, [x0, #32]
    ldp q12, q13, [x0, #64]
    ldp q14, q15, [x0, #96]
    /* Restore general-purpose register (callee saved register) */
    ldp x19, x20, [x0, #128]
    ldp x21, x22, [x0, #144]
    ldp x23, x24, [x0, #160]
    ldp x25, x26, [x0, #176]
    ldp x27, x28, [x0, #192]
    ldp x20, x30, [x0, #208]
    ldr x2, [x0, #240]
    mov sp, x2
    /* Check if x1 (val) is equal to 0, if equal then increment */
    mov x0, x1
    cmp x0, #0
    cinc x0, x0, eq
    br x30
FUNCTION_E(_l_longjmp)

.end
