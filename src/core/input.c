#include "input.h"

static Window* window = NULL;
static int keys[512] = {0};
static int prev_keys[512] = {0};
static double mouse_x = 0, mouse_y = 0;
static double mouse_dx = 0, mouse_dy = 0;
static double last_x = 0, last_y = 0;
static int first_mouse = 1;

static void key_callback(GLFWwindow* handle, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) keys[key] = 1;
    else if (action == GLFW_RELEASE) keys[key] = 0;
}

static void mouse_callback(GLFWwindow* handle, double xpos, double ypos) {
    if (first_mouse) {
        last_x = xpos;
        last_y = ypos;
        first_mouse = 0;
    }
    mouse_dx = xpos - last_x;
    mouse_dy = last_y - ypos;
    last_x = xpos;
    last_y = ypos;
    mouse_x = xpos;
    mouse_y = ypos;
}

void input_init(Window* win) {
    window = win;
    glfwSetKeyCallback(win->handle, key_callback);
    glfwSetCursorPosCallback(win->handle, mouse_callback);
    glfwSetInputMode(win->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

int input_key_down(int key) {
    return keys[key];
}

int input_key_pressed(int key) {
    return keys[key] && !prev_keys[key];
}

float input_mouse_x(void) {
    return (float)mouse_x;
}

float input_mouse_y(void) {
    return (float)mouse_y;
}

float input_mouse_dx(void) {
    return (float)mouse_dx;
}

float input_mouse_dy(void) {
    return (float)mouse_dy;
}

void input_update(void) {
    memcpy(prev_keys, keys, sizeof(keys));
    mouse_dx = 0;
    mouse_dy = 0;
}
