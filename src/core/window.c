#include "window.h"
#include <stdlib.h>

Window* window_create(int width, int height, const char* title) {
    if (!glfwInit()) return NULL;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* handle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!handle) {
        glfwTerminate();
        return NULL;
    }
    
    glfwMakeContextCurrent(handle);
    glfwSwapInterval(1);
    
    Window* win = (Window*)malloc(sizeof(Window));
    win->handle = handle;
    win->width = width;
    win->height = height;
    win->title = title;
    
    return win;
}

void window_destroy(Window* win) {
    if (win && win->handle) {
        glfwDestroyWindow(win->handle);
        glfwTerminate();
    }
    free(win);
}

int window_should_close(Window* win) {
    return win ? glfwWindowShouldClose(win->handle) : 1;
}

void window_swap_buffers(Window* win) {
    if (win) glfwSwapBuffers(win->handle);
}

void window_poll_events(void) {
    glfwPollEvents();
}

float window_get_time(void) {
    return (float)glfwGetTime();
}
