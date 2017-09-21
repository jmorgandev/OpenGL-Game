#ifndef LOADPARAMETERS_H
#define LOADPARAMETERS_H

#include <string>
#include "Vector3.h"
//Parameters to pass into every gameobject for loading
class LoadParameters {
public:

	LoadParameters(float x, float y, float z, float xRot, float yRot, float zRot, float xScale, float yScale, float zScale, std::string name, std::string tag) :
		m_position(x, y, z), m_rotationEuler(xRot, yRot, zRot), m_scale(xScale, yScale, zScale), m_objectName(name), m_objectTag(tag){}

	Vector3f getPosition() const { return m_position; }
	Vector3f getRotation() const { return m_rotationEuler; }
	Vector3f getScale() const { return m_scale; }

	std::string getName() const { return m_objectName; }
	std::string getTag() const { return m_objectTag; }

private:
	
	std::string m_objectName;
	std::string m_objectTag;

	Vector3f m_position;
	Vector3f m_rotationEuler;
	Vector3f m_scale;
};

#endif