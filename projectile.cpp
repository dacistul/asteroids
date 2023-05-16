#define GLM_FORCE_RADIANS
#include "projectile.h"
#include <iostream>

    projectile::projectile(glm::vec3 position) : physics_object(position)
    {
        drag = 1.0;
        vbo = (GLfloat*)__vertices;
        vbo_len = sizeof(__vertices);
        ibo = (GLuint*)__indices;
        ibo_len = sizeof(__indices);
    }

    void projectile::render()
    {
        glUseProgram(shader_ref);
        glBindVertexArray(vao_ref);

        //vertex shader attributes
        unsigned int transformLoc = glGetUniformLocation(shader_ref, "transform");
        //unsigned int scaleLoc = glGetUniformLocation(shader_ref, "scale"); //maybe don't and just use transform
        angle = glm::atan(vel.y / vel.x) - 3.1415926f / 2;
        trans = getTransform();
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //glUniformMatrix4fv(scaleLoc, 1, GL_FALSE, glm::value_ptr(scale)); TODO FIXME
        //glUniform3f();

        //fragment shader attributes
        unsigned int colorLoc = glGetUniformLocation(shader_ref, "color");
        glm::vec4 color = glm::vec4(1.0, 1.0, 0.0, 1.0);
        glUniform4fv(colorLoc, 1, glm::value_ptr(color));

        glDrawElements(GL_TRIANGLES, ibo_len, GL_UNSIGNED_INT, 0);
    }

    glm::vec3 projectile::getPos()
    {
        return physics_object::pos;
    }
