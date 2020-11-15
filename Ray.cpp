#include "StdAfx.h"
#include "Ray.h"

void Ray::Normalize(Point input)
{
	float modR = sqrt((input.x * input.x) + (input.y* input.y) + (input.z * input.z));
	input.x = input.x / modR;
	input.y = input.y / modR;
	input.z = input.z / modR;
}
Point Ray::VectorMult(Point x, float t)
{
	Point temp = { x.x * t, x.y * t, x.z * t };
	return temp;
}

Point Ray::PointAt(float t)
{
	Point sum = VectorMult(direction, t);
	Point temp = { origin.x + sum.x, origin.y + sum.y, origin.z + sum.z };
	return temp;
}