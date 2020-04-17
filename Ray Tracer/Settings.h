#pragma once
#include "Vec3f.h"
#include <cstdint>

class Settings
{
public:
	uint16_t Width, Height, MaxRecursion ,RadiosityRayCount;
	float Fov, Bais;

public:
	Settings();
	~Settings();
};

