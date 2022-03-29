/**
 * @file render.h
 * @brief graph renderer definitions
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

#ifndef _CGRF_RENDER_H
#define _CGRF_RENDER_H

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear/nuklear.h"
#include "nuklear/nuklear_glfw_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024  /**< maximum gui vertex buffer size */
#define MAX_ELEMENT_BUFFER 128 * 1024 /**< maximum gui element buffer size */

/**
 * @brief set gui font
 *
 * @param ctx nuklear context
 * @param glfw nuklear-glfw context
 * @param file_name font file name
 */
void cgrf_set_font(struct nk_context *ctx, struct nk_glfw *glfw,
                   const char *file_name);

/**
 * @brief graph render function
 *
 * @param ctx nuklear context
 * @param glfw nuklear-glfw context
 */
void cgrf_render_graph(struct nk_context *ctx, struct nk_glfw *glfw);

#endif /* _CGRF_RENDER_H */
