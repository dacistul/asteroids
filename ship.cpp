#define GLM_FORCE_RADIANS
#include "ship.h"
#include <iostream>

    ship::ship(glm::vec3 position) : physics_object(position), disc_collider(glm::vec3(0.0f, 0.0f, 0), 0.06f)
    {
        drag=0.95f;
        vbo = (GLfloat*)__vertices;
        vbo_len = sizeof(__vertices);
        ibo = (GLuint*)__indices;
        ibo_len = sizeof(__indices);
    }

    void ship::pointTo(glm::vec3 dest)
    {
        auto delta = dest - this->getPos();
        //std::cout << delta.x << " " << delta.y << "\n";
        angle = glm::atan(delta.y / delta.x)+3.14159f / 2;
        //std::cout << angle*180/3.14 << "\n";
        if(delta.x>0)
            angle-=3.14159f;
    }

    void ship::render() {
        glUseProgram(shader_ref);
        glBindVertexArray(vao_ref);

        //vertex shader attributes
        unsigned int transformLoc = glGetUniformLocation(shader_ref, "transform");
        trans = getTransform();
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        //fragment shader attributes
        unsigned int colorLoc = glGetUniformLocation(shader_ref, "color");
        glm::vec4 color = glm::vec4(0.5, 0.1, 0.5, 1);
        glUniform4fv(colorLoc, 1, glm::value_ptr(color));

        glDrawElements(GL_TRIANGLES, ibo_len, GL_UNSIGNED_INT, 0);
    }

    projectile ship::shoot()
    {
        projectile latifi = projectile(physics_object::pos);
        latifi.init();
        latifi.angle = this->angle;
        glm::vec3 sped = glm::vec3(glm::cos(angle + 3.14 / 2), glm::sin(angle + 3.14 / 2), 0);
        latifi.addVel(5.0f * sped);
        return latifi;
    }

    glm::vec3 ship::getPos()
    {
        return physics_object::pos;
    }
