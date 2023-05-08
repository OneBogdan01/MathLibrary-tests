#include "Transform.hpp"
Transform::Transform(vec3 pos) :
	position(pos)
{

}

Transform::Transform()
{
	parent = nullptr;
}

Transform::~Transform()
= default;

const vec3 Transform::ToObjectSpace(const vec3 &pos,const World& w) const
{
	vec3 upright=pos-position;
    return {w.getX().dot(upright), w.getY().dot( upright), w.getZ().dot(upright)};   
}


const vec3 Transform::getParentPosition() const
{
	return *parent;
}

const vec3 Transform::getPosition() const
{
    return position;
}
