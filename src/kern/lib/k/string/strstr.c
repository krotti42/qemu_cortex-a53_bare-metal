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
 * Find the first occurrence in the string pointed to by *str1* of the sequence 
 * of characters in the string pointed to by *str2*.
 * 
 * Returns the pointer from the found string in *str1*, or a NULL pointer if 
 * not. If *str2* is empty than the pointer from *str1* is returned.
 */

char *strstr(const char *str1, const char *str2)
{
    size_t s2_len = 0;
    size_t i;
    char *ret = NULL;
    char *s1;
    char *s2;
    
    s2_len = strlen(str2);
    s1 = (char *) str1;
    
    if (s2_len == 0)
        return s1;
    
    s2 = (char *) str2;
    
    while (*s1 != '\0') {
        if (*s1 == *s2) {
            ret = s1;
            
            for (i = 0; i < s2_len; i++) {
                if (*s1 != *s2) {
                    ret = NULL;
                    s2 = (char *) str2;
                    break;
                } else {
                    if (i == (s2_len - 1))
                        return ret;
                    
                    s1++;
                    s2++;
                }
                
            }
            
            s1--;
        }
        
        s1++;
    }
    
    return NULL;
}
