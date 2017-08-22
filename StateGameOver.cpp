#include <iostream>
#include "StateMainMenu.h" //
//#include "AnimatedGraphic.h"
#include "StateGameOver.h"
#include "StatePlay.h"
#include "Texture.h"
#include "Game.h"
#include "Button.h"
//#include "StateParser.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain() {
	Game::Instance()->getStateMachine()->changeState(new	StateMainMenu());
}

void GameOverState::s_restartPlay() {
	Game::Instance()->getStateMachine()->changeState(new	StatePlay());
}

void GameOverState::update() {
	for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->move();
	}
}

void GameOverState::render() {
	for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->render();
	}
}

bool GameOverState::onEnter() {
	//StateParser stateParser;	// parse the state

	//stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	// set the callbacks for menu items
	setCallbacks(m_callbacks);
	std::cout << "entering PauseState\n";
	return true;

	std::cout << "entering GameOverState\n";

	return true;
}

bool GameOverState::onExit() {
	//for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
	//	m_gameObjects[i]->clean();
	//}

	m_gameObjects.clear();

	// clear the texture manager
	for (unsigned int i = 0; i < m_textureIDList.size(); i++) {
		Texture::Instance()->clearFromTextureMap(m_textureIDList[i]);	// P155 Texture clearing on leaving the state
	}

	std::cout << "exiting MenuState\n";

	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks) {
	// go through the game objects
	for (unsigned int i = 0; i < m_gameObjects.size(); i++) {
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if (dynamic_cast<Button*>(m_gameObjects[i])) {
			Button* pButton = dynamic_cast<Button*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}
