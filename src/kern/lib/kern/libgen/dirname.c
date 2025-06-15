/**
 *
 * Copyright (c) 2024 Johannes Krottmayer <johannes@krotti42.com>
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
#include <libgen.h>

char *dirname(char *path)
{
    static char ret[256];
    size_t i = 0;
    size_t j = 0;
    size_t i_begin;
    size_t i_end;
    
    memset(ret, 0, 256);
    
    if (strlen(path) == 0) {
        strcpy(ret, ".");
        return ret;
    }
    
    i = strlen(path);
    
    while (path[i - 1] == '/') {
        j++;
        i--;
    }
    
    if (i == 0) {
        if (j == 2) {
            strcpy(ret, "//");
            return ret;
        } else {
            strcpy(ret, "/");
            return ret;
        }
    }
    
    while ((path[i - 1] != '/') && (i != 0))
        i--;
    
    if (i == 0) {
        strcpy(ret, ".");
        return ret;
    } else {
        i_begin = 0;
        
        if (!((path[i - 1] == '/') && (i == 1)))
            while (path[i - 1] == '/')
                i--;
        
        i_end = i;
    }
    
    strncpy(ret, &path[i_begin], i_end - i_begin);
    
    return ret;
}
