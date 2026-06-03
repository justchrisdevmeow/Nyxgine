#include "vec3.h"

Vec3 vec3(float x, float y, float z) {
    Vec3 v = {x, y, z};
    return v;
}

Vec3 vec3_zero(void) {
    return vec3(0, 0, 0);
}

Vec3 vec3_one(void) {
    return vec3(1, 1, 1);
}

Vec3 vec3_add(Vec3 a, Vec3 b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 vec3_mul(Vec3 v, float s) {
    return vec3(v.x * s, v.y * s, v.z * s);
}

Vec3 vec3_div(Vec3 v, float s) {
    return vec3(v.x / s, v.y / s, v.z / s);
}

Vec3 vec3_neg(Vec3 v) {
    return vec3(-v.x, -v.y, -v.z);
}

float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3_len(Vec3 v) {
    return sqrtf(vec3_dot(v, v));
}

float vec3_len_sq(Vec3 v) {
    return vec3_dot(v, v);
}

Vec3 vec3_norm(Vec3 v) {
    float len = vec3_len(v);
    if (len == 0) return vec3_zero();
    return vec3_div(v, len);
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

void vec3_add_eq(Vec3 *v, Vec3 a) {
    v->x += a.x;
    v->y += a.y;
    v->z += a.z;
}

void vec3_sub_eq(Vec3 *v, Vec3 a) {
    v->x -= a.x;
    v->y -= a.y;
    v->z -= a.z;
}

void vec3_mul_eq(Vec3 *v, float s) {
    v->x *= s;
    v->y *= s;
    v->z *= s;
}
