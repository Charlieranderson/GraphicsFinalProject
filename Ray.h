#pragma once

#ifndef RAY_
#define RAY_

#include	"math.h"

 struct Point
{
	float x;
	float y;
	float z;

	static float DotProduct(Point a, Point b);

} ;

typedef	struct {
	Point direction;
	Point point;
} GzLine;

typedef	struct {
	Point normal;
	float d;
} GzPlane;


class Ray 
{
	
private:

public:
	Point origin;
	Point direction;
	//Constructors
	Ray() = default;
	~Ray() = default;
	Ray(Point org, Point dir)
	{
		origin = org;
		direction = dir;
		Normalize(direction);
	}

	//Normalizes vector made by point - origin
	void Normalize(Point input);

	//multiplies vector by scalar 
	Point VectorMult(Point x, float t); 

	//Calculates a ray 
	static Ray CalculateRay(float head[3], float origin[3]);

};
#endif
