#ifndef MENU_H
#define MENU_H

//#include "MenuState.h"
#include "Button.h"
#include "Texture.h"

//class Menu : public MenuState {
class Menu {
public:
	static Menu* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Menu();
			return s_pInstance;
		}

		return s_pInstance;
	}

	virtual void update();
	//virtual void render() {};

	virtual bool init();
	virtual bool clean();

	TTF_Font *gFont = NULL;

	// Menu Text
	Texture gMenuTextTexture1;
	Texture gMenuTextTexture2;
	Texture gMenuTextTexture3;
	Texture gMenuTextTexture4;
	Texture gMenuTextTexture5;
	Texture gMenuTextTexture6;
	Texture gMenuTextTexture7;
	Texture gMenuTextTexture8;

	//Buttons objects
	Button gButtons[TOTAL_BUTTONS];
	Button gMenuButtons[TOTAL_BUTTONS];

	SDL_Rect gSpriteClipsMenu[BUTTON_SPRITE_TOTAL];
	Texture gButtonSpriteSheetTexture;
	
	void handleMenuEvents(SDL_Event& e);
	void drawPause();

private:
	static Menu* s_pInstance;
};

#endif