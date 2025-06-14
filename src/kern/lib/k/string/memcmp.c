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
 * Compare the first *num* characters of the object pointed to by *ptr1*
 * with the object pointed to by *ptr2*.
 * 
 * Returns the integer zero if *ptr1* and *ptr2* are equal, or an integer
 * less or greater than zero if not.
 */

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    unsigned char *p1;
    unsigned char *p2;
    size_t i;
    
    p1 = (unsigned char *) ptr1;
    p2 = (unsigned char *) ptr2;
    
    for (i = 0; i < num; i++) {
        if (*p1 != *p2)
            return (int) (*p1 - *p2);
        
        p1++;
        p2++;
    }
    
    return 0;
}
