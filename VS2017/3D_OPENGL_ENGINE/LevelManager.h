#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Level.h"
#include <map>
#include "Material.h"

#define LEVEL_FLOOR		0xFF000000
#define LEVEL_WALL		0xFFFFFFFF
#define LEVEL_CORNER	0xFF7F7F7F
#define LEVEL_ELEVATOR	0xFF00FF00
#define LEVEL_LIGHT		0xFF00FFFF
#define LEVEL_ENEMY_CW	0xFF0000FF
#define LEVEL_ENEMY_ACW 0xFF006AFF
#define LEVEL_KEYCARD	0xFFFF0000

class LevelManager {
public:
	LevelManager(){}

	static LevelManager* instance();

	bool loadStartLevel();
	bool loadNextLevel();
	bool loadPreviousLevel();
	
	void restartCurrentLevel();

	bool loadLevelByIndex(int index);

	bool loadLevels(const char* filename);

	Level* getCurrentLevel(){ return m_loadedLevel; }

	std::string currentLevelName() { return m_loadedLevel->getLevelName(); }

	void useMaterials(std::map<std::string, Material*> list) { m_materialList = list; }

	void clean();

private:
	std::vector<std::pair<std::string, std::string>> m_levelList;
	std::map<std::string, Material*> m_materialList;
	
	Level* m_loadedLevel;

	unsigned int m_currentLevel;
};

#endif