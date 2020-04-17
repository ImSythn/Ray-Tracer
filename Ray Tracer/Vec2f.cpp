#include "Vec2f.h"
#include <cmath>

Vec2f::Vec2f()
	: x(0.0f), y(0.0f)
{}

Vec2f::Vec2f(float n)
	: x(n), y(n)
{}

Vec2f::Vec2f(float x, float y)
	: x(x), y(y)
{}


Vec2f Vec2f::operator * (const float& r) const {
	return Vec2f(x * r, y * r);
}

Vec2f Vec2f::operator * (const Vec2f& v) const {
	return Vec2f(x * v.x, y * v.y);
}

Vec2f Vec2f::operator / (const float& r) const {
	return Vec2f(x / r, y / r);
}

Vec2f Vec2f::operator / (const Vec2f& v) const {
	return Vec2f(x / v.x, y / v.y);
}

Vec2f Vec2f::operator + (const Vec2f& v) const {
	return Vec2f(x + v.x, y + v.y);
}

Vec2f Vec2f::operator - (const Vec2f& v) const {
	return Vec2f(x - v.x, y - v.y);
}

Vec2f Vec2f::operator - () const {
	return Vec2f(-x, -y);
}

Vec2f& Vec2f::operator += (const Vec2f& v) {
	Vec2f(x += v.x, y += v.y);
	return *this;
}

Vec2f Vec2f::Normalize(const Vec2f& v) {
	float mag2 = v.x * v.x + v.y * v.y;
	if (mag2 > 0) {
		float invMag = 1 / sqrtf(mag2);
		return Vec2f(v.x * invMag, v.y * invMag);
	}
	return v;
}