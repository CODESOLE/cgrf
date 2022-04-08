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
#include "mlib/m-array.h"
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

static uint32_t uid = 0;

typedef struct node {
  const char *inner_text;
  uint32_t id;
  float x, y, w, h;
  CGRF_PAD(4);
} node_s;

ARRAY_DEF(arr_node, node_s, M_POD_OPLIST)

static arr_node_t nodes = ARRAY_INIT_VALUE();

static inline float _get_text_width(struct nk_style *style, const char *text) {
  return style->font->width(style->font->userdata, style->font->height, text,
                            strlen(text));
}

static inline void _draw_circle(struct nk_command_buffer *buf, node_s *n,
                                struct nk_color col) {
  nk_fill_circle(buf, (struct nk_rect){n->x, n->y, n->w, n->h}, col);
  nk_stroke_circle(buf, (struct nk_rect){n->x, n->y, n->w, n->h}, 0.1f,
                   nk_rgb(255, 255, 255));
}

static inline node_s _create_node(struct nk_style *style,
                                  const char *inner_text) {
  node_s n = {strndupl(inner_text, strlen(inner_text)),
              uid++,
              0.0f,
              0.0f,
              _get_text_width(style, inner_text) + 10.0f,
              style->font->height,
              {0}};
  return n;
}

void cgrf_calculate_node_pos(struct nk_style *style, struct array_str_s *toks) {
  for (size_t i = 0; i < array_str_size(toks); ++i) {
    node_s n = _create_node(style, *array_str_get(toks, i));
    n.x = rand() % width;
    n.y = rand() % height;
    arr_node_push_back(nodes, n);
  }
}

void cgrf_render_graph(struct nk_context *ctx, struct array_str_s *toks) {
  static struct nk_rect scrolling = {0};
  struct nk_input *in = &ctx->input;
  if (nk_begin(ctx, "Graph Viewer", nk_rect(0, 0, width, height), 0)) {
    /* allocate complete window space */
    struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);
    struct nk_rect total_space = nk_window_get_content_region(ctx);
    nk_layout_space_begin(ctx, NK_STATIC, total_space.h, array_str_size(toks));

    arr_node_it_t it;
    for (arr_node_it(it, nodes); !arr_node_end_p(it); arr_node_next(it)) {
      /* calculate scrolled node window position and size */
      nk_layout_space_push(ctx,
                           nk_rect(arr_node_cref(it)->x - scrolling.x,
                                   arr_node_cref(it)->y - scrolling.y,
                                   arr_node_cref(it)->w, arr_node_cref(it)->h));

      /* execute node window */
      if (nk_group_begin(ctx, arr_node_cref(it)->inner_text, 0)) {
        /* ================= NODE CONTENT =====================*/
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_draw_text(canvas,
                     nk_rect(arr_node_cref(it)->x - scrolling.x,
                             arr_node_cref(it)->y - scrolling.y,
                             arr_node_cref(it)->w, arr_node_cref(it)->h),
                     arr_node_cref(it)->inner_text,
                     strlen(arr_node_cref(it)->inner_text), ctx->style.font,
                     nk_rgb(255, 255, 255), nk_rgb(0, 0, 0));
        /* ====================================================*/
        nk_group_end(ctx);
      }
    }

    struct nk_rect size = nk_layout_space_bounds(ctx);

    /* display grid */
    const float grid_size = 32.0f;
    const struct nk_color grid_color = nk_rgb(50, 50, 50);
    for (float x = (float)fmod(size.x - scrolling.x, grid_size); x < size.w;
         x += grid_size)
      nk_stroke_line(canvas, x + size.x, size.y, x + size.x, size.y + size.h,
                     1.0f, grid_color);
    for (float y = (float)fmod(size.y - scrolling.y, grid_size); y < size.h;
         y += grid_size)
      nk_stroke_line(canvas, size.x, y + size.y, size.x + size.w, y + size.y,
                     1.0f, grid_color);

    for (size_t i = 0; i < arr_node_size(nodes); ++i)
      _draw_circle(canvas, arr_node_get(nodes, i), nk_rgb(25, 25, 25));

    /* window content scrolling */
    if (nk_input_is_mouse_hovering_rect(in, nk_window_get_bounds(ctx)) &&
        nk_input_is_mouse_down(in, NK_BUTTON_MIDDLE)) {
      scrolling.x -= in->mouse.delta.x;
      scrolling.y -= in->mouse.delta.y;
    }
    nk_layout_space_end(ctx);
  }
  nk_end(ctx);

  nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}
