#ifndef INPUT_H
#define INPUT_H

#include "window.h"

void input_init(Window* win);
int input_key_down(int key);
int input_key_pressed(int key);
float input_mouse_x(void);
float input_mouse_y(void);
float input_mouse_dx(void);
float input_mouse_dy(void);
void input_update(void);

#endif
