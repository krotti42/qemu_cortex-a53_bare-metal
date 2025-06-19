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

#define GICD_BASE               0xFFFF000008000000UL
#define GICC_BASE               0xFFFF000008010000UL

#define GIC_SGI_MAX             16
#define GIC_PPI_MAX             16
#define GIC_SPI_MAX             988

struct regs_gicv2_distributor {
    volatile unsigned int CTLR;                 /* Distributor Control Register */
    volatile unsigned int TYPER;                /* Interrupt Controller Type Register */
    volatile unsigned int IIDR;                 /* Distributor Implementer Identification Register */
    unsigned int res1[29];
    volatile unsigned int IGROUPR[16];          /* Interrupt Group Registers */
    unsigned int res2[16];
    volatile unsigned int ISENABLER[16];        /* Interrupt Set-Enable Registers */
    unsigned int res3[16];
    volatile unsigned int ICENABLER[16];        /* Interrupt Clear-Enable Registers */
    unsigned int res4[16];
    volatile unsigned int ISPENDR[16];          /* Interrupt Set-Pending Registers */
    unsigned int res5[16];
    volatile unsigned int ICPENDR[16];          /* Interrupt Clear-Pending Registers */
    unsigned int res6[16];
    volatile unsigned int ISACTIVER[16];        /* Interrupt Set-Active Registers */
    unsigned int res7[16];
    volatile unsigned int ICACTIVER[16];        /* Interrupt Clear-Active Registers */
    unsigned int res8[16];
    volatile unsigned int IPRIORITYR[128];      /* Interrupt Priority Registers */
    unsigned int res9[128];
    volatile unsigned int ITARGETSR[128];       /* Interrupt Processor Targets Registers */
    unsigned int res10[128];
    volatile unsigned int ICFGR[32];            /* Interrupt Configuration Registers */
    unsigned int res11[32];
    volatile unsigned int PPISR;                /* Private Peripheral Interrupt Status Register */
    volatile unsigned int SPISR[15];            /* Shared Peripheral Interrupt Status Registers */
    unsigned int res12[112];
    volatile unsigned int SGIR;                 /* Software Generated Interrupt Register */
    unsigned int res13[3];
    volatile unsigned int CPENDSGIR[4];         /* SGI Clear-Pending Registers */
    volatile unsigned int SPENDSGIR[4];         /* SGI Set-Pending Registers */
    unsigned int res14[40];
    volatile unsigned int PIDR4;                /* Peripheral ID 4 Register */
    volatile unsigned int PIDR5;                /* Peripheral ID 5 Register */
    volatile unsigned int PIDR6;                /* Peripheral ID 6 Register */
    volatile unsigned int PIDR7;                /* Peripheral ID 7 Register */
    volatile unsigned int PIDR0;                /* Peripheral ID 0 Register */
    volatile unsigned int PIDR1;                /* Peripheral ID 1 Register */
    volatile unsigned int PIDR2;                /* Peripheral ID 2 Register */
    volatile unsigned int PIDR3;                /* Peripheral ID 3 Register */
    volatile unsigned int CIDR0;                /* Component ID 0 Register */
    volatile unsigned int CIDR1;                /* Component ID 1 Register */
    volatile unsigned int CIDR2;                /* Component ID 2 Register */
    volatile unsigned int CIDR3;                /* Component ID 3 Register */
};

struct regs_gicv2_cpu {
    volatile unsigned int CTLR;                 /* CPU Interface Control Register */
    volatile unsigned int PMR;                  /* Interrupt Priority Mask Register */
    volatile unsigned int BPR;                  /* Binary Point Register */
    volatile unsigned int IAR;                  /* Interrupt Acknowledge Register */
    volatile unsigned int EOIR;                 /* End of Interrupt Register */
    volatile unsigned int RPR;                  /* Running Priority Register */
    volatile unsigned int HPPIR;                /* Highest Priority Pending Interrupt Register */
    volatile unsigned int ABPR;                 /* Aliased Binary Point Register */
    volatile unsigned int AIAR;                 /* Aliased Interrupt Acknowledge Register */
    volatile unsigned int AEOIR;                /* Aliased End of Interrupt Register  */
    volatile unsigned int AHPPIR;               /* Aliased Highest Priority Pending Interrupt Register */
    unsigned int res15[40];
    volatile unsigned int APR0;                 /* Active Priority Register */
    unsigned int res16[3];
    volatile unsigned int NSAPR0;               /* Non-Secure Active Priority Register */
    unsigned int res17[6];
    volatile unsigned int IIDR;                 /* CPU Interface Identification Register */
    unsigned int res18[960];
    volatile unsigned int DIR;                  /* Deactivate Interrupt Register */
};

#define GICD                        ((struct regs_gicv2_distributor *) GICD_BASE)
#define GICC                        ((struct regs_gicv2_cpu *) GICC_BASE)

void gicv2_irq_clear(int nr)
{
    int off;
    int pos;

    off = nr / 32;
    pos = nr % 32;

    GICD->ICPENDR[off] |= (1 << pos);
    GICC->EOIR = (nr & 0x3FF);
}

void gicv2_irq_enable(int nr)
{
    int off;
    int pos;

    off = nr / 32;
    pos = nr % 32;

    GICD->ISENABLER[off] |= (1 << pos);
}

void gicv2_init(void)
{
    GICD->CTLR |= (1 << 0);
    GICC->CTLR |= (1 << 0);
    GICC->PMR = 0xFF;
}

int gicv2_get_irq(void)
{
    int ret;
    ret = (GICC->IAR & 0x3FF);

    return ret;
}


