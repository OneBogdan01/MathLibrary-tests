#pragma once
#include "CorePhysics.hpp"
#include "World.hpp"
class Transform
{
private:
	vec3* parent;
	vec3 position;
public:
	Transform(vec3 pos = { 0,0,0 });
	Transform();
	~Transform();
	const vec3 ToObjectSpace(const vec3&,const World&) const;
	const vec3 getParentPosition() const;
	const vec3 getPosition() const;

};
