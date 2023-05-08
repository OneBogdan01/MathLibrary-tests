#pragma once
#include "CorePhysics.hpp"
class World
{
private:
//basis
    vec3 i, j ,k;
//actual basis
    vec3 x, y ,z;
public:
    World();
    World(vec3 x, vec3 y, vec3 z);
    const vec3 ToGlobalSpace(const vec3& pos)const;
    ~World();
    const  vec3 getX() const{
        return x;
    }
    const  vec3 getY() const{
        return y;
    }
    const  vec3 getZ() const{
        return z;
    }
};
