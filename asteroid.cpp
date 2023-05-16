#include "asteroid.h"

glm::vec3 asteroid::__vertices[];
GLuint asteroid::__indices[];

float asteroid::startingHealth=4;

    asteroid::asteroid(glm::vec3 position, float size) : physics_object(position), disc_collider(glm::vec3(0.0f, 0.0f, 0), size)
    {
        drag=1;
        health=startingHealth;
        vbo = (GLfloat*)__vertices;
        vbo_len = sizeof(__vertices);
        ibo = (GLuint*)__indices;
        ibo_len = sizeof(__indices);
    }

    void asteroid::init()
    {
        __vertices[0] = glm::vec3(0.0f, 0.0f, 0);

        for (int i = 0; i < points; i++)
        {
            float offset = (rand() % 10) * 0.03f + 0.2f;
            float angle = 3.14159f * 2 / points * (i);
            __vertices[i + 1] = glm::vec3(glm::sin(angle), glm::cos(angle), 0) * offset*r*2.1f;
        }

        for (int i = 1; i < points; i++)
        {
            __indices[i * 3] = i + 1;
            __indices[i * 3 + 1] = i;
            __indices[i * 3 + 2] = 0;
        }

        __indices[0] = 1;
        __indices[1] = points;
        __indices[2] = 0;

        rendered_object::init();
    }


    void asteroid::render() {
        glUseProgram(shader_ref);
        glBindVertexArray(vao_ref);

        //vertex shader attributes
        unsigned int transformLoc = glGetUniformLocation(shader_ref, "transform");
        trans = getTransform();
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        //fragment shader attributes
        unsigned int colorLoc = glGetUniformLocation(shader_ref, "color");
        glm::vec4 color = deadColor+(fullColor-deadColor)*health/(float)startingHealth;
        glUniform4fv(colorLoc, 1, glm::value_ptr(color));

        glDrawElements(GL_TRIANGLES, ibo_len, GL_UNSIGNED_INT, 0);
    }

    glm::vec3 asteroid::getPos()
    {
        return physics_object::pos;
    }
