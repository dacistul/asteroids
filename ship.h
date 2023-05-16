#pragma once

#include "dependente\glm\glm.hpp"
#include "dependente/glew/glew.h"

#include "collisions.h"
#include "rendered_object.h"
#include "physics_object.h"
#include "projectile.h"

class ship : public physics_object, public rendered_object, public disc_collider {
public:

    float health = 5.0f;

    ship(glm::vec3 position);

    void pointTo(glm::vec3 dest);

    void render() override;

    projectile shoot();

    glm::vec3 getPos() override;

private:
    constexpr static GLfloat __vertices[9] = {
        0.03f, -0.02f, 0.0f,
        0.00f, 0.06f, 0.0f,
        -0.03f, -0.02f, 0.0f
        // spaceship
    };
    constexpr static GLuint __indices[3] = {  // note that we start from 0!
        0, 1, 2  // spaceship
    };

};
