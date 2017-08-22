#ifndef MAIN_MENU_STATE
#define MAIN_MENU_STATE

#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState {
public:
	virtual ~MainMenuState() {}

	virtual void update();
	virtual void render();

	virtual bool init();
	virtual bool clean();

	virtual std::string getStateID() const { return s_menuID; }

private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	// call back functions for menu items
	static void s_menuToPlay();
	static void s_highScores();
	static void s_exitFromMenu();

	static const std::string s_menuID;

	std::vector<GameObject*> m_gameObjects;
};

#endif
