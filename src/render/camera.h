#ifndef CAMERA_H
#define CAMERA_H

#include "../math/vec3.h"
#include "../math/mat4.h"

typedef struct {
    Vec3 position;
    Vec3 front;
    Vec3 up;
    float yaw;
    float pitch;
    float fov;
    float aspect;
    float near;
    float far;
} Camera;

Camera* camera_create(float aspect);
void camera_destroy(Camera* cam);
void camera_update(Camera* cam);
Mat4 camera_get_view(Camera* cam);
Mat4 camera_get_projection(Camera* cam);
void camera_process_mouse(Camera* cam, float dx, float dy);
void camera_process_keyboard(Camera* cam, float dt);

#endif
