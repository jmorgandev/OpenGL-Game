#ifndef KEYCARD_H
#define KEYCARD_H
#include "GameObject.h"
#include "BoxCollider.h"

#define ROTATION_SPEED 1.0f
#define BOB_MAGNITUDE 8.0f
#define BOB_SPEED 0.5f

#define KEYCARD_HEIGHT 1.0f

class Keycard : public GameObject {
public:
	Keycard();
	virtual ~Keycard();

	void draw();
	void update();
	void load(const LoadParameters parameters);
	void clean(){}

	void collision(std::string tag);

	virtual bool toRemove(){ return m_removeMe; }

private:

	float sinBob;
	float originalHeight;

	BoxCollider m_collider;

	bool m_removeMe;
};

#endif