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
 * Compare the first *num* characters of the string pointed to by *str1*
 * with the string pointed to by *str2*.
 * 
 * Returns the integer zero if *str1* and *str2* are equal, or an integer
 * less or greater than zero if not.
 */

int strncmp(const char *str1, const char *str2, size_t num)
{
    size_t i;
    size_t s1_len = 0;
    size_t s2_len = 0;
    char *s1;
    char *s2;
    
    s1_len = strlen(str1);
    s2_len = strlen(str2);
    s1 = (char *) str1;
    s2 = (char *) str2;
    
    if ((s1_len >= num) || (s2_len >= num)) {
        for (i = 0; i < num; i++) {
            if (*s1 != *s2)
                return (int) *s1 - *s2;
            
            s1++;
            s2++;
        }
    } else {
        if (s1_len != s2_len)
            return (int) s1_len - s2_len;
        
        while (*s1 != '\0') {
            if (*s1 != *s2)
                return (int) *s1 - *s2;
            
            s1++;
            s2++;
        }
    }
    
    return 0;
}
