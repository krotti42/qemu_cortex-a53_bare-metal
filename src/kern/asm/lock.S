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

FUNCTION_S(_mutex_trylock)
    prfm PSTL1STRM, [x0]
    ldaxr w1, [x0]
    cbnz w1, 1f
    mov w1, #1
    stxr w2, w1, [x0]
    cbnz w2, 1f
    mov x0, #0
    dsb SY
    ret
1:
    mov x0, #1
    ret
FUNCTION_E(_mutex_trylock)

FUNCTION_S(_mutex_unlock)
    prfm PSTL1STRM, [x0]
1:
    ldxr w1, [x0]
    mov w1, #0
    stxr w2, w1, [x0]
    cbnz w2, 1b
    dsb SY
    ret
FUNCTION_E(_mutex_unlock)

.end
