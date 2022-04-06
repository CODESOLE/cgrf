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

void cgrf_set_font(struct nk_context *ctx, const char *file_name) {
  if (file_name == NULL) {
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();
  } else {
    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    struct nk_font *droid =
        nk_font_atlas_add_from_file(atlas, "DejaVuSans.ttf", 14, 0);
    nk_sdl_font_stash_end();
    nk_style_set_font(ctx, &droid->handle);
  }
}

static inline float _get_text_width(struct nk_style *style,
                                    struct array_str_s *toks, size_t i) {
  return style->font->width(style->font->userdata, style->font->height,
                            *array_str_get(toks, i),
                            strlen(*array_str_get(toks, i)));
}

static inline void _draw_circle(struct nk_command_buffer *buf, float x, float y,
                                float w, float h, struct nk_color col) {
  nk_fill_circle(buf, (struct nk_rect){x, y, w, h}, col);
  nk_stroke_circle(buf, (struct nk_rect){x, y, w, h}, 0.1f,
                   nk_rgb(255, 255, 255));
}

void cgrf_calculate_node_pos(struct nk_style *style, struct array_str_s *toks,
                             float *pos) {
  for (size_t i = 0; i < array_str_size(toks); ++i) {
    pos[i * 4] = 100.0f;
    pos[i * 4 + 1] = 100.0f;
    pos[i * 4 + 2] = _get_text_width(style, toks, i);
    pos[i * 4 + 3] = style->font->height;
  }
}

void cgrf_render_graph(struct nk_context *ctx, struct array_str_s *toks,
                       float *pos) {
  if (nk_begin(ctx, "Graph Viewer", nk_rect(0, 0, width, height), 0)) {
    struct nk_command_buffer *buf = nk_window_get_canvas(ctx);
    for (size_t i = 0; i < array_str_size(toks); ++i)
      _draw_circle(buf, pos[i * 4], pos[i * 4 + 1], pos[i * 4 + 2],
                   pos[i * 4 + 3], nk_rgb(25, 25, 25));
  }
  nk_end(ctx);

  nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}
