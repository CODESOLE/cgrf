/**
 * @file parser.c
 * @brief cgrf graph parser implementation file
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

#include "parser.h"
#include "global.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *trim_line(char *line) {
  char *is_comment = strchr(line, '#');
  if (is_comment)
    *is_comment = '\0';
  while (*line != '\0' && *line != '\n') {
    if (isspace(*line))
      line++;
    else
      break;
  }
  char *end = line + strlen(line) - 1;
  while (*end != '\0') {
    if (isspace(*end))
      end--;
    else
      break;
  }
  *(end + 1) = '\0';
  return line;
}

static array_str_t t = ARRAY_INIT_VALUE();

static void tokenize(char *haystack, char *needle) {
  if (strncmp(haystack, "", 1) == 0)
    return;
  char *rett = haystack;
  while (rett && *rett != '\n') {
    char *ret = strstr(rett, needle);
    if (!ret || *rett == '\0') {
      array_str_push_back(t, strndupl(rett, strlen(rett)));
      break;
    }
    array_str_push_back(t, strndupl(rett, ret - rett));
    if (*(ret + 1) == '\0' || *(ret + 2) == '\0')
      break;
    rett = ret + strlen(needle);
  }
}

static inline _Bool check_extension(const char *filename) {
  return strncmp(filename + strlen(filename) - 5, ".cgrf", 5) == 0 ? 0 : 1;
}

struct array_str_s *cgrf_parse_file(const char *filename) {
  CGRF_ASSERT(filename, "File name should not be NULL", __FILE__, __LINE__);
  CGRF_ASSERT(check_extension(filename) == 0,
              "Extension of file should be .cgrf", __FILE__, __LINE__);
  FILE *f = NULL;
  CGRF_FOPEN(f, filename, "r", exit(EXIT_FAILURE));

  char line[MAX_CHAR];
  while (!feof(f) && fgets(line, MAX_CHAR, f) != NULL) {
    tokenize(trim_line(line), "->");
    for (size_t i = 0; i < array_str_size(t); i++)
      array_str_set_at(t, i, trim_line(*array_str_get(t, i)));
  }
  return t;
}
