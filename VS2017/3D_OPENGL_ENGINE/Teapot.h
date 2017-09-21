#ifndef TEAPOT_PRIMITIVE_H
#define TEAPOT_PRIMITIVE_H

#include "GameObject.h"
#include "SphereCollider.h"

class Teapot : public GameObject {
public:
	Teapot(){}
	~Teapot(){}

	virtual void load(const LoadParameters parameters){ GameObject::load(parameters); m_collider.SetPosition(m_transform.Position()); m_collider.SetRadius(1.0f); }

	virtual void draw();
	virtual void update(){ m_transform.Rotation().mod(0.2f, 0.4f, 0.0f); }
	virtual void clean(){}

	virtual SphereCollider& Collider() { return m_collider; }

private:
	SphereCollider m_collider;
};

#endif