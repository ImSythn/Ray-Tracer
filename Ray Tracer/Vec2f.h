#pragma once
class Vec2f
{
public:
	float x, y;

public:
	Vec2f();
	Vec2f(float n);
	Vec2f(float x, float y);

	Vec2f operator * (const float& r) const;
	Vec2f operator * (const Vec2f& v) const;
	Vec2f operator / (const float& r) const;
	Vec2f operator / (const Vec2f& v) const;
	Vec2f operator + (const Vec2f& v) const;
	Vec2f operator - (const Vec2f& v) const;
	Vec2f operator - () const;
	Vec2f& operator += (const Vec2f& v);

	static Vec2f Normalize(const Vec2f& v);
};

