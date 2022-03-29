/**
 * @file render.c
 * @brief graph renderer
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

#include "render.h"
#include <stdio.h>

void cgrf_set_font(struct nk_context *ctx, struct nk_glfw *glfw,
                   const char *file_name) {
  if (file_name == NULL) {
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(glfw, &atlas);
    nk_glfw3_font_stash_end(glfw);
  } else {
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(glfw, &atlas);
    struct nk_font *droid =
        nk_font_atlas_add_from_file(atlas, "DejaVuSans.ttf", 14, 0);
    nk_glfw3_font_stash_end(glfw);
    nk_style_set_font(ctx, &droid->handle);
  }
}

void cgrf_render_graph(struct nk_context *ctx, struct nk_glfw *glfw) {
  /* GUI */
  if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
               NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                   NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
    enum { EASY, HARD };
    static int op = EASY;
    static int property = 20;

    nk_layout_row_static(ctx, 30, 80, 1);

    if (nk_button_label(ctx, "button"))
      fprintf(stdout, "button pressed\n");

    nk_layout_row_dynamic(ctx, 30, 2);
    if (nk_option_label(ctx, "easy", op == EASY))
      op = EASY;
    if (nk_option_label(ctx, "hard", op == HARD))
      op = HARD;

    nk_layout_row_dynamic(ctx, 25, 1);
    nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);
  }
  nk_end(ctx);

  nk_glfw3_render(glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER,
                  MAX_ELEMENT_BUFFER);
}
