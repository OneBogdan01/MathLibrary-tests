#include "MathFunctions.hpp"
#include <cfloat>
#include <algorithm>

bool MathFunctions::areEqualRel(float a, float b)
{
	return (fabs(a - b) <= FLT_EPSILON * std::max(fabs(a), fabs(b)));
}
