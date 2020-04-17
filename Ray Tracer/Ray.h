#pragma once
#include "Vec3f.h"

class Ray
{
public: 
	Vec3f origin, direction;
public:
	Ray();
	Ray(const Vec3f& o, const Vec3f& d);
	~Ray();
};

