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

#ifndef __LIBK_H
#define __LIBK_H

#include <k/stdlib.h>

enum _libk_ofmt_itype_e {
    FMT_ITYPE_CHAR,
    FMT_ITYPE_UCHAR,
    FMT_ITYPE_SHORT,
    FMT_ITYPE_USHORT,
    FMT_ITYPE_INT,
    FMT_ITYPE_UINT,
    FMT_ITYPE_LONGINT,
    FMT_ITYPE_ULONGINT,
    FMT_ITYPE_LONGLONGINT,
    FMT_ITYPE_ULONGLONGINT,
    FMT_ITYPE_POINTER,
};

enum _libk_ofmt_otype_e {
    FMT_OTYPE_BINARY,
    FMT_OTYPE_OCTAL,
    FMT_OTYPE_DECIMAL,
    FMT_OTYPE_HEXADECIMALLOWER,
    FMT_OTYPE_HEXADECIMALUPPER,
    FMT_OTYPE_CHAR,
    FMT_OTYPE_STRING,
    FMT_OTYPE_POINTER,
    FMT_OTYPE_LENGTH,
    FMT_OTYPE_PERCENTAGE,
};

enum _libk_ofmt_justify_e {
    FMT_JUSTIFY_RIGHT,
    FMT_JUSTIFY_LEFT
};

enum _libk_ofmt_sign_e {
    FMT_SIGN_DEFAULT,
    FMT_SIGN_PLUS,
    FMT_SIGN_BLANK
};

struct _libk_ofmt {
    int f_itype;
    int f_otype;
    int f_size;
    int f_justify;
    int f_sign;
    int f_prefix;
    int f_padwzero;
    int f_widtharg;
    int f_precisionarg;
    size_t f_width;
    size_t f_precision;
};

extern void _libk_seterrno(int num);
extern int _libk_geterrno(void);

extern void _libk_malloc_init(void);
extern void *_libk_mem_alloc(size_t size);
extern void _libk_mem_free(void *ptr);
extern size_t _libk_mem_size(void *ptr);

extern void _libk_rand_init(void);
extern unsigned long int _libk_rand_get(void);
extern void _libk_rand_set(unsigned long int seed);

extern int _libk_ofmt_parse(const char *s, struct _libk_ofmt *fmt);
extern int _libk_ofmt_str(struct _libk_ofmt *fmt, const char *val, int width, char *out);
extern int _libk_ofmt_chr(struct _libk_ofmt *fmt, const char val, int width, char *out);
extern int _libk_ofmt_int(struct _libk_ofmt *fmt, const int val, int width, char *out);
extern int _libk_ofmt_intc(struct _libk_ofmt *fmt, const char val, int width, char *out);
extern int _libk_ofmt_ints(struct _libk_ofmt *fmt, const short val, int width, char *out);
extern int _libk_ofmt_intl(struct _libk_ofmt *fmt, const long int val, int width, char *out);

#endif
