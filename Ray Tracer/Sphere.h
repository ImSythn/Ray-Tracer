#pragma once
#include "Object.cpp"
#include "Vec3f.h"
#include "MathFunc.h"

class Sphere : public Object
{
public:
	Vec3f Center;
	float Radius2;

public:
	Sphere(const Vec3f center, const float radius);
	bool Intersect(const Vec3f& origin, const Vec3f& direction, float& t);
	void GetNormal(Vec3f& normal, const Vec3f& intersect);
	~Sphere();
};

