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

/**
 * Kernel linker script
 */

ENTRY(_lo_start)

MEMORY {
    RAM_LOCORE (rwx) : ORIGIN = 0x0000000041000000, LENGTH = 64M
    RAM_LOKERN (rwx) : ORIGIN = 0x0000000041200000, LENGTH = 128M
    RAM_HIKERN (rwx) : ORIGIN = 0xFFFF000041200000, LENGTH = 128M
}

STACK_SIZE_KERN = 16K;      /* Kernel stack size */

SECTIONS {
    .text.locore : ALIGN(0x1000) {
        *(.text.locore*)
    } > RAM_LOCORE

    .stack.locore (NOLOAD): ALIGN(0x1000) {
        _stack_lo_s = .;
        . = . + STACK_SIZE_KERN;
        _stack_lo_e = .;
    } > RAM_LOCORE

    .tlb (NOLOAD): ALIGN(0x1000) {
        _tlb_s = .;
        *(.tlb)
        _tlb_e = .;
    } > RAM_LOCORE

    .text : ALIGN(0x1000) {
        _text_s = .;
        _isr_vector_s = .;
        KEEP(*(.isr_vector))
        _isr_vector_e = .;
        *(.text.isr*)
        *(.text)
        *(.text*)
        _text_e = .;
    } > RAM_HIKERN AT > RAM_LOKERN

    .iplt : ALIGN(0x1000) {
        _iplt_s = .;
        *(.iplt)
        _iplt_e = .;
    } > RAM_HIKERN AT > RAM_LOKERN

    .preinit_array : ALIGN(0x1000) {
        _preinit_array_s = .;
        KEEP(*(.preinit_array))
        KEEP(*(.preinit_array*))
        _preinit_array_e = .;
    } > RAM_HIKERN AT > RAM_LOKERN

    .init_array : ALIGN(0x1000) {
        _init_array_s = .;
        KEEP(*(.init_array))
        KEEP(*(.init_array*))
        _init_array_e = .;
    } > RAM_HIKERN AT > RAM_LOKERN

    .fini_array : ALIGN(0x1000) {
        _fini_array_s = .;
        KEEP(*(.fini_array))
        KEEP(*(.fini_array*))
        _fini_array_e = .;
    } > RAM_HIKERN AT > RAM_LOKERN

    .rodata (READONLY) : ALIGN(0x1000) {
        _rodata_s = .;
        *(.rodata)
        *(.rodata*)
        _rodata_e = .;
    } > RAM_HIKERN AT > RAM_LOKERN

    .rela.dyn (READONLY) : ALIGN(0x1000) {
        _rela_dyn_s = .;
        *(.rela.iplt)
        *(.rela.*)
        _rela_dyn_e = .;
    } > RAM_HIKERN AT > RAM_LOKERN

    .data : ALIGN(0x1000) {
        _data_s = .;
        *(.data)
        *(.data*)
        _data_e = .;
    } > RAM_HIKERN AT > RAM_LOKERN

    .igot.plt : ALIGN(0x1000) {
        _igot_plt_s = .;
        *(.igot.plt)
        _igot_plt_e = .;
    } > RAM_HIKERN AT > RAM_LOKERN

    .bss (NOLOAD): ALIGN(0x1000) {
        _bss_s = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        _bss_e = .;
    } > RAM_HIKERN

    .heap (NOLOAD): ALIGN(0x1000) {
        _heap_s = .;
        . = . + (ORIGIN(RAM_HIKERN) + LENGTH(RAM_HIKERN)) - _heap_s - (2 * STACK_SIZE_KERN);
        _heap_e = .;
    } > RAM_HIKERN

    .stack (NOLOAD): ALIGN(0x1000) {
        _stack_el0_s = .;
        . = . + STACK_SIZE_KERN;
        _stack_el0_e = .;
        _stack_el1_s = .;
        . = . + STACK_SIZE_KERN;
        _stack_el1_e = .;
    } > RAM_HIKERN

    /DISCARD/ : {
        *(.note)
        *(.note.*)
    }
}
