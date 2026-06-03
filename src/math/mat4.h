#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"

typedef struct {
    float m[4][4];
} Mat4;

// Creation
Mat4 mat4_identity(void);
Mat4 mat4_zero(void);

// Transformations
Mat4 mat4_translate(Vec3 t);
Mat4 mat4_scale(Vec3 s);
Mat4 mat4_rotate_x(float angle);
Mat4 mat4_rotate_y(float angle);
Mat4 mat4_rotate_z(float angle);
Mat4 mat4_look_at(Vec3 eye, Vec3 target, Vec3 up);
Mat4 mat4_perspective(float fov, float aspect, float near, float far);

// Operations
Mat4 mat4_mul(Mat4 a, Mat4 b);
Vec3 mat4_mul_vec3(Mat4 m, Vec3 v);
Mat4 mat4_transpose(Mat4 m);

#endif
