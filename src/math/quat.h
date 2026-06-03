#ifndef QUAT_H
#define QUAT_H

#include "vec3.h"

typedef struct {
    float x, y, z, w;
} Quat;

// Creation
Quat quat(float x, float y, float z, float w);
Quat quat_identity(void);
Quat quat_axis_angle(Vec3 axis, float angle);
Quat quat_euler(float pitch, float yaw, float roll);

// Operations
Quat quat_mul(Quat a, Quat b);
Quat quat_conjugate(Quat q);
Quat quat_normalize(Quat q);
Vec3 quat_rotate_vec3(Quat q, Vec3 v);

// Conversion
void quat_to_mat4(Quat q, float mat[4][4]);

#endif
