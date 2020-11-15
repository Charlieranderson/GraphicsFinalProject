#pragma once

#ifndef RAY_
#define RAY_

#include	"math.h"

typedef struct
{
	float x;
	float y;
	float z;
} Point;

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


	//Functions
	Point getOrigin() { return origin; }
	Point getDirection(){ return direction; }
	Point PointAt(float t);

	//Normalizes vector made by point - origin
	void Normalize(Point input);

	//multiplies vector by scalar 
	Point VectorMult(Point x, float t); 

};
#endif
