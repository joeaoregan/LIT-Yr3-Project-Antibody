// 2017/02/27 Abstract Game State class used as a template class for game states

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <iostream>
#include <vector>

class StateGameAbstract {
public:

	virtual ~StateGameAbstract() {}

	virtual void update() = 0;
	virtual void render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual void resume() {}

	virtual std::string getStateID() const = 0;

protected:

	StateGameAbstract() : m_loadingComplete(false), m_exiting(false) {}

	bool m_loadingComplete;
	bool m_exiting;

	std::vector<std::string> m_textureIDList; // P151 A list of texture IDs for each state
};

#endif