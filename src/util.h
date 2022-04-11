/**
 * @file util.h
 * @brief general utilities
 * @author CODESOLE
 * @copyright Copyright (c) 2022
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef _CGRF_UTIL_H
#define _CGRF_UTIL_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Copy string src to buffer dst of size dsize.  At most dsize-1
 * chars will be copied.  Always NUL terminates (unless dsize == 0).
 * Returns strlen(src); if retval >= dsize, truncation occurred.
 */
size_t xstrlcpy(char *dst, const char *src, size_t siz);
/*
 * Appends src to string dst of size dsize (unlike strncat, dsize is the
 * full size of dst, not space left).  At most dsize-1 characters
 * will be copied.  Always NUL terminates (unless dsize <= strlen(dst)).
 * Returns strlen(src) + MIN(dsize, strlen(initial dst)).
 * If retval >= dsize, truncation occurred.
 */
size_t xstrlcat(char *dst, const char *src, size_t siz);
size_t xstrnlen(const char *s, size_t n);
char *xstrndup(const char *s, size_t n);

#define CGRF_STRINGIFY(name) #name
#define CGRF_CONCAT_IMPL(a, b) a##b
#define CGRF_CONCAT(a, b) CGRF_CONCAT_IMPL(a, b)
#define CGRF_MACRO_VAR(name) CGRF_CONCAT(name, __LINE__)
#define CGRF_PAD(n) char CGRF_MACRO_VAR(_padding_)[n]

#define CGRF_FOPEN(f, file_name, modes, action, file, line)                    \
  do {                                                                         \
    f = fopen(file_name, modes);                                               \
    if (f == NULL) {                                                           \
      fprintf(stderr, "FOPEN ERR [%s::%d] : %s\n", file, line, file_name);     \
      action;                                                                  \
    }                                                                          \
  } while (0)

#define CGRF_MALLOC(p, s, file_name, line, action)                             \
  do {                                                                         \
    p = malloc(s);                                                             \
    if (p == NULL) {                                                           \
      fprintf(stderr, "ALLOC ERR [%s::%d] : %zu Bytes\n", file_name, line, s); \
      action;                                                                  \
    }                                                                          \
  } while (0)

#define CGRF_CALLOC(p, l, s, file_name, line, action)                          \
  do {                                                                         \
    p = calloc(l, s);                                                          \
    if (p == NULL) {                                                           \
      fprintf(stderr, "ALLOC ERR [%s::%d] : %zu Bytes\n", file_name, line, s); \
      action;                                                                  \
    }                                                                          \
  } while (0)

#define CGRF_REALLOC(p, s, file_name, line, action)                            \
  do {                                                                         \
    void *np = realloc(p, s);                                                  \
    if (np == NULL) {                                                          \
      fprintf(stderr, "ALLOC ERR [%s::%d] : %zu Bytes\n", file_name, line, s); \
      action;                                                                  \
    } else {                                                                   \
      p = np;                                                                  \
    }                                                                          \
  } while (0)

#define CGRF_FREE(p)                                                           \
  do {                                                                         \
    free(p);                                                                   \
    p = NULL;                                                                  \
  } while (0)

#define CGRF_UNUSED(expr)                                                      \
  do {                                                                         \
    (void)(expr);                                                              \
  } while (0)

#define CGRF_ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))

#endif /* _CGRF_UTIL_H */
