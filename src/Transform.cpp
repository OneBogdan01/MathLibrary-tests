#include "Transform.hpp"

Transform::Transform(vec3 &parent,vec3 pos):
    parent(&parent),
    position(pos) 
{

}

Transform::Transform()
{
    parent=nullptr;
}

Transform::~Transform()
{
}

const vec3 Transform::GetParentPosition()
{
    return *parent;
}

