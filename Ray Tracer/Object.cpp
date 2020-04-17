#include "Object.h"

Object::Object() 
	: Albedo(0.18) // 18% because real world objects avarage this value
{}

Object::~Object() {
}

bool Object::Intersect(const Vec3f& origin, const Vec3f& direction, float& t) {
	return 0;
}

void Object::GetNormal(Vec3f& normal, const Vec3f& intersect) {
}