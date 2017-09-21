#include "Enemy.h"
#include "CollisionHandler.h"
#include <math.h>

Enemy::Enemy(bool antiClockwise) {
	m_acw = antiClockwise;
	m_collider.set(-0.3f, -0.8f, -0.3f, 0.3f, 0.4f, 0.3f);
	m_collider.setParent(this);
	sinBob = rand() % 10;
}

Enemy::~Enemy() {
	CollisionHandler::instance()->removeCollider(&m_collider);
}

void Enemy::load(const LoadParameters parameters) {
	GameObject::load(parameters);
	originalHeight = ENEMY_HEIGHT;
	CollisionHandler::instance()->registerCollider(&m_collider);
	m_direction.set(1.0f, 0.0f, 0.0f);
	m_collider.set(m_transform.Position());
}

void Enemy::update() {
	Vector3f newPos = (m_transform.Position() + (m_direction * ENEMY_SPEED));

	if (CollisionHandler::instance()->getWorldCollision(m_transform.Position().getX(), newPos.getZ() + (m_direction.getZ() / 2.0f)) == COLLISION_WALL) {
		changeDirection();
	}
	if (CollisionHandler::instance()->getWorldCollision(newPos.getX() + (m_direction.getX() / 2.0f), m_transform.Position().getZ()) == COLLISION_WALL) {
		changeDirection();
	}

	m_transform.Position().mod(m_direction * ENEMY_SPEED);

	sinBob += 0.1f;
	m_transform.Position().setY((sinf(sinBob * BOB_SPEED) / BOB_MAGNITUDE) + originalHeight);

	m_collider.move(m_direction * ENEMY_SPEED);
}

void Enemy::draw() {
	m_material->updateMaterial();
	glPushMatrix();

	glTranslatef(m_transform.Position().getX(), m_transform.Position().getY(), m_transform.Position().getZ());

	glRotatef(m_transform.Rotation().getX(), 1.0f, 0.0f, 0.0f);
	glRotatef(m_transform.Rotation().getY(), 0.0f, 1.0f, 0.0f);
	glRotatef(m_transform.Rotation().getZ(), 0.0f, 0.0f, 1.0f);

	glScalef(m_transform.Scale().getX(), m_transform.Scale().getY(), m_transform.Scale().getZ());
	
	glutSolidSphere(0.4f, 32, 32);

	glPopMatrix();

	//m_collider.debugDraw();
}

void Enemy::changeDirection() {
	Vector3f crossVector = m_direction.Cross(Vector3f(0.0f, 1.0f, 0.0f));
	m_direction.set((m_acw) ? -crossVector : crossVector);
}

void Enemy::collision(std::string tag) {
}

