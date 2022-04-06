/**
 * @file common.c
 * @brief common function declaration
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
#include "libbsd_string/string.h"
#include "util.h"
#include <string.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear/nuklear.h"
#include "nuklear/nuklear_sdl_gl3.h"

static inline void usage(void) {
  puts("Usage: cgrf [OPTION...] [FILE...]\n"
       "A simple graph visualization program\n"
       "\n"
       "--version           print version\n"
       "--help              print help\n"
       "--file [filename]   specify file\n");
}

void cgrf_bg_clear_color(float r, float g, float b, float a) {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(r, g, b, a);
}

SDL_Window *cgrf_app_init(SDL_GLContext *glContext, int width, int height,
                          const char *window_name) {
  SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_Window *window = SDL_CreateWindow(
      window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
      height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

  if (!window) {
    perror("ERR::WINDOW::CREATION::FAILED");
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  SDL_SetWindowResizable(window, SDL_TRUE);
  *glContext = SDL_GL_CreateContext(window);
  CGRF_UNUSED(glContext);

  if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
    perror("Failed to initialize GLAD");
    exit(EXIT_FAILURE);
  }

  printf("GL Vendor:   %s\n", glGetString(GL_VENDOR));
  printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
  printf("GL Version:  %s\n", glGetString(GL_VERSION));

  return window;
}

float cgrf_calculate_ratio(SDL_Window *window, int *width, int *height) {
  SDL_GetWindowSize(window, width, height);
  return *width / (float)*height;
}

void cgrf_app_routine(SDL_Window *window, int *width, int *height) {
  SDL_GetWindowSize(window, width, height);
  glViewport(0, 0, *width, *height);
  SDL_GL_SwapWindow(window);
}

void cgrf_destroy_terminate_sdl(SDL_Window *window, SDL_GLContext *glContext) {
  nk_sdl_shutdown();
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

#define ARGS_FILE 0
#define ARGS_HELP 1
#define ARGS_VERSION 2

void cgrf_parse_cmd_arguments(int argc, char **argv) {
  if (argc < 2) {
    usage();
    exit(EXIT_FAILURE);
  }
  int opts = -1, option_index = 0;
  static struct option longopts[] = {{"file", required_argument, 0, ARGS_FILE},
                                     {"help", no_argument, 0, ARGS_HELP},
                                     {"version", no_argument, 0, ARGS_VERSION},
                                     {NULL, 0, NULL, 0}};

  while ((opts = getopt_long(argc, argv, "", longopts, &option_index)) != -1) {
    switch (opts) {
    case ARGS_VERSION:
      flag_version = 1;
      printf("VERSION: v%d.%d\n", CGRF_MAJOR_VER, CGRF_MINOR_VER);
      exit(EXIT_SUCCESS);
      break;
    case ARGS_FILE:
      flag_file = 1;
      strlcpy(file, optarg, sizeof(file));
      printf("file to visualize: %s\n", file);
      break;
    case ARGS_HELP:
      flag_help = 1;
      usage();
      exit(EXIT_SUCCESS);
      break;
    case '?':
      exit(EXIT_FAILURE);
      break;
    default:
      usage();
      exit(EXIT_FAILURE);
    }
  }

  for (; optind < argc; optind++) {
    printf("Unknown argument entered ( type --help to get help ): %s\n",
           argv[optind]);
    if (optind + 1 >= argc)
      exit(EXIT_FAILURE);
  }
}

void cgrf_handle_input(struct nk_context *ctx, SDL_Event *evt,
                       _Bool *is_running) {
  nk_input_begin(ctx);
  const uint8_t *state = SDL_GetKeyboardState(NULL);
  while (SDL_PollEvent(evt)) {
    if (evt->type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE] ||
        state[SDL_SCANCODE_CAPSLOCK])
      *is_running = 0;
    nk_sdl_handle_event(evt);
  }
  nk_input_end(ctx);
}
