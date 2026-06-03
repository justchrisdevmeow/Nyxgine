#ifndef MESH_H
#define MESH_H

#include "../../libs/glad.h"

typedef struct {
    unsigned int vao, vbo;
    int vertex_count;
} Mesh;

Mesh* mesh_create_cube(void);
Mesh* mesh_create_sphere(float radius, int rings, int sectors);
Mesh* mesh_create_plane(float size);
void mesh_draw(Mesh* m);
void mesh_destroy(Mesh* m);

#endif
