#ifndef WINDOW_H
#define WINDOW_H

#include "../../libs/glad.h"
#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow* handle;
    int width, height;
    const char* title;
} Window;

Window* window_create(int width, int height, const char* title);
void window_destroy(Window* win);
int window_should_close(Window* win);
void window_swap_buffers(Window* win);
void window_poll_events(void);
float window_get_time(void);

#endif
