#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Vector3.h"
#include <stdio.h>

class SphereCollider {
public:
	SphereCollider() : m_position(0.0f, 0.0f, 0.0f), m_radius(1.0f){}
	SphereCollider(float x, float y, float z, float r) : m_position(x, y, z), m_radius(r){}
	SphereCollider(Vector3f pos, float radius) : m_position(pos), m_radius(radius){}

	void SetPosition(Vector3f pos) { m_position = pos; }
	void SetRadius(float radius) { m_radius = radius; }

	bool Collision(SphereCollider& sphere) {
		return ((m_position - sphere.m_position).length() < (m_radius + sphere.m_radius));
	}
private:
	Vector3f m_position;
	float m_radius;
};

#endif