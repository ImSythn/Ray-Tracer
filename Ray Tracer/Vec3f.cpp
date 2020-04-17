#include "Vec3f.h"
#include <cmath>

Vec3f::Vec3f()
	: x(0.0f), y(0.0f), z(0.0f)
{}

Vec3f::Vec3f(float n)
	: x(n), y(n), z(n)
{}

Vec3f::Vec3f(float x, float y, float z)
	: x(x), y(y), z(z)
{}

Vec3f Vec3f::operator * (const float& r) const {
	return Vec3f(x * r, y * r, z * r);
}

Vec3f Vec3f::operator * (const Vec3f& v) const {
	return Vec3f(x * v.x, y * v.y, z * v.z);
}

Vec3f Vec3f::operator / (const float& r) const {
	return Vec3f(x / r, y / r, z / r);
}

Vec3f Vec3f::operator / (const Vec3f& v) const {
	return Vec3f(x / v.x, y / v.y, z / v.z);
}

Vec3f Vec3f::operator + (const Vec3f& v) const {
	return Vec3f(x + v.x, y + v.y, z + v.z);
}

Vec3f Vec3f::operator - (const Vec3f& v) const {
	return Vec3f(x - v.x, y - v.y, z - v.z);
}

Vec3f Vec3f::operator - () const {
	return Vec3f(-x , -y, -z);
}

Vec3f& Vec3f::operator += (const Vec3f& v)  {
	Vec3f(x += v.x, y += v.y, z += v.z);
	return *this;
}

Vec3f Vec3f::Normalize(const Vec3f& v) {
	float mag2 = v.x * v.x + v.y * v.y + v.z * v.z;
	if (mag2 > 0) {
		float invMag = 1 / sqrtf(mag2);
		return Vec3f(v.x * invMag, v.y * invMag, v.z * invMag);
	}
	return v;
}