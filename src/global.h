/**
 * @file global.h
 * @brief global variable definitions
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

#ifndef _CGRF_GLOBAL_H_
#define _CGRF_GLOBAL_H_

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MAX_FILE_NAME 128
extern char file[MAX_FILE_NAME];
extern _Bool flag_version, flag_help, flag_file, is_running;
extern int width, height;

#define SDL_clamp(x, a, b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))

#endif /* _CGRF_GLOBAL_H_ */
