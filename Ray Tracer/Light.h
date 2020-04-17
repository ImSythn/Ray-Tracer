#pragma once
#include "Vec3f.h"

class Light
{
public:
	Vec3f Position;
	Vec3f Intensity;
public:
	Light(const Vec3f& position, const Vec3f& intensity);
	~Light();
};

