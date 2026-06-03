#include "mat4.h"
#include <string.h>

static float rad(float deg) {
    return deg * 3.14159265359f / 180.0f;
}

Mat4 mat4_identity(void) {
    Mat4 m = {0};
    for (int i = 0; i < 4; i++) m.m[i][i] = 1.0f;
    return m;
}

Mat4 mat4_zero(void) {
    Mat4 m = {0};
    return m;
}

Mat4 mat4_translate(Vec3 t) {
    Mat4 m = mat4_identity();
    m.m[0][3] = t.x;
    m.m[1][3] = t.y;
    m.m[2][3] = t.z;
    return m;
}

Mat4 mat4_scale(Vec3 s) {
    Mat4 m = mat4_identity();
    m.m[0][0] = s.x;
    m.m[1][1] = s.y;
    m.m[2][2] = s.z;
    return m;
}

Mat4 mat4_rotate_x(float angle) {
    float c = cosf(rad(angle));
    float s = sinf(rad(angle));
    Mat4 m = mat4_identity();
    m.m[1][1] = c;
    m.m[1][2] = -s;
    m.m[2][1] = s;
    m.m[2][2] = c;
    return m;
}

Mat4 mat4_rotate_y(float angle) {
    float c = cosf(rad(angle));
    float s = sinf(rad(angle));
    Mat4 m = mat4_identity();
    m.m[0][0] = c;
    m.m[0][2] = s;
    m.m[2][0] = -s;
    m.m[2][2] = c;
    return m;
}

Mat4 mat4_rotate_z(float angle) {
    float c = cosf(rad(angle));
    float s = sinf(rad(angle));
    Mat4 m = mat4_identity();
    m.m[0][0] = c;
    m.m[0][1] = -s;
    m.m[1][0] = s;
    m.m[1][1] = c;
    return m;
}

Mat4 mat4_look_at(Vec3 eye, Vec3 target, Vec3 up) {
    Vec3 f = vec3_norm(vec3_sub(target, eye));
    Vec3 r = vec3_norm(vec3_cross(f, up));
    Vec3 u = vec3_cross(r, f);
    
    Mat4 m = mat4_identity();
    m.m[0][0] = r.x;
    m.m[0][1] = r.y;
    m.m[0][2] = r.z;
    m.m[1][0] = u.x;
    m.m[1][1] = u.y;
    m.m[1][2] = u.z;
    m.m[2][0] = -f.x;
    m.m[2][1] = -f.y;
    m.m[2][2] = -f.z;
    m.m[0][3] = -vec3_dot(r, eye);
    m.m[1][3] = -vec3_dot(u, eye);
    m.m[2][3] = vec3_dot(f, eye);
    return m;
}

Mat4 mat4_perspective(float fov, float aspect, float near, float far) {
    float tan_half = tanf(rad(fov) / 2.0f);
    Mat4 m = mat4_zero();
    m.m[0][0] = 1.0f / (aspect * tan_half);
    m.m[1][1] = 1.0f / tan_half;
    m.m[2][2] = -(far + near) / (far - near);
    m.m[2][3] = -(2.0f * far * near) / (far - near);
    m.m[3][2] = -1.0f;
    return m;
}

Mat4 mat4_mul(Mat4 a, Mat4 b) {
    Mat4 m = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                m.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return m;
}

Vec3 mat4_mul_vec3(Mat4 m, Vec3 v) {
    float x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
    float y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
    float z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
    float w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3];
    return vec3(x / w, y / w, z / w);
}

Mat4 mat4_transpose(Mat4 m) {
    Mat4 t;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            t.m[i][j] = m.m[j][i];
    return t;
}
