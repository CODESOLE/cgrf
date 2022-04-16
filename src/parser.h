/**
 * @file parser.h
 * @brief cgrf graph parser
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

#ifndef _PARSER_H_
#define _PARSER_H_

#include "mlib/m-array.h"
#include "mlib/m-string.h"

ARRAY_DEF(array_str, char *)

#define MAX_CHAR 4096

/**
 * @brief parse .cgrf file which will be visualize
 *
 * @param filename file to be parsed with the .cgrf extension
 * @return struct dict_string_s* tokenized strings
 */
struct array_str_s *cgrf_parse_file(const char *filename);

#endif /* _PARSER_H_ */
