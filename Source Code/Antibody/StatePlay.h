#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "StateGameAbstract.h"
#include "GameObject.h"
//#include "SDLGameObject.h" // SDLGameObject
//#include <vector>
#include <string>
//#include "Level.h"

class GameObject;

class StatePlay : public StateGameAbstract {
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }
	//bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	//bool checkCollision(GameObject* p1, GameObject* p2);

private:
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;
	//Level* pLevel;

};

#endif