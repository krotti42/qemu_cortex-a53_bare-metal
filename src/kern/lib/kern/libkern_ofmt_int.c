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

#include <_libkern.h>

/* Format integer (char) */
int _libkern_ofmt_intc(struct _libkern_ofmt *fmt, const char val, int width, char *out)
{
    unsigned char tmp = 0;
    unsigned char rem_a = 0;
    unsigned char rem_b = 0;
    unsigned char shift = 0x80;
    unsigned char nib;
    size_t r_cnt = 0;
    size_t o_cnt = 0;
    size_t i, j, k;
    int sign = 0;
    
    if (fmt->f_itype != FMT_ITYPE_UCHAR) {
        if (val & 0x80) {
            tmp = ~val;
            tmp++;
            sign = 1;
        } else
            tmp = val;
    } else {
        tmp = val;
    }
    
    /* Analyze */
    switch (fmt->f_otype) {
        case FMT_OTYPE_DECIMAL:
            if (tmp == 0) {
                r_cnt++;
            } else {
                while (tmp != 0) {
                    tmp = tmp / 10;
                    r_cnt++;
                }
            }
            
            o_cnt = r_cnt;
            
            if (sign)
                o_cnt++;
            else {
                if (fmt->f_sign == FMT_SIGN_PLUS)
                    o_cnt++;
                else if (fmt->f_sign == FMT_SIGN_BLANK)
                    o_cnt++;
            }
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_BINARY:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 8;
                
                for (i = 0; i < 8; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 1;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 2;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_OCTAL:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 3;
                
                if (!(val & 0xC0))
                    r_cnt--;
                
                shift = 0x38;
                
                for (i = 0; i < 2; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 3;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 1;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_HEXADECIMALLOWER:
        case FMT_OTYPE_HEXADECIMALUPPER:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 2;
                
                nib = ((tmp & 0xF0) >> 4);
                
                if (nib == 0)
                    r_cnt--;
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 2;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        default:
            return -1;
    }
    
    if (fmt->f_itype != FMT_ITYPE_UCHAR) {
        if (val & 0x80) {
            tmp = ~val;
            tmp++;
            sign = 1;
        } else
            tmp = val;
    } else {
        tmp = val;
    }
    
    /* Build */
    if (out) {
        switch (fmt->f_otype) {
            case FMT_OTYPE_DECIMAL:
                k = 0;
                out[o_cnt] = '\0';
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (sign) {
                            out[k] = '-';
                            k++;
                        } else {
                            if (fmt->f_sign == FMT_SIGN_PLUS) {
                                out[k] = '+';
                                k++;
                            } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                                out[k] = ' ';
                                k++;
                            }
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (!sign) {
                            if ((fmt->f_sign == FMT_SIGN_PLUS) || 
                                (fmt->f_sign == FMT_SIGN_BLANK)) {
                                if (fmt->f_width > 0) {
                                    for (k = k; k < (o_cnt - r_cnt - 1); k++) {
                                        out[k] = ' ';
                                    }
                                }
                            } else {
                                for (k = k; k < (o_cnt - r_cnt); k++) {
                                    out[k] = ' ';
                                }
                            }
                            
                            if (fmt->f_sign == FMT_SIGN_PLUS) {
                                out[k] = '+';
                                k++;
                            } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                                out[k] = ' ';
                                k++;
                            }
                        } else {
                            for (k = k; k < ((o_cnt - r_cnt) - 1); k++) {
                                out[k] = ' ';
                            }
                            
                            out[k] = '-';
                            k++;
                        }
                    }
                } else {
                    if (sign) {
                        out[k] = '-';
                        k++;
                    } else {
                        if (fmt->f_sign == FMT_SIGN_PLUS) {
                            out[k] = '+';
                            k++;
                        } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                            out[k] = ' ';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                rem_a = tmp;
                
                for (i = r_cnt; i > 0; i--, k++) {
                    tmp = 1;
                    
                    for (j = 0; j < (i - 1); j++)
                        tmp *= 10;
                    
                    rem_b = rem_a / tmp;
                    out[k] = rem_b + '0';
                    rem_a = rem_a - (rem_b * tmp);
                }
                
                break;
            case FMT_OTYPE_BINARY:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0x80;
                shift >>= (8 - r_cnt);
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            out[k] = 'b';
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 2); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            out[k] = 'b';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift)
                        out[k] = '1';
                    else
                        out[k] = '0';
                
                    shift >>= 1;
                    k++;
                }
                
                break;
            case FMT_OTYPE_OCTAL:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0x7;
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 1); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                if (r_cnt == 3) {
                    nib = (tmp & 0xC0) >> 6;
                    out[k] = nib + '0';
                    k++;
                }
                
                if (r_cnt < 2) {
                    nib = (tmp & 0x07);
                    out[k] = nib + '0';
                } else {
                    nib = (tmp & 0x38) >> 3;
                    out[k] = nib + '0';
                    k++;
                    nib = (tmp & 0x07);
                    out[k] = nib + '0';
                }
                
                break;
            case FMT_OTYPE_HEXADECIMALLOWER:
            case FMT_OTYPE_HEXADECIMALUPPER:
                k = 0;
                out[o_cnt] = '\0';
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = 'x';
                            else
                                out[k] = 'X';
                            
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 2); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = 'x';
                            else
                                out[k] = 'X';
                            
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                if (r_cnt > 1) {
                    nib = ((tmp & 0xF0) >> 4);
                    
                    if (nib > 9) {
                        if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                            out[k] = nib + ('a' - 10);
                        else
                            out[k] = nib + ('A' - 10);
                    } else {
                        out[k] = nib + '0';
                    }
                    
                    nib = (tmp & 0x0F);
                    k++;
                    
                    if (nib > 9) {
                        if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                            out[k] = nib + ('a' - 10);
                        else
                            out[k] = nib + ('A' - 10);
                    } else {
                        out[k] = nib + '0';
                    }
                    
                    
                } else {
                    nib = (tmp & 0x0F);
                    
                    if (nib > 9) {
                        if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                            out[k] = nib + ('a' - 10);
                        else
                            out[k] = nib + ('A' - 10);
                    } else {
                        out[k] = nib + '0';
                    }
                }
                
                break;
            default:
                return -1;
        }
    }
    
    return o_cnt;
}

/* Format integer (short) */
int _libkern_ofmt_ints(struct _libkern_ofmt *fmt, const short val, int width, char *out)
{
    unsigned short tmp;
    unsigned short rem_a;
    unsigned short rem_b;
    unsigned short shift = 0x8000;
    unsigned short nib;
    size_t r_cnt = 0;
    size_t o_cnt = 0;
    size_t i, j, k;
    int sign = 0;
    
    if (fmt->f_itype != FMT_ITYPE_USHORT) {
        if (val & 0x80) {
            tmp = ~val;
            tmp++;
            sign = 1;
        } else
            tmp = val;
    } else {
        tmp = val;
    }
    
    /* Analyze */
    switch (fmt->f_otype) {
        case FMT_OTYPE_DECIMAL:
            if (tmp == 0) {
                r_cnt++;
            } else {
                while (tmp != 0) {
                    tmp = tmp / 10;
                    r_cnt++;
                }
            }
            
            o_cnt = r_cnt;
            
            if (sign)
                o_cnt++;
            else {
                if (fmt->f_sign == FMT_SIGN_PLUS)
                    o_cnt++;
                else if (fmt->f_sign == FMT_SIGN_BLANK)
                    o_cnt++;
            }
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_BINARY:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 16;
                
                for (i = 0; i < 16; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 1;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 2;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_OCTAL:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 6;
                
                if (!(val & 0x8000))
                    r_cnt--;
                
                shift = 0x7000;
                
                for (i = 0; i < 5; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 3;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 1;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_HEXADECIMALLOWER:
        case FMT_OTYPE_HEXADECIMALUPPER:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 4;
                
                shift = 0xF000;
                
                for (i = 0; i < 4; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 4;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 2;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        default:
            return -1;
    }
    
    if (fmt->f_itype != FMT_ITYPE_USHORT) {
        if (val & 0x80) {
            tmp = ~val;
            tmp++;
            sign = 1;
        } else
            tmp = val;
    } else {
        tmp = val;
    }
    
    /* Build */
    if (out) {
        switch (fmt->f_otype) {
            case FMT_OTYPE_DECIMAL:
                k = 0;
                out[o_cnt] = '\0';
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (sign) {
                            out[k] = '-';
                            k++;
                        } else {
                            if (fmt->f_sign == FMT_SIGN_PLUS) {
                                out[k] = '+';
                                k++;
                            } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                                out[k] = ' ';
                                k++;
                            }
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (!sign) {
                            if ((fmt->f_sign == FMT_SIGN_PLUS) || 
                                (fmt->f_sign == FMT_SIGN_BLANK)) {
                                if (fmt->f_width > 0) {
                                    for (k = k; k < (o_cnt - r_cnt - 1); k++) {
                                        out[k] = ' ';
                                    }
                                }
                            } else {
                                for (k = k; k < (o_cnt - r_cnt); k++) {
                                    out[k] = ' ';
                                }
                            }
                            
                            if (fmt->f_sign == FMT_SIGN_PLUS) {
                                out[k] = '+';
                                k++;
                            } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                                out[k] = ' ';
                                k++;
                            }
                        } else {
                            for (k = k; k < ((o_cnt - r_cnt) - 1); k++) {
                                out[k] = ' ';
                            }
                            
                            out[k] = '-';
                            k++;
                        }
                    }
                } else {
                    if (sign) {
                        out[k] = '-';
                        k++;
                    } else {
                        if (fmt->f_sign == FMT_SIGN_PLUS) {
                            out[k] = '+';
                            k++;
                        } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                            out[k] = ' ';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                rem_a = tmp;
                
                for (i = r_cnt; i > 0; i--, k++) {
                    tmp = 1;
                    
                    for (j = 0; j < (i - 1); j++)
                        tmp *= 10;
                    
                    rem_b = rem_a / tmp;
                    out[k] = rem_b + '0';
                    rem_a = rem_a - (rem_b * tmp);
                }
                
                break;
            case FMT_OTYPE_BINARY:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0x8000;
                shift >>= (16 - r_cnt);
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            out[k] = 'b';
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 2); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            out[k] = 'b';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift)
                        out[k] = '1';
                    else
                        out[k] = '0';
                
                    shift >>= 1;
                    k++;
                }
                
                break;
            case FMT_OTYPE_OCTAL:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0x7000;
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 1); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                if (r_cnt == 6) {
                    nib = (tmp & 0x8000) >> 15;
                    out[k] = nib + '0';
                    k++;
                }
                
                for (i = (5 - r_cnt); i > 0; i--) {
                    shift >>= 3;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift) {
                        nib = (tmp & shift) >> ((i - 1) * 3);
                        out[k] = nib + '0';
                    }
                    
                    shift >>= 3;
                    k++;
                }
                
                break;
            case FMT_OTYPE_HEXADECIMALLOWER:
            case FMT_OTYPE_HEXADECIMALUPPER:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0xF000;
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = 'x';
                            else
                                out[k] = 'X';
                            
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 2); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = 'x';
                            else
                                out[k] = 'X';
                            
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                for (i = (4 - r_cnt); i > 0; i--) {
                    shift >>= 4;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift) {
                        nib = (tmp & shift) >> ((i - 1) * 4);
                        
                        if (nib > 9) {
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = nib + ('a' - 10);
                            else
                                out[k] = nib + ('A' - 10);
                        } else {
                            out[k] = nib + '0';
                        }
                    }
                    
                    shift >>= 4;
                    k++;
                }
                
                break;
            default:
                return -1;
        }
    }
    
    return o_cnt;
}

/* Format integer */
int _libkern_ofmt_int(struct _libkern_ofmt *fmt, const int val, int width, char *out)
{
    unsigned int tmp;
    unsigned int rem_a;
    unsigned int rem_b;
    unsigned int shift = 0x80000000;
    unsigned int nib;
    size_t r_cnt = 0;
    size_t o_cnt = 0;
    size_t i, j, k;
    int sign = 0;
    
    if (fmt->f_itype != FMT_ITYPE_UINT) {
        if (val & 0x80) {
            tmp = ~val;
            tmp++;
            sign = 1;
        } else
            tmp = val;
    } else {
        tmp = val;
    }
    
    /* Analyze */
    switch (fmt->f_otype) {
        case FMT_OTYPE_DECIMAL:
            if (tmp == 0) {
                r_cnt++;
            } else {
                while (tmp != 0) {
                    tmp = tmp / 10;
                    r_cnt++;
                }
            }
            
            o_cnt = r_cnt;
            
            if (sign)
                o_cnt++;
            else {
                if (fmt->f_sign == FMT_SIGN_PLUS)
                    o_cnt++;
                else if (fmt->f_sign == FMT_SIGN_BLANK)
                    o_cnt++;
            }
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_BINARY:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 32;
                
                for (i = 0; i < 32; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 1;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 2;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
               o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_OCTAL:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 11;
                
                if (!(val & 0xC0000000))
                    r_cnt--;
                
                shift = 0x38000000;
                
                for (i = 0; i < 10; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 3;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 1;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
               o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_HEXADECIMALLOWER:
        case FMT_OTYPE_HEXADECIMALUPPER:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 8;
                
                shift = 0xF0000000;
                
                for (i = 0; i < 8; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 4;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 2;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        default:
            return -1;
    }
    
    if (fmt->f_itype != FMT_ITYPE_UINT) {
        if (val & 0x80) {
            tmp = ~val;
            tmp++;
            sign = 1;
        } else
            tmp = val;
    } else {
        tmp = val;
    }
    
    /* Build */
    if (out) {
        switch (fmt->f_otype) {
            case FMT_OTYPE_DECIMAL:
                k = 0;
                out[o_cnt] = '\0';
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (sign) {
                            out[k] = '-';
                            k++;
                        } else {
                            if (fmt->f_sign == FMT_SIGN_PLUS) {
                                out[k] = '+';
                                k++;
                            } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                                out[k] = ' ';
                                k++;
                            }
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (!sign) {
                            if ((fmt->f_sign == FMT_SIGN_PLUS) || 
                                (fmt->f_sign == FMT_SIGN_BLANK)) {
                                if (fmt->f_width > 0) {
                                    for (k = k; k < (o_cnt - r_cnt - 1); k++) {
                                        out[k] = ' ';
                                    }
                                }
                            } else {
                                for (k = k; k < (o_cnt - r_cnt); k++) {
                                    out[k] = ' ';
                                }
                            }
                            
                            if (fmt->f_sign == FMT_SIGN_PLUS) {
                                out[k] = '+';
                                k++;
                            } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                                out[k] = ' ';
                                k++;
                            }
                        } else {
                            for (k = k; k < ((o_cnt - r_cnt) - 1); k++) {
                                out[k] = ' ';
                            }
                            
                            out[k] = '-';
                            k++;
                        }
                    }
                } else {
                    if (sign) {
                        out[k] = '-';
                        k++;
                    } else {
                        if (fmt->f_sign == FMT_SIGN_PLUS) {
                            out[k] = '+';
                            k++;
                        } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                            out[k] = ' ';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                rem_a = tmp;
                
                for (i = r_cnt; i > 0; i--, k++) {
                    tmp = 1;
                    
                    for (j = 0; j < (i - 1); j++)
                        tmp *= 10;
                    
                    rem_b = rem_a / tmp;
                    out[k] = rem_b + '0';
                    rem_a = rem_a - (rem_b * tmp);
                }
                
                break;
            case FMT_OTYPE_BINARY:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0x80000000;
                shift >>= (32 - r_cnt);
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            out[k] = 'b';
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 2); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            out[k] = 'b';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift)
                        out[k] = '1';
                    else
                        out[k] = '0';
                
                    shift >>= 1;
                    k++;
                }
                
                break;
            case FMT_OTYPE_OCTAL:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0x38000000;
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 1); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                if (r_cnt == 11) {
                    nib = (tmp & 0xC0000000) >> 30;
                    out[k] = nib + '0';
                    k++;
                }
                
                for (i = (10 - r_cnt); i > 0; i--) {
                    shift >>= 3;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift) {
                        nib = (tmp & shift) >> ((i - 1) * 3);
                        out[k] = nib + '0';
                    }
                    
                    shift >>= 3;
                    k++;
                }
                
                break;
            case FMT_OTYPE_HEXADECIMALLOWER:
            case FMT_OTYPE_HEXADECIMALUPPER:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0xF0000000;
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = 'x';
                            else
                                out[k] = 'X';
                            
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 2); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = 'x';
                            else
                                out[k] = 'X';
                            
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                for (i = (8 - r_cnt); i > 0; i--) {
                    shift >>= 4;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift) {
                        nib = (tmp & shift) >> ((i - 1) * 4);
                        
                        if (nib > 9) {
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = nib + ('a' - 10);
                            else
                                out[k] = nib + ('A' - 10);
                        } else {
                            out[k] = nib + '0';
                        }
                    }
                    
                    shift >>= 4;
                    k++;
                }
                
                break;
            default:
                return -1;
        }
    }
    
    return o_cnt;
}

/* Format integer (long integer) */
int _libkern_ofmt_intl(struct _libkern_ofmt *fmt, const long int val, int width, char *out)
{
    unsigned long int tmp;
    unsigned long int rem_a;
    unsigned long int rem_b;
    unsigned long int shift = 0x8000000000000000UL;
    unsigned long int nib;
    size_t r_cnt = 0;
    size_t o_cnt = 0;
    size_t i, j, k;
    int sign = 0;
    
    if (fmt->f_itype != FMT_ITYPE_ULONGINT) {
        if (val & 0x80) {
            tmp = ~val;
            tmp++;
            sign = 1;
        } else
            tmp = val;
    } else {
        tmp = val;
    }
    
    /* Analyze */
    switch (fmt->f_otype) {
        case FMT_OTYPE_DECIMAL:
            if (tmp == 0) {
                r_cnt++;
            } else {
                while (tmp != 0) {
                    tmp = tmp / 10;
                    r_cnt++;
                }
            }
            
            o_cnt = r_cnt;
            
            if (sign)
                o_cnt++;
            else {
                if (fmt->f_sign == FMT_SIGN_PLUS)
                    o_cnt++;
                else if (fmt->f_sign == FMT_SIGN_BLANK)
                    o_cnt++;
            }
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_BINARY:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 64;
                
                for (i = 0; i < 64; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 1;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 2;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_OCTAL:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 22;
                
                if (!(val & 0x8000000000000000UL))
                    r_cnt--;
                
                shift = 0x7000000000000000UL;
                
                for (i = 0; i < 21; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 3;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 1;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        case FMT_OTYPE_HEXADECIMALLOWER:
        case FMT_OTYPE_HEXADECIMALUPPER:
            if (val == 0) {
                r_cnt = 1;
            } else {
                r_cnt = 16;
                
                shift = 0xF000000000000000UL;
                
                for (i = 0; i < 16; i++) {
                    if (!(val & shift)) {
                        r_cnt--;
                    } else
                        break;
                    
                    shift >>= 4;
                }
            }
            
            o_cnt = r_cnt;
            
            if (fmt->f_prefix)
                o_cnt += 2;
            
            if (fmt->f_widtharg) {
                fmt->f_width = width;
            }
            
            if (fmt->f_width > o_cnt) {
                o_cnt = fmt->f_width;
            }
            
            break;
        default:
            return -1;
    }
    
    if (fmt->f_itype != FMT_ITYPE_ULONGINT) {
        if (val & 0x80) {
            tmp = ~val;
            tmp++;
            sign = 1;
        } else
            tmp = val;
    } else {
        tmp = val;
    }
    
    /* Build */
    if (out) {
        switch (fmt->f_otype) {
            case FMT_OTYPE_DECIMAL:
                k = 0;
                out[o_cnt] = '\0';
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (sign) {
                            out[k] = '-';
                            k++;
                        } else {
                            if (fmt->f_sign == FMT_SIGN_PLUS) {
                                out[k] = '+';
                                k++;
                            } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                                out[k] = ' ';
                                k++;
                            }
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (!sign) {
                            if ((fmt->f_sign == FMT_SIGN_PLUS) || 
                                (fmt->f_sign == FMT_SIGN_BLANK)) {
                                if (fmt->f_width > 0) {
                                    for (k = k; k < (o_cnt - r_cnt - 1); k++) {
                                        out[k] = ' ';
                                    }
                                }
                            } else {
                                for (k = k; k < (o_cnt - r_cnt); k++) {
                                    out[k] = ' ';
                                }
                            }
                            
                            if (fmt->f_sign == FMT_SIGN_PLUS) {
                                out[k] = '+';
                                k++;
                            } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                                out[k] = ' ';
                                k++;
                            }
                        } else {
                            for (k = k; k < ((o_cnt - r_cnt) - 1); k++) {
                                out[k] = ' ';
                            }
                            
                            out[k] = '-';
                            k++;
                        }
                    }
                } else {
                    if (sign) {
                        out[k] = '-';
                        k++;
                    } else {
                        if (fmt->f_sign == FMT_SIGN_PLUS) {
                            out[k] = '+';
                            k++;
                        } else if (fmt->f_sign == FMT_SIGN_BLANK) {
                            out[k] = ' ';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                rem_a = tmp;
                
                for (i = r_cnt; i > 0; i--, k++) {
                    tmp = 1;
                    
                    for (j = 0; j < (i - 1); j++)
                        tmp *= 10;
                    
                    rem_b = rem_a / tmp;
                    out[k] = rem_b + '0';
                    rem_a = rem_a - (rem_b * tmp);
                }
                
                break;
            case FMT_OTYPE_BINARY:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0x8000000000000000UL;
                shift >>= (64 - r_cnt);
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            out[k] = 'b';
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 2); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            out[k] = 'b';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift)
                        out[k] = '1';
                    else
                        out[k] = '0';
                
                    shift >>= 1;
                    k++;
                }
                
                break;
            case FMT_OTYPE_OCTAL:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0x7000000000000000UL;
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 1); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                if (r_cnt == 22) {
                    nib = (tmp & 0x8000000000000000UL) >> 63;
                    out[k] = nib + '0';
                    k++;
                }
                
                for (i = (21 - r_cnt); i > 0; i--) {
                    shift >>= 3;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift) {
                        nib = (tmp & shift) >> ((i - 1) * 3);
                        out[k] = nib + '0';
                    }
                    
                    shift >>= 3;
                    k++;
                }
                
                break;
            case FMT_OTYPE_HEXADECIMALLOWER:
            case FMT_OTYPE_HEXADECIMALUPPER:
                k = 0;
                out[o_cnt] = '\0';
                shift = 0xF000000000000000UL;
                
                if (o_cnt > r_cnt) {
                    if (fmt->f_padwzero) {
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = 'x';
                            else
                                out[k] = 'X';
                            
                            k++;
                        }
                        
                        for (k = k; k < (o_cnt - r_cnt); k++) {
                            out[k] = '0';
                        }
                    } else {
                        if (fmt->f_prefix)
                            for (k = k; k < (o_cnt - r_cnt - 2); k++) {
                                out[k] = ' ';
                            }
                        else
                            for (k = k; k < (o_cnt - r_cnt); k++) {
                                out[k] = ' ';
                            }
                        
                        if (fmt->f_prefix) {
                            out[k] = '0';
                            k++;
                            
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = 'x';
                            else
                                out[k] = 'X';
                            
                            k++;
                        }
                    }
                }
                
                if (tmp == 0) {
                    out[k] = '0';
                    break;
                }
                
                for (i = (16 - r_cnt); i > 0; i--) {
                    shift >>= 4;
                }
                
                for (i = r_cnt; i > 0; i--) {
                    if (val & shift) {
                        nib = (tmp & shift) >> ((i - 1) * 4);
                        
                        if (nib > 9) {
                            if (fmt->f_otype == FMT_OTYPE_HEXADECIMALLOWER)
                                out[k] = nib + ('a' - 10);
                            else
                                out[k] = nib + ('A' - 10);
                        } else {
                            out[k] = nib + '0';
                        }
                    }
                    
                    shift >>= 4;
                    k++;
                }
                
                break;
            default:
                return -1;
        }
    }
    
    return o_cnt;
}
