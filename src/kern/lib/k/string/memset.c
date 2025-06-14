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

#include <k/string.h>

/*
 * Copy *num* characters of the value of *val* (converted to unsigned char)
 * into the object pointed to by *ptr*.
 * 
 * Returns the pointer from the object *ptr*.
 */

#ifndef JLIBC_CONFIG_ARCH_MEMSET

void *memset(void *ptr, int val, size_t num)
{
    size_t i;
    unsigned char *p;
    
    p = (unsigned char *) ptr;
    
    for (i = 0; i < num; i++) {
        *p = (unsigned char) val;
        p++;
    }
    
    return ptr;
}

#endif
