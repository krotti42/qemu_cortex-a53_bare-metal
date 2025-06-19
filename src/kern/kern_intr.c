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

#include <string.h>

#include <kern_intr.h>
#include <kern_panic.h>

#include <dev/serial/pl011_uart.h>
#include <dev/intc/arm_gicv2.h>

extern void intr_disable(void);
extern unsigned long int timer_get_freq(void);
extern void timer_phys_set_compvalue(unsigned long int);
extern void timer_phys_enable();

struct _ret_regs_aarch64 ctx64_ret;
struct _ret_regs_aarch32 ctx32_ret;

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

void kern_intr_init(void)
{
    memset(&ctx64_ret, 0, sizeof(struct _ret_regs_aarch64));
    memset(&ctx32_ret, 0, sizeof(struct _ret_regs_aarch32));
    gicv2_init();
    gicv2_irq_enable(30);
    timer_phys_set_compvalue(timer_get_freq() / 1000);
    timer_phys_enable();
}

struct _ret_regs_aarch64 *intr_handler_kern_sp0_sync(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_thread(p_regs, INTR_SYNC);

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_kern_sp0_irq(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;
    int ret;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    ret = gicv2_get_irq();

    if (ret != 30) {
        intr_disable();
        kern_panic_thread(p_regs, INTR_IRQ);
    } else {
        timer_phys_set_compvalue(timer_get_freq() / 1000);
        gicv2_irq_clear(ret);
    }

    return &ctx64_ret;

}

struct _ret_regs_aarch64 *intr_handler_kern_sp0_fiq(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_thread(p_regs, INTR_FIQ);

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_kern_sp0_serr(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_thread(p_regs, INTR_SERR);

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_kern_sp1_sync(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_handler(p_regs, INTR_SYNC);

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_kern_sp1_irq(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;
    int ret;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    ret = gicv2_get_irq();

    if (ret != 30) {
        intr_disable();
        kern_panic_handler(p_regs, INTR_IRQ);
    } else {
        timer_phys_set_compvalue(timer_get_freq() / 1000);
        gicv2_irq_clear(ret);
    }

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_kern_sp1_fiq(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_handler(p_regs, INTR_FIQ);

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_kern_sp1_serr(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_handler(p_regs, INTR_SERR);

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_user64_sync(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_user64(p_regs, INTR_SYNC);

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_user64_irq(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;
    int ret;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    ret = gicv2_get_irq();

    if (ret != 30) {
        intr_disable();
        kern_panic_user64(p_regs, INTR_IRQ);
    } else {
        timer_phys_set_compvalue(timer_get_freq() / 1000);
        gicv2_irq_clear(ret);
    }

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_user64_fiq(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_user64(p_regs, INTR_FIQ);

    return &ctx64_ret;
}

struct _ret_regs_aarch64 *intr_handler_user64_serr(unsigned long int regs)
{
    struct _isr_regs_aarch64 *p_regs;

    p_regs = (struct _isr_regs_aarch64 *) regs;
    ctx64_ret.elr = p_regs->elr;
    ctx64_ret.sp = p_regs->sp;
    ctx64_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_user64(p_regs, INTR_SERR);

    return &ctx64_ret;
}

struct _ret_regs_aarch32 *intr_handler_user32_sync(unsigned long int regs)
{
    struct _isr_regs_aarch32 *p_regs;

    p_regs = (struct _isr_regs_aarch32 *) regs;
    ctx32_ret.elr = p_regs->elr;
    ctx32_ret.sp = p_regs->sp;
    ctx32_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_user32(p_regs, INTR_SYNC);

    return &ctx32_ret;
}

struct _ret_regs_aarch32 *intr_handler_user32_irq(unsigned long int regs)
{
    struct _isr_regs_aarch32 *p_regs;
    int ret;

    p_regs = (struct _isr_regs_aarch32 *) regs;
    ctx32_ret.elr = p_regs->elr;
    ctx32_ret.sp = p_regs->sp;
    ctx32_ret.spsr = p_regs->spsr;
    ret = gicv2_get_irq();

    if (ret != 30) {
        intr_disable();
        kern_panic_user32(p_regs, INTR_IRQ);
    } else {
        timer_phys_set_compvalue(timer_get_freq() / 1000);
        gicv2_irq_clear(ret);
    }

    return &ctx32_ret;
}

struct _ret_regs_aarch32 *intr_handler_user32_fiq(unsigned long int regs)
{
    struct _isr_regs_aarch32 *p_regs;

    p_regs = (struct _isr_regs_aarch32 *) regs;
    ctx32_ret.elr = p_regs->elr;
    ctx32_ret.sp = p_regs->sp;
    ctx32_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_user32(p_regs, INTR_FIQ);

    return &ctx32_ret;
}

struct _ret_regs_aarch32 *intr_handler_user32_serr(unsigned long int regs)
{
    struct _isr_regs_aarch32 *p_regs;

    p_regs = (struct _isr_regs_aarch32 *) regs;
    ctx32_ret.elr = p_regs->elr;
    ctx32_ret.sp = p_regs->sp;
    ctx32_ret.spsr = p_regs->spsr;
    intr_disable();
    kern_panic_user32(p_regs, INTR_SERR);

    return &ctx32_ret;
}
