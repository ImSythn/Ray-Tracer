#include "Ray.h"
Ray::Ray()
	: origin(0), direction(0, 0, -1)
{}

Ray::Ray(const Vec3f& o, const Vec3f& d)
	: origin(o), direction(d)
{}

Ray::~Ray() 
{

}