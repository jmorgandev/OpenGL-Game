#ifndef PLANE_PRIMITIVE_H
#define PLANE_PRIMITIVE_H

#include "GameObject.h"
#include "BoxCollider.h"

class Plane : public GameObject {
public:
	Plane(){ m_collider.getMinimum().set(-0.5f, -0.5f, -0.1f); m_collider.getMaximum().set(0.5f, 0.5f, 0.1f); }
	Plane(Vector3f min, Vector3f max) { m_collider.set(min, max); }
	Plane(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) { m_collider.set(xMin, yMin, zMin, xMax, yMax, zMax); }
	~Plane(){}

	virtual void load(const LoadParameters parameters){ GameObject::load(parameters); }

	virtual void draw();
	virtual void update(){ }
	virtual void clean(){}

private:
	BoxCollider m_collider;
};

#endif