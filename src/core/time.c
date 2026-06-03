#include "time.h"
#include "window.h"

static float last_time = 0;
static float delta_time = 0;

void time_update(void) {
    float now = window_get_time();
    delta_time = now - last_time;
    last_time = now;
}

float time_delta(void) {
    return delta_time;
}

float time_now(void) {
    return window_get_time();
}
