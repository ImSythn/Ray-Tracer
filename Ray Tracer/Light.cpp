#include "Light.h"

Light::Light(const Vec3f& position, const Vec3f& intensity)
	: Position(position), Intensity(intensity)
{}

Light::~Light() {
}