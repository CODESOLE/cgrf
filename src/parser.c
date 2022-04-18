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
#include <SDL2/SDL.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *_trim_line(char *line) {
  char *is_comment = strchr(line, '#');
  if (is_comment)
    *is_comment = '\0';
  while (*line != '\0') {
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
static int line_num = 0; /**< Indicates active line */

static void _tokenize(char *haystack, char *needle) {
  short i = 0;
  if (strncmp(haystack, "", 1) == 0)
    return;
  char *rett = haystack;
  while (rett && *rett != '\n') {
    char *ret = strstr(rett, needle);
    if (!ret || *rett == '\0') {
      array_str_push_back(t, xstrndup(rett, strlen(rett)));
      i++;
      break;
    }
    i++;
    array_str_push_back(t, xstrndup(rett, ret - rett));
    if (*(ret + 1) == '\0' || *(ret + 2) == '\0')
      break;
    rett = ret + strlen(needle);
  }
  if (i != 2 && i != 0) {
    printf("[ERROR AT LINE %d ] Each line should contain 2 node!\n", line_num);
    exit(EXIT_FAILURE);
  }
}

static inline _Bool _check_extension(const char *filename, const char *ext) {
  return strncmp(filename + strlen(filename) - strlen(ext), ext, strlen(ext)) ==
                 0
             ? 0
             : 1;
}

static void
_check_remove_duplicated_and_revese_pairs(struct array_str_s *toks) {
  char tmp[512] = {0};
  char tmp2[512] = {0};
  for (size_t i = 0; i < array_str_size(toks); i += 2) {
    char *s1 = *array_str_get(toks, i);
    char *s2 = *array_str_get(toks, i + 1);
    snprintf(tmp, 512, "%s%s", s1, s2);
    for (size_t j = 0; j < array_str_size(toks); j += 2) {
      if (j == i)
        continue;
      char *ss1 = *array_str_get(toks, j);
      char *ss2 = *array_str_get(toks, j + 1);
      snprintf(tmp2, 512, "%s%s", ss1, ss2);
      if (strncmp(tmp, tmp2, strlen(tmp2)) == 0) {
        array_str_erase(toks, j);
        array_str_erase(toks, j);
      }
    }
  }
}

struct array_str_s *cgrf_parse_file(const char *filename) {
  assert(filename);
  CGRF_FAIL_IF_WRONG(_check_extension(filename, ".cgrf") == 0, __FILE__,
                     __LINE__, exit(EXIT_FAILURE));
  FILE *f = NULL;
  CGRF_FOPEN(f, filename, "r", exit(EXIT_FAILURE), __FILE__, __LINE__);
  char line[MAX_CHAR];
  while (!feof(f) && fgets(line, MAX_CHAR, f) != NULL) {
    line_num++;
    _tokenize(_trim_line(line), "--");
    for (size_t i = 0; i < array_str_size(t); i++)
      array_str_set_at(t, i, _trim_line(*array_str_get(t, i)));
  }
  for (size_t i = 0; i < array_str_size(t); i += 2) {
    char *s1 = *array_str_get(t, i);
    char *s2 = *array_str_get(t, i + 1);
    if (strncmp(s1, s2, strlen(s2)) == 0) { /* removing X--X */
      array_str_erase(t, i);
      array_str_erase(t, i);
    }
  }
  /* removing { A--B, B--A } and { A--B, A--B } */
  _check_remove_duplicated_and_revese_pairs(t);

  for (size_t i = 0; i < array_str_size(t); i += 2)
    printf("-(%s, %s)-\n", *array_str_get(t, i), *array_str_get(t, i + 1));

  return t;
}
