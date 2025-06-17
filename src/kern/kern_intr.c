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

#include <dev/serial/pl011_uart.h>

#define ESR_EC_UNKNOWN              0
#define ESR_EC_TRAPWF               1
#define ESR_EC_TRAPMCR0             3
#define ESR_EC_TRAPMCRR             4
#define ESR_EC_TRAPMCR1             5
#define ESR_EC_TRAPLDC              6
#define ESR_EC_TRAPSIMDFP           7
#define ESR_EC_TRAPLDST64           10
#define ESR_EC_TRAPMRRC             12
#define ESR_EC_BRANCH               13
#define ESR_EC_ILLEXEC              14
#define ESR_EC_SVC32                17
#define ESR_EC_SVC64                21
#define ESR_EC_TRAPMSR              24
#define ESR_EC_TRAPSVE              25
#define ESR_EC_POINTER              28
#define ESR_EC_MMULOEL              32
#define ESR_EC_MMU                  33
#define ESR_EC_PCALIGN              34
#define ESR_EC_DATALOEL             36
#define ESR_EC_DATA                 37
#define ESR_EC_SPALIGN              38
#define ESR_EC_FPU32                40
#define ESR_EC_FPU64                44
#define ESR_EC_SERROR               47
#define ESR_EC_BKPLOEL              48
#define ESR_EC_BKP                  49
#define ESR_EC_SWSTEPLOEL           50
#define ESR_EC_SWSTEP               51
#define ESR_EC_WPLOEL               52
#define ESR_EC_WP                   53
#define ESR_EC_BKPT32               56
#define ESR_EC_BRK64                60

void intr_handler_kern_el0_sync(unsigned long int esyn, unsigned long int faddr)
{
    char message[512];

    pl011_puts("EXCEPTION: Synchronous (kernel thread)\r\n");
    memset(message, 0, 512);
    sprintf(message, "Fault address: 0x%016llX\r\n", faddr);
    pl011_puts(message);
    sprintf(message, "Reason (raw) : 0x%016llX\r\n", esyn);
    pl011_puts("PANIC    : loop forever\r\n");

    /**
     * Panic (currently loop forever)
     */
    while (1)
        ;
}

void intr_handler_kern_el0_irq(void)
{
    pl011_puts("IRQ (kernel thread)\r\n");

    /**
     * Panic (currently loop forever)
     */
    while (1)
        ;
}

void intr_handler_kern_el0_fiq(void)
{
    pl011_puts("FIQ (kernel thread)\r\n");

    /**
     * Panic (currently loop forever)
     */
    while (1)
        ;
}

void intr_handler_kern_el0_serr(unsigned long int esyn)
{
    char message[512];

    pl011_puts("EXCEPTION: SError (kernel thread)\r\n");
    memset(message, 0, 512);
    sprintf(message, "Reason (raw) : 0x%016llX\r\n", esyn);
    pl011_puts("PANIC    : loop forever\r\n");

    /**
     * Panic (currently loop forever)
     */
    while (1)
        ;
}

void intr_handler_kern_el1_sync(unsigned long int esyn, unsigned long int faddr)
{
    char message[512];

    pl011_puts("EXCEPTION: Synchronous (kernel handler)\r\n");
    memset(message, 0, 512);
    sprintf(message, "Fault address: 0x%016llX\r\n", faddr);
    pl011_puts(message);
    sprintf(message, "Reason (raw) : 0x%016llX\r\n", esyn);
    pl011_puts("PANIC    : loop forever\r\n");

    /**
     * Panic (currently loop forever)
     */
    while (1)
        ;
}

void intr_handler_kern_el1_irq(void)
{
    pl011_puts("IRQ (kernel handler)\r\n");

    /**
     * Panic (currently loop forever)
     */
    while (1)
        ;
}

void intr_handler_kern_el1_fiq(void)
{
    pl011_puts("FIQ (kernel handler)\r\n");

    /**
     * Panic (currently loop forever)
     */
    while (1)
        ;
}

void intr_handler_kern_el1_serr(unsigned long int esyn)
{

    char message[512];

    pl011_puts("EXCEPTION: SError (kernel handler)\r\n");
    memset(message, 0, 512);
    sprintf(message, "Reason (raw) : 0x%016llX\r\n", esyn);
    pl011_puts("PANIC    : loop forever\r\n");

    /**
     * Panic (currently loop forever)
     */
    while (1)
        ;
}


