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

#define CGRF_MAJOR_VER 0 /**< CGRF MAJOR VERSION */
#define CGRF_MINOR_VER 1 /**< CGRF MINOR VERSION */

/**
 * @brief mouse callback for glfw
 *
 * @param window
 * @param xpos
 * @param ypos
 */
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

/**
 * @brief scroll callback for glfw
 *
 * @param window
 * @param xoffset
 * @param yoffset
 */
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

/**
 * @brief error callback for glfw
 *
 * @param error
 * @param description
 */
void error_callback(int error, const char *description);

/**
 * @brief when window resized framebuffer callback for glfw
 *
 * @param window
 * @param width
 * @param height
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

/**
 * @brief key event callback for glfw
 *
 * @param window
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);

/**
 * @brief opengl clear color for framebuffer
 *
 * @param clear_color
 */
void cgrf_gl_clear_color(float clear_color[4]);

/**
 * @brief initial windows creation & opengl context creation
 *
 * @param width
 * @param height
 * @param window_name
 * @return GLFWwindow*
 */
GLFWwindow *cgrf_glfw_glad_init(int width, int height, const char *window_name);

/**
 * @brief calculate aspect ratio
 *
 * @param window
 * @param width
 * @param height
 * @return float
 */
float cgrf_calculate_ratio(GLFWwindow *window, int *width, int *height);

/**
 * @brief swap buffers, pollevents and viewport resize actions
 *
 * @param window
 * @param width
 * @param height
 */
void cgrf_glfw_routine(GLFWwindow *window, int *width, int *height);

/**
 * @brief window destroy
 *
 * @param window
 */
void cgrf_destroy_terminate_glfw(GLFWwindow *window);

/**
 * @brief handle user input
 *
 * @param win
 */
void cgrf_handle_input(GLFWwindow *win);

/**
 * @brief parse command line arguments
 *
 * @param argc
 * @param argv
 * @param optstring
 */
void cgrf_parse_cmd_arguments(int argc, char **argv);

#endif /* _CGRF_COMMON_H_ */
