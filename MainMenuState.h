#ifndef MAIN_MENU_STATE_
#define MAIN_MENU_STATE_

//#include <vector>
#include "MenuStateAbstract.h"
#include "GameObject.h"

class MainMenuState : public MenuStateAbstract {	// P148 Derives from absract MenuState class
public:

	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }

private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	// call back functions for menu items
	static void s_menuToPlay();
	static void s_exitFromMenu();
	static const std::string s_menuID;

	std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__MainMenuState__) */