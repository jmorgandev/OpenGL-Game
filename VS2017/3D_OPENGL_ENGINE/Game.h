#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "EventHandler.h"
#include "Camera.h"

//Main game class
class Game {
public:
	static Game* instance();
	~Game(){}

	bool init(const char* title, int xpos, int ypos, int width, int height, double aspectRatio, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void quit();
	void clean();

	void addEventHandler(EventHandler* pHandler);
	void removeEventHandler(EventHandler* pHandler);

	bool running() { return m_bRunning; }
	SDL_Renderer* getRenderer() { return m_pRenderer; }
	Camera* getCamera() { return m_mainCamera; }

	int getScreenWidth() { return m_ScreenWidth; }
	int getScreenHeight() { return m_ScreenHeight; }
	double getAspectRatio() { return m_aspectRatio; }

private:
	Game() {}

	int m_ScreenWidth;
	int m_ScreenHeight;
	double m_aspectRatio;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	Camera* m_mainCamera;
	SDL_GLContext m_GLContext;
	bool m_bRunning;
};

#endif