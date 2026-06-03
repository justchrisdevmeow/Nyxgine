#include "rigidbody.h"
#include <stdlib.h>

static const Vec3 GRAVITY = {0, -9.8f, 0};

RigidBody* rigidbody_create(Vec3 pos, float mass) {
    RigidBody* rb = (RigidBody*)malloc(sizeof(RigidBody));
    rb->position = pos;
    rb->velocity = vec3_zero();
    rb->acceleration = vec3_zero();
    rb->mass = mass;
    rb->restitution = 0.5f;
    rb->use_gravity = 1;
    return rb;
}

void rigidbody_destroy(RigidBody* rb) {
    free(rb);
}

void rigidbody_add_force(RigidBody* rb, Vec3 force) {
    Vec3 acc = vec3_div(force, rb->mass);
    rb->acceleration = vec3_add(rb->acceleration, acc);
}

void rigidbody_add_impulse(RigidBody* rb, Vec3 impulse) {
    rb->velocity = vec3_add(rb->velocity, vec3_div(impulse, rb->mass));
}

void rigidbody_update(RigidBody* rb, float dt) {
    if (rb->use_gravity) {
        rigidbody_add_force(rb, vec3_mul(GRAVITY, rb->mass));
    }
    
    rb->velocity = vec3_add(rb->velocity, vec3_mul(rb->acceleration, dt));
    rb->position = vec3_add(rb->position, vec3_mul(rb->velocity, dt));
    
    // Ground collision
    if (rb->position.y < 0) {
        rb->position.y = 0;
        if (rb->velocity.y < 0) {
            rb->velocity.y = -rb->velocity.y * rb->restitution;
            if (rb->velocity.y < 0.1f) rb->velocity.y = 0;
        }
    }
    
    rb->acceleration = vec3_zero();
}
