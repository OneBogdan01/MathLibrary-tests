#include "MathFunctions.hpp"

bool MathFunctions::areEqualRel(float a, float b)
{
    return (fabs(a - b) <= __FLT_EPSILON__ * std::max(fabs(a), fabs(b)));
}