#include "Sphere.h"

Sphere::Sphere(const Vec3f center, const float radius)
    :Center(center), Radius2(radius * 2)
{}

bool Sphere::Intersect(const Vec3f& origin, const Vec3f& direction, float& tnear) {
    Vec3f L = origin - Center;
    float a = MathFunc::DotProduct(direction, direction);
    float b = 2 * MathFunc::DotProduct(direction, L);
    float c = MathFunc::DotProduct(L, L) - Radius2;
    float t0, t1;

    // Solves the quadratic equation of a sphere
    if (!MathFunc::SolveQuadratic(a, b, c, t0, t1)) {
        return false;
    }

    // Makes sure the first hit point is stored in t0 and the second hit point if existing in t1 
    if (t0 > t1) {
        std::swap(t0, t1);
    }

    // Makes sure the point of the ray that hit is positive and not behind the camera 
    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) {
            return false;
        }
    }

    tnear = t0;

    return true;
}

void Sphere::GetNormal(Vec3f& normal, const Vec3f& intersect) {
    normal = Vec3f::Normalize(intersect - Center);
}

Sphere::~Sphere() {

}