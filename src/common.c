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

static inline void usage(void) {
  puts("Usage: cgrf [OPTION...] [FILE...]\n"
       "A simple graph visualization program\n"
       "\n"
       "--version           print version\n"
       "--help              print help\n"
       "--file [filename]   specify file\n");
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  CGRF_UNUSED(window);
  CGRF_UNUSED(xpos);
  CGRF_UNUSED(ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  CGRF_UNUSED(window);
  CGRF_UNUSED(xoffset);
  CGRF_UNUSED(yoffset);
}

void error_callback(int error, const char *description) {
  CGRF_UNUSED(error);
  fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  CGRF_UNUSED(window);
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  CGRF_UNUSED(scancode);
  CGRF_UNUSED(mods);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void cgrf_gl_clear_color(float clear_color[4]) {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
}

GLFWwindow *cgrf_glfw_glad_init(int width, int height,
                                const char *window_name) {
  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(width, height, window_name, NULL, NULL);

  if (!window) {
    perror("ERR::WINDOW::CREATION::FAILED");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGL(glfwGetProcAddress)) {
    perror("Failed to initialize GLAD");
    exit(EXIT_FAILURE);
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetErrorCallback(error_callback);

  printf("Vendor:   %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version:  %s\n", glGetString(GL_VERSION));

  glfwSwapInterval(1);
  return window;
}

float cgrf_calculate_ratio(GLFWwindow *window, int *width, int *height) {
  glfwGetFramebufferSize(window, width, height);
  return *width / (float)*height;
}

void cgrf_glfw_routine(GLFWwindow *window, int *width, int *height) {
  glfwGetWindowSize(window, width, height);
  glViewport(0, 0, *width, *height);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void cgrf_destroy_terminate_glfw(GLFWwindow *window) {
  glfwDestroyWindow(window);
  glfwTerminate();
}

#define ARGS_FILE 0
#define ARGS_HELP 1
#define ARGS_VERSION 2

void cgrf_parse_cmd_arguments(int argc, char **argv) {
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

void cgrf_handle_input(GLFWwindow *win) {
  if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(win, GLFW_TRUE);
}
