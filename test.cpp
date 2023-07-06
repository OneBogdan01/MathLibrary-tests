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
//displays to cout the insides of 3x3 matrix
std::ostream& operator<<(std::ostream& os, mat3x3 const& m) {
	for (int i = 0; i < 3; i++)
	{
		os << "\n";

		for (int j = 0; j < 3; j++)
		{
			os << m.m[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}
//displays to cout the insides of 3x3 matrix
std::ostream& operator<<(std::ostream& os, mat2x2 const& m) {
	for (int i = 0; i < 2; i++)
	{
		os << "\n";

		for (int j = 0; j < 2; j++)
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
TEST(LinearAlgebra, 2DRotation)
{
	mat2x2 currentR;
	mat2x2 r;
	mat2x2 rotated;
	const float angleToRotate = PI / 2.0f;
	rotated.m[0][0] = cos(angleToRotate);
	rotated.m[0][1] = sin(angleToRotate);
	rotated.m[1][0] = -sin(angleToRotate);
	rotated.m[1][1] = cos(angleToRotate);

	mat2x2::Rotate2D(angleToRotate, r);

	ASSERT_EQ(currentR * r, rotated) << r;

}
TEST(LinearAlgebra, 3DRotation)
{
	const mat3x3 currentR;
	mat3x3 r;
	mat3x3 rotated;
	const float angleToRotate = -15 * PI / 180;
	//some magic rotation answer from here: https://gamemath.com/book/answers.html#matrixtransforms
	//to int for easier comparison
	rotated.m[0][0] = 968;
	rotated.m[0][1] = -212;
	rotated.m[0][2] = -131;

	rotated.m[1][0] = 203;
	rotated.m[1][1] = 976;
	rotated.m[1][2] = -84;

	rotated.m[2][0] = 146;
	rotated.m[2][1] = 54;
	rotated.m[2][2] = 988;


	mat3x3::Rotate3D(angleToRotate, vec3(0.267f, -0.535f, 0.802f), r);

	ASSERT_EQ(mat3x3::RoundToInt(currentR * r), rotated) << r;

}
TEST(LinearAlgebra, 3DUniformScaling)
{
	mat3x3 currentR;
	mat3x3 rotated;
	rotated.m[0][0] = 2;
	rotated.m[1][1] = 2;
	rotated.m[2][2] = 2;
	mat3x3 r;
	r.m[0][1] = -1;
	mat3x3::Scale(r, 2);
	ASSERT_EQ(currentR * r, rotated) << r;

}
TEST(LinearAlgebra, 3DScalingAroundAxis)
{
	mat3x3 rotated;
	rotated.m[0][0] = 1.285f;
	rotated.m[0][1] = -0.571f;
	rotated.m[0][2] = 0.857f;

	rotated.m[1][0] = -0.571f;
	rotated.m[1][1] = 2.145f;
	rotated.m[1][2] = -1.716f;

	rotated.m[2][0] = 0.857f;
	rotated.m[2][1] = -1.716f;
	rotated.m[2][2] = 3.573f;

	mat3x3 r;
	r.m[0][1] = -1;
	mat3x3::ScaleAlongAxis(r, 5, vec3(0.267f, -0.535f, 0.802f));

	ASSERT_EQ(mat3x3::RoundToInt(r), mat3x3::RoundToInt(rotated)) << r;

}
TEST(LinearAlgebra, 3DOrthographicProjection)
{
	mat3x3 projected;
	projected.m[0][0] = 0.929f;
	projected.m[0][1] = 0.143f;
	projected.m[0][2] = -0.214f;

	projected.m[1][0] = 0.143f;
	projected.m[1][1] = 0.714f;
	projected.m[1][2] = 0.429f;

	projected.m[2][0] = -0.214f;
	projected.m[2][1] = 0.429f;
	projected.m[2][2] = 0.357f;

	mat3x3 r;
	r.m[0][1] = -1;
	mat3x3::OrthographicProjection(r, vec3(0.267f, -0.535f, 0.802f));

	ASSERT_EQ(mat3x3::RoundToInt(r), mat3x3::RoundToInt(projected)) << r;

}
TEST(LinearAlgebra, 3DReflection)
{
	mat3x3 projected;
	projected.m[0][0] = 0.857f;
	projected.m[0][1] = 0.286f;
	projected.m[0][2] = -0.428f;

	projected.m[1][0] = 0.286f;
	projected.m[1][1] = 0.428f;
	projected.m[1][2] = 0.858f;

	projected.m[2][0] = -0.428f;
	projected.m[2][1] = 0.858f;
	projected.m[2][2] = -0.286f;

	mat3x3 r;
	r.m[0][1] = -1;
	mat3x3::Reflection(r, vec3(0.267f, -0.535f, 0.802f));

	ASSERT_EQ(mat3x3::RoundToInt(r), mat3x3::RoundToInt(projected)) << r;

}