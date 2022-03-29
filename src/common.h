/**
 * @file common.h
 * @brief common function definitions
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

#ifndef _CGRF_COMMON_H_
#define _CGRF_COMMON_H_

#include "debugbreak/debugbreak.h"
#include "glad/glad.h"
#include "global.h"
#include <GLFW/glfw3.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CGRF_ASSERT(x)                                                         \
  if (!(x))                                                                    \
    debug_break();

#define CGRF_UNUSED(expr)                                                      \
  do {                                                                         \
    (void)(expr);                                                              \
  } while (0)

#define CGRF_MAJOR_VER 0
#define CGRF_MINOR_VER 1

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void error_callback(int error, const char *description);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);

void cgrf_gl_clear_color(float clear_color[4]);

GLFWwindow *cgrf_glfw_glad_init(int width, int height, const char *window_name);

float cgrf_calculate_ratio(GLFWwindow *window, int *width, int *height);

void cgrf_glfw_routine(GLFWwindow *window, int *width, int *height);

void cgrf_destroy_terminate_glfw(GLFWwindow *window);

void cgrf_handle_parsed_arguments(void);

void cgrf_handle_input(GLFWwindow *win);

void cgrf_parse_cmd_arguments(int argc, char **argv, const char *optstring);

#endif /* _CGRF_COMMON_H_ */
