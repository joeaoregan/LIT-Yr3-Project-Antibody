#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "GameStateAbstract.h"
//#include <vector>

class GameStateMachine {
public:
	GameStateMachine() {}
	~GameStateMachine() {}

	void update();
	void render();

	void pushState(GameStateAbstract* pState);
	void changeState(GameStateAbstract* pState);
	void popState();

	void clean();

	std::vector<GameStateAbstract*>& getGameStates() { return m_gameStates; }

private:
	std::vector<GameStateAbstract*> m_gameStates; // P106 A place to store states
};


#endif