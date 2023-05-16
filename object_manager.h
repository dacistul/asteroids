#pragma once
#include <cstddef>
#include <functional>

template <typename T, int maxObjects>
class object_manager
{
public:
    T pool[maxObjects];
    bool alive[maxObjects];

    void forEach(std::function<void(int, T&)> objCallback)
    {
        for(int i=0;i<maxObjects;i++)
        {
            if(alive[i])
            {
                objCallback(i,pool[i]);
            }
        }

    }
    int push(T instance)
    {
        for(int i=0;i<maxObjects;i++)
        {
            if(!alive[i])
            {
                pool[i]=instance;
                alive[i]=true;
                return i;
            }
        }
        return -1;
    }
    void erase(int index)
    {
        alive[index]=false;
    }
    size_t size()
    {
        size_t count=0;
        for(bool isAlive : alive)
        {
            if(isAlive)
                count++;
        }
        return count;
    }

};

#include "projectile.h"
typedef object_manager<projectile,100> projectile_manager;

#include "asteroid.h"
typedef object_manager<asteroid,100> asteroid_manager;
