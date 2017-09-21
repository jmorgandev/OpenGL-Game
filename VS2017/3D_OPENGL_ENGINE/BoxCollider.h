#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <glut.h>
#include "GameObject.h"
#include "Vector3.h"

class BoxCollider {
public:
	BoxCollider(){ v_min.set(-0.5f, -0.5f, -0.5f); v_max.set(0.5f, 0.5f, 0.5f); }
	BoxCollider(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) { v_min.set(xMin, yMin, zMin); v_max.set(xMax, yMax, zMax); }
	BoxCollider(Vector3f min, Vector3f max){ v_min = min; v_max = max; }
	~BoxCollider(){}

	//AABB Intersection Test
	bool intersect(BoxCollider& box);

	//Draw the AABB outline for debugging
	void debugDraw();

	void set(float xMin, float yMin, float zMin, float xMax, float yMax, float zMax) {
		v_min.set(xMin, yMin, zMin);
		v_max.set(xMax, yMax, zMax);
	}
	void set(Vector3f min, Vector3f max) { v_min = min; v_max = max; }
	void set(Vector3f pos);

	void move(Vector3f amount);
	void move(float x, float y, float z);

	void setParent(GameObject* parent) { parent_ref = parent; }
	GameObject* getParent() { return parent_ref; }

	Vector3f& getMinimum() { return v_min; }
	Vector3f& getMaximum() { return v_max; }
private:

	Vector3f v_min, v_max;

	GameObject* parent_ref;
};

#endif