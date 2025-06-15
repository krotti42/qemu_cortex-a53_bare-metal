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

#ifndef _LIBKERN_CTYPE_H
#define _LIBKERN_CTYPE_H

/**
 * Standard C library character classification functions 
 */

/* Test if *val* is a alphabetic/numeric character */
extern int isalnum(const int val);

/* Test if *val* is a alphabetic character */
extern int isalpha(const int val);

/* Test if *val* is a blank character */
extern int isblank(const int val);

/* Test if *val* is a control character */
extern int iscntrl(const int val);

/* Test if *val* is a digit */
extern int isdigit(const int val);

/* Test if *val* is a graphic character */
extern int isgraph(const int val);

/* Test if *val* is a lower character */
extern int islower(const int val);

/* Test if *val* is a printable character */
extern int isprint(const int val);

/* Test if *val* is a punctuation character */
extern int ispunct(const int val);

/* Test if *val* is a space character */
extern int isspace(const int val);

/* Test if *val* is a upper character */
extern int isupper(const int val);

/* Test if *val* is a hexadecimal digit */
extern int isxdigit(const int val);

/** 
 * Standard C library character case mapping functions 
 */

/* Convert *val* to a lower character */
extern int tolower(const int val);

/* Convert *val* to a upper character */
extern int toupper(const int val);

#endif
