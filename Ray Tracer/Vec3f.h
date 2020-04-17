#ifndef VEC3F_H
#define VEC3F_H
#include <iostream>

class Vec3f
{
public:
	float x, y, z;

public:
	Vec3f();
	Vec3f(float n);
	Vec3f(float x, float y, float z);

	Vec3f operator * (const float& r) const;
	Vec3f operator * (const Vec3f& v) const;
	Vec3f operator / (const float& r) const;
	Vec3f operator / (const Vec3f& v) const;
	Vec3f operator + (const Vec3f& v) const;
	Vec3f operator - (const Vec3f& v) const;
	Vec3f operator - () const;
	Vec3f& operator += (const Vec3f& v);

	static Vec3f Normalize(const Vec3f& v);
};

#endif