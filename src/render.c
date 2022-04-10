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
#include <time.h>

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

static void _draw_grid(struct nk_context *ctx, const struct nk_rect scrolling,
                       const float grid_size,
                       const struct nk_color grid_color) {
  struct nk_rect size = nk_layout_space_bounds(ctx);
  struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);
  for (float x = (float)fmod(size.x - scrolling.x, grid_size); x < size.w;
       x += grid_size)
    nk_stroke_line(canvas, x + size.x, size.y, x + size.x, size.y + size.h,
                   1.0f, grid_color);
  for (float y = (float)fmod(size.y - scrolling.y, grid_size); y < size.h;
       y += grid_size)
    nk_stroke_line(canvas, size.x, y + size.y, size.x + size.w, y + size.y,
                   1.0f, grid_color);
}

static uint32_t uid = 0;

typedef struct node {
  const char *inner_text;
  uint32_t id;
  struct nk_rect bound;
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
  nk_fill_circle(buf, n->bound, col);
  nk_stroke_circle(buf, n->bound, 0.1f, nk_rgb(255, 255, 255));
}

static inline node_s _create_node(struct nk_style *style,
                                  const char *inner_text) {
  return (node_s){strndupl(inner_text, strlen(inner_text)),
                  uid++,
                  (struct nk_rect){0.0f, 0.0f,
                                   _get_text_width(style, inner_text) + 10.0f,
                                   style->font->height},
                  {0}};
}

void cgrf_calculate_node_pos(struct nk_style *style, struct array_str_s *toks) {
  srand(time(NULL));
  for (size_t i = 0; i < array_str_size(toks); ++i) {
    node_s n = _create_node(style, *array_str_get(toks, i));
    n.bound.x = rand() % width;
    n.bound.y = rand() % height;
    arr_node_push_back(nodes, n);
  }
}

void cgrf_render_graph(struct nk_context *ctx, struct array_str_s *toks) {
  static struct nk_rect scrolling = {0};
  struct nk_input *in = &ctx->input;
  if (nk_begin(ctx, "Graph Viewer", nk_rect(0, 0, width, height),
               NK_WINDOW_NO_SCROLLBAR)) {
    struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);
    struct nk_rect total_space = nk_window_get_content_region(ctx);
#if 0

    nk_layout_space_begin(ctx, NK_STATIC, total_space.h, array_str_size(toks));
    _draw_grid(ctx, scrolling, 32.0f, nk_rgb(50, 50, 50));
    struct nk_style_item background = ctx->style.window.fixed_background;
    ctx->style.window.fixed_background = nk_style_item_hide();
    ctx->style.window.border_color = nk_rgba(0, 0, 0, 0);

    ctx->style.window.spacing = nk_vec2(0, 0);
    ctx->style.window.padding = nk_vec2(0, 0);

    for (size_t i = 0; i < arr_node_size(nodes); ++i) {
      node_s *n = arr_node_get(nodes, i);
      if (nk_popup_begin(ctx, NK_POPUP_STATIC, "piemenu",
                         NK_WINDOW_NO_SCROLLBAR, n->bound)) {
        _draw_circle(canvas, n, nk_rgb(25, 25, 25));
        struct nk_rect text_pos = {n->bound.x + 5, n->bound.y, n->bound.w,
                                   n->bound.h};
        nk_draw_text(canvas, text_pos, n->inner_text, strlen(n->inner_text),
                     ctx->style.font, nk_rgb(255, 0, 0), nk_rgb(0, 255, 0));
      }
      nk_popup_end(ctx);
    }
    ctx->style.window.fixed_background = background;

#else

    nk_layout_space_begin(ctx, NK_STATIC, total_space.h, array_str_size(toks));

    _draw_grid(ctx, scrolling, 32.0f, nk_rgb(50, 50, 50));

    for (size_t i = 0; i < arr_node_size(nodes); ++i) {
      node_s *n = arr_node_get(nodes, i);
      _draw_circle(canvas, n, nk_rgb(25, 25, 25));
      struct nk_rect text_pos = {n->bound.x + 5, n->bound.y, n->bound.w,
                                 n->bound.h};
      nk_draw_text(canvas, text_pos, n->inner_text, strlen(n->inner_text),
                   ctx->style.font, nk_rgb(255, 0, 0), nk_rgb(0, 255, 0));
    }

#endif
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
