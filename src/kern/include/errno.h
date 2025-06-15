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

#ifndef _LIBKERN_ERRNO_H
#define _LIBKERN_ERRNO_H

#define ENONE           0       /* No error */
#define EINVAL          1       /* Invalid argument */
#define ENOMEM          2       /* No free memory */
#define EFAULT          3       /* Page fault */
#define EDOM            4       /* Domain error */
#define ERANGE          5       /* Range error */
#define ENOENT          6       /* No such file or directory */
#define EIO             7       /* I/O error */
#define EBADF           8       /* Bad file descriptor */
#define EACCES          9       /* Access denied */
#define EBUSY           10      /* Device busy */
#define EEXIST          11      /* File or directory exists */
#define EMFILE          12      /* Too many opened files */
#define EFBIG           13      /* File too big */
#define ENOSPC          14      /* No space left on device */
#define	ENAMETOOLONG    15      /* Name or path too long */
#define	ENOSYS          16      /* No such syscall or not implemented */

extern int _libkern_geterrno(void);

#define errno           (_libkern_geterrno())

#endif
