#include "quat.h"
#include <math.h>

static float rad(float deg) {
    return deg * 3.14159265359f / 180.0f;
}

Quat quat(float x, float y, float z, float w) {
    Quat q = {x, y, z, w};
    return q;
}

Quat quat_identity(void) {
    return quat(0, 0, 0, 1);
}

Quat quat_axis_angle(Vec3 axis, float angle) {
    float half = rad(angle) * 0.5f;
    float s = sinf(half);
    axis = vec3_norm(axis);
    return quat(axis.x * s, axis.y * s, axis.z * s, cosf(half));
}

Quat quat_euler(float pitch, float yaw, float roll) {
    float p = rad(pitch) * 0.5f;
    float y = rad(yaw) * 0.5f;
    float r = rad(roll) * 0.5f;
    
    float cp = cosf(p), sp = sinf(p);
    float cy = cosf(y), sy = sinf(y);
    float cr = cosf(r), sr = sinf(r);
    
    Quat q;
    q.x = sp * cy * cr - cp * sy * sr;
    q.y = cp * sy * cr + sp * cy * sr;
    q.z = cp * cy * sr - sp * sy * cr;
    q.w = cp * cy * cr + sp * sy * sr;
    return q;
}

Quat quat_mul(Quat a, Quat b) {
    return quat(
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
        a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
    );
}

Quat quat_conjugate(Quat q) {
    return quat(-q.x, -q.y, -q.z, q.w);
}

Quat quat_normalize(Quat q) {
    float len = sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
    if (len == 0) return quat_identity();
    return quat(q.x/len, q.y/len, q.z/len, q.w/len);
}

Vec3 quat_rotate_vec3(Quat q, Vec3 v) {
    Quat p = quat(v.x, v.y, v.z, 0);
    Quat r = quat_mul(quat_mul(q, p), quat_conjugate(q));
    return vec3(r.x, r.y, r.z);
}

void quat_to_mat4(Quat q, float mat[4][4]) {
    float xx = q.x * q.x;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float xw = q.x * q.w;
    float yy = q.y * q.y;
    float yz = q.y * q.z;
    float yw = q.y * q.w;
    float zz = q.z * q.z;
    float zw = q.z * q.w;
    
    mat[0][0] = 1 - 2 * (yy + zz);
    mat[0][1] = 2 * (xy - zw);
    mat[0][2] = 2 * (xz + yw);
    mat[0][3] = 0;
    
    mat[1][0] = 2 * (xy + zw);
    mat[1][1] = 1 - 2 * (xx + zz);
    mat[1][2] = 2 * (yz - xw);
    mat[1][3] = 0;
    
    mat[2][0] = 2 * (xz - yw);
    mat[2][1] = 2 * (yz + xw);
    mat[2][2] = 1 - 2 * (xx + yy);
    mat[2][3] = 0;
    
    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}
