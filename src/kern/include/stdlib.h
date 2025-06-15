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

#ifndef _LIBKERN_STDLIB_H
#define _LIBKERN_STDLIB_H

#include <stddef.h>

#ifndef RAND_MAX
#define RAND_MAX            32767
#endif

#define EXIT_SUCCESS        0
#define EXIT_FAILURE        (-1)

struct div_s {
    int quot;
    int rem;
};

struct ldiv_s {
    long int quot;
    long int rem;
};

struct lldiv_s {
    long long int quot;
    long long int rem;
};

typedef struct div_s div_t;
typedef struct ldiv_s ldiv_t;
typedef struct lldiv_s lldiv_t;

/* Communication with the environment */
extern void abort(void);

/* Numeric conversion functions */
extern int atoi(const char *nptr);
extern long int atol(const char *nptr);
extern long long int atoll(const char *nptr);
extern float strtof(const char * __restrict nptr, char ** __restrict endptr);
extern long int strtol(const char * __restrict nptr, char ** __restrict endptr, int base);
extern long long int strtoll(const char * __restrict nptr, char ** __restrict endptr, int base);
extern unsigned long int strtoul(const char * __restrict nptr, char ** __restrict endptr, int base);
extern unsigned long long int strtoull(const char * __restrict nptr, char ** __restrict endptr, int base);

/* Pseudo-random sequence generation functions */
extern int rand(void);
extern void srand(unsigned int seed);

/* Memory management functions */
extern void *calloc(size_t nmemb, size_t size);
extern void free(void *ptr);
extern void *malloc(size_t size);
extern void *realloc(void *ptr, size_t size);

/* Searching and sorting utilities */
extern void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, 
                     int (*compar)(const void *, const void *));
extern void qsort(void *base, size_t nmemb, size_t size, 
                  int (*compar)(const void *, const void *));

/* Integer arithmetic functions */
extern int abs(int j);
extern long int labs(long int j);
extern long long int llabs(long long int j);
extern div_t div(int numer, int denom);
extern ldiv_t ldiv(long int numer, long int denom);
extern lldiv_t lldiv(long long int numer, long long int denom);

#endif
