#pragma once
#include "dependente\glm\ext.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"


class physics_object {
public:
    physics_object(glm::vec3 position);

    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0), vel = glm::vec3(0.0f, 0.0f, 0);
    float drag = 0.9;
    float angle = 0;
    float angular_velocity = 0;
    void addVel(glm::vec3 v);
    void addAngularVel(float va);

    void deltaT(float dT);
    glm::mat4 getTransform();
};
