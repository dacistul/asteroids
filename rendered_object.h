#pragma once
#include "dependente\glew\glew.h"
#include "dependente\glm\glm.hpp"

class rendered_object {
public:
    GLfloat* vbo; //array
    size_t vbo_len;
    GLuint* ibo;
    size_t ibo_len;
    glm::mat4 trans = glm::mat4(1.0f);
    // gpu references

    GLuint vbo_ref, vao_ref, ibo_ref;

    static GLuint shader_ref;

    virtual void init();
    virtual void render() = 0;
};
