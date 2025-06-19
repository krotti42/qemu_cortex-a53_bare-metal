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

#include <stdio.h>
#include <string.h>

#include <kern_intr.h>

#include <dev/serial/pl011_uart.h>

void kern_panic_print64(struct _isr_regs_aarch64 *regs)
{
    char out[512];

    memset(out, 0, 512);
    pl011_puts("-----------------------------------------------------------------\r\n");
    sprintf(out, "SPSR= %016llX\r\n", regs->spsr);
    pl011_puts(out);
    sprintf(out, "ELR = %016llX\r\n", regs->elr);
    pl011_puts(out);
    sprintf(out, "FAR = %016llX\r\n", regs->far);
    pl011_puts(out);
    sprintf(out, "ESR = %016llX\r\n", regs->esr);
    pl011_puts(out);
    pl011_puts("-----------------------------------------------------------------\r\n");
    sprintf(out, "sp = %016llX x0 = %016llX x1 = %016llX\r\n", regs->sp, regs->x0, regs->x1);
    pl011_puts(out);
    sprintf(out, "x2 = %016llX x3 = %016llX x4 = %016llX\r\n", regs->x2, regs->x3, regs->x4);
    pl011_puts(out);
    sprintf(out, "x5 = %016llX x6 = %016llX x7 = %016llX\r\n", regs->x5, regs->x6, regs->x7);
    pl011_puts(out);
    sprintf(out, "x8 = %016llX x9 = %016llX x10= %016llX\r\n", regs->x8, regs->x9, regs->x10);
    pl011_puts(out);
    sprintf(out, "x11= %016llX x12= %016llX x13= %016llX\r\n", regs->x11, regs->x12, regs->x13);
    pl011_puts(out);
    sprintf(out, "x14= %016llX x15= %016llX x16= %016llX\r\n", regs->x14, regs->x15, regs->x16);
    pl011_puts(out);
    sprintf(out, "x17= %016llX x18= %016llX x19= %016llX\r\n", regs->x17, regs->x18, regs->x19);
    pl011_puts(out);
    sprintf(out, "x20= %016llX x21= %016llX x22= %016llX\r\n", regs->x20, regs->x21, regs->x22);
    pl011_puts(out);
    sprintf(out, "x22= %016llX x23= %016llX x24= %016llX\r\n", regs->x22, regs->x23, regs->x24);
    pl011_puts(out);
    sprintf(out, "x25= %016llX x26= %016llX x27= %016llX\r\n", regs->x25, regs->x26, regs->x27);
    pl011_puts(out);
    sprintf(out, "x28= %016llX x29= %016llX x30= %016llX\r\n", regs->x28, regs->x29, regs->x30);
    pl011_puts(out);
    pl011_puts("-----------------------------------------------------------------\r\n");
}

void kern_panic_print32(struct _isr_regs_aarch32 *regs)
{
    char out[512];

    memset(out, 0, 512);
    pl011_puts("-----------------------------------------------------------------\r\n");
    sprintf(out, "SPSR= %016llX\r\n", regs->spsr);
    pl011_puts(out);
    sprintf(out, "ELR = %016llX\r\n", regs->elr);
    pl011_puts(out);
    sprintf(out, "FAR = %016llX\r\n", regs->far);
    pl011_puts(out);
    sprintf(out, "ESR = %016llX\r\n", regs->esr);
    pl011_puts(out);
    pl011_puts("-----------------------------------------------------------------\r\n");
    sprintf(out, "sp = %016llX w0 = %016X w1 = %016X\r\n", regs->sp, regs->w0, regs->w1);
    pl011_puts(out);
    sprintf(out, "w2 = %016X w3 = %016X w4 = %016X\r\n", regs->w2, regs->w3, regs->w4);
    pl011_puts(out);
    sprintf(out, "w5 = %016X w6 = %016X w7 = %016X\r\n", regs->w5, regs->w6, regs->w7);
    pl011_puts(out);
    sprintf(out, "w8 = %016X w9 = %016X w10= %016X\r\n", regs->w8, regs->w9, regs->w10);
    pl011_puts(out);
    sprintf(out, "w11= %016X w12= %016X w13= %016X\r\n", regs->w11, regs->w12, regs->w13);
    pl011_puts(out);
    sprintf(out, "w14= %016X w15= %016X w16= %016X\r\n", regs->w14, regs->w15, regs->w16);
    pl011_puts(out);
    sprintf(out, "w17= %016X w18= %016X w19= %016X\r\n", regs->w17, regs->w18, regs->w19);
    pl011_puts(out);
    sprintf(out, "w20= %016X w21= %016X w22= %016X\r\n", regs->w20, regs->w21, regs->w22);
    pl011_puts(out);
    sprintf(out, "w22= %016X w23= %016X w24= %016X\r\n", regs->w22, regs->w23, regs->w24);
    pl011_puts(out);
    sprintf(out, "w25= %016X w26= %016X w27= %016X\r\n", regs->w25, regs->w26, regs->w27);
    pl011_puts(out);
    sprintf(out, "w28= %016X w29= %016X w30= %016X\r\n", regs->w28, regs->w29, regs->w30);
    pl011_puts(out);
    pl011_puts("-----------------------------------------------------------------\r\n");
}

void kern_panic_thread(struct _isr_regs_aarch64 *regs, int type)
{
    pl011_puts("-----------------------------------------------------------------\r\n");
    pl011_puts("- Kernel thread PANIC                                           -\r\n");
    pl011_puts("-----------------------------------------------------------------\r\n");

    switch (type) {
        case INTR_SYNC:
            pl011_puts("Unhandled Synchronous\r\n");
            break;
        case INTR_IRQ:
            pl011_puts("Unhandled IRQ\r\n");
            break;
        case INTR_FIQ:
            pl011_puts("Unhandled FIQ\r\n");
            break;
        case INTR_SERR:
            pl011_puts("Unhandled SError\r\n");
            break;
        default:
            pl011_puts("UNKNOWN\r\n");
    }

    kern_panic_print64(regs);
    pl011_puts("Stop.\r\n");

    while (1)
        ;
}

void kern_panic_handler(struct _isr_regs_aarch64 *regs, int type)
{
    pl011_puts("-----------------------------------------------------------------\r\n");
    pl011_puts("- Kernel handler PANIC                                          -\r\n");
    pl011_puts("-----------------------------------------------------------------\r\n");

    switch (type) {
        case INTR_SYNC:
            pl011_puts("Unhandled Synchronous\r\n");
            break;
        case INTR_IRQ:
            pl011_puts("Unhandled IRQ\r\n");
            break;
        case INTR_FIQ:
            pl011_puts("Unhandled FIQ\r\n");
            break;
        case INTR_SERR:
            pl011_puts("Unhandled SError\r\n");
            break;
        default:
            pl011_puts("UNKNOWN\r\n");
    }

    kern_panic_print64(regs);
    pl011_puts("Stop.\r\n");

    while (1)
        ;
}

void kern_panic_user64(struct _isr_regs_aarch64 *regs, int type)
{
    pl011_puts("-----------------------------------------------------------------\r\n");
    pl011_puts("- Kernel AArch64 userspace PANIC                                -\r\n");
    pl011_puts("-----------------------------------------------------------------\r\n");

    switch (type) {
        case INTR_SYNC:
            pl011_puts("Unhandled Synchronous\r\n");
            break;
        case INTR_IRQ:
            pl011_puts("Unhandled IRQ\r\n");
            break;
        case INTR_FIQ:
            pl011_puts("Unhandled FIQ\r\n");
            break;
        case INTR_SERR:
            pl011_puts("Unhandled SError\r\n");
            break;
        default:
            pl011_puts("UNKNOWN\r\n");
    }

    kern_panic_print64(regs);
    pl011_puts("Stop.\r\n");

    while (1)
        ;
}

void kern_panic_user32(struct _isr_regs_aarch32 *regs, int type)
{
    pl011_puts("-----------------------------------------------------------------\r\n");
    pl011_puts("- Kernel AArch32 userspace PANIC                                -\r\n");
    pl011_puts("-----------------------------------------------------------------\r\n");

    switch (type) {
        case INTR_SYNC:
            pl011_puts("Unhandled Synchronous\r\n");
            break;
        case INTR_IRQ:
            pl011_puts("Unhandled IRQ\r\n");
            break;
        case INTR_FIQ:
            pl011_puts("Unhandled FIQ\r\n");
            break;
        case INTR_SERR:
            pl011_puts("Unhandled SError\r\n");
            break;
        default:
            pl011_puts("UNKNOWN\r\n");
    }

    kern_panic_print32(regs);
    pl011_puts("Stop.\r\n");

    while (1)
        ;
}
