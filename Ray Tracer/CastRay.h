#pragma once
#define _USE_MATH_DEFINES
#include "Vec2f.h"
#include "Vec3f.h"
#include "Settings.h"
#include "Object.h"
#include "Light.h"
#include "MathFunc.h"
#include <vector>
#include <iostream> 

class CastRay
{
public:
	static Vec3f Ray(const Vec3f& origin, const Vec3f& direction, 
		const std::vector<std::unique_ptr<Object>>& objects, 
		const std::vector<std::unique_ptr<Light>>& lights, 
		const Settings& settings, uint16_t depth);
};

