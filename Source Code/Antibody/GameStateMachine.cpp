#include "GameStateMachine.h"

void GameStateMachine::clean() {
	if (!m_gameStates.empty()) {
		m_gameStates.back()->onExit();

		delete m_gameStates.back();

		m_gameStates.clear();
	}
}

/* Update the current state, always uses state at the back of the array */
void GameStateMachine::update() {
	if (!m_gameStates.empty()) {		// P110 Check if there is any state in the vector of states
		m_gameStates.back()->update();	// If there is a state update it
	}
}

/* Render the current state, always uses state at the back of the array  */
void GameStateMachine::render() {
	if (!m_gameStates.empty()) {		// P110 Check if there is any state in the vector of states
		m_gameStates.back()->render();	// If there is a state render it
	}
}
/* P108 Push the passed-in pState parameter into the m_gameStates array and 
call its onEnter function */
void GameStateMachine::pushState(StateGameAbstract *pState) {
	m_gameStates.push_back(pState);		// Add a state to vector of states
	m_gameStates.back()->onEnter();		// Call the onEnter function to init the state
}

/* P108 Check if there's states available to remove, and if there is, call the 
onExit function of the current state, to clear it our of memory, and then remove it */
void GameStateMachine::popState() {
	if (!m_gameStates.empty()) {			// If the vector of stored states is not empty
		m_gameStates.back()->onExit();		// Call the onExit function to clear the state
		m_gameStates.pop_back();			// Remove current state
	}

	m_gameStates.back()->resume();
}
/* P109 Check if there are states in the array, do nothing if the state matches the 
current stored states ID. It its not a match remove the current state, add the new
state, call its onEnter function */
void GameStateMachine::changeState(StateGameAbstract *pState) {
	if (!m_gameStates.empty()) {											// If the vector of states is not empty
		if (m_gameStates.back()->getStateID() == pState->getStateID()) {	// If the state is the same as the one stored
			return;															// do nothing
		}

		m_gameStates.back()->onExit();										// Clear the previous state
		m_gameStates.pop_back();											// Remove it
	}
		
	pState->onEnter();														// Initialise new state
	
	m_gameStates.push_back(pState);											// Push back new state
}