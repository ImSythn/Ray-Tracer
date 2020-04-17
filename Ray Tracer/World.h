#pragma once
#include "Settings.h"
#include "CastRay.h"
#include "SDL.h"
#include "Object.h"
#include "Sphere.h"
#include "Light.h"
#include "MathFunc.h"
#include <windows.h>
#include <cmath>
#include <vector>
#include <iostream> 
#undef main

class World
{
private:
	Settings settings;
	Vec3f* framebuffer;
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Light>> lights;

public:
	World();
	~World();

	void BuildScene();
	void RenderScene();
	void DisplayScene();
};


