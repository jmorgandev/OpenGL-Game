#ifndef LEVEL_H
#define LEVEL_H

#include "GameObject.h"
#include "Camera.h"
#include <vector>
#include <string>

class Level {
public:
	Level(const char* name) { m_levelName = name; transitionTarget = 0.0f; transitionColorAmount = 1.0f; }

	GameObject* FindByName(char* name);
	GameObject* FindByTag(char* tag);

	std::vector<GameObject*> FindObjectsByName(char* name);
	std::vector<GameObject*> FindObjectsByTag(char* tag);

	Camera* getCamera();

	void update();
	void render();
	void clean();

	void unloadLevel() { unload = true; }
	void transitionFade() { transitionTarget = 1.0f; }

	std::string getLevelName() { return m_levelName; }

	bool levelCompleted() { return completed; }
	void setCompleted() { completed = true; }

	void insertGameObject(GameObject* object, int position);
	void addGameObject(GameObject* object) { m_gameObjects.push_back(object); }
	
	int getLightCount() { return m_lightCount; }
	void addLightCount() { m_lightCount++; }

private:
	std::vector<GameObject*> m_gameObjects;

	std::string m_levelName;

	int m_lightCount;

	bool unload;
	bool completed;

	float transitionColorAmount;
	float transitionTarget;
};

#endif