#include "camera.h"
#include <stdlib.h>
#include <math.h>

static const float PI = 3.14159265359f;

Camera* camera_create(float aspect) {
    Camera* cam = (Camera*)malloc(sizeof(Camera));
    cam->position = vec3(0, 2, 5);
    cam->front = vec3(0, 0, -1);
    cam->up = vec3(0, 1, 0);
    cam->yaw = -90.0f;
    cam->pitch = 0.0f;
    cam->fov = 70.0f;
    cam->aspect = aspect;
    cam->near = 0.1f;
    cam->far = 100.0f;
    camera_update(cam);
    return cam;
}

void camera_destroy(Camera* cam) {
    free(cam);
}

void camera_update(Camera* cam) {
    Vec3 front;
    front.x = cos(cam->yaw * PI / 180.0f) * cos(cam->pitch * PI / 180.0f);
    front.y = sin(cam->pitch * PI / 180.0f);
    front.z = sin(cam->yaw * PI / 180.0f) * cos(cam->pitch * PI / 180.0f);
    cam->front = vec3_norm(front);
}

Mat4 camera_get_view(Camera* cam) {
    return mat4_look_at(cam->position, vec3_add(cam->position, cam->front), cam->up);
}

Mat4 camera_get_projection(Camera* cam) {
    return mat4_perspective(cam->fov, cam->aspect, cam->near, cam->far);
}

void camera_process_mouse(Camera* cam, float dx, float dy) {
    float sensitivity = 0.2f;
    cam->yaw += dx * sensitivity;
    cam->pitch -= dy * sensitivity;
    
    if (cam->pitch > 89.0f) cam->pitch = 89.0f;
    if (cam->pitch < -89.0f) cam->pitch = -89.0f;
    
    camera_update(cam);
}

void camera_process_keyboard(Camera* cam, float dt) {
    float speed = 5.0f * dt;
    Vec3 right = vec3_cross(cam->front, cam->up);
    
    // Assume input keys are handled externally
    // This will be integrated with input.c later
}
