#include "WinState.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "JMath.h"
#include "Game.h"
#include "PlayState.h"

const std::string WinState::s_stateID = "WIN";

void WinState::update() {
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

void WinState::render() {
	TextureManager::instance()->drawTextureToScreen("menuWin", 0, 0, 1, 1);
	m_transitionAmount = Math::Lerp(m_transitionAmount, m_transitionTarget, 0.05f);
	TextureManager::instance()->drawColorToScreen(0.0f, 0.0f, 0.0f, m_transitionAmount, 0, 0, 1, 1);
}

int WinState::onEnter() {
	activateEvents();
	bool textureSuccess = true;

	textureSuccess = TextureManager::instance()->loadTexture("res/menu_WIN.png", "menuWin");

	if (!textureSuccess) return STATE_ERROR;

	transitionTimer = 120;
	m_transitionAmount = 1.0f;
	m_transitionTarget = 0.0f;
	return STATE_CLEAN;
}

void WinState::onExit() {
	deactivateEvents();
}

void WinState::OnKeyboardEvent(const SDL_KeyboardEvent& e) {
	if (transitioning) return;

	switch (e.keysym.scancode) {
	case SDL_SCANCODE_ESCAPE: case SDL_SCANCODE_Q:
		transitioning = true;
		m_transitionTarget = 1.0f;
		quitGame = true;
		break;
	case SDL_SCANCODE_R:
		transitioning = true;
		m_transitionTarget = 1.0f;
		break;
		break;
	}
}

