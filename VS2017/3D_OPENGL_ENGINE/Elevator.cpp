#include "Elevator.h"
#include "JMath.h"
#include "LevelManager.h"
#include "CollisionHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"

void Elevator::draw() {
	m_material->updateMaterial();

	glPushMatrix();

	glTranslatef(m_transform.Position().getX(), m_transform.Position().getY(), m_transform.Position().getZ());

	glRotatef(m_transform.Rotation().getX(), 1.0f, 0.0f, 0.0f);
	glRotatef(m_transform.Rotation().getY(), 0.0f, 1.0f, 0.0f);
	glRotatef(m_transform.Rotation().getZ(), 0.0f, 0.0f, 1.0f);

	glScalef(m_transform.Scale().getX(), m_transform.Scale().getY(), m_transform.Scale().getZ());

	renderInside();
	renderDoor();

	glPopMatrix();

	//m_collider.debugDraw();
}

void Elevator::update() {

	//Keep the door Open if the player is near, or closed if the player is far
	switch (doorState) {
	case DOOR_OPEN:
		doorPosition.setX(Math::Lerp(doorPosition.getX(), OPEN_POSITION, DOOR_SPEED));
		break;
	case DOOR_CLOSED:
	case DOOR_LOCKED:
		doorPosition.setX(Math::Lerp(doorPosition.getX(), CLOSED_POSITION, DOOR_SPEED));
		break;
	}
	if (doorState != DOOR_LOCKED) {
		if (doorTimer != 0) {
			doorTimer--;
			if (doorTimer == 0) {
				doorState = DOOR_CLOSED;
			}
		}
	}

	if (levelTransition) {
		levelTimer--;
		if (levelTimer == 120) {
			LevelManager::instance()->getCurrentLevel()->transitionFade();
		}
		else if (levelTimer == 0) {
			if (!LevelManager::instance()->loadNextLevel()) {
				GameStateMachine::instance()->changeState(new MenuState);
			}
		}
	}
	else {
		//If the player is inside the elevator with the keycard, trigger the next level transition
		GameObject* player = LevelManager::instance()->getCurrentLevel()->FindByTag("PLAYER");
		if (CollisionHandler::instance()->getWorldCollision(player->Transform().Position().getX(), player->Transform().Position().getZ()) == COLLISION_ELEVATOR) {
			if (LevelManager::instance()->getCurrentLevel()->levelCompleted() && doorState == DOOR_CLOSED) {
				doorState = DOOR_LOCKED;
				levelTransition = true;
				CollisionHandler::instance()->setWorldCollision(m_transform.Position().getX(), m_transform.Position().getZ() - 1, COLLISION_WALL);
			}
		}
	}
}

void Elevator::collision(std::string object) {
	if (object == "PLAYER") {
		if (doorState != DOOR_LOCKED) {
			doorState = DOOR_OPEN;
			doorTimer = DOOR_TIME;
		}
	}
}

void Elevator::renderDoor() {
	m_doorMaterial->updateMaterial();

	glPushMatrix();
	glTranslatef(doorPosition.getX(), doorPosition.getY(), doorPosition.getZ());

	glDisable(GL_CULL_FACE);
	glBegin(GL_QUADS); {

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLOCK_HEIGHT, 0.0f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(1.0f, BLOCK_HEIGHT, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);

	} glEnd();
	glEnable(GL_CULL_FACE);

	glPopMatrix();
}

void Elevator::renderInside() {

	glBegin(GL_QUADS); {

		//FRONT FACE
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, BLOCK_HEIGHT, 1.0f - 0.001f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, BLOCK_HEIGHT, 1.0f - 0.001f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 1.0f);

		//LEFT FACE
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 0.0f); glVertex3f(0.001f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(0.001f, BLOCK_HEIGHT, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.001f, BLOCK_HEIGHT, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.001f, 0.0f, 1.0f);

		//RIGHT FACE
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 0.0f); glVertex3f(1.0f - 0.001f, 0.0f, 1.0f);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(1.0f - 0.001f, BLOCK_HEIGHT, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f - 0.001f, BLOCK_HEIGHT, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f - 0.001f, 0.0f, 0.0f);

		//BOTTOM FACE
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f); glVertex3f(1.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, 0.0f, 1.0f);

		//TOP FACE
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, BLOCK_HEIGHT, 1.0f);
		glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, BLOCK_HEIGHT, 0.0f);
		glTexCoord2f(0.5f, 0.5f); glVertex3f(1.0f, BLOCK_HEIGHT, 0.0f);
		glTexCoord2f(0.5f, 0.0f); glVertex3f(1.0f, BLOCK_HEIGHT, 1.0f);

	} glEnd();
}