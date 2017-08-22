//#include <SDL.h>
//#include <SDL_ttf.h>
#include "Texture.h"

Texture* Texture::s_pInstance = 0;

Texture::Texture(int degrees) {
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mAlpha = 255;				// Default alpha is fully solid colour
	mDegrees = degrees;
	mFlash = false;
}

Texture::~Texture() {
	free();						// Deallocate
}

bool Texture::load(std::string fileName, std::string id) {
//bool Texture::load(std::string fileName, std::string id, SDL_Renderer* rend) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) {
		//std::cout << IMG_GetError();
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

void Texture::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
//void Texture::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* rend, SDL_RendererFlip flip) {
//	SDL_Rect renderQuad = { x, y, mWidth, mHeight };	// Set rendering space and render to screen
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(Game::Instance()->getRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void Texture::renderMap(std::string id, int x, int y, int width, int height) {
//void Texture::renderMap(std::string id, int x, int y, int width, int height, SDL_Renderer* rend) {
	SDL_Rect renderQuad = { x, y, width, height };	// Set rendering space and render to screen


	SDL_RenderCopyEx(Game::Instance()->getRenderer(), m_textureMap[id], NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);	// Render to screen
}

void Texture::weaponIndicator(std::string textureID, int x) {
//void Texture::weaponIndicator(std::string textureID, int x, SDL_Renderer* rend) {
	renderMap(textureID, x + 5, 5, 50, 48);
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
// render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
//void Texture::render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };	// Set rendering space and render to screen

	if (clip != NULL) {									// Set clip rendering dimensions
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(Game::Instance()->getRenderer(), mTexture, clip, &renderQuad, angle, center, flip);	// Render to screen
}



SDL_Color Texture::getFontColour() {
	return txtColour;
}
void Texture::setFontColour(SDL_Color f) {
	txtColour = f;
}

SDL_Texture* Texture::loadTexture(std::string path) {
//SDL_Texture* Texture::loadTexture(std::string path, SDL_Renderer *rend) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);	//Get rid of old loaded surface
	}

	return newTexture;
}




bool Texture::loadFromFile(std::string path) {
//bool Texture::loadFromFile(std::string path, SDL_Renderer *rend) {
	free();	// Get rid of preexisting texture

	SDL_Texture* newTexture = NULL;							// The final texture

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());	// Load image at specified path
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));	// Color key image TURNED OFF FOR BLUE VIRUS

		newTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), loadedSurface);								// Create texture from surface pixels
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);	// Get rid of old loaded surface
	}

	mTexture = newTexture;					// Return success
	return mTexture != NULL;
}

void Texture::loadInputText(std::string input) {
//void Texture::loadInputText(std::string input, SDL_Renderer* rend) {
	SDL_Texture* inputTextTexture = 0;
	Texture::Instance()->loadFromRenderedTextID(inputTextTexture, input, "inputTextID", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);		// Lives in top left corner
}
void Texture::loadEnterNameText(std::string nameText) {
//void Texture::loadEnterNameText(std::string nameText, SDL_Renderer* rend) {
	SDL_Texture* enterName = 0;	// The actual hardware texture
	Texture::Instance()->loadFromRenderedTextID(enterName, nameText, "enterNameID", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);		// Lives in top left corner
}

bool Texture::loadFromRenderedTextID(SDL_Texture* text, std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, bool textWrapped) {
//bool Texture::loadFromRenderedTextID(SDL_Texture* text, std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped)
		textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//Render text surface
	else
		textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);

	if (textSurface != NULL) {
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), textSurface);
		if (mTexture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);	//Get rid of old surface
	}
	else {
		printf("loadFromRenderedText(): Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//if (mTexture != 0) {
	if (text != 0) {
		//m_textureMap[id] = mTexture;	// Add to texture map
		m_textureMap[id] = text;	// Add to texture map
		return true;
	}

	//std::cout << "NOT WORKING" << std::endl;
	return false;
}

#ifdef _SDL_TTF_H
bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, bool textWrapped) {
//bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped)
		textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//Render text surface
	else
		textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);

	if (textSurface != NULL) {
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), textSurface);
		if (mTexture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);	//Get rid of old surface
	}
	else {
		printf("loadFromRenderedText(): Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	return mTexture != NULL;	// Return success
}
#endif
void Texture::free() {
	// Free texture if it exists
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(mTexture, red, green, blue);	// Modulate texture rgb
}

void Texture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(mTexture, blending);		// Set blending function
}

int counter = 0;					// counter for changing alpha for flashing
int alphaUp = 5, alphaDown = 5;		// turn the alpha value up or down

//void LTexture::flashGameObject(int &alpha, bool &flash, int rate, int times) {
void Texture::flashGameObject(int rate, int times) {
	if (getFlash()) {
		if (alphaDown > 5) {
			alphaDown -= rate;
			if (getAlpha() < 5) setAlpha(5);
			else setAlpha(alphaDown);
			if (alphaDown <= 5) alphaUp = 5;
		}
		if (alphaUp < 255) {
			alphaUp += rate;
			if (getAlpha() > 255) setAlpha(255);
			else setAlpha(alphaUp);
			if (alphaUp >= 255) alphaDown = 255;
		}

		if (times != 0 && counter > times * 50) {	// takes 25 decrements of 10 to set alpha to 5, and 25 increments to set alpha back to 255, 50 = 1 flash approx.
			setFlash(false);
			counter = 0;
			setAlpha(255);
		}
	}
	else setAlpha(255);	// Set visibility back to maximum

	counter++;
}

void Texture::modifyAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(mTexture, alpha);			// Modulate texture alpha
}

/*
	2017/02/20:
	Function to show who created the game
*/
//void Texture::createdByText(SDL_Renderer* rend) {
void Texture::createdByText() {
	std::string textureText = "ANTIBODY";
	SDL_Color txtColour = { 0, 255, 0, 255 };

	if (SDL_GetTicks() > 0 && SDL_GetTicks() <= lastTime + 1500) {								// Decrement countdown timer
		textureText = "ANTIBODY";
		txtColour = { 50, 200, 255, 255 };	// light blue
	}
	else if (SDL_GetTicks() > lastTime + 1500 && SDL_GetTicks() < lastTime + 3000) {
		textureText = "A GAME BY";
		txtColour = { 0, 255, 0, 255 };
	}
	else if (SDL_GetTicks() > lastTime + 3000 && SDL_GetTicks() < lastTime + 4500) {
		textureText = "Seán Horgan and Joe O'Regan";
		txtColour = { 0, 255, 0, 255 };
	}
	else if (SDL_GetTicks() >= lastTime + 4500)
		lastTime = SDL_GetTicks();

	if (!loadFromRenderedText(textureText, txtColour, TTF_OpenFont("Fonts/Retro.ttf", 16), true)) {		// Green Text
	//if (!loadFromRenderedText(textureText, txtColour, TTF_OpenFont("Fonts/Retro.ttf", 16), rend, true)) {		// Green Text
		printf("createdByText(): Unable to render Created By Text Texture!\n");
	}
}
/*
	2017/02/19:
	Function to indicate if a speed boost is active or not
*/
void Texture::speedBoostText(std::string textureText) {
//void Texture::speedBoostText(std::string textureText, SDL_Renderer* rend) {
	if (!loadFromRenderedText(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 13), true)) {		// Green Text
		printf("speedBoostText(): Unable to render Speed Boost User Interface Text Texture!\n");
	}
}
/*
	2017/02/19:
	Function to indicate how many rockets a player has left
*/
void Texture::numRocketsLeft(std::string textureText) {
//void Texture::numRocketsLeft(std::string textureText, SDL_Renderer* rend) {
	if (!loadFromRenderedText(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 36))) {		// Green Text
		printf("numRocketsLeft(): Unable to render Num Rockets Left User Interface Text Texture!\n");
	}
}
/*
	2017-02-15:
	Function to render the players scores, the FPS, and the current game level
*/
void Texture::UIText(std::string textureText) {
//void Texture::UIText(std::string textureText, SDL_Renderer* rend) {
	if (!loadFromRenderedText(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {		// Green Text
		printf("Unable to render UIText() User Interface Text Texture!\n");
	}

	//render((SCREEN_WIDTH - 150) / 2, 8, rend);
}
/*
	2017-02-15:
	Like the UIText function, only it alters font colour depending on if the timer is running out or not
*/
void Texture::UITextTimer(std::string timerText, unsigned int Timer) {
//void Texture::UITextTimer(std::string timerText, SDL_Renderer* rend, unsigned int Timer) {
	// Time running out change colour to red
	if (Timer >= 0 && Timer <= 5) {
		setFlash(true);

		if (!loadFromRenderedText(timerText, { 255, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {		// Red Text
			printf("Unable to render UITextTimer() User Interface Timer Text Texture!\n");
		}
	}
	else {
		setFlash(false);

		if (!loadFromRenderedText(timerText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {		// Green Text
			printf("Unable to render loadFromRenderedText() User Interface Timer Text Texture!\n");
		}
	}
}

/*
	2017/02/15:
	Independent messages for player 1 and 2, for picking up objects and upgrading weapons etc
*/
void Texture::UITextPlayerMessage(std::string playerMessage, int type) {
//void Texture::UITextPlayerMessage(std::string playerMessage, SDL_Renderer* rend, int type) {
	if (type == 0) {
		if (!loadFromRenderedText(playerMessage, { 65, 210, 240, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {	// Blue Text For General Message
			printf("Unable to render General Info Message text texture!\n");
		}
	}
	else if (type == 1) {
		if (!loadFromRenderedText(playerMessage, { 240, 210, 65, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {	// Gold Text For Player 1
			printf("Unable to render player 1 Message text texture!\n");
		}
	}
	else if (type == 2) {
		if (!loadFromRenderedText(playerMessage, { 0, 255, 150, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {	// Green Text For Player 2
			printf("Unable to render player 2 Message text texture!\n");
		}
	}
}

void Texture::renderMap() {
//void Texture::renderMap(SDL_Renderer* rend) {
	SDL_RenderCopy(Game::Instance()->getRenderer(), mTexture, NULL, NULL);
}

bool Texture::loadTextureMedia() {
//bool Texture::loadTextureMedia(SDL_Renderer* rend) {
	bool success = true;

	// Init the game title and credit screens
	if (Texture::Instance()->load("Art/Logo1720.png", "logoL1ID")) {
		printf("Failed to load Logo 1 - Game Logo texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/Logo2720.png", "creatorL1ID")) {
	//if (!gGameCreatorsTexture.loadFromFile("Art/Logo2720.png", rend)) {						// Load the Game Creators Logo
		printf("Failed to load Logo 2 - Game Creators texture!\n");
		success = false;
	}

	// Level backdrops
	if (Texture::Instance()->load("Art/Level1720.png", "level1ID")) {
		printf("Failed to load Level 1 texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/Level2720.png", "level2ID")) {
		printf("Failed to load Level 2 texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/Level3720.png", "level3ID")) {
		printf("Failed to load Level 3 texture!\n");
		success = false;
	}

	// Init the objects to give information on
	if (Texture::Instance()->load("Art/EnemyShip.png", "enemyShipID")) {
		printf("Failed to load Enemy Ship texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/VirusGreen.png", "greenVirusID")) {
		printf("Failed to load Green Enemy Virus texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/VirusOrange.png", "orangeVirusID")) {
		printf("Failed to load Orange Enemy Virus texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/VirusBlue.png", "blueVirusID")) {
		printf("Failed to load Orange Enemy Virus texture!\n");
		success = false;
	}


	// Weapons
	if (Texture::Instance()->load("Art/VirusFireball.png", "fireballID")) {
		printf("Failed to load Enemy Virus Orange Fireball texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/EnemyVirusSatellite.png", "satelliteID")) {
		printf("Failed to load Enemy Virus Orange Fireball texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/LaserGreen.png", "greenLaserID")) {
		printf("Failed to load Green Laser texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/LaserOrange.png", "orangeLaserID")) {
		printf("Failed to load Orange Laser texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/LaserBlue.png", "blueLaserID")) {
		printf("Failed to load Blue Laser texture!\n");
		success = false;
	}

	// Power Ups
	if (Texture::Instance()->load("Art/PowerUpLife.png", "lifePowerUpID")) {
		printf("Failed to load New Life texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/PowerUpClock.png", "checkpointPowerUpID")) {
		printf("Failed to load Checkpoint texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/PowerUpRocket.png", "rocketPowerUpID")) {
		printf("Failed to load Power Up - Rocket texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/PowerUpHealthBox.png", "healthPowerUpID")) {
		printf("Failed to load Health Power Up texture!\n");
		success = false;
	}
	if (Texture::Instance()->load("Art/PowerUpLaser.png", "laserPowerUpID")) {
		printf("Failed to load Laser Power Up texture!\n");
		success = false;
	}
//	if (Texture::Instance()->load("Art/LaserGunV2.png", "laserV2PowerUpID")) {
	if (Texture::Instance()->load("Art/LaserGunV3.png", "laserV2PowerUpID")) {
		printf("Failed to load Laser V2 Power Up texture!\n");
		success = false;
	}
	return success;
}


