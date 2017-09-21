#include "Keycard.h"

#include "CollisionHandler.h"
#include <math.h>

Keycard::Keycard() {
	m_collider.set(-0.1f, -0.8f, -0.1f, 0.1f, 0.4f, 0.1f);
	m_collider.setParent(this);
	sinBob = rand() % 10;
}

Keycard::~Keycard() {
	CollisionHandler::instance()->removeCollider(&m_collider);
}

void Keycard::load(const LoadParameters parameters) {
	GameObject::load(parameters);
	originalHeight = KEYCARD_HEIGHT;
	CollisionHandler::instance()->registerCollider(&m_collider);
	m_collider.set(m_transform.Position());
}

void Keycard::update() {
	sinBob += 0.1f;
	m_transform.Rotation().modY(ROTATION_SPEED);
	m_transform.Position().setY((sinf(sinBob * BOB_SPEED) / BOB_MAGNITUDE) + originalHeight);
}

void Keycard::draw() {
	m_material->updateMaterial();
	glPushMatrix();

	glTranslatef(m_transform.Position().getX(), m_transform.Position().getY(), m_transform.Position().getZ());

	glRotatef(m_transform.Rotation().getX(), 1.0f, 0.0f, 0.0f);
	glRotatef(m_transform.Rotation().getY(), 0.0f, 1.0f, 0.0f);
	glRotatef(m_transform.Rotation().getZ(), 0.0f, 0.0f, 1.0f);

	glScalef(m_transform.Scale().getX(), m_transform.Scale().getY(), m_transform.Scale().getZ());

	glutSolidCube(1.0f);

	glPopMatrix();

	//m_collider.debugDraw();
}

void Keycard::collision(std::string tag) {
	if (tag == "PLAYER") {
		m_removeMe = true;
	}
}