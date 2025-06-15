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

extern unsigned long int _preinit_array_s;
extern unsigned long int _preinit_array_e;
extern unsigned long int _init_array_s;
extern unsigned long int _init_array_e;

void _init(void)
{
    unsigned long int a;
    void (*f)(void);
    
    for (a = _preinit_array_s; a != _preinit_array_e; a++) {
        f = (void (*)(void)) a;
        (*f)();
    }

    for (a = _preinit_array_s; a != _preinit_array_e; a++) {
        f = (void (*)(void)) a;
        (*f)();
    }
}

unsigned long int _preinit_array_s __attribute__ ((used,
                                                   section(".preinit_array"),
                                                   aligned(sizeof(unsigned long int))));
unsigned long int _preinit_array_e __attribute__ ((used,
                                                   section(".preinit_array"),
                                                   aligned(sizeof(unsigned long int))));
unsigned long int _init_array_s __attribute__ ((used,
                                                section(".init_array"),
                                                aligned(sizeof(unsigned long int))));
unsigned long int _init_array_e __attribute__ ((used,
                                                section(".init_array"),
                                                aligned(sizeof(unsigned long int))));
