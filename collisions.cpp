#include "collisions.h"

    bool collision::collided() { return dist <= 0; }


    glm::vec3 collider::getPos() { return glm::vec3(0.0f, 0.0f, 0); };
    
    float collider::getSkin(glm::vec3 direction) { return 0; };
    glm::vec3 collider::getNormal(glm::vec3 direction) { return direction; };
    
    collision collider::getCollision(collider& other) {
        auto pos = this->getPos();
        auto otherPos = other.getPos();
        auto centerToCenter = otherPos - pos;
        auto dir = glm::normalize(centerToCenter);
        auto skin = this->getSkin(dir);
        auto otherSkin = other.getSkin(-dir);
        float distance = glm::length(centerToCenter) - skin - otherSkin;
        return { distance, -other.getNormal(dir) };
    };


    collision inverted_collider::getCollision(collider& other)
    {
        auto col = collider::getCollision(other);
        return { -col.dist,-col.norm };
    }


    disc_collider::disc_collider(glm::vec3 pos, float r) : pos(pos), r(r) {}
    glm::vec3 disc_collider::getPos()
    {
        return pos;
    }
    float disc_collider::getSkin(glm::vec3 direction) { return r; };


    bounding_box::bounding_box(glm::vec3 pos, float w, float h) : pos(pos), w(w), h(h) {}

    glm::vec3 bounding_box::getPos()
    {
        return pos;
    }

    float bounding_box::getSkin(glm::vec3 dir)
    {
        bool xlimit = std::abs(dir.x / w) >= std::abs(dir.y / h);
        //glm::vec2 scaled_vec = {dir.x*w,dir.y*h};
        if (xlimit)
        {
            return glm::length(((dir / dir.x * w)));
        }
        else
        {
            return glm::length((dir / dir.y * h));
        }
    }

    glm::vec3 bounding_box::getNormal(glm::vec3 dir)
    {
        glm::vec3 normal = glm::vec3(0.0f, 0.0f, 0);

        if (dir.x > 0 && dir.x > std::abs(dir.y))
        {
            return glm::vec3(1.0f, 0.0f, 0);
        }
        if (dir.y > 0 && dir.y > std::abs(dir.x))
        {
            return glm::vec3(0.0f, 1.0f, 0);
        }
        if (dir.x<0 && -dir.x>std::abs(dir.y))
        {
            return glm::vec3(-1.0f, 0.0f, 0);
        }
        if (dir.y<0 && -dir.y>std::abs(dir.x))
        {
            return glm::vec3(0.0f, -1.0f, 0);
        }
        return dir; // BUG
    }
