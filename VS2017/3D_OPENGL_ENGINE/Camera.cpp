#include "Camera.h"
#include "Game.h"

Camera::Camera() {
}

void Camera::draw() {
	//Use Opengl to rotate the perspective based on the target point calculated by trigonometry
	gluLookAt(
		m_transform.Position().getX(), m_transform.Position().getY(), m_transform.Position().getZ(),
		m_transform.Position().getX() + m_target.getX(), m_transform.Position().getY() + m_target.getY(), m_transform.Position().getZ() + m_target.getZ(),
		0, 1.0, 0
		);
}

void Camera::update() {
	
}