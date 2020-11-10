#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include    "Camera.h"

#define PI (float) 3.14159265358979323846
void crossProduct(Point x, Point y, Point z) 
{
	x.x = y.y * z.z - y.z * z.y;
	x.y = y.z * z.x - y.x * z.z;
	x.z = y.x * z.y - y.y * z.x;
}
Point minus(Point A, Point B) 
{
  Point temp = { A.x - B.x, A.y - B.y, A.z - B.z };
  return temp;
}
Point add(Point A, Point B) 
{
	Point temp = { A.x + B.x, A.y + B.y, A.z + B.z };
	return temp;
}
void Camera::update()
{
	Point worldUp = { 0.0f, 1.0f, 0.0f };
	float theta = m_fov*(PI/180);
	float half_height = (float)(tan(theta * 0.5f));
	float half_width = m_aspect * half_height;

	m_axisZ = { m_pos.x - m_target.x, m_pos.y - m_target.y, m_pos.z - m_target.z };
	normalize(m_axisZ);
	crossProduct(m_axisX, worldUp, m_axisZ);
	normalize(m_axisX);
	crossProduct(m_axisY, m_axisZ, m_axisX);
	normalize(m_axisY);

	Point temp1 = minus(m_pos, dotProduct(m_axisX, half_width));
	Point temp2 = minus(temp1, dotProduct(m_axisY, half_height));
	m_lowerLeftCorner = minus(temp2, m_axisZ);

	m_horizontal = dotProduct(dotProduct(m_axisX, 2), half_width);
	m_vertical = dotProduct(dotProduct(m_axisY, 2), half_height);
}

Ray Camera::getRay(float s, float t)
{
	Point temp1 = minus(dotProduct(m_vertical, t), m_pos);
	Point temp2 = add(m_lowerLeftCorner, dotProduct(m_horizontal, s));
	return Ray(m_pos, add(temp1, temp2));
}
