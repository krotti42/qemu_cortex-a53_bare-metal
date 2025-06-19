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

#include <libkern.h>

#include <stdio.h>
#include <string.h>

#include <dev/dev_init.h>
#include <dev/serial/pl011_uart.h>

extern void kern_intr_init(void);

void kern_main(void)
{

    libkern_init();
    dev_init();
    kern_intr_init();
    pl011_puts("QEMU Cortex-A53 (ARMv8-A) bare-metal example\r\n");

    while (1)
        ;

    libkern_fini();
}
