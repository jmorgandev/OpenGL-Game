#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "BoxCollider.h"

#define UNITS_PER_SECOND 1.0f / 60
#define ENEMY_SPEED 1.5 * UNITS_PER_SECOND
#define ENEMY_HEIGHT 0.75f

#define BOB_SPEED 0.5f
#define BOB_MAGNITUDE 6.0f

class Enemy : public GameObject {
public:
	Enemy(bool antiClockwise);
	virtual ~Enemy();

	void draw();
	void update();
	void load(const LoadParameters parameters);
	void clean(){}

	void collision(std::string tag);

private:
	Vector3f m_direction;

	float sinBob;
	bool m_acw;
	float originalHeight;

	BoxCollider m_collider;

	void changeDirection();
};

#endif