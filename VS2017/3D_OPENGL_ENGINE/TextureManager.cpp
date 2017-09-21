#include "TextureManager.h"

#include <SDL_image.h>

TextureManager* TextureManager::instance() {
	static TextureManager textureManager_instance;
	return &textureManager_instance;
}


//Load a texture into the map
bool TextureManager::loadTexture(std::string fileName, std::string id) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == NULL) {
		printf("\nError: %s", IMG_GetError());
		return false;
	}

	GLuint newTexture;
	glGenTextures(1, &newTexture);
	glBindTexture(GL_TEXTURE_2D, newTexture);
	int bpp = (pTempSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, bpp, pTempSurface->w, pTempSurface->h, 0, bpp, GL_UNSIGNED_BYTE, (unsigned char*)pTempSurface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);

	SDL_FreeSurface(pTempSurface);

	m_textureMap[id] = newTexture;
	return true;
}

GLuint TextureManager::getTexture(std::string id) {
	int i = m_textureMap[id];
	return m_textureMap[id];
}


//remove texture from map
void TextureManager::clearTexture(std::string id) {
	glDeleteTextures(1, &m_textureMap[id]);
	m_textureMap.erase(id);
}

//clean everything
void TextureManager::clean() {
	for (std::map<std::string, GLuint>::iterator it = m_textureMap.begin(); it != m_textureMap.end(); it++) {
		glDeleteTextures(1, &it->second);
	}
	m_textureMap.clear();
}

void TextureManager::drawTextureToScreen(std::string id, int x, int y, int w, int h) {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);


	//glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, m_textureMap[id]);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(x - 1, h, 0.01f);
	glTexCoord2f(0, 1); glVertex3f(x - 1, y - 1, 0.01f);
	glTexCoord2f(1, 1); glVertex3f(w, y - 1, 0.01f);
	glTexCoord2f(1, 0); glVertex3f(w, h, 0.01f);
	glEnd();


	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void TextureManager::drawColorToScreen(float r, float g, float b, float a, int x, int y, int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glColor4f(r, g, b, a);

	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(x - 1, h, 0.01f);
	glTexCoord2f(0, 1); glVertex3f(x - 1, y - 1, 0.01f);
	glTexCoord2f(1, 1); glVertex3f(w, y - 1, 0.01f);
	glTexCoord2f(1, 0); glVertex3f(w, h, 0.01f);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}