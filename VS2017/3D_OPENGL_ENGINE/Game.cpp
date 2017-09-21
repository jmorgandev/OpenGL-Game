#include <glut.h>
#include <math.h>

#include "Game.h"
#include "GameStateMachine.h"
#include "EventPoller.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"
#include "LevelManager.h"

#include <stdio.h>
#include <time.h>

GLuint textureData = 0;

Game* Game::instance() {
	static Game game_instance;
	return &game_instance;
}

//Initialise the SDL window to the scaled resolution
//and then set the internal resolution to the passed width and height arguments
bool Game::init(const char* title, int xpos, int ypos, int width, int height, double aspectRatio, bool fullscreen) {
	m_ScreenWidth = width;
	m_ScreenHeight = height;
	m_aspectRatio = aspectRatio;
	int flags = NULL;
	flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
	srand((unsigned)time(0));

#ifdef USING_OPENGL
	flags |= SDL_WINDOW_OPENGL;
#endif

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Failed to initialise SDL. Error: %s", SDL_GetError());
		return false;
	}
	m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (m_pWindow == NULL) {
		printf("Failed to create SDL Window. Error: %s", SDL_GetError());
		return false;
	}

#ifdef USING_OPENGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	m_GLContext = SDL_GL_CreateContext(m_pWindow);

	if (m_GLContext == NULL) {
		printf("Failed to create GL Context. Error: %s", SDL_GetError());
		return false;
	}

	int a = 0;
	char** s = 0;
	glutInit(&a, s);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, aspectRatio, 0.1, 1000.0);

	GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	glMatrixMode(GL_MODELVIEW);

#else
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_pRenderer == NULL) {
		printf("Failed to create SDL Renderer. Error: %s", SDL_GetError());
		return false;
	}
	SDL_RenderSetLogicalSize(m_pRenderer, width, height);
	SDL_SetRenderDrawColor(m_pRenderer, 0xFB, 0xD8, 0xB8, 0xFF);

#endif

	

	GameStateMachine::instance()->changeState(new MenuState);

	m_bRunning = true;

	//Lock and Hide mouse cursor
	SDL_SetRelativeMouseMode(SDL_TRUE);

	return true;
}

//Render the current gamestate
void Game::render() {
#ifdef USING_OPENGL
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);
	//m_mainCamera->update();
#else
	SDL_RenderClear(m_pRenderer);
#endif
	GameStateMachine::instance()->render();

#ifdef USING_OPENGL
	SDL_GL_SwapWindow(m_pWindow);
#else
	SDL_RenderPresent(m_pRenderer);
#endif
}

//Add an event handler to the Event Poller
void Game::addEventHandler(EventHandler* pHandler) {
	EventPoller::instance()->addHandler(pHandler);
}

//Remove an event handler from the Event Poller
void Game::removeEventHandler(EventHandler* pHandler) {
	EventPoller::instance()->removeHandler(pHandler);
}

//Poll SDL Events using Event Poller
void Game::handleEvents() {
	EventPoller::instance()->update();
}

//Update the current GameState
void Game::update() {
	GameStateMachine::instance()->update();
}

//Quit the program
void Game::quit() {
	m_bRunning = false;
}


//Clean up everything
void Game::clean() {
	GameStateMachine::instance()->clean();
	EventPoller::instance()->clean();
	TextureManager::instance()->clean();
	GameObjectFactory::instance()->clean();

#ifdef USING_OPENGL
	SDL_GL_DeleteContext(m_GLContext);
	m_GLContext = NULL;
#else
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
#endif
}