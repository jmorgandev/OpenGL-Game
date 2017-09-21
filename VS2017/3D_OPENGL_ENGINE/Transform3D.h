#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include "Vector3.h"

class Transform3D {
public:
	Transform3D(){}
	~Transform3D(){}

	Vector3f& Position() { return m_position; }
	Vector3f& Rotation() { return m_rotation; }
	Vector3f& Scale() { return m_scale; }

	void setTransform(Vector3f& position, Vector3f& rotation, Vector3f& scale) {
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;
	}

	void eulerLookAt(Vector3f direction) {
		direction.normalize();
		Vector3f a = Vector3f(0.0f, 1.0f, 0.0f).Cross(direction);
		float angle = acos(Vector3f(0.0f, 1.0f, 0.0f).dotProduct(direction));
		
		m_rotation = a * angle;
	}

private:
	Vector3f m_position;
	Vector3f m_rotation;
	Vector3f m_scale;
};

#endif