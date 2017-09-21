#include "Player.h"
#include "CollisionHandler.h"
#include "JMath.h"
#include "Game.h"
#include "Block.h"
#include <math.h>
#include "TextureManager.h"
#include "LevelManager.h"
#include "GameStateMachine.h"
#include "MenuState.h"

Player::Player() {
	activateEvents();
	m_collider.set(-0.3f, 0.0f, -0.3f, 0.3f, PLAYER_HEIGHT, 0.3f);
	m_collider.setParent(this);
	m_cameraRef = new Camera();
	originalCameraHeight = PLAYER_HEIGHT;
	m_cameraRef->Transform().Position().setY(originalCameraHeight);
}

Player::~Player() {
	deactivateEvents();
	CollisionHandler::instance()->removeCollider(&m_collider);
}

void Player::draw() {
	m_cameraRef->draw();
	//m_collider.debugDraw();
}

void Player::load(const LoadParameters parameters) {
	GameObject::load(parameters);
	CollisionHandler::instance()->registerCollider(&m_collider);
	m_collider.set(m_transform.Position());
	deathTimer = 150;
}

void Player::update() {
	m_cameraRef->lookAt(sinf(m_transform.Rotation().getY()), -tanf(m_transform.Rotation().getX()), -cosf(m_transform.Rotation().getY()));

	if (!isDead) {
		m_right.set(m_cameraRef->getTarget().Cross(Vector3f(0.0f, 1.0f, 0.0f)));
		m_velocity.set((m_cameraRef->getTarget() * m_forwardAxis) + (m_right * m_rightAxis));
		m_velocity.setY(0.0f);
		m_velocity.normalize();

		Vector3f newPos = (m_transform.Position() + (m_velocity * PLAYER_SPEED));

		CollisionHandler* CH = CollisionHandler::instance();

		float oldX = m_transform.Position().getX();
		float oldZ = m_transform.Position().getZ();
		float newX = newPos.getX();
		float newZ = newPos.getZ();

		if (CH->getWorldCollision(oldX + WORLD_COLLISION_OFFSET, newZ + WORLD_COLLISION_OFFSET) == COLLISION_WALL ||
			CH->getWorldCollision(oldX - WORLD_COLLISION_OFFSET, newZ - WORLD_COLLISION_OFFSET) == COLLISION_WALL ||
			CH->getWorldCollision(oldX + WORLD_COLLISION_OFFSET, newZ - WORLD_COLLISION_OFFSET) == COLLISION_WALL ||
			CH->getWorldCollision(oldX - WORLD_COLLISION_OFFSET, newZ + WORLD_COLLISION_OFFSET) == COLLISION_WALL) {
			m_velocity.setZ(0.0f);
		}
		if (CH->getWorldCollision(newX + WORLD_COLLISION_OFFSET, oldZ + WORLD_COLLISION_OFFSET) == COLLISION_WALL ||
			CH->getWorldCollision(newX - WORLD_COLLISION_OFFSET, oldZ - WORLD_COLLISION_OFFSET) == COLLISION_WALL ||
			CH->getWorldCollision(newX + WORLD_COLLISION_OFFSET, oldZ - WORLD_COLLISION_OFFSET) == COLLISION_WALL ||
			CH->getWorldCollision(newX - WORLD_COLLISION_OFFSET, oldZ + WORLD_COLLISION_OFFSET) == COLLISION_WALL) {
			m_velocity.setX(0.0f);
		}

		m_transform.Position().mod(m_velocity * PLAYER_SPEED);
		m_collider.move(m_velocity * PLAYER_SPEED);

		if (m_velocity.lengthSqr() > 0.0f) {
			headBob += 0.1f;
			m_cameraRef->Transform().Position().setY(Math::Lerp(m_cameraRef->Transform().Position().getY(), originalCameraHeight + (sinf(headBob * HEADBOB_SPEED) / HEADBOB_MAGNITUDE), 0.25f));
		}
		else {
			headBob = 0.0f;
			m_cameraRef->Transform().Position().setY(Math::Lerp(m_cameraRef->Transform().Position().getY(), originalCameraHeight, 0.1f));
		}
		m_cameraRef->Transform().Position().setX(m_transform.Position().getX());
		m_cameraRef->Transform().Position().setZ(m_transform.Position().getZ());
	}
	else {
		m_transform.Rotation().setX(Math::Lerp(m_transform.Rotation().getX(), -MAXIMUM_VERTICAL_LOOK, 0.1f));
		m_cameraRef->Transform().Position().setY(Math::Lerp(m_cameraRef->Transform().Position().getY(), 0.2f, 0.1f));
		deathTimer--;
		if (deathTimer == 120) LevelManager::instance()->getCurrentLevel()->transitionFade();
		else if (deathTimer == 0) {
			if (goToMenu) GameStateMachine::instance()->changeState(new MenuState);
			else LevelManager::instance()->restartCurrentLevel();
		}
	}
}

void Player::OnMouseMotionEvent(const SDL_MouseMotionEvent& e) {
	if (isDead) return;
	m_transform.Rotation().mod((float)e.yrel * 0.0042f, (float)e.xrel * 0.0035f, 0.0f);
	m_transform.Rotation().setX(Math::Clamp(m_transform.Rotation().getX(), -MAXIMUM_VERTICAL_LOOK, MAXIMUM_VERTICAL_LOOK));
}

void Player::OnKeyboardEvent(const SDL_KeyboardEvent& e) {
	switch (e.keysym.scancode) {
	case SDL_SCANCODE_W:
		m_forwardAxis = (e.state == SDL_PRESSED) ? 1.0 : 0.0f;
		break;
	case SDL_SCANCODE_S:
		m_forwardAxis = (e.state == SDL_PRESSED) ? -1.0f : 0.0f;
		break;
	case SDL_SCANCODE_A:
		m_rightAxis = (e.state == SDL_PRESSED) ? -1.0f : 0.0f;
		break;
	case SDL_SCANCODE_D:
		m_rightAxis = (e.state == SDL_PRESSED) ? 1.0f : 0.0f;
		break;
	case SDL_SCANCODE_ESCAPE:
		isDead = true;
		goToMenu = true;
		break;
	case SDL_SCANCODE_RETURN:
		LevelManager::instance()->getCurrentLevel()->setCompleted();
		break;
	}
}

void Player::clean() {
	m_cameraRef->clean();
	delete m_cameraRef;
}

void Player::collision(std::string tag) {
	if (tag == "ENEMY" && !isDead) {
		isDead = true;
	}
	else if (tag == "KEYCARD") {
		LevelManager::instance()->getCurrentLevel()->setCompleted();
	}
}