#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera : public GameObject {
public:
	Camera();
	virtual ~Camera(){}

	void draw();
	void update();
	void clean(){}

	void lookAt(Vector3f& point) { m_target = point; }
	void lookAt(float x, float y, float z) { m_target = Vector3f(x, y, z); }

	Vector3f& getTarget() { return m_target; }

private:
	Vector3f m_target;
};

#endif