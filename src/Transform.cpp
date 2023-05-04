#include "Transform.hpp"

Transform::Transform(vec3& parent, vec3 pos) :
	parent(&parent),
	position(pos)
{

}

Transform::Transform()
{
	parent = nullptr;
}

Transform::~Transform()
= default;

const vec3 Transform::GetParentPosition() const
{
	return *parent;
}

