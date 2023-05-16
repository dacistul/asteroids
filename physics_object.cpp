#include "physics_object.h"
#include <iostream>

    physics_object::physics_object(glm::vec3 position)
    {
        pos = position;
    }

    void physics_object::addVel(glm::vec3 v)
    {
        vel += v;
    }
    void physics_object::addAngularVel(float va)
    {
        angular_velocity += va;
    }
    
    void physics_object::deltaT(float dT)
    {
        pos += vel * dT;
        vel *= drag;//TODO this should be affected by dT
        angle += angular_velocity * dT;
        angular_velocity *= drag;
    }

    glm::mat4 physics_object::getTransform()
    {
        auto trans = glm::translate(glm::mat4(1.0f), pos);
        //std::cout << angle << "\n";
        trans = glm::rotate(trans, angle, glm::vec3(0.0, 0.0, 1.0));
        return trans;
    }
