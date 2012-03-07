#include "Vec2.h"

Vec2::Vec2() : x(0), y(0)
{
}

Vec2::Vec2(float newX, float newY) : x(newX), y(newY)
{
}

Vec2::~Vec2()
{
}

float Vec2::GetLength()
{
	return sqrt(x*x + y*y);
}

Vec2 Vec2::GetNormalized()
{
	return *this/GetLength();
}

Vec2 Vec2::GetPerpendicular()
{
	return Vec2(-y, x);
}

Vec2& Vec2::operator+=(const Vec2& V)
{
	x += V.x;
	y += V.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& V)
{
	x -= V.x;
	y -= V.y;
	return *this;
}

Vec2& Vec2::operator*=(const float& f)
{
	x *= f;
	y *= f;
	return *this;
}

Vec2& Vec2::operator/=(const float& f)
{
	x /= f;
	y /= f;
	return *this;
}

Vec2 operator-(const Vec2& V)
{
	return Vec2(-V.x, -V.y);
}

Vec2 operator+(const Vec2& V1, const Vec2& V2)
{
	return Vec2(V1.x + V2.x, V1.y + V2.y);
}

Vec2 operator-(const Vec2& V1, const Vec2& V2)
{
	return Vec2(V1.x - V2.x, V1.y - V2.y);
}

Vec2 operator*(const Vec2& V, const float& f)
{
	return Vec2(V.x*f, V.y*f);
}

Vec2 operator*(const float& f, const Vec2& V)
{
	return Vec2(V.x*f, V.y*f);
}

Vec2 operator/(const Vec2& V, const float& f)
{
	return Vec2(V.x/f, V.y/f);
}

float operator*(const Vec2& V1, const Vec2& V2)
{
	return (V1.x*V2.x + V1.y*V2.y);
}

bool operator== (const Vec2& V1, const Vec2& V2)
{
	return (V1.x == V2.x && V1.y == V2.y);
}

bool operator!= (const Vec2& V1, const Vec2& V2)
{
	return (V1.x != V2.x || V1.y != V2.y);
}

bool operator> (Vec2& V1, Vec2& V2)
{
	return (V1.GetLength() > V2.GetLength());
}

bool operator< (Vec2& V1, Vec2& V2)
{
	return (V1.GetLength() < V2.GetLength());
}

bool operator>= (Vec2& V1, Vec2& V2)
{
	return (V1.GetLength() >= V2.GetLength());
}

bool operator<= (Vec2& V1, Vec2& V2)
{
	return (V1.GetLength() <= V2.GetLength());
}

