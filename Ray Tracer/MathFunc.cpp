#include "MathFunc.h"

float MathFunc::Clamp(const float& lo, const float& hi, const float& v)
{
    return std::max(lo, std::min(hi, v));
}

float MathFunc::DegreeToRadian(const float& deg)
{
    return deg * M_PI / 180;
}

float MathFunc::DotProduct(const Vec3f& a, const Vec3f& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3f MathFunc::CrossProduct(const Vec3f& a, const Vec3f& b)
{
    return Vec3f(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

// Solves a quadratic equation whether a circle gets hit 0, 1 or 2 times
bool MathFunc::SolveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
    float discr = b * b - 4 * a * c;
    // If the discriminant is smaller than zero the ray falls outside of the sphere
    if (discr < 0) {
        return false;
    }
    // If the discriminant is 0 the ray intercects with the sphere once on one of the edges
    else if (discr == 0) {
        x0 = x1 = -0.5 * b / a;
    }
    // If the discriminant is bigger than 0 the ray intercects a sphere twice 
    else {
        float q = (b > 0) ?
            -0.5 * (b + sqrt(discr)) :
            -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }

    return true;
}