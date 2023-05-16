#include "rendered_object.h"

GLuint rendered_object::shader_ref;

    void rendered_object::init() {
        glGenVertexArrays(1, &vao_ref);
        glGenBuffers(1, &vbo_ref);
        glGenBuffers(1, &ibo_ref);

        //bind VAO
        glBindVertexArray(vao_ref);

        //bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ref);
        glBufferData(GL_ARRAY_BUFFER, vbo_len, vbo, GL_STATIC_DRAW);

        //bind IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_ref);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo_len, ibo, GL_STATIC_DRAW);

        //set attribute pointers
        glVertexAttribPointer(
            0,                  // attribute 0, must match the layout in the shader.
            3,                  // size of each attribute
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            3 * sizeof(float),  // stride
            (void*)0            // array buffer offset
        );

        glEnableVertexAttribArray(0);
    };
