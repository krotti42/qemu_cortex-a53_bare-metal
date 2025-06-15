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
 * Kernel library heap functions (Simple memory allocator)
 *
 * TODO:
 *
 * - add function for allocating aligned memory
 */

#include <stdlib.h>
#include <string.h>

extern unsigned long int _heap_s;       /* Defined in linker script */
extern unsigned long int _heap_e;       /* Defined in linker script */

#define BLOCK_MAGIC_BGN     0x4283382438244283
#define BLOCK_MAGIC_END     0x3824428342833824

struct _libkern_heap {
    unsigned long int *p_start;         /* Heap start pointer */
    unsigned long int *p_end;           /* Heap end */
    unsigned long int len_bytes;        /* Heap size in bytes */
    unsigned long int len_block;        /* Heap size in blocks (64-Bit) */
    unsigned long int free_bytes;       /* Free bytes */
    unsigned long int free_block;       /* Free blocks */
    struct _libkern_heap *next;            /* Not implemented (unused) */
};

static struct _libkern_heap __kern_heap;

/**
 * Find free memory
 */
static unsigned long int *find_hole(unsigned long int block_cnt)
{
    unsigned long int block_len;
    unsigned long int block_found;
    unsigned long int *ptr;
    unsigned long int *ptr_ret;
    
    ptr = __kern_heap.p_start;
    ptr_ret = ptr;
    block_len = 0;
    block_found = 0;
    
    do {
        if ((*ptr) == BLOCK_MAGIC_BGN) {
            ptr++;
            block_len = (*ptr);
            ptr += (block_len + 2);
            
            if ((*ptr) == BLOCK_MAGIC_END)
                block_found = 0;
            
            ptr++;
            ptr_ret = ptr;
        } else {
            block_found++;
            if (block_found >= (block_cnt + 4))
                return ptr_ret;
            
            ptr++;
        }
    } while (ptr < __kern_heap.p_end);
    
    return NULL;
}

/**
 * Allocate memory
 */
static void *do_alloc(unsigned long int block_cnt, unsigned long int size)
{
    unsigned long int *ptr;
    unsigned long int *ptr_ret;
    if (!block_cnt)
        return NULL;
    
    if (!size)
        return NULL;
    
    ptr = find_hole(block_cnt);
    
    if (!ptr)
        return NULL;
    
    (*ptr) = BLOCK_MAGIC_BGN;
    ptr++;
    (*ptr) = block_cnt;
    ptr++;
    (*ptr) = size;
    ptr++;
    ptr_ret = ptr;
    ptr += block_cnt;
    (*ptr) = BLOCK_MAGIC_END;
    __kern_heap.free_block -= (block_cnt + 4);
    __kern_heap.free_bytes -= (__kern_heap.free_block * sizeof(unsigned long int));
    
    return ptr_ret;
}

/**
 * Free memory
 */
static void do_free(void *p)
{
    unsigned long int *ptr;
    unsigned long int *ptr_start;
    unsigned long int block_cnt;
    
    if (!p)
        return;
    
    ptr = (unsigned long int *) p;
    
    ptr -= 3;
    ptr_start = ptr;
    
    if ((*ptr) != BLOCK_MAGIC_BGN)
        abort();
    
    ptr++;
    block_cnt = (*ptr);
    
    if (block_cnt == 0)
        abort();
    
    ptr += block_cnt + 2;
    
    if ((*ptr) != BLOCK_MAGIC_END)
        abort();
    
    memset(ptr_start, 0, (block_cnt + 4) * sizeof(unsigned long int));
    __kern_heap.free_block += (block_cnt + 4);
    __kern_heap.free_bytes += (__kern_heap.free_block * sizeof(unsigned long int));
}

/**
 * Return size of allocated memory
 */
static unsigned long int do_size(void *p)
{
    unsigned long int *ptr;
    unsigned long int block_cnt;
    unsigned long int ret;
    
    if (!p)
        return 0;
    
    ptr = (unsigned long int *) p;
    ptr -= 3;
    
    if ((*ptr) != BLOCK_MAGIC_BGN)
        abort();
    
    ptr++;
    block_cnt = (*ptr);
    ptr++;
    ret = (*ptr);
    
    if (block_cnt == 0)
        abort();
    
    ptr += block_cnt + 1;
    
    if ((*ptr) != BLOCK_MAGIC_END)
        abort();
    
    return ret;
}

void _libkern_malloc_init(void)
{
    memset(&__kern_heap, 0, sizeof(struct _libkern_heap));
    __kern_heap.p_start = (unsigned long int *) _heap_s;
    __kern_heap.p_end = (unsigned long int *) _heap_e;
    __kern_heap.len_bytes = (unsigned long int) (__kern_heap.p_end - __kern_heap.p_start);
    __kern_heap.len_block = __kern_heap.len_bytes / sizeof(unsigned long int);
    __kern_heap.free_bytes = __kern_heap.len_bytes;
    __kern_heap.free_block = __kern_heap.len_block;
}

void *_libkern_mem_alloc(size_t size)
{
    unsigned long int block_cnt;
    
    if (!size)
        return NULL;
    
    block_cnt = size / sizeof(unsigned long int);
    
    if ((size % sizeof(unsigned long int)) != 0)
        block_cnt++;
    
    return do_alloc(block_cnt, size);
}

void _libkern_mem_free(void *ptr)
{
    if (!ptr)
        return;
    
    if (ptr < (void *) __kern_heap.p_start)
        return;
    
    if (ptr > (void *) __kern_heap.p_end)
        return;
    
    do_free(ptr);
}

size_t _libkern_mem_size(void *ptr)
{
    if (!ptr)
        return 0;
    
    if (ptr < (void *) __kern_heap.p_start)
        return 0;
    
    if (ptr > (void *) __kern_heap.p_end)
        return 0;
    
    return do_size(ptr);
}
