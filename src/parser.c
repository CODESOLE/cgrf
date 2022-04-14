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

static char *_trim_line(char *line) {
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

ARRAY_DEF(array_str, char *)
static array_str_t t = ARRAY_INIT_VALUE();

static void _tokenize(char *haystack, char *needle) {
  if (strncmp(haystack, "", 1) == 0)
    return;
  char *rett = haystack;
  while (rett && *rett != '\n') {
    char *ret = strstr(rett, needle);
    if (!ret || *rett == '\0') {
      array_str_push_back(t, xstrndup(rett, strlen(rett)));
      break;
    }
    array_str_push_back(t, xstrndup(rett, ret - rett));
    if (*(ret + 1) == '\0' || *(ret + 2) == '\0')
      break;
    rett = ret + strlen(needle);
  }
}

static inline _Bool _check_extension(const char *filename) {
  return strncmp(filename + strlen(filename) - 5, ".cgrf", 5) == 0 ? 0 : 1;
}

struct dict_string_s *cgrf_parse_file(const char *filename) {
  assert(filename);
  assert(_check_extension(filename) == 0);
  m_string_t s1, s2;
  m_string_init(s1);
  m_string_init(s2);
  struct dict_string_s *token_strings = NULL;
  CGRF_MALLOC(token_strings, sizeof(struct dict_string_s), __FILE__, __LINE__,
              exit(EXIT_FAILURE));
  dict_string_init(token_strings);
  FILE *f = NULL;
  CGRF_FOPEN(f, filename, "r", exit(EXIT_FAILURE), __FILE__, __LINE__);
  char line[MAX_CHAR];
  while (!feof(f) && fgets(line, MAX_CHAR, f) != NULL) {
    _tokenize(_trim_line(line), "--");
    for (size_t i = 0; i < array_str_size(t); i++)
      array_str_set_at(t, i, _trim_line(*array_str_get(t, i)));
  }
  for (size_t i = 0; i < array_str_size(t) - 1; i++) {
    m_string_set_str(s1, *array_str_get(t, i));
    m_string_set_str(s2, *array_str_get(t, i + 1));
    if (m_string_cmp(s1, s2) != 0)
      dict_string_set_at(token_strings, s1, s2);
  }
  for (size_t i = 0; i < array_str_size(t); i++)
    printf("%s\n", *array_str_get(t, i));
  dict_string_out_str(stdout, token_strings);
  puts("");
  array_str_clear(t);

  return token_strings;
}
