#pragma once
#include "Vec3f.h"

class Object
{
public:
	Vec3f Albedo;

public:
	Object();
	virtual ~Object();

public:
	virtual bool Intersect(const Vec3f& origin, const Vec3f& direction, float& t);
	virtual void GetNormal(Vec3f& normal, const Vec3f& intersect);
};

