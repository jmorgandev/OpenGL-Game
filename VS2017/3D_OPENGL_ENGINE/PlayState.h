#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"


//Main menu state
class PlayState : public GameState {
public:
	virtual void update();
	virtual void render();

	virtual int onEnter();
	virtual void onExit();

	virtual std::string getStateID() const { return s_stateID; }

private:
	static const std::string s_stateID;
};

#endif