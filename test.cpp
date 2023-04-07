#include "pch.h"
#include  "./src/CorePhysics.hpp"

TEST(DotProduct, vec2d)
{
	vec2 a{ 0,0 };
	vec2 b{ 1,23 };
	ASSERT_EQ(0.0f, a.dot(b));
}