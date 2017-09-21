#include "MenuState.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "JMath.h"
#include "Game.h"
#include "PlayState.h"

const std::string MenuState::s_stateID = "MENU";

void MenuState::update() {
	if (transitioning) {
		transitionTimer--;
		if (transitionTimer == 0) {
			if (quitGame) {
				Game::instance()->quit();
			}
			else {
				GameStateMachine::instance()->changeState(new PlayState);
			}
		}
	}
}

void MenuState::render() {
	TextureManager::instance()->drawTextureToScreen("mainMenu", 0, 0, 1, 1);
	m_transitionAmount = Math::Lerp(m_transitionAmount, m_transitionTarget, 0.05f);
	TextureManager::instance()->drawColorToScreen(0.0f, 0.0f, 0.0f, m_transitionAmount, 0, 0, 1, 1);
}

int MenuState::onEnter() {
	activateEvents();
	bool textureSuccess = true;

	textureSuccess = TextureManager::instance()->loadTexture("res/menu_MAIN.png", "mainMenu");
	
	if (!textureSuccess) return STATE_ERROR;

	transitionTimer = 120;
	m_transitionAmount = 1.0f;
	m_transitionTarget = 0.0f;
	return STATE_CLEAN;
}

void MenuState::onExit() {
	deactivateEvents();
}

void MenuState::OnKeyboardEvent(const SDL_KeyboardEvent& e) {
	if (transitioning) return;

	switch (e.keysym.scancode) {
	case SDL_SCANCODE_ESCAPE: case SDL_SCANCODE_Q:
		transitioning = true;
		m_transitionTarget = 1.0f;
		quitGame = true;
		break;
	case SDL_SCANCODE_LALT:
	case SDL_SCANCODE_LCTRL:
	case SDL_SCANCODE_LSHIFT:
		break;
	default:
		transitioning = true;
		m_transitionTarget = 1.0f;
		quitGame = false;
		break;
	}
}

