#pragma once
#define NOMINMAX
#define _USE_MATH_DEFINES
#include "Vec3f.h"
#include <algorithm> 
#include <cmath>
#include <random> 

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0, 1);

class MathFunc
{
public:
    static float Clamp(const float& lo, const float& hi, const float& v);
    static float DegreeToRadian(const float& deg);
    static float DotProduct(const Vec3f& a, const Vec3f& b);
    static Vec3f CrossProduct(const Vec3f& a, const Vec3f& b);
    static bool SolveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1);  
};