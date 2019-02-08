#include <iostream>
#include "StateMainMenu.h"
#include "StatePlay.h"
#include "Texture.h"
#include "Game.h"
#include "Button.h"
//#include "StateParser.h"

const std::string StateMainMenu::s_menuID = "MENU";

bool StateMainMenu::onEnter() {
	// parse the state
	//StateParser stateParser;														// P148 Create StateParser
	//stateParser.parseState("test.xml", s_menuID, &m_gameObjects, &m_textureIDList);	// Use it to parse the current state
	m_callbacks.push_back(0); //pushback 0 callbackID start from 1					// Push any callbacks to the m_callbacks array inherited from MenuState
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);
	// set the callbacks for menu items
	setCallbacks(m_callbacks);
	std::cout << "entering MenuState\n";
	return true;
}

bool StateMainMenu::onExit() {
	//for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
	//	m_gameObjects[i]->clean();
	//}

	m_gameObjects.clear();

	// P151 Clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++) {
		Texture::Instance()->clearFromTextureMap(m_textureIDList[i]);	// P151 clear any used textures in the onExit function of each state
	}

	std::cout << "exiting MenuState\n";

	return true;
}

void StateMainMenu::update() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->move();
	}
}

void StateMainMenu::render() {
	for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->render();
	}
}

void StateMainMenu::s_menuToPlay() {
	std::cout << "Play button clicked\n";

	Game::Instance()->getStateMachine()->changeState(new StatePlay());
}

void StateMainMenu::s_exitFromMenu() {
	std::cout << "Exit button clicked\n";

	Game::Instance()->close();	// Exit the game
}

// Assign callbacks
void StateMainMenu::setCallbacks(const std::vector<Callback>& callbacks) {
	// go through the game objects
	for (int i = 0; i < m_gameObjects.size(); i++) {
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if (dynamic_cast<Button*>(m_gameObjects[i])) {													// P149 Use dynamic_cast to object is a MenuButton
			Button* pButton = dynamic_cast<Button*>(m_gameObjects[i]);								// Actually cast the object to a MenuButton
			pButton->setCallback(callbacks[pButton->getCallbackID()]);										// Use the callbackID as the index into the callbacks vector and assign the correct function
		}
	}
}