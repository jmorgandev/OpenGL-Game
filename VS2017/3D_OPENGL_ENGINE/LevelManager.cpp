#include "LevelManager.h"
#include "tinyxml.h"
#include <SDL_image.h>
#include <SDL.h>
#include "GameStateMachine.h"
#include "CollisionHandler.h"

#include "Block.h"
#include "Floor.h"
#include "Light.h"
#include "Elevator.h"
#include "Player.h"
#include "Enemy.h"
#include "Keycard.h"
#include "WinState.h"

LevelManager* LevelManager::instance() {
	static LevelManager levelManager_instance;
	return &levelManager_instance;
}

bool LevelManager::loadLevels(const char* filename) {
	TiXmlDocument XML_FILE;

	if (!XML_FILE.LoadFile(filename)) {
		printf("ERROR: Could not load %s\n", filename);
		printf("XML ERROR: %s\n", XML_FILE.ErrorDesc());
		return false;
	}

	TiXmlElement* pRoot = XML_FILE.RootElement();

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		std::string id = e->Attribute("name");
		std::string file_directory = e->Attribute("filename");

		m_levelList.push_back(std::make_pair(id, file_directory));
	}

	return true;
}

bool LevelManager::loadStartLevel() { return loadLevelByIndex(0); }
bool LevelManager::loadNextLevel() {
	if (m_currentLevel + 1 >= m_levelList.size()) {
		GameStateMachine::instance()->changeState(new WinState);
		return true;
	}
	return loadLevelByIndex(m_currentLevel + 1);
}
bool LevelManager::loadPreviousLevel() { return loadLevelByIndex(m_currentLevel - 1); }

bool LevelManager::loadLevelByIndex(int index) {
	if (m_loadedLevel != NULL) {
		m_loadedLevel->clean();
		delete m_loadedLevel;
		m_loadedLevel = NULL;
	}

	SDL_Surface* fileSurface = IMG_Load(m_levelList[index].second.c_str());
	if (fileSurface == NULL) {
		printf("ERROR: Cannot open level file \"%s\"\n", m_levelList[index].second);
		printf("SDL ERROR: %s.\n", IMG_GetError);
		return false;
	}

	CollisionHandler::instance()->clean();

	CollisionHandler::instance()->createWorldRegistry(fileSurface->w, fileSurface->h);

	Level* newLevel = new Level(m_levelList[index].first.c_str());

	Uint32* pixelData = (Uint32*)fileSurface->pixels;

	GameObject* player = new Player();
	newLevel->addGameObject(player);

	for (int i = 0; i < fileSurface->w * fileSurface->h; i++) {
		GameObject* object = NULL;
		float xPos = i % fileSurface->w;
		float zPos = i / fileSurface->w;

		Uint32 debugHEX = pixelData[i];
		switch (pixelData[i]) {
		case LEVEL_FLOOR:
			object = new Floor();
			object->load(LoadParameters(xPos, 0.0f, zPos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Floor", "FLOOR"));
			object->setMaterial(m_materialList["room"]);

			CollisionHandler::instance()->setWorldCollision(xPos, zPos, COLLISION_NONE);
			break;

		case LEVEL_WALL:
			object = new Block();
			object->load(LoadParameters(xPos, 0.0f, zPos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Panel", "WALL"));
			object->setMaterial(m_materialList["panel"]);

			CollisionHandler::instance()->setWorldCollision(xPos, zPos, COLLISION_WALL);
			break;

		case LEVEL_CORNER:
			object = new Block();
			object->load(LoadParameters(xPos, 0.0f, zPos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Corner", "WALL"));
			object->setMaterial(m_materialList["corner"]);

			CollisionHandler::instance()->setWorldCollision(xPos, zPos, COLLISION_WALL);
			break;

		case LEVEL_ELEVATOR:
			object = new Elevator(m_materialList["elevatorDoor"]);
			object->load(LoadParameters(xPos, 0.0f, zPos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Elevator", "ELEVATOR"));
			object->setMaterial(m_materialList["elevatorInside"]);
			player->load(LoadParameters(xPos + BLOCK_HALFWIDTH, 0.0f, zPos + BLOCK_HALFWIDTH + (BLOCK_HALFWIDTH / 2), 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Player", "PLAYER"));
			CollisionHandler::instance()->setWorldCollision(xPos, zPos, COLLISION_ELEVATOR);
			break;

		case LEVEL_LIGHT:
			object = new Light(Vector3f(xPos + BLOCK_HALFWIDTH, LIGHT_HEIGHT, zPos + BLOCK_HALFWIDTH), false, newLevel->getLightCount(), Color3f(1.0f, 1.0f, 1.0f, 1.0f), Color3f(0.0f, 0.0f, 0.0f, 1.0f), Color3f(1.0f, 1.0f, 1.0f, 1.0f));
			newLevel->addLightCount();
			newLevel->insertGameObject(object, 1);

			object = new Floor();
			object->load(LoadParameters(xPos, 0.0f, zPos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Floor", "FLOOR"));
			object->setMaterial(m_materialList["roomLight"]);
			CollisionHandler::instance()->setWorldCollision(xPos, zPos, COLLISION_NONE);
			break;

		case LEVEL_ENEMY_CW:
			object = new Enemy(false);
			object->load(LoadParameters(xPos + BLOCK_HALFWIDTH, 1.0f, zPos + BLOCK_HALFWIDTH, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Enemy", "ENEMY"));
			object->setMaterial(m_materialList["enemy"]);
			newLevel->addGameObject(object);

			object = new Floor();
			object->load(LoadParameters(xPos, 0.0f, zPos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Floor", "FLOOR"));
			object->setMaterial(m_materialList["room"]);
			CollisionHandler::instance()->setWorldCollision(xPos, zPos, COLLISION_NONE);
			break;

		case LEVEL_ENEMY_ACW:
			object = new Enemy(true);
			object->load(LoadParameters(xPos + BLOCK_HALFWIDTH, 1.0f, zPos + BLOCK_HALFWIDTH, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Enemy", "ENEMY"));
			object->setMaterial(m_materialList["enemy"]);
			newLevel->addGameObject(object);

			object = new Floor();
			object->load(LoadParameters(xPos, 0.0f, zPos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Floor", "FLOOR"));
			object->setMaterial(m_materialList["room"]);
			CollisionHandler::instance()->setWorldCollision(xPos, zPos, COLLISION_NONE);
			break;

		case LEVEL_KEYCARD:
			object = new Keycard();
			object->load(LoadParameters(xPos + BLOCK_HALFWIDTH, 1.0f, zPos + BLOCK_HALFWIDTH, 0.0f, 0.0f, 0.0f, 0.3f, 0.5f, 0.1f, "Keycard", "KEYCARD"));
			object->setMaterial(m_materialList["keycard"]);
			newLevel->addGameObject(object);

			object = new Floor();
			object->load(LoadParameters(xPos, 0.0f, zPos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "Floor", "FLOOR"));
			object->setMaterial(m_materialList["room"]);
			CollisionHandler::instance()->setWorldCollision(xPos, zPos, COLLISION_NONE);
			break;
		}
		if(object != NULL) newLevel->addGameObject(object);
	}

	m_loadedLevel = newLevel;
	m_currentLevel = index;

	return true;
}

void LevelManager::restartCurrentLevel() {
	loadLevelByIndex(m_currentLevel);
}

void LevelManager::clean() {
	m_levelList.clear();

	m_loadedLevel->clean();
	delete m_loadedLevel;
	m_loadedLevel = NULL;
}