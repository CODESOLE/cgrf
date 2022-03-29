/**
 * @file main.c
 * @brief main entry point file
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

#include "common.h"
#include "global.h"
#include "render.h"
#include <stdio.h>

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

int main(int argc, char **argv) {
  static struct nk_glfw glfw = {0};
  static int width = 0, height = 0;
  static struct nk_colorf bg = {0.1f, 0.2f, 0.3f, 1.0f};

  cgrf_parse_cmd_arguments(argc, argv, ":vhf:");

  GLFWwindow *win = cgrf_glfw_glad_init(800, 600, "CGRF GRAPH VISUALIZATION");

  struct nk_context *ctx =
      nk_glfw3_init(&glfw, win, NK_GLFW3_INSTALL_CALLBACKS);
  cgrf_set_font(ctx, &glfw, NULL);

  while (!glfwWindowShouldClose(win)) {
    nk_glfw3_new_frame(&glfw);
    cgrf_handle_input(win);
    cgrf_gl_clear_color((float[4]){bg.r, bg.g, bg.b, bg.a});
    cgrf_render_graph(ctx, &glfw, &bg);
    cgrf_glfw_routine(win, &width, &height);
  }

  nk_glfw3_shutdown(&glfw);
  cgrf_destroy_terminate_glfw(win);

  return 0;
}
