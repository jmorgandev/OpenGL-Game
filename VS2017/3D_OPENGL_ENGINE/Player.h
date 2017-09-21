#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "EventHandler.h"
#include "Vector2.h"
#include "BoxCollider.h"

#define HEADBOB_SPEED 2.0f
#define HEADBOB_MAGNITUDE 8

#define MAXIMUM_VERTICAL_LOOK 1.5f

#define UNITS_PER_SECOND 1.0f / 60
#define PLAYER_SPEED 3 * UNITS_PER_SECOND
#define WORLD_COLLISION_OFFSET 0.25f
#define PLAYER_HEIGHT 1.2f

class Player : public GameObject, public EventHandler {
public:
	Player();
	virtual ~Player();

	void draw();
	void update();
	void load(const LoadParameters parameters);
	void clean();

	void collision(std::string tag);

private:
	bool isDead;
	int deathTimer;

	Vector3f m_right;
	Vector3f m_velocity;

	float m_forwardAxis = 0.0f;
	float m_rightAxis = 0.0f;

	float m_xLook = 0.0f;
	float m_yLook = 0.0f;

	float originalCameraHeight;
	float headBob;

	bool goToMenu;

	float yOffset, xOffset;

	Camera* m_cameraRef;

	BoxCollider m_collider;

	virtual void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);

	virtual void OnKeyboardEvent(const SDL_KeyboardEvent& e);

};

#endif