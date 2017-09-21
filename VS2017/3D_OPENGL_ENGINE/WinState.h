#ifndef WINSTATE_H
#define WINSTATE_H

#include "GameState.h"
#include "EventHandler.h"


//Main menu state
class WinState : public GameState, public EventHandler {
public:
	virtual void update();
	virtual void render();

	virtual int onEnter();
	virtual void onExit();

	virtual std::string getStateID() const { return s_stateID; }

private:
	static const std::string s_stateID;

	float m_transitionAmount;
	float m_transitionTarget;

	int transitionTimer;
	bool transitioning;
	bool quitGame;

	virtual void OnKeyboardEvent(const SDL_KeyboardEvent& e);
};

#endif