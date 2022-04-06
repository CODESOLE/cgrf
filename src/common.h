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
#include <SDL2/SDL.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CGRF_MAJOR_VER 0 /**< CGRF MAJOR VERSION */
#define CGRF_MINOR_VER 1 /**< CGRF MINOR VERSION */

struct nk_context;

/**
 * @brief opengl clear color for framebuffer
 *
 * @param r red color
 * @param g green color
 * @param b blue color
 * @param a alpha color
 */
void cgrf_gl_clear_color(float r, float g, float b, float a);

/**
 * @brief initial windows creation & opengl context creation
 *
 * @param glContext OpenGL context
 * @param width initial window width
 * @param height initial window height
 * @param window_name window name
 * @return SDL_Window* window handle
 */
SDL_Window *cgrf_sdl_glad_init(SDL_GLContext *glContext, int width, int height,
                               const char *window_name);

/**
 * @brief calculate aspect ratio
 *
 * @param window
 * @param width
 * @param height
 * @return float
 */
float cgrf_calculate_ratio(SDL_Window *window, int *width, int *height);

/**
 * @brief swap buffers, pollevents and viewport resize actions
 *
 * @param window
 * @param width
 * @param height
 */
void cgrf_sdl_routine(SDL_Window *window, int *width, int *height);

/**
 * @brief window destroy
 *
 * @param window
 * @param glContext OpenGL context
 */
void cgrf_destroy_terminate_sdl(SDL_Window *window, SDL_GLContext *glContext);

/**
 * @brief handle user input
 *
 * @param ctx nuklear context
 * @param evt SDL event
 * @param is_running should window open
 */
void cgrf_handle_input(struct nk_context *ctx, SDL_Event *evt,
                       _Bool *is_running);

/**
 * @brief parse command line arguments
 *
 * @param argc
 * @param argv
 */
void cgrf_parse_cmd_arguments(int argc, char **argv);

#endif /* _CGRF_COMMON_H_ */
