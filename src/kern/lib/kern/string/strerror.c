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
#include <errno.h>

char *strerror(int errnum)
{
    switch (errnum) {
        case ENONE:
            return "no error";
            break;
        case EINVAL:
            return "invalid argument";
            break;
        case ENOMEM:
            return "no free memory";
            break;
        case EFAULT:
            return "page fault";
            break;
        case EDOM:
            return "domain error";
            break;
        case ERANGE:
            return "range error";
            break;
        case ENOENT:
            return "no such file or directory";
            break;
        case EIO:
            return "I/O error";
            break;
        case EBADF:
            return "bad file descriptor";
            break;
        case EACCES:
            return "access denied";
            break;
        case EBUSY:
            return "device busy";
            break;
        case EEXIST:
            return "file or directory exists";
            break;
        case EMFILE:
            return "too many opened files";
            break;
        case EFBIG:
            return "file too big";
            break;
        case ENOSPC:
            return "no space left on device";
            break;
        case ENAMETOOLONG:
            return "name or path too long";
            break;
        case ENOSYS:
            return "no such syscall or not implemented";
            break;
        default:
            return "unknown error";
    }

    return NULL;
}
