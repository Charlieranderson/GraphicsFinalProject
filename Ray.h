#include	"math.h"
#ifndef RAY_
#define RAY_

typedef struct
{
	float x;
	float y;
	float z;
} Point;

void normalize(Point input) 
{
	float modR = sqrt((input.x * input.x) + (input.y* input.y) + (input.z * input.z));
	input.x = input.x / modR;
	input.y = input.y / modR;
	input.z = input.z / modR;
}
Point dotProduct(Point x, float t) 
{
	Point temp = { x.x * t, x.y * t, x.z * t };
	return temp;
}
class Ray 
{
	
private:
		Point origin;
	    Point direction;
public:
	Ray() = default;
	~Ray() = default;
	Ray(Point org, Point dir)
	{
		origin = org;
		direction = dir;
		normalize(direction);
	}
	Point getOrigin() { return origin; }
	Point getDirection(){ return direction; }
	Point PointAt(float t)
	{
		Point sum = dotProduct(direction, t);
		Point temp = { origin.x + sum.x, origin.y + sum.y, origin.z + sum.z };
		return temp;
	}

};
#endif
