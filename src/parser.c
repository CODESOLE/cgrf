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
#include "klib/kvec.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *trim_line(char *line) {
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

static kvec_t(char *) t;
static void tokenize(char *haystack, char *needle) {
  char *rett = haystack;
  kv_init(t);
  while (rett) {
    char *ret = strstr(rett, needle);
    if (!ret || *rett == '\0') {
      printf("string:%s\n", rett);
      break;
    }
    kv_push(char *, t, strndup(rett, ret - rett));
    printf("string:%s@\n", kv_A(t, kv_size(t) - 1));
    if (*(ret + 1) == '\0' || *(ret + 2) == '\0')
      break;
    rett = ret + 2;
  }
}

void cgrf_parse_file(const char *filename) {
  CGRF_IF_NULL(filename, "File name should not be NULL", __FILE__, __LINE__,
               exit(EXIT_FAILURE));

  FILE *f = NULL;
  CGRF_FOPEN(f, filename, "r", exit(EXIT_FAILURE));

  char line[MAX_CHAR];
  while (!feof(f) && fgets(line, MAX_CHAR, f) != NULL) {
    tokenize(trim_line(line), "->");
    for (size_t i = 0; i < kv_size(t); i++)
      trim_line(kv_A(t, i));
  }
  puts("=====================FINAL======================");
  for (size_t i = 0; i < kv_size(t); i++)
    printf("final_string:%s@\n", kv_A(t, i));
}
