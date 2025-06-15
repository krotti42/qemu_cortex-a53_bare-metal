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

#include <string.h>

/*
 * Compute the length of the maximum initial segment of the string pointed 
 * to by *str1* which consists entirely of characters NOT from the string
 * pointed to by *str2*.
 * 
 * Returns the length of the segment.
 */

size_t strcspn(const char *str1, const char *str2)
{
    size_t ret = 0;
    char *s1;
    char *s2;
    
    s1 = (char *) str1;
    s2 = (char *) str2;
    
    while (*s1 != '\0') {
        while (*s2 != '\0') {
            if (*s1 == *s2)
                return ret;
            
            s2++;
        }
        
        s2 = (char *) str2;
        s1++;
        ret++;
    }
    
    return ret;
}
