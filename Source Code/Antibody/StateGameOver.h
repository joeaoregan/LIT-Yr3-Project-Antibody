#ifndef GAME_OVER_STATE
#define GAME_OVER_STATE

#include "StateGameAbstract.h"
#include "GameObject.h"
#include "StateMenuAbstract.h"
//#include <vector>

class GameObject;

class GameOverState : public StateMenuAbstract {	// P154 To handle callbacks GameOverState inherits from MenuState
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; }

private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_gameOverToMain();
	static void s_restartPlay();

	static const std::string s_gameOverID;
	std::vector<GameObject*> m_gameObjects;

};

#endif