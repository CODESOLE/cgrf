/**
 * @file util.h
 * @brief general utilities used around program
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

#include "debugbreak/debugbreak.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t strnlength(const char *s, size_t n);

char *strndupl(const char *s, size_t n);

#define CGRF_FOPEN(f, file_name, modes, action, file, line)                    \
  do {                                                                         \
    f = fopen(file_name, modes);                                               \
    if (f == NULL) {                                                           \
      fprintf(stderr, "FOPEN ERR [file::line] : %s\n", file_name);             \
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

#define CGRF_ASSERT(x, message, file_name, line, func_name)                    \
  if (!(x)) {                                                                  \
    fprintf(stderr, "ASSERT[FUNC: %s]" message " [%s::%d]\n", func_name,       \
            file_name, line);                                                  \
    debug_break();                                                             \
  }

#define CGRF_UNUSED(expr)                                                      \
  do {                                                                         \
    (void)(expr);                                                              \
  } while (0)

#define CGRF_ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))

#endif /* _CGRF_UTIL_H */
