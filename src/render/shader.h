#ifndef SHADER_H
#define SHADER_H

typedef struct {
    unsigned int id;
} Shader;

Shader* shader_create(const char* vert_src, const char* frag_src);
void shader_destroy(Shader* s);
void shader_use(Shader* s);
void shader_set_int(Shader* s, const char* name, int value);
void shader_set_float(Shader* s, const char* name, float value);
void shader_set_vec3(Shader* s, const char* name, float x, float y, float z);
void shader_set_mat4(Shader* s, const char* name, float* mat);

#endif
