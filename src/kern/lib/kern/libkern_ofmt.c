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

#include <ctype.h>
#include <string.h>

#include <_libkern.h>

int _libkern_ofmt_parse(const char *s, struct _libkern_ofmt *fmt)
{
    int i = 0;
    int j;
    int flags_end;
    int minwidth_s = 0;
    int minwidth_e = 0;
    int precision_s = 0;
    int precision_e = 0;
    int length_end, length_size;
    size_t mul = 1;
    
    if (!s)
        return -1;
    
    if (!fmt)
        return -1;
    
    if (s[i] != '%')
        return -1;
    
    /* Parse flags */
    i++;
    fmt->f_justify = FMT_JUSTIFY_RIGHT;
    fmt->f_sign = FMT_SIGN_DEFAULT;
    fmt->f_prefix = 0;
    fmt->f_padwzero = 0;
    
    while (!flags_end) {
        switch (s[i]) {
            case '-':
                fmt->f_justify = FMT_JUSTIFY_LEFT;
                i++;
                break;
            case '+':
                fmt->f_sign = FMT_SIGN_PLUS;
                i++;
                break;
            case ' ':
                fmt->f_sign = FMT_SIGN_BLANK;
                i++;
                break;
            case '#':
                fmt->f_prefix = 1;
                i++;
                break;
            case '0':
                fmt->f_padwzero = 1;
                i++;
                break;
            default:
                flags_end = 1;
        }
    }
    
    /* Parse width */
    fmt->f_widtharg = 0;
    fmt->f_width = 0;
    
    if (s[i] == '*') {
        fmt->f_widtharg = 1;
        i++;
    } else if (isdigit((int) s[i])) {
        minwidth_s = i;
        
        while (isdigit((int) s[i]))
            i++;
        
        minwidth_e = i - 1;
        
        for (j = minwidth_e; j >= minwidth_s; j--) {
            fmt->f_width += (s[j] - '0') * mul;
            mul *= 10;
        }
    }
    
    /* Parse precision */
    fmt->f_precisionarg = 0;
    fmt->f_precision = 0;
    
    if (s[i] == '.') {
        i++;
        
        if (s[i] == '*') {
            fmt->f_precisionarg = 1;
            i++;
        } else {
            precision_s = i;
            
            while (isdigit((int) s[i]))
                i++;
            
            precision_e = i - 1;
            mul = 1;
            
            for (j = precision_e; j >= precision_s; j--) {
                fmt->f_precision += (s[j] - '0') * mul;
                mul *= 10;
            }
        }
    }
    
    /* Parse sub-specifiers (length) */
    length_end = 0;
    length_size = 0;
    
    while (!length_end) {
        switch (s[i]) {
            case 'h':
                length_size--;
                
                if (length_size == -2) {
                    length_end = 1;
                }
                
                i++;
                break;
            case 'l':
                length_size++;
                
                if (length_size == 2) {
                    length_end = 1;
                }
                
                i++;
                break;
            case 'j':       /* Currently not supported */
                break;
            case 'z':       /* Currently not supported */
                break;
            case 't':       /* Currently not supported */
                break;
            case 'L':
                length_size++;
                length_end = 1;
                i++;
                break;
            default:
                length_end = 1;
        }
    }
    
    /* Parse specifiers */
    switch (s[i]) {
        case 'd':
        case 'i': {
            switch (length_size) {
                case -2:
                    fmt->f_itype = FMT_ITYPE_CHAR;
                    break;
                case -1:
                    fmt->f_itype = FMT_ITYPE_SHORT;
                    break;
                case 0:
                    fmt->f_itype = FMT_ITYPE_INT;
                    break;
                case 1:
                    fmt->f_itype = FMT_ITYPE_LONGINT;
                    break;
                case 2:
                    fmt->f_itype = FMT_ITYPE_LONGLONGINT;
                    break;
                default:
                    return -1;
            }
            
            fmt->f_otype = FMT_OTYPE_DECIMAL;
            break;
        }
        case 'u':
            switch (length_size) {
                case -2:
                    fmt->f_itype = FMT_ITYPE_UCHAR;
                    break;
                case -1:
                    fmt->f_itype = FMT_ITYPE_USHORT;
                    break;
                case 0:
                    fmt->f_itype = FMT_ITYPE_UINT;
                    break;
                case 1:
                    fmt->f_itype = FMT_ITYPE_ULONGINT;
                    break;
                case 2:
                    fmt->f_itype = FMT_ITYPE_ULONGLONGINT;
                    break;
                default:
                    return -1;
            }
            
            fmt->f_otype = FMT_OTYPE_DECIMAL;
            break;
        case 'b':
            switch (length_size) {
                case -2:
                    fmt->f_itype = FMT_ITYPE_UCHAR;
                    break;
                case -1:
                    fmt->f_itype = FMT_ITYPE_USHORT;
                    break;
                case 0:
                    fmt->f_itype = FMT_ITYPE_UINT;
                    break;
                case 1:
                    fmt->f_itype = FMT_ITYPE_ULONGINT;
                    break;
                case 2:
                    fmt->f_itype = FMT_ITYPE_ULONGLONGINT;
                    break;
                default:
                    return -1;
            }
            
            fmt->f_otype = FMT_OTYPE_BINARY;
            break;
        case 'o':
            switch (length_size) {
                case -2:
                    fmt->f_itype = FMT_ITYPE_UCHAR;
                    break;
                case -1:
                    fmt->f_itype = FMT_ITYPE_USHORT;
                    break;
                case 0:
                    fmt->f_itype = FMT_ITYPE_UINT;
                    break;
                case 1:
                    fmt->f_itype = FMT_ITYPE_ULONGINT;
                    break;
                case 2:
                    fmt->f_itype = FMT_ITYPE_ULONGLONGINT;
                    break;
                default:
                    return -1;
            }
            
            fmt->f_otype = FMT_OTYPE_OCTAL;
            break;
        case 'x':
            switch (length_size) {
                case -2:
                    fmt->f_itype = FMT_ITYPE_UCHAR;
                    break;
                case -1:
                    fmt->f_itype = FMT_ITYPE_USHORT;
                    break;
                case 0:
                    fmt->f_itype = FMT_ITYPE_UINT;
                    break;
                case 1:
                    fmt->f_itype = FMT_ITYPE_ULONGINT;
                    break;
                case 2:
                    fmt->f_itype = FMT_ITYPE_ULONGLONGINT;
                    break;
                default:
                    return -1;
            }
            
            fmt->f_otype = FMT_OTYPE_HEXADECIMALLOWER;
            break;
        case 'X':
            switch (length_size) {
                case -2:
                    fmt->f_itype = FMT_ITYPE_UCHAR;
                    break;
                case -1:
                    fmt->f_itype = FMT_ITYPE_USHORT;
                    break;
                case 0:
                    fmt->f_itype = FMT_ITYPE_UINT;
                    break;
                case 1:
                    fmt->f_itype = FMT_ITYPE_ULONGINT;
                    break;
                case 2:
                    fmt->f_itype = FMT_ITYPE_ULONGLONGINT;
                    break;
                default:
                    return -1;
            }
            
            fmt->f_otype = FMT_OTYPE_HEXADECIMALUPPER;
            break;
        case 'c':
            fmt->f_otype = FMT_OTYPE_CHAR;
            break;
        case 's':
            fmt->f_otype = FMT_OTYPE_STRING;
            break;
        case 'p':
            fmt->f_otype = FMT_OTYPE_POINTER;
            break;
        case 'n':
            fmt->f_otype = FMT_OTYPE_LENGTH;
            break;
        case '%':
            fmt->f_otype = FMT_OTYPE_PERCENTAGE;
            break;
        default:
            return -1;
    }
    
    i++;
    return i;
}

/* Format string */
int _libkern_ofmt_str(struct _libkern_ofmt *fmt, const char *val, int width, char *out)
{
    size_t r_cnt = 0;
    size_t o_cnt = 0;
    size_t k = 0;
    size_t i = 0;
    
    /* Analyze */
    r_cnt = strlen(val);
    o_cnt = r_cnt;
    
    if (fmt->f_widtharg)
        fmt->f_width = width;
    
    if (fmt->f_width > o_cnt)
        o_cnt = width;
    
    /* Build */
    if (out) {
        out[o_cnt] = '\0';
        
        if (fmt->f_width > 0)
            for (k = k; k < (o_cnt - r_cnt - 1); k++)
                out[k] = ' ';
        
        while (val[i] != '\0') {
            out[k] = val[i];
            k++;
            i++;
        }
    }
    
    return o_cnt;
}

/* Format char */
int _libkern_ofmt_chr(struct _libkern_ofmt *fmt, const char val, int width, char *out)
{
    size_t r_cnt = 0;
    size_t o_cnt = 0;
    size_t k = 0;
    
    /* Analyze */
    r_cnt = 1;
    o_cnt = r_cnt;
    
    if (fmt->f_widtharg)
        fmt->f_width = width;
    
    if (fmt->f_width > o_cnt)
        o_cnt = width;
    
    /* Build */
    if (out) {
        out[o_cnt] = '\0';
        
        if (fmt->f_width > 0)
            for (k = k; k < (o_cnt - r_cnt - 1); k++)
                out[k] = ' ';
        
        out[k] = val;
    }
    
    return o_cnt;
}
