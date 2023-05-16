#pragma once

#include "dependente\glm\glm.hpp"

#include "collisions.h"
#include "rendered_object.h"
#include "physics_object.h"

class asteroid : public physics_object, public rendered_object, public disc_collider {
public:

    static constexpr glm::vec4 fullColor=glm::vec4(0.0f,1.0f,0.0f,1.0f);
    static constexpr glm::vec4 deadColor=glm::vec4(1.0f,0.0f,0.0f,1.0f);


    asteroid(glm::vec3 position, float size);
    asteroid() : asteroid(glm::vec3(0,0,0),1.0f){};
    static float startingHealth;
    float health;

    void init() override;


    virtual void render() override;

    virtual glm::vec3 getPos() override;

private:
    constexpr static int points = 10;
    static glm::vec3 __vertices[points + 1]; // {flaot, float, float},{flaot, float, float},{flaot, float, float}
    static GLuint __indices[(points + 1) * 3];
};
