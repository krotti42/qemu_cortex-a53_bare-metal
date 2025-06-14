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

#ifndef LIBK_STRING_H
#define LIBK_STRING_H

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef LIBK_SIZE_T
#define LIBK_SIZE_T
typedef unsigned long int size_t;
#endif

/* 
 * Copying functions 
 */
extern void *memcpy(void * __restrict dst, const void * __restrict src, size_t num);
extern void *memmove(void *dst, const void *src, size_t num);
extern char *strcpy(char * __restrict dst, const char * __restrict src);
extern char *strncpy(char * __restrict dst, const char * __restrict src, size_t num);

/* 
 * Concatenation functions 
 */
extern char *strcat(char * __restrict dst, const char * __restrict src);
extern char *strncat(char * __restrict dst, const char * __restrict src, size_t num);

/* 
 * Comparsion functions 
 */
extern int memcmp(const void *ptr1, const void *ptr2, size_t num);
extern int strcmp(const char *str1, const char *str2);
extern int strncmp(const char *str1, const char *str2, size_t num);

/* 
 * Search functions 
 */
extern void *memchr(const void *ptr, int val, size_t num);
extern char *strchr(const char *str, int val);
extern size_t strcspn(const char *str1, const char *str2);
extern char *strpbrk(const char *str1, const char *str2);
extern char *strrchr(const char *str, int val);
extern size_t strspn(const char *str1, const char *str2);
extern char *strstr(const char *str1, const char *str2);
extern char *strtok(char *str, const char *sep);

/* 
 * Miscellaneous functions 
 */
extern void *memset(void *ptr, int val, size_t num);
extern size_t strlen(const char *str);

#endif
