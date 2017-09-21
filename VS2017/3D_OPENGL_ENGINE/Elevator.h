#ifndef ENT_ELEVATOR
#define ENT_ELEVATOR

#include "Block.h"
#include "CollisionHandler.h"

#define OPEN_POSITION -1.0f
#define CLOSED_POSITION 0.0f
#define DOOR_SPEED 0.1f
#define DOOR_TIME 60

class Elevator : public Block {
public:
	Elevator(Material* doorMaterial){ 
		m_doorMaterial = doorMaterial;
		m_collider.set(0.0f, 0.0f, -0.5f, 1.0f, BLOCK_HEIGHT, 0.25f);
		m_collider.setParent(this);
		CollisionHandler::instance()->registerCollider(&m_collider);
		doorPosition.set(CLOSED_POSITION, 0.0f, 0.001f);
		levelTimer = 180;
	}
	~Elevator(){
		CollisionHandler::instance()->removeCollider(&m_collider);
	}

	virtual void load(const LoadParameters parameters) {
		GameObject::load(parameters);
		m_collider.set(m_transform.Position());
	}
	virtual void draw();
	virtual void update();

	virtual void collision(std::string object);

private:
	void renderDoor();
	void renderInside();

	bool levelTransition;
	int levelTimer;
	int doorTimer;
	
	Vector3f doorPosition;
	enum D_STATE { DOOR_OPEN, DOOR_CLOSED, DOOR_LOCKED };
	D_STATE doorState = DOOR_CLOSED;

	Material* m_doorMaterial;

	BoxCollider m_collider;
};

#endif