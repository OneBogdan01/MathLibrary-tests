#include "pch.h"
#include "./src/Transform.hpp"

TEST(LinearAlgebra, vec2d)
{
	vec2 a{ 0,0 };
	vec2 b{ 1,23 };
	ASSERT_EQ(0.0f, a.dot(b));
}
TEST(LinearAlgebra, localToWorld)
{
	vec3 a{ 0,0,1};
	vec3 b{ 1,23,2};
	Transform t(a);
	a.y=5;
	ASSERT_EQ(vec3(0,5,1), t.GetParentPosition());
	
}
