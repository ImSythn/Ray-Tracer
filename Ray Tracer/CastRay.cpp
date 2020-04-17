#include "CastRay.h"

bool trace(const Vec3f& origin, const Vec3f& direction,
	const std::vector<std::unique_ptr<Object>>& objects, float& tNear, Object** hitObject) {
	// Check against every object of the scene if the current ray intersects with one
	for (uint16_t k = 0; k < objects.size(); ++k) {
		float tNearK = std::numeric_limits<float>::max();

		// If the ray intersects get the value at what point(t) along the ray it hits an object  
		if (objects[k]->Intersect(origin, direction, tNearK) && tNearK < tNear) {
			*hitObject = objects[k].get();
			tNear = tNearK;
		}
	}

	return (*hitObject != nullptr);
}

void createCoordinateSystem(const Vec3f& N, Vec3f& Nt, Vec3f& Nb)
{
	if (std::fabs(N.x) > std::fabs(N.y))
		Nt = Vec3f(N.z, 0, -N.x) / sqrtf(N.x * N.x + N.z * N.z);
	else
		Nt = Vec3f(0, -N.z, N.y) / sqrtf(N.y * N.y + N.z * N.z);
	Nb = MathFunc::CrossProduct(N, Nt);
}

Vec3f uniformSampleHemisphere(const float& r1, const float& r2)
{
	float sinTheta = sqrtf(1 - r1 * r1);
	float phi = 2 * M_PI * r2;
	float x = sinTheta * cosf(phi);
	float z = sinTheta * sinf(phi);
	return Vec3f(x, r1, z);
}

Vec3f CastRay::Ray(const Vec3f& origin, const Vec3f& direction,
	const std::vector<std::unique_ptr<Object>>& objects,
	const std::vector<std::unique_ptr<Light>>& lights, const Settings& settings, uint16_t depth) {
	if (depth > settings.MaxRecursion) {
		return 0;
	}

	Vec3f pixelColour = 0;
	float tNear = std::numeric_limits<float>::max();
	Object* hitObject = nullptr;

	// Check for each object if there was an intersection
	// Yes: calculate colour for this pixel
	// No: Return the background colour
	if (trace(origin, direction, objects, tNear, &hitObject)) {
		Vec3f directDiffuse, indirectDiffuse, hitNormal;
		Vec3f hitPoint = origin + direction * tNear;
		hitObject->GetNormal(hitNormal, hitPoint);

		// Direct illumination
		for (uint8_t i = 0; i < lights.size(); ++i) {
			Vec3f lightDirection = lights[i]->Position - hitPoint;
			Vec3f lightDistance2 = MathFunc::DotProduct(lightDirection, lightDirection);
			lightDirection = Vec3f::Normalize(lightDirection);
			float tNearShadow = std::numeric_limits<float>::max();
			// Trace from the traced point if the light is reachable without intersecting other objects
			if (trace(hitPoint + hitNormal * settings.Bais, lightDirection, objects, tNearShadow, &hitObject)) {
				directDiffuse += lights[i]->Intensity * std::max(0.0f, MathFunc::DotProduct(lightDirection, hitNormal));
			}
		}

		// Indirect illumination
		Vec3f Nt, Nb;

		// Creates a hemisphere's cardinate coordinate system with its up vector towards the shading normal
		createCoordinateSystem(hitNormal, Nt, Nb);

		for (uint32_t r = 0; r < settings.RadiosityRayCount; ++r) {
			// Generate evenly distributed samples over the hemisphere 
			float r1 = distribution(generator); 
			float r2 = distribution(generator);
			Vec3f sample = uniformSampleHemisphere(r1, r2);
			// transforms the hemispheres axis so Nt(x+) and Nb(z+) alighn with the world space axis
			Vec3f sampleWorld(
				sample.x * Nb.x + sample.y * hitNormal.x + sample.z * Nt.x,
				sample.x * Nb.y + sample.y * hitNormal.y + sample.z * Nt.y,
				sample.x * Nb.z + sample.y * hitNormal.z + sample.z * Nt.z);
			// Cast ray in space, if it hits a object check if a light hits that point and add this returned colour to the light of this pixel 
			indirectDiffuse += Ray(hitPoint + sampleWorld * settings.Bais, sampleWorld, objects,
				lights,	settings, depth + 1) * r1 / 1 / (2 * M_PI);
		}
		indirectDiffuse = indirectDiffuse / settings.MaxRecursion;

		pixelColour = (directDiffuse / M_PI + indirectDiffuse * 2) * hitObject->Albedo;

	}
	return pixelColour;
}