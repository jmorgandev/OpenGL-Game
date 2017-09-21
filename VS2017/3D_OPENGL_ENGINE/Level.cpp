#include "Level.h"
#include <algorithm>
#include "TextureManager.h"
#include "JMath.h"
#include "LevelManager.h"
#include "GameStateMachine.h"
#include "CollisionHandler.h"

void Level::update() {
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();) {
		if ((*it)->toRemove()) it = m_gameObjects.erase(it);
		else {
			(*it)->update();
			if (m_gameObjects.empty()) {
				return;
			}
			//if (LevelManager::instance()->getCurrentLevel() != this) return;
			if (GameStateMachine::instance()->getCurrentID() != "PLAY") return;
			it++;
		}
	}
}

void Level::render() {
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
		(*it)->draw();
	}
	transitionColorAmount = Math::Lerp(transitionColorAmount, transitionTarget, 0.05f);
	TextureManager::instance()->drawColorToScreen(0.0f, 0.0f, 0.0f, transitionColorAmount, 0, 0, 1, 1);
}

void Level::insertGameObject(GameObject* object, int position) {
	std::vector<GameObject*>::iterator it = m_gameObjects.begin() + position;
	m_gameObjects.insert(it, object);
}

GameObject* Level::FindByName(char* name) {
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
		if ((*it)->getName() == name) return (*it);
	}
	return NULL;
}

GameObject* Level::FindByTag(char* tag) {
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
		if ((*it)->getTag() == tag) return (*it);
	}
	return NULL;
}

void Level::clean() {
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
		(*it)->clean();
		delete *it;
	}
	m_gameObjects.clear();
}