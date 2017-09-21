#include "PlayState.h"
#include "LevelManager.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "CollisionHandler.h"

const std::string PlayState::s_stateID = "PLAY";

void PlayState::update() {
	LevelManager::instance()->getCurrentLevel()->update();
	CollisionHandler::instance()->handleCollisions();
}

void PlayState::render() {
	LevelManager::instance()->getCurrentLevel()->render();
}

int PlayState::onEnter() {
	if (!LevelManager::instance()->loadLevels("data/levelData.xml")) return STATE_ERROR;

	if (!TextureManager::instance()->loadTexture("res/panel_normal.png", "texture_PANEL")) return STATE_ERROR;
	if (!TextureManager::instance()->loadTexture("res/panel_corner.png", "texture_CORNER")) return STATE_ERROR;
	if (!TextureManager::instance()->loadTexture("res/room_normal.png", "texture_ROOM")) return STATE_ERROR;
	if (!TextureManager::instance()->loadTexture("res/room_light.png", "texture_ROOMLIGHT")) return STATE_ERROR;
	if (!TextureManager::instance()->loadTexture("res/room_elevator.png", "texture_ELEVATOR")) return STATE_ERROR;
	if (!TextureManager::instance()->loadTexture("res/door_elevator.png", "texture_ELEVATORDOOR")) return STATE_ERROR;
	if (!TextureManager::instance()->loadTexture("res/room_window.png", "texture_WINDOW")) return STATE_ERROR;

	m_materials["panel"] = new Material(TextureManager::instance()->getTexture("texture_PANEL"));
	m_materials["corner"] = new Material(TextureManager::instance()->getTexture("texture_CORNER"));
	m_materials["room"] = new Material(TextureManager::instance()->getTexture("texture_ROOM"));
	m_materials["roomLight"] = new Material(TextureManager::instance()->getTexture("texture_ROOMLIGHT"));
	m_materials["elevatorInside"] = new Material(TextureManager::instance()->getTexture("texture_ELEVATOR"));
	m_materials["elevatorDoor"] = new Material(TextureManager::instance()->getTexture("texture_ELEVATORDOOR"));
	m_materials["enemy"] = new Material(0.0f, 0.0f, 0.0f, 1.0f, 0.01f, 0.01f, 0.01f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	m_materials["keycard"] = new Material(0.1f, 0.35f, 0.1f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.45f, 0.55f, 0.45f, 1.0f, 0.25f, 0.5f, 0.25f, 1.0f);
	
	m_materials["window"] = new Material();
	m_materials["window"]->setDiffuse(109 / 255.0f, 219 / 255.0f, 249 / 255.0f, 0.3f);
	//m_materials["window"]->setShininess(1.0f);
	//m_materials["window"]->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	m_materials["windowFloor"] = new Material(TextureManager::instance()->getTexture("texture_WINDOW"));

	m_materials["elevatorInside"]->setEmission(0.5f, 0.5f, 0.5f, 1.0f);
	m_materials["enemy"]->setShininess(0.1f);
	m_materials["keycard"]->setShininess(0.25f);

	LevelManager::instance()->useMaterials(m_materials);

	if (!LevelManager::instance()->loadStartLevel()) return STATE_ERROR;

	return STATE_CLEAN;
}

void PlayState::onExit() {

	LevelManager::instance()->clean();

	for (std::map<std::string, Material*>::iterator it = m_materials.begin(); it != m_materials.end(); it++) {
		delete it->second;
	}
	m_materials.clear();
}

