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

#define UART1_CLOCK             24000000        /* 24MHz clock */

#define UART1_BASE              0xFFFF000009000000UL

struct regs_pl011_uart {
    volatile unsigned int DR;               /* Data Register */
    volatile unsigned int RSR_ECR;          /* Receive Status Register/Error Clear Register */
    volatile unsigned int res0[4];          /* Reserved */
    volatile unsigned int FR;               /* Flag Register */
    volatile unsigned int res1;             /* Reserved */
    volatile unsigned int ILPR;             /* IrDA Low-Power Counter Register */
    volatile unsigned int IBDR;             /* Integer Baud Rate Register */
    volatile unsigned int FBDR;             /* Fractional Baud Rate Register */
    volatile unsigned int LCR_H;            /* Line Control Register */
    volatile unsigned int CR;               /* Control Register */
    volatile unsigned int IFLS;             /* Interrupt FIFO Level Select Register */
    volatile unsigned int IMSC;             /* Interrupt Mask Set/Clear Register */
    volatile unsigned int RIS;              /* Raw Interrupt Status Register */
    volatile unsigned int MIS;              /* Masked Interrupt Status Register */
    volatile unsigned int ICR;              /* Interrupt Clear Register */
    volatile unsigned int DMACR;            /* DMA Control Register */
    volatile unsigned int res2[998];        /* Reserved */
    volatile unsigned int PeriphID0;        /* Peripheral Identification Register 0 */
    volatile unsigned int PeriphID1;        /* Peripheral Identification Register 1 */
    volatile unsigned int PeriphID2;        /* Peripheral Identification Register 2 */
    volatile unsigned int PeriphID3;        /* Peripheral Identification Register 3 */
    volatile unsigned int PCellID0;         /* PrimeCell Identification Register 0 */
    volatile unsigned int PCellID1;         /* PrimeCell Identification Register 1 */
    volatile unsigned int PCellID2;         /* PrimeCell Identification Register 2 */
    volatile unsigned int PCellID3;         /* PrimeCell Identification Register 3 */
};

#define UART1                       ((struct regs_pl011_uart *) UART1_BASE)

#define UART1_CR_UARTEN             (1U << 0)
#define UART1_CR_TXE                (1U << 8)
#define UART1_CR_RXE                (1U << 9)

#define UART1_FR_TXFF               (1U << 5)
#define UART1_FR_BUSY               (1U << 3)

void pl011_init(void)
{
    unsigned int div = 4 * UART1_CLOCK / 115200;
    unsigned int fractional = div & 0x3f;
    unsigned int integer = (div >> 6) & 0xffff;

    UART1->CR &= ~(UART1_CR_UARTEN);

    while (UART1->FR & UART1_FR_BUSY)
        ;

    UART1->IBDR = integer;
    UART1->FBDR = fractional;
    UART1->IMSC = 0x7ff;
    UART1->DMACR = 0;
    UART1->LCR_H = 0x70;
    UART1->CR |= UART1_CR_TXE;          /* Enable transmitter */
    UART1->CR |= UART1_CR_UARTEN;       /* Enable UART */
}

void pl011_putc(const char c)
{
    while (UART1->FR & UART1_FR_TXFF)
        ;

    UART1->DR = (unsigned int) c;
}

void pl011_puts(const char *s)
{
    char *p = (char *) s;

    while (*p != '\0') {
        pl011_putc(*p);
        p++;
    }
}
