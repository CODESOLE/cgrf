/**
 * @file util.c
 * @brief general utilities used around program implementation
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

#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t strnlength(const char *s, size_t n) {
  const char *found = memchr(s, '\0', n);
  return found ? (size_t)(found - s) : n;
}

char *strndupl(const char *s, size_t n) {
  size_t len = strnlength(s, n);
  char *new = (char *)malloc(len + 1);
  if (new == NULL)
    return NULL;
  new[len] = '\0';
  return (char *)memcpy(new, s, len);
}
