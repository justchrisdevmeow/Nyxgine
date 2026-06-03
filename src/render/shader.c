#include "shader.h"
#include <stdlib.h>
#include <stdio.h>

static unsigned int compile_shader(const char* src, unsigned int type) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(id, 512, NULL, log);
        printf("Shader compile error: %s\n", log);
        glDeleteShader(id);
        return 0;
    }
    return id;
}

Shader* shader_create(const char* vert_src, const char* frag_src) {
    Shader* s = (Shader*)malloc(sizeof(Shader));
    unsigned int vert = compile_shader(vert_src, GL_VERTEX_SHADER);
    unsigned int frag = compile_shader(frag_src, GL_FRAGMENT_SHADER);
    
    s->id = glCreateProgram();
    glAttachShader(s->id, vert);
    glAttachShader(s->id, frag);
    glLinkProgram(s->id);
    
    int success;
    glGetProgramiv(s->id, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(s->id, 512, NULL, log);
        printf("Shader link error: %s\n", log);
    }
    
    glDeleteShader(vert);
    glDeleteShader(frag);
    return s;
}

void shader_destroy(Shader* s) {
    glDeleteProgram(s->id);
    free(s);
}

void shader_use(Shader* s) {
    glUseProgram(s->id);
}

void shader_set_int(Shader* s, const char* name, int value) {
    glUniform1i(glGetUniformLocation(s->id, name), value);
}

void shader_set_float(Shader* s, const char* name, float value) {
    glUniform1f(glGetUniformLocation(s->id, name), value);
}

void shader_set_vec3(Shader* s, const char* name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(s->id, name), x, y, z);
}

void shader_set_mat4(Shader* s, const char* name, float* mat) {
    glUniformMatrix4fv(glGetUniformLocation(s->id, name), 1, GL_FALSE, mat);
}
