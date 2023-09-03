#include "pch.h"
#include "Transform.hpp"

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
std::ostream& operator<<(std::ostream& os, vec3 const& m) {
	for (int i = 0; i < 3; i++)
	{
		os << m.cell[i];

		os << " ";
	}
	os << "\n";

	return os;
}
std::ostream& operator<<(std::ostream& os, vec2 const& m) {
	for (int i = 0; i < 2; i++)
	{
		os << m.cell[i];

		os << "\n";
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, mat4x4 const& m) {
	for (int i = 0; i < 4; i++)
	{
		os << "\n";

		for (int j = 0; j < 4; j++)
		{
			os << m.m[i][j] << " ";
		}
		os << "\n";
	}
	return os;
}
//displays to cout the insides of 2x2 matrix
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
std::ostream& operator<<(std::ostream& os, poco2 const& m) {


	os << m.r << " " << m.a << " ";

	os << "\n";

	return os;
}
std::ostream& operator<<(std::ostream& os, spco3 const& m) {


	os << m.r << " " << m.h << " " << m.p << " ";

	os << "\n";

	return os;
}



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
	vec3 w = world.ToGlobalSpace(vec3(0, 5, 10.0f));
	w = w + robo.getPosition();
	ASSERT_EQ(vec3(6, 15, 11.66f), w) << " wrong because:" << w.x << " " << w.y << " " << w.z << "\n";
	vec3 pos = { 0,0,0 };
	vec3 o = robo.ToObjectSpace(pos, world);
	ASSERT_EQ(vec3(0.634f, -10.0f, -3.098f), o) << " wrong because:" << o.x << " " << o.y << " " << o.z << "\n";

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
TEST(LinearAlgebra, 3DMultipleAffineTransformations)
{
	mat3x3 rotate30;
	mat3x3 rotate20;
	mat3x3 rotated;
	mat3x3 rotated2;
	float angleToRotate = PI / 6;
	rotated.m[0][0] = 0.866f;
	rotated.m[0][1] = -0.187f;
	rotated.m[0][2] = -0.464f;

	rotated.m[1][0] = 0;
	rotated.m[1][1] = 0.927f;
	rotated.m[1][2] = -0.375;

	rotated.m[2][0] = 0.5f;
	rotated.m[2][1] = 0.324f;
	rotated.m[2][2] = 0.803f;

	rotated2.m[0][0] = 0.866f;
	rotated2.m[0][1] = 0;
	rotated2.m[0][2] = 0.5f;

	rotated2.m[1][0] = -0.187f;
	rotated2.m[1][1] = 0.927f;
	rotated2.m[1][2] = 0.324f;

	rotated2.m[2][0] = -0.464f;
	rotated2.m[2][1] = -0.375f;
	rotated2.m[2][2] = 0.803f;
	//rotate 30 degress in object space then -22 in world
	mat3x3::Rotate3D(angleToRotate, vec3(0, 1, 0), rotate30);
	angleToRotate = -22 * PI / 180;
	mat3x3::Rotate3D(angleToRotate, vec3(1, 0, 0), rotate20);

	mat3x3 r = rotate30 * rotate20;
	ASSERT_EQ(mat3x3::RoundToInt(r), mat3x3::RoundToInt(rotated)) << r;
	//world to object
	angleToRotate = 22 * PI / 180;

	mat3x3::Rotate3D(angleToRotate, vec3(1, 0, 0), rotate20);
	angleToRotate = -PI / 6;
	mat3x3::Rotate3D(angleToRotate, vec3(0, 1, 0), rotate30);
	r = rotate20 * rotate30;

	ASSERT_EQ(mat3x3::RoundToInt(r), mat3x3::RoundToInt(rotated2)) << r;

}
TEST(LinearAlgebra, 2DDeterminant)
{
	mat2x2 r;

	r.m[0][0] = 3;
	r.m[0][1] = -2;

	r.m[1][0] = 1;
	r.m[1][1] = 4;

	ASSERT_EQ(mat2x2::det(r), 14) << r;

}
TEST(LinearAlgebra, 3DetAdjInv)
{
	mat3x3 r;

	r.m[0][0] = 3;
	r.m[0][1] = -2;

	r.m[1][0] = 1;
	r.m[1][1] = 4;
	r.m[2][2] = 2;

	mat3x3 adj;

	adj.m[0][0] = 8;
	adj.m[0][1] = 4;

	adj.m[1][0] = -2;
	adj.m[1][1] = 6;
	adj.m[2][2] = 14;



	const float det = mat3x3::det(r);
	ASSERT_EQ(det, 28) << r;
	mat3x3 adjointedR = mat3x3::adj(r);
	ASSERT_EQ(adjointedR, adj) << adjointedR;
	//inverse
	mat3x3 inv;
	inv.m[0][0] = 2.0f / 7;
	inv.m[0][1] = 1.0f / 7;

	inv.m[1][0] = -1.0f / 14;
	inv.m[1][1] = 3.0f / 14;
	inv.m[2][2] = 1.0f / 2;
	ASSERT_EQ(adjointedR / det, inv) << adjointedR / det;
}
TEST(LinearAlgebra, 3DOrthogonal)
{
	mat3x3 r;

	r.m[0][0] = -0.1495f;
	r.m[0][1] = -0.1986f;
	r.m[0][2] = -0.9685f;

	r.m[1][0] = -0.8256f;
	r.m[1][1] = 0.5640f;
	r.m[1][2] = 0.0117f;

	r.m[2][0] = 0.5439f;
	r.m[2][1] = 0.8015f;
	r.m[2][2] = 0.2484f;

	mat3x3 inverse = mat3x3::inv(r);
	mat3x3::transpose(r);

	float tolerance = 0.8f; // Set an appropriate tolerance value

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_NEAR(r.m[i][j], inverse.m[i][j], tolerance) << "Mismatch at index (" << i << ", " << j << ")";
		}
	}


}
TEST(LinearAlgebra, 4DInvert)
{
	mat4x4 r;

	r.m[0][0] = -0.1495f;
	r.m[0][1] = -0.1986f;
	r.m[0][2] = -0.9685f;

	r.m[1][0] = -0.8256f;
	r.m[1][1] = 0.5640f;
	r.m[1][2] = 0.0117f;

	r.m[2][0] = -0.5439f;
	r.m[2][1] = -0.8015f;
	r.m[2][2] = 0.2484f;

	r.m[3][0] = 1.7928f;
	r.m[3][1] = -5.3116f;
	r.m[3][2] = 8.0151f;

	mat3x3 li = mat4x4::GetLinearTransformation(r);
	vec3 trans = mat4x4::GetTranslation(r);
	li = mat3x3::inv(li);
	//inverse of the last row is just the negative version
	trans = -trans;

	mat4x4 result;
	result.m[0][0] = -0.1495f;
	result.m[0][1] = -0.8256f;
	result.m[0][2] = -0.5439f;

	result.m[1][0] = -0.1986f;
	result.m[1][1] = 0.5640f;
	result.m[1][2] = -0.8015f;

	result.m[2][0] = -0.9685f;
	result.m[2][1] = 0.0117f;
	result.m[2][2] = 0.2484f;

	result.m[3][0] = 6.976f;
	result.m[3][1] = 4.382f;
	result.m[3][2] = -5.273f;

	mat4x4 res = mat4x4::multiplyTranslationLinear(li, trans);

	float tolerance = 0.001f; // Set an appropriate tolerance value

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_NEAR(res.m[i][j], result.m[i][j], tolerance) << "Mismatch at index (" << i << ", " << j << ")";
		}
	}
}
TEST(LinearAlgebra, 4DTranslation)
{
	mat4x4 r;

	r.m[1][1] = 0.94f;
	r.m[1][2] = 0.342f;

	r.m[2][1] = -0.342f;
	r.m[2][2] = 0.94f;

	r.m[3][0] = 4;
	r.m[3][1] = 2;
	r.m[3][2] = 3;
	mat4x4 r2;

	r2.m[1][1] = 0.94f;
	r2.m[1][2] = 0.342f;

	r2.m[2][1] = -0.342f;
	r2.m[2][2] = 0.94f;

	r2.m[3][0] = 4;
	r2.m[3][1] = .853f;
	r2.m[3][2] = 3.503f;

	vec3 trans(4, 2, 3);

	const float angle = 20 * PI / 180;
	mat3x3 rot;
	mat3x3::Rotate3D(angle, vec3(1, 0, 0), rot);
	mat4x4 m = mat4x4::constructLinearTransformation(rot, trans);

	float tolerance = 0.001f; // Set an appropriate tolerance value

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ASSERT_NEAR(m.m[i][j], r.m[i][j], tolerance) << "Mismatch at index (" << i << ", " << j << ")";
		}
	}
	m = mat4x4::multiplyTranslationLinear(rot, trans);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ASSERT_NEAR(m.m[i][j], r2.m[i][j], tolerance) << "Mismatch at index (" << i << ", " << j << ")";
		}
	}
}
TEST(LinearAlgebra, PerspectiveProjection)
{
	mat4x4 r = mat4x4::PerspectiveProjection(vec3(1, 0, 0), 5);
	mat4x4 result;
	result.m[0][3] = 1.0f / 5;
	result.m[3][3] = 0;
	vec3 w = vec3(105, -243, 89);

	ASSERT_EQ(r, result) << r;
	w = mat4x4::PerspectiveProjectionToVec3(r, w);

	ASSERT_EQ(w, vec3(5, -81.0f / 7, 89.0f / 21)) << w;
}
TEST(LinearAlgebra, PolarCanonicalForm)
{
	poco2 p(12.6f, 11.0f * PI / 4.0f);
	ASSERT_EQ(p, poco2(12.6f, 3.0f * PI / 4.0f));
}
TEST(LinearAlgebra, PolarToCartesian)
{
	const float angle = 11.0f * PI / 4.0f;
	const float radius = 12.6f;
	poco2 p(radius, angle);
	const vec2 v = poco2::ToCartesianForm(p);
	const vec2 answer = vec2(p.r * cos(p.a), p.r * sin(p.a));
	ASSERT_EQ(v, answer) << v;
}
TEST(LinearAlgebra, CartesianToPolar)
{
	const int testNumbers = 6;
	const  vec2 testData[] = { {10,20},{-12,-5},{0,4.5f} ,{-3,4},{0,0},{-5280,0} };

	for (int i = 0; i < testNumbers; i++)
	{

		poco2 p(testData[i]);

		const float r = sqrt(testData[i].x * testData[i].x + testData[i].y * testData[i].y);
		const float a = atan2(testData[i].y, testData[i].x);
		poco2 answer(r, a);
		ASSERT_EQ(p, answer);

	}

}
TEST(LinearAlgebra, CylindricalToCartesian)
{
	const int testNumbers = 4;
	const  cyco3 testData[] = { {4,120.0f * PI_OVER_180,5},{2,45.0f * PI_OVER_180,-1},{6,-PI / 6,-3} ,{3,3 * PI,1} };

	for (int i = 0; i < testNumbers; i++)
	{

		cyco3 c(testData[i]);
		poco2 justFirst2 = c.p;
		vec3 p = poco2::ToCartesianForm(justFirst2);
		p.z = c.z;
		const float x = justFirst2.r * cosf(justFirst2.a);
		const float y = justFirst2.r * sinf(justFirst2.a);
		const float z = testData[i].z;
		vec3 answer(x, y, z);
		ASSERT_EQ(p, answer);

	}

}
TEST(LinearAlgebra, CartesianToCylindrical)
{
	const int testNumbers = 4;
	const  vec3 testData[] = { {1,1,1},{0,-5,2},{-3,4,-7} ,{0,0,-3} };

	for (int i = 0; i < testNumbers; i++)
	{

		poco2 p(testData[i]);

		const cyco3 c(p, testData[i].z);

		const float r = sqrt(testData[i].x * testData[i].x + testData[i].y * testData[i].y);
		const float a = atan2(testData[i].y, testData[i].x);
		const float z = testData[i].z;
		const cyco3 answer(r, a, z);
		ASSERT_EQ(c, answer);

	}

}
TEST(LinearAlgebra, SphericalToCartesian)
{
	const int testNumbers = 4;
	const  spco3 testData[] = { {4,PI / 3,3 * PI / 4},{5,-5 * PI / 6,PI / 3},{2,-PI / 6,PI} ,{8,9 * PI / 4,PI / 6} };

	for (int i = 0; i < testNumbers; i++)
	{

		spco3 s(testData[i]);

		vec3 v = spco3::ToCartesianFormRightHanded(s);

		const float x = s.po.r * sin(s.p) * cos(s.po.a);
		const float y = s.po.r * sin(s.p) * sin(s.po.a);
		const float z = s.po.r * cos(s.p);
		const vec3 answer(x, y, z);
		ASSERT_EQ(v, answer);

	}

}
TEST(LinearAlgebra, SphericalLeftConventionTpCartesian)
{
	const int testNumbers = 4;
	const  spco3 testData[] = { {4,PI / 3,3 * PI / 4},{5,-5 * PI / 6,PI / 3},{2,-PI / 6,PI} ,{8,9 * PI / 4,PI / 6} };

	for (int i = 0; i < testNumbers; i++)
	{

		spco3 s(testData[i]);

		vec3 v = spco3::ToCartesianForm(s);
		//std::cout << s << "\n";

		const float x = s.r * cos(s.p) * sin(s.h);
		const float y = -s.r * sin(s.p);
		const float z = s.r * cos(s.p) * cos(s.h);
		const vec3 answer(x, y, z);
		//std::cout << v << '\n';
		ASSERT_EQ(v, answer);

	}
	spco3 s;


}
TEST(LinearAlgebra, CartesianToSphericalLeftHanded)
{
	const int testNumbers = 6;
	const  vec3 testData[] = {
		{sqrtf(2),2 * sqrtf(3),-sqrtf(2)},
		{2 * sqrtf(3), 6,-4},
		{-1,-1,-1} ,
		{2,-2 * sqrtf(3),4} ,
		{-sqrtf(3), -sqrtf(3),2 * sqrtf(2)},
		{3, 4,12}
	};

	for (int i = 0; i < testNumbers; i++)
	{

		spco3 s(testData[i]);

		//std::cout << s << "\n";

		float r = sqrt(testData[i].x * testData[i].x + testData[i].y * testData[i].y + testData[i].z * testData[i].z);
		float h = atan2(testData[i].x, testData[i].z);
		float p = asin(-testData[i].y / r);
		const spco3 answer(r, h, p);
		ASSERT_EQ(s, answer);

	}
	spco3 s;
}
TEST(LinearAlgebra, 3DRotationsConversionFromQuat)
{
	qua4 q;
	q.w = -1;
	mat3x3 m = RotationConversions::Qua4ToMat3x3(q);
	ASSERT_EQ(m, mat3x3());
	vec3 euler = RotationConversions::Qua4ToEulerAnglesToUpright(q);
	ASSERT_EQ(euler, vec3());

	q = qua4(0.653f, -0.653f, -0.271f, -0.271f);
	euler = RotationConversions::Qua4ToEulerAnglesToUpright(q);
	ASSERT_EQ(euler, vec3(-0.7853982f, -1.570796f, 0));

	q = qua4(0.364f, -0.106f, 0.848f, -0.372f);
	euler = RotationConversions::Qua4ToEulerAnglesToUpright(q);
	ASSERT_EQ(euler, vec3(PI_OVER_180 * 123, PI_OVER_180 * 33.5f, PI_OVER_180 * -32.7f));
}