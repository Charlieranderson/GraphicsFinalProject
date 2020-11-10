#pragma once

#include "Ray.h"
#ifndef CAMERA_
#define CAMERA_

class Camera
{
public:
	Point m_pos; // camera position in world space
	Point m_target; // target position in world space
	Point m_lowerLeftCorner; // position of the lower left corner of the near plane of the viewing cone
	Point m_horizontal; // horizontal span of the near plane in the camera coordinate system
	Point m_vertical; // The vertical span of the near plane in the camera coordinate system
	float m_fov; // field of view
	float m_aspect;// Screen aspect ratio
	Point m_axisX, m_axisY, m_axisZ;

	Camera(Point cameraPos, Point target, float fov, float aspect);

	Point getPosition() const { return m_pos; }
	Point getTarget() const { return m_target; }
	Point getAxisX() const { return m_axisX; }
	Point getAxisY() const { return m_axisY; }
	Point getAxisZ() const { return m_axisZ; }
	void setPosition(Point pos) { m_pos = pos; update(); }
	void setTarget(Point tar) { m_target = tar; update(); }
	void setFov(float fov) { m_fov = fov; update(); }
	void setAspect(float asp) { m_aspect = asp; update(); }

	Ray getRay(float s, float t);

private:
	void update();
};

#endif