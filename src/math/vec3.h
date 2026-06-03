#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct {
    float x, y, z;
} Vec3;

// Creation
Vec3 vec3(float x, float y, float z);
Vec3 vec3_zero(void);
Vec3 vec3_one(void);

// Operations
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_mul(Vec3 v, float s);
Vec3 vec3_div(Vec3 v, float s);
Vec3 vec3_neg(Vec3 v);

// Math
float vec3_dot(Vec3 a, Vec3 b);
float vec3_len(Vec3 v);
float vec3_len_sq(Vec3 v);
Vec3 vec3_norm(Vec3 v);
Vec3 vec3_cross(Vec3 a, Vec3 b);

// In-place
void vec3_add_eq(Vec3 *v, Vec3 a);
void vec3_sub_eq(Vec3 *v, Vec3 a);
void vec3_mul_eq(Vec3 *v, float s);

#endif
