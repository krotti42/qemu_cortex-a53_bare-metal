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

#include <stdarg.h>
#include <stdio.h>

#include <_libkern.h>

int vsprintf(char *str, const char *format, va_list args)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    int width;
    struct _libkern_ofmt fmt;
    
    while (format[k] != '\0') {
        if (format[k] == '%') {
            i = _libkern_ofmt_parse(&format[k], &fmt);
            k += i;
            
            switch (fmt.f_otype) {
                case FMT_OTYPE_DECIMAL:
                {
                    switch (fmt.f_itype) {
                        case FMT_ITYPE_INT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_int(&fmt, va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_int(&fmt, va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_CHAR:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_SHORT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_LONGINT:
                        case FMT_ITYPE_LONGLONGINT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_UINT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_int(&fmt, va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_int(&fmt, va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_UCHAR:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_USHORT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_ULONGINT:
                        case FMT_ITYPE_ULONGLONGINT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        default:
                            return -1;
                    }
                    
                    break;
                }
                case FMT_OTYPE_BINARY:
                {
                    switch (fmt.f_itype) {
                        case FMT_ITYPE_UINT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_int(&fmt, va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_int(&fmt, va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_UCHAR:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_USHORT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_ULONGINT:
                        case FMT_ITYPE_ULONGLONGINT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        default:
                            return -1;
                    }
                    
                    break;
                }
                case FMT_OTYPE_OCTAL:
                {
                    switch (fmt.f_itype) {
                        case FMT_ITYPE_UINT:
                            i = _libkern_ofmt_int(&fmt, va_arg(args, int), 0, &str[j]);
                            j += i;
                            break;
                        case FMT_ITYPE_UCHAR:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_USHORT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_ULONGINT:
                        case FMT_ITYPE_ULONGLONGINT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        default:
                            return -1;
                    }
                    
                    break;
                }
                case FMT_OTYPE_HEXADECIMALLOWER:
                {
                    switch (fmt.f_itype) {
                        case FMT_ITYPE_UINT:
                            i = _libkern_ofmt_int(&fmt, va_arg(args, int), 0, &str[j]);
                            j += i;
                            break;
                        case FMT_ITYPE_UCHAR:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_USHORT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_ULONGINT:
                        case FMT_ITYPE_ULONGLONGINT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        default:
                            return -1;
                    }
                    
                    break;
                }
                case FMT_OTYPE_HEXADECIMALUPPER:
                {
                    switch (fmt.f_itype) {
                        case FMT_ITYPE_UINT:
                            i = _libkern_ofmt_int(&fmt, va_arg(args, int), 0, &str[j]);
                            j += i;
                            break;
                        case FMT_ITYPE_UCHAR:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intc(&fmt, (char) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_USHORT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_ints(&fmt, (short) va_arg(args, int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        case FMT_ITYPE_ULONGINT:
                        case FMT_ITYPE_ULONGLONGINT:
                            if (fmt.f_widtharg) {
                                width = va_arg(args, int);
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), width, &str[j]);
                            } else {
                                i = _libkern_ofmt_intl(&fmt, va_arg(args, long int), 0, &str[j]);
                            }
                            
                            j += i;
                            
                            break;
                        default:
                            return -1;
                    }
                    
                    break;
                }
                case FMT_OTYPE_STRING:
                    if (fmt.f_widtharg) {
                        width = va_arg(args, int);
                        i = _libkern_ofmt_str(&fmt, va_arg(args, char *), width, &str[j]);
                    } else {
                        i = _libkern_ofmt_str(&fmt, va_arg(args, char *), 0, &str[j]);
                    }
                    
                    j += i;
                    
                    break;
                case FMT_OTYPE_CHAR:
                    if (fmt.f_widtharg) {
                        width = va_arg(args, int);
                        i = _libkern_ofmt_chr(&fmt, (char) va_arg(args, int), width, &str[j]);
                    } else {
                        i = _libkern_ofmt_chr(&fmt, (char) va_arg(args, int), 0, &str[j]);
                    }
                    
                    j += i;
                    
                    break;
                case FMT_OTYPE_POINTER:
                    if (fmt.f_widtharg) {
                        width = va_arg(args, int);
                        i = _libkern_ofmt_intl(&fmt, (long int) va_arg(args, void *), width, &str[j]);
                    } else {
                        i = _libkern_ofmt_intl(&fmt, (long int) va_arg(args, void *), 0, &str[j]);
                    }
                    
                    j += i;
                    
                    break;
                case FMT_OTYPE_PERCENTAGE:
                    str[j] = '%';
                    j++;
                    
                    break;
                default:
                    return -1;
            }
            
        } else {
            str[j] = format[k];
            k++;
            j++;
        }
    }
    
    str[j] = '\0';
    
    return j;
}
