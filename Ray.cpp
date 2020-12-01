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

Ray Ray::CalculateRay(float head[3], float origin[3]) {
	Point Pos, Dir;
	Pos.x = origin[0];
	Pos.y = origin[1];
	Pos.z = origin[2];

	Dir.x = head[0] - origin[0];
	Dir.y = head[1] - origin[1];
	Dir.z = head[2] - origin[2];


	return Ray(Pos, Dir);
}


float Point::DotProduct(Point a, Point b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}