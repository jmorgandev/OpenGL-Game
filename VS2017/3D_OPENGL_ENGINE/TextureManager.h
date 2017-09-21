#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <glut.h>
#include <SDL.h>
#include <string>
#include <map>
//Singleton to handle all currently loaded textures, and loading of textures
class TextureManager {
public:
	static TextureManager* instance();

	void drawColorToScreen(float r, float g, float b, float a, int x, int y, int w, int h);
	void drawTextureToScreen(std::string id, int x, int y, int w, int h);
	bool loadTexture(std::string fileName, std::string id);

	GLuint getTexture(std::string id);

	void clearTexture(std::string id);
	void clean();
private:
	TextureManager(){}

	std::map<std::string, GLuint> m_textureMap;
};

#endif