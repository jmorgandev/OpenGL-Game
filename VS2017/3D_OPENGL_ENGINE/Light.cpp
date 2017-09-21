#include "Light.h"

Light::Light(Vector3f& position, int ID) {
	Light(position, false, ID, Color3f().White(), Color3f().Black(), Color3f().Black());
}

Light::Light(Vector3f& position, bool directional, int ID) {
	Light(position, directional, ID, Color3f().White(), Color3f().Black(), Color3f().Black());
}

Light::Light(Vector3f& position, bool directional, int ID, Color3f diffuse, Color3f ambient, Color3f specular) {
	m_transform.Position().set(position);
	m_bDirectional = directional;

	diffuse.toMatrix(m_diffuse);
	ambient.toMatrix(m_ambient);
	specular.toMatrix(m_specular);

	m_lightID = ID + GL_LIGHT0;
	glEnable(m_lightID);
	updateLight();
}

void Light::draw() {
	glLightfv(m_lightID, GL_POSITION, m_positionMatrix);
}

void Light::update() {
}

void Light::clean() {
	glDisable(m_lightID);
}

void Light::updateLight() {
	m_transform.Position().toMatrix(m_positionMatrix);
	m_positionMatrix[3] = (m_bDirectional) ? 0.0f : 1.0f;
	glLightfv(m_lightID, GL_DIFFUSE, m_diffuse);
	glLightfv(m_lightID, GL_AMBIENT, m_ambient);
	glLightfv(m_lightID, GL_SPECULAR, m_specular);
	glLightf(m_lightID, GL_LINEAR_ATTENUATION, 1.0f);
	glLightf(m_lightID, GL_QUADRATIC_ATTENUATION, 0.1f);
}

