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

#include <stdlib.h>

#include "strto_helper.h"

long long int strtoll(const char *nptr, char **endptr, int base)
{
    long long int ret = 0;
    long long int mul = 1;
    int i = 0;
    int int_start, int_end;
    int sign = 0;
    int b;
    
    if (base == 0) {
        b = 10;
        
        while ((nptr[i] != '+') && (nptr[i] != '-') && !strto_isvaliddig(nptr[i], b))
            i++;
        
        if (nptr[i] == '+') {
            sign = 0;
            i++;
        } else if (nptr[i] == '-') {
            sign = 1;
            i++;
        }
        
        if (nptr[i] == '0') {
            i++;
            
            if ((nptr[i] == 'x') || (nptr[i] == 'X')) {
                i++;
                b = 16;
            } else {
                b = 8;
            }
        }
        
        int_start = i;
    } else if (base == 16) {
        b = base;
        
        while ((nptr[i] != '+') && (nptr[i] != '-') && !strto_isvaliddig(nptr[i], b))
            i++;
        
        if (nptr[i] == '+') {
            sign = 0;
            i++;
        } else if (nptr[i] == '-') {
            sign = 1;
            i++;
        }
        
        if (nptr[i] == '0') {
            i++;
            
            if ((nptr[i] == 'x') || (nptr[i] == 'X')) {
                i++;
            }
        }
        
        int_start = i;
    } else if ((base >= 2) && (base <= 36)) {
        b = base;
        
        while ((nptr[i] != '+') && (nptr[i] != '-') && !strto_isvaliddig(nptr[i], b))
            i++;
        
        if (nptr[i] == '+') {
            sign = 0;
            i++;
        } else if (nptr[i] == '-') {
            sign = 1;
            i++;
        }
        
        int_start = i;
    } else
        return 0;
    
    while (strto_isvaliddig(nptr[i], b))
        i++;
    
    int_end = i;
    
    if (endptr != NULL)
        (*endptr) = (char *) &nptr[i];
    
    for (i = (int_end - 1); i > (int_start - 1); i--) {
        ret += strto_tobaseval(nptr[i], b) * mul;
        mul = mul * b;
    }
    
    if (sign) {
        ret--;
        ret = ~ret;
    }
    
    return ret;
}
