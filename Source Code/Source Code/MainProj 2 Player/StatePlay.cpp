#include "StatePlay.h"
#include "Game.h"
#include "Texture.h"
#include "Player.h"
//#include "InputHandler.h"
//#include "StatePause.h"
#include "Enemy.h"
#include "GameObject.h"
#include "StateGameOver.h"
//#include "StateParser.h"
#include <iostream>
//#include "LevelParser.h"
//#include "Level.h"
const std::string StatePlay::s_playID = "PLAY";

void StatePlay::update() {
	//	std::cout << "entering PlayState:update loop \n";

	// PAUSE THE GAME
	//if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
	//	TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	//}

	//pLevel->update();
}

void StatePlay::render() {
	//pLevel->render();
}

bool StatePlay::onEnter() {
	// parse the state

	//LevelParser levelParser;
	std::cout << "about to load map1-helicopter.tmx\n";
	//pLevel = levelParser.parseLevel("assets/map1-helicopter.tmx");
	std::cout << "entering PlayState\n";

	return true;
}

bool StatePlay::onExit() {
	/*
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
	m_gameObjects[i]->clean();
	}
	*/
	//	m_gameObjects.clear();
	//	TheTextureManager::Instance()->clearFromTextureMap("helicopter");
	// clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++) {								// P152 Texture clearing code
		Texture::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "exiting PlayState\n";
	return true;

}
/*
bool StatePlay::checkCollision(GameObject* p1, GameObject* p2) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}
*/