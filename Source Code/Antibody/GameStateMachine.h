#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "StateGameAbstract.h"
//#include <vector>

class GameStateMachine {
public:
	GameStateMachine() {}
	~GameStateMachine() {}

	void update();
	void render();

	void pushState(StateGameAbstract* pState);
	void changeState(StateGameAbstract* pState);
	void popState();

	void clean();

	std::vector<StateGameAbstract*>& getGameStates() { return m_gameStates; }

private:
	std::vector<StateGameAbstract*> m_gameStates; // P106 A place to store states
};


#endif