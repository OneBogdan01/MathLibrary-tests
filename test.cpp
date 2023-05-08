#include "pch.h"
#include "./src/Transform.hpp"
#include "./src/World.hpp"
TEST(LinearAlgebra, vec2d)
{
	vec2 a{ 0,0 };
	vec2 b{ 1,23 };
	ASSERT_EQ(0.0f, a.dot(b));
	
}
TEST(LinearAlgebra, localToWorld)
{
	
	//robo upright space
	Transform robo(vec3{1,10,3});
	//upright axis
	vec3 x{ .866f,0,-.5f}, y{0,1,0}, z{0.5f,0,.866f};
	World world {x,y,z};
	vec3 w=world.ToGlobalSpace(vec3(0, 5, 10.0f))+robo.getPosition();
	ASSERT_EQ(vec3(6, 15, 11.66f), w)<<" wrong because:"<<w.x<<" "<<w.y<<" "<<w.z<<"\n";
	vec3 pos={0,0,0};
	vec3 o=robo.ToObjectSpace(pos,world);
	ASSERT_EQ(vec3(0.634f, -10.0f, -3.098f), o)<<" wrong because:"<<o.x<<" "<<o.y<<" "<<o.z<<"\n";
	
}
