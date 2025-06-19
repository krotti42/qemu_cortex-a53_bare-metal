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

#ifndef _KERN_INTR_H
#define _KERN_INTR_H

/**
 * Saved registers from ISR for AArch64
 */
struct _isr_regs_aarch64 {
    unsigned long int esr;
    unsigned long int far;
    unsigned long int elr;
    unsigned long int spsr;
    unsigned long int sp;
    unsigned long int x0;
    unsigned long int x1;
    unsigned long int x2;
    unsigned long int x3;
    unsigned long int x4;
    unsigned long int x5;
    unsigned long int x6;
    unsigned long int x7;
    unsigned long int x8;
    unsigned long int x9;
    unsigned long int x10;
    unsigned long int x11;
    unsigned long int x12;
    unsigned long int x13;
    unsigned long int x14;
    unsigned long int x15;
    unsigned long int x16;
    unsigned long int x17;
    unsigned long int x18;
    unsigned long int x19;
    unsigned long int x20;
    unsigned long int x21;
    unsigned long int x22;
    unsigned long int x23;
    unsigned long int x24;
    unsigned long int x25;
    unsigned long int x26;
    unsigned long int x27;
    unsigned long int x28;
    unsigned long int x29;
    unsigned long int x30;
};

struct _ret_regs_aarch64 {
    unsigned long int elr;
    unsigned long int spsr;
    unsigned long int sp;
};

struct _isr_regs_aarch32 {
    unsigned long int esr;
    unsigned long int far;
    unsigned long int elr;
    unsigned long int spsr;
    unsigned long int res0;
    unsigned long int sp;
    unsigned int res1;
    unsigned int w0;
    unsigned int w1;
    unsigned int w2;
    unsigned int w3;
    unsigned int w4;
    unsigned int w5;
    unsigned int w6;
    unsigned int w7;
    unsigned int w8;
    unsigned int w9;
    unsigned int w10;
    unsigned int w11;
    unsigned int w12;
    unsigned int w13;
    unsigned int w14;
    unsigned int w15;
    unsigned int w16;
    unsigned int w17;
    unsigned int w18;
    unsigned int w19;
    unsigned int w20;
    unsigned int w21;
    unsigned int w22;
    unsigned int w23;
    unsigned int w24;
    unsigned int w25;
    unsigned int w26;
    unsigned int w27;
    unsigned int w28;
    unsigned int w29;
    unsigned int w30;
};

struct _ret_regs_aarch32 {
    unsigned long int elr;
    unsigned long int spsr;
    unsigned long int sp;
};

#define INTR_SYNC           1
#define INTR_IRQ            2
#define INTR_FIQ            3
#define INTR_SERR           4

#endif
