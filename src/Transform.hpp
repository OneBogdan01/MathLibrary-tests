#pragma once
#include "CorePhysics.hpp"
class Transform
{
private:
    vec3 *parent;
    vec3 position;
public:
    Transform(vec3 &parent,vec3 pos={0,0,0});
    Transform();
    ~Transform();

    const vec3 GetParentPosition();
};
