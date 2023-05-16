#pragma once
#include "dependente\glm\glm.hpp"

struct collision {
    float dist; // distance from surface
    glm::vec3 norm; // normal to surface
    bool collided();
};

class collider {
public:
    virtual glm::vec3 getPos();
    /**
     *
     *
     * @returns distance to the surface
     */
    virtual float getSkin(glm::vec3 direction);
    virtual glm::vec3 getNormal(glm::vec3 direction);
    /**
     *
     * @returns null if no collision detected
     */
    virtual collision getCollision(collider& other);
};

class inverted_collider : public collider {
public:
    virtual collision getCollision(collider& other) override;
};

class disc_collider : public collider {
public:
    glm::vec3 pos;
    float r;
    disc_collider(glm::vec3 pos, float r);
    virtual glm::vec3 getPos() override;
    virtual float getSkin(glm::vec3 direction) override;
};

class bounding_box : public inverted_collider {
public:
    glm::vec3 pos;
    float w, h;
    bounding_box(glm::vec3 pos, float w, float h);

    virtual glm::vec3 getPos() override;

    virtual float getSkin(glm::vec3 dir) override;

    virtual glm::vec3 getNormal(glm::vec3 dir) override;
};
