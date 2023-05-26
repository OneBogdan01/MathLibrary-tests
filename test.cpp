#include "pch.h"
#include "Transform.hpp"
#include "World.hpp"
TEST(LinearAlgebra, vec2d)
{
	vec2 a{ 0,0 };
	vec2 b{ 1,23 };
	ASSERT_EQ(0.0f, a.dot(b));

}
TEST(LinearAlgebra, localToWorld)
{

	//robo upright space
	Transform robo(vec3{ 1,10,3 });
	//upright axis
	vec3 x{ .866f,0,-.5f }, y{ 0,1,0 }, z{ 0.5f,0,.866f };
	World world{ x,y,z };
	vec3 w = world.ToGlobalSpace(vec3(0, 5, 10.0f)) + robo.getPosition();
	ASSERT_EQ(vec3(6, 15, 11.66f), w) << " wrong because:" << w.x << " " << w.y << " " << w.z << "\n";
	vec3 pos = { 0,0,0 };
	vec3 o = robo.ToObjectSpace(pos, world);
	ASSERT_EQ(vec3(0.634f, -10.0f, -3.098f), o) << " wrong because:" << o.x << " " << o.y << " " << o.z << "\n";

}
std::ostream& operator<<(std::ostream& os, mat3x3 const& m) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			os << m.m[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}
TEST(LinearAlgebra, matrices)
{
	mat3x3 m;
	m.m[0][0] = 10;
	m.m[0][1] = 25;
	mat3x3 transpose_m;
	transpose_m.m[0][0] = 10;
	transpose_m.m[1][0] = 25;
	/*vec3 a = { 1,2.5f,1 };
	mat3x3::rowVectorMultiplication(m, a);*/

	mat3x3 result;
	result.m[0][0] = 725;
	result.m[0][1] = 25;
	result.m[1][0] = 25;
	//ASSERT_EQ(transpose_m, m); */
	ASSERT_EQ(m * transpose_m, result) << m * transpose_m;

}