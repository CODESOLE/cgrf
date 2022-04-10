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
#include "parser.h"
#include "render.h"
#include "util.h"
#include <stdio.h>

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif

int main(int argc, char **argv) {
  struct array_str_s *toks = NULL;
  SDL_GLContext gl_ctx = NULL;
  cgrf_parse_cmdline_args(argc, argv);

  if (flag_file)
    toks = cgrf_parse_file(file);
  else
    exit(EXIT_FAILURE);

  SDL_Window *win =
      cgrf_app_init(gl_ctx, WIN_WIDTH, WIN_HEIGHT, "CGRF GRAPH VISUALIZATION");

  struct nk_context *ctx = nk_sdl_init(win);
  cgrf_set_font(ctx, NULL);
  cgrf_calculate_node_pos(&ctx->style, toks);

  SDL_Event evt;
  while (is_running) {
    cgrf_handle_input(ctx, &evt, &is_running);
    cgrf_bg_clear_color(0.1f, 0.1f, 0.1f, 1.0f);
    cgrf_render_graph(ctx, toks);
    cgrf_app_routine(win, &width, &height);
  }
  cgrf_destroy_terminate_sdl(win, gl_ctx);
  array_str_clear(toks);

  return 0;
}
