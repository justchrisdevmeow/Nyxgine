#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../math/vec3.h"

typedef struct {
    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;
    float mass;
    float restitution;
    int use_gravity;
} RigidBody;

RigidBody* rigidbody_create(Vec3 pos, float mass);
void rigidbody_destroy(RigidBody* rb);
void rigidbody_add_force(RigidBody* rb, Vec3 force);
void rigidbody_add_impulse(RigidBody* rb, Vec3 impulse);
void rigidbody_update(RigidBody* rb, float dt);
void rigidbody_set_gravity(RigidBody* rb, int enable);

#endif
