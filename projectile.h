#pragma once

#include "dependente\glm\glm.hpp"
#include "dependente/glew/glew.h"
#include "dependente/glm/gtc/type_ptr.hpp"

#include "collisions.h"
#include "rendered_object.h"
#include "physics_object.h"

class projectile : public physics_object, public rendered_object, public collider {
public:
    projectile(glm::vec3 position);
    projectile() : projectile(glm::vec3(0,0,0)){};

    void render() override;

    glm::vec3 getPos() override;

    //projectile(projectile const&){}

private:
    constexpr static GLfloat __vertices[12] =
    {
        -0.01, 0.1, 0.0,
        0.01,  0.1, 0.0,
        -0.01, -0.1, 0.0,
        0.01,  -0.1, 0.0
    };
    constexpr static GLuint __indices[6] =
    {
      0, 2, 3,
      3, 1, 0
    };
};
