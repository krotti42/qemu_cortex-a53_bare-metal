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

#ifndef _LIBKERN_STDDEF_H
#define _LIBKERN_STDDEF_H

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef _LIBKERN_SIZE_T
#define _LIBKERN_SIZE_T
typedef unsigned long int size_t;
#endif

#ifndef _LIBKERN_PTRDIFF_T
#define _LIBKERN_PTRDIFF_T
typedef long int *ptrdiff_t;
#endif

#ifndef _LIBKERN_SSIZE_T
#define _LIBKERN_SSIZE_T
typedef long int ssize_t;
#endif

#ifndef _LIBKERN_ADDR_T
#define _LIBKERN_ADDR_T
typedef unsigned long int addr_t;
#endif

#ifndef _LIBKERN_OFF_T
#define _LIBKERN_OFF_T
typedef unsigned long int off_t;
#endif

#endif
