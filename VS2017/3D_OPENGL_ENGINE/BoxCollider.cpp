#include "BoxCollider.h"

bool BoxCollider::intersect(BoxCollider& box) {
	return v_max.getX() > box.v_min.getX() && box.v_max.getX() > v_min.getX() &&
		v_max.getY() > box.v_min.getY() && box.v_max.getY() > v_min.getY() &&
		v_max.getZ() > box.v_min.getZ() && box.v_max.getZ() > v_min.getZ();
}

void BoxCollider::debugDraw() {
	glDisable(GL_LIGHTING);
	glPushMatrix();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);

	//FRONT FACE//
	glVertex3f(v_min.getX(), v_min.getY(), v_min.getZ());	//Bottom left front
	glVertex3f(v_max.getX(), v_min.getY(), v_min.getZ());	//Bottom right front

	glVertex3f(v_min.getX(), v_min.getY(), v_min.getZ());	//Bottom left front
	glVertex3f(v_min.getX(), v_max.getY(), v_min.getZ());	//Top left front

	glVertex3f(v_max.getX(), v_min.getY(), v_min.getZ());	//Bottom right front
	glVertex3f(v_max.getX(), v_max.getY(), v_min.getZ());	//Top right front

	glVertex3f(v_max.getX(), v_max.getY(), v_min.getZ());	//Top right front
	glVertex3f(v_min.getX(), v_max.getY(), v_min.getZ());	//Top left front


	//TOP FACE//
	glVertex3f(v_min.getX(), v_max.getY(), v_min.getZ());	//Top left front
	glVertex3f(v_min.getX(), v_max.getY(), v_max.getZ());	//Top left Back

	glVertex3f(v_max.getX(), v_max.getY(), v_min.getZ());	//Top right front
	glVertex3f(v_max.getX(), v_max.getY(), v_max.getZ());	//Top right back

	glVertex3f(v_min.getX(), v_max.getY(), v_max.getZ());	//Top left Back
	glVertex3f(v_max.getX(), v_max.getY(), v_max.getZ());	//Top right back


	//BACK FACE//
	glVertex3f(v_min.getX(), v_max.getY(), v_max.getZ());	//Top left Back
	glVertex3f(v_min.getX(), v_min.getY(), v_max.getZ());	//Bottom left Back

	glVertex3f(v_max.getX(), v_max.getY(), v_max.getZ());	//Top right back
	glVertex3f(v_max.getX(), v_min.getY(), v_max.getZ());	//Bottom right Back

	glVertex3f(v_min.getX(), v_min.getY(), v_max.getZ());	//Bottom left Back
	glVertex3f(v_max.getX(), v_min.getY(), v_max.getZ());	//Bottom right Back


	//RIGHT FACE//
	glVertex3f(v_max.getX(), v_min.getY(), v_min.getZ());	//Bottom right front
	glVertex3f(v_max.getX(), v_min.getY(), v_max.getZ());	//Bottom right Back

	//LEFT FACE//
	glVertex3f(v_min.getX(), v_min.getY(), v_min.getZ());	//Bottom left front
	glVertex3f(v_min.getX(), v_min.getY(), v_max.getZ());	//Bottom left Back

	glEnd();

	glPopMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
}

void BoxCollider::move(Vector3f amount) {
	v_min += amount;
	v_max += amount;
}

void BoxCollider::move(float x, float y, float z) {
	v_min.mod(x, y, z);
	v_max.mod(x, y, z);
}

void BoxCollider::set(Vector3f pos) {
	v_min = pos + v_min;
	v_max = pos + v_max;
}