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

#include <k/stdlib.h>

static void do_swap(void *a, void *b, size_t size)
{
    switch (size) {
    case 1: {
        unsigned char tmp;
        
        tmp = *((unsigned char *) a);
        *((unsigned char *) a) = *((unsigned char *) b);
        *((unsigned char *) b) = tmp;
        break;
    }
    case 2: {
        unsigned short tmp;
        
        tmp = *((unsigned short *) a);
        *((unsigned short *) a) = *((unsigned short *) b);
        *((unsigned short *) b) = tmp;
        break;
    }
    case 4: {
        unsigned int tmp;
        
        tmp = *((unsigned int *) a);
        *((unsigned int *) a) = *((unsigned int *) b);
        *((unsigned int *) b) = tmp;
        break;
    }
    default: {
        unsigned char *c = a;
        unsigned char *d = b;
        unsigned char tmp;
        size_t i;
        
        for (i = 0; i < size; i++) {
            tmp = c[i];
            c[i] = d[i];
            d[i] = tmp;
        }
    }
    }
}

static size_t do_partition(void *base, size_t low, size_t high, size_t size, 
                           int (*compar)(const void *, const void *))
{
    unsigned char *arr;
    unsigned char *pivot;
    size_t i, j;
    
    arr = (unsigned char *) base;
    pivot = &arr[high];
    i = (low - 1);
    
    for (j = low; j <= high; j++) {
        if (compar((void *) &arr[j], (void *) pivot) < 0) {
            i++;
            do_swap((void *) &arr[i], (void *) &arr[j], size);
        }
    }
    
    do_swap((void *) &arr[i + 1], (void *) &arr[high], size);
    return (i + 1);
}

static void do_sort(void *base, size_t low, size_t high, size_t size, 
                    int (*compar)(const void *, const void *))
{
    size_t pi;
    
    if (low < high) {
        pi = do_partition(base, low, high, size, compar);
        do_sort(base, low, pi - 1, size, compar);
        do_sort(base, pi + 1, high, size, compar);
    }
}

void qsort(void *base, size_t nmemb, size_t size, 
           int (*compar)(const void *, const void *))
{
    do_sort(base, 0, nmemb - 1, size, compar);
}
