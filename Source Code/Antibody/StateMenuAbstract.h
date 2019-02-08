#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "StateGameAbstract.h"
#include <vector>

// Abstract class that inherits from GameState

class StateMenuAbstract : public StateGameAbstract {
protected:
	typedef void(*Callback)();
	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;	// P147 Function that sets the callbacks for any items that need it

	std::vector<Callback> m_callbacks;										// P147 Vector of Callback objects
};

#endif