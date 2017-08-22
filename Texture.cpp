/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Texture.cpp
	- Description:			cpp file for the Texture class.
	- Information:			This class manages all texture functionality for the game. Loading textures from, storing them to 
							a map for indexing, and then rendering to screen. There are functions to render textures from text, 
							and also to handle the alpha value of objects, to make them transparent or flash.
	- Log:
		2017/03/22		Added animation sprite sheets to the Texture map
		2017/03/18		Added the Ninja Stars and Saw texture to the texture map in Texture class
		2017/03/17		Added the Blood Cell texture to the texture map in Texture class
		2017/02/28		Moved background texture loading to texture map
		2017/02/26		Added singletons for Game and Texture
		2017/02/09		Set a display time for textures such as information messages
						A separate texture is needed for each individual score text, as score value changes for all, when a new score is recorded
		2017/01/30		Added rotation angle to constructors for Textures that rotate
						Moved flashGameObject() functionality into Texture class
		2017/01/24		Changed screen size from 1280 x 720 from 800 x 600
		2017/01/11		Alter function for alpha values to handle any object and not just Players
		2017/01/09		Changed screen size and background to be 800 x 600 instead of 600 x 480
	----------------------------------------------------------------------------------------------------------------------*/
#include "Texture.h"
#include <string>

Texture* Texture::s_pInstance = 0;	// Singleton, so only one instance of texture class is used throughout the game

Texture::Texture() {
	// Initialize
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
	m_Alpha = 255;				// Default alpha is fully solid colour
	m_Flash = false;
}

Texture::~Texture() {
	free();						// Deallocate
}

/*
	Load an image to the texture map given its path, assigning an ID
*/
bool Texture::load(std::string fileName, std::string id) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) {
		std::cout << IMG_GetError();
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0) {
		m_TextureMap[id] = pTexture;
		return true;
	}

	return false;
}

/*
	Render a Texture from the map using an ID
*/
void Texture::renderMap(std::string id) {
	//void Texture::renderMap(SDL_Renderer* rend) {
	if (id == "")
		SDL_RenderCopy(Game::Instance()->getRenderer(), m_Texture, NULL, NULL);
	else
		SDL_RenderCopy(Game::Instance()->getRenderer(), m_TextureMap[id], NULL, NULL);	// render texture from map using id

}
/*
	Render a Texture from map, with position, and dimensions
*/
void Texture::renderMap(std::string id, int x, int y, int width, int height) {
	//void Texture::renderMap(std::string id, int x, int y, int width, int height, SDL_Renderer* rend) {
	SDL_Rect renderQuad = { x, y, width, height };	// Set rendering space and render to screen

	SDL_RenderCopyEx(Game::Instance()->getRenderer(), m_TextureMap[id], NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);	// Render to screen
}
/*
	Render an animated or rotated Texture from the map
*/
void Texture::render(std::string id, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };	// Set rendering space and render to screen

	if (clip != NULL) {									// Set clip rendering dimensions
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(Game::Instance()->getRenderer(), m_TextureMap[id], clip, &renderQuad, angle, center, flip);	// Render to screen
}
/*
	Render a texture
*/
void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };	// Set rendering space and render to screen

	if (clip != NULL) {									// Set clip rendering dimensions
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(Game::Instance()->getRenderer(), m_Texture, clip, &renderQuad, angle, center, flip);	// Render to screen
}
/*
	Render to a point
*/
void Texture::renderP(int x, int y) {
	SDL_Rect renderQuad = { x, y, m_Width, m_Height };	// Set rendering space and render to screen

	SDL_RenderCopyEx(Game::Instance()->getRenderer(), m_Texture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);	// Render to screen
}
/*
	Load a texture give the path to the image loacation
*/
SDL_Texture* Texture::loadTexture(std::string path) {	
	SDL_Texture* newTexture = NULL;																		// The final texture
		
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());												// Load image at specified path
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {		
		newTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), loadedSurface);		// Create texture from surface pixels
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());	// Error message
		}

		SDL_FreeSurface(loadedSurface);																	// Get rid of old loaded surface
	}

	return newTexture;
}
/*
	load Texture image from file given the path
*/
bool Texture::loadFromFile(std::string path) {
	free();	// Get rid of preexisting texture

	SDL_Texture* newTexture = NULL;							// The final texture

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());	// Load image at specified path
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));	// Color key image TURNED OFF FOR BLUE VIRUS

		newTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), loadedSurface);		// Create texture from surface pixels
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {			
			m_Width = loadedSurface->w;	// Get image dimensions
			m_Height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);	// Get rid of old loaded surface
	}

	m_Texture = newTexture;				// Return success
	return m_Texture != NULL;
}

/*
	Render text to a Texture
*/
bool Texture::renderTextToTexture(std::string textureText, SDL_Color textColor, TTF_Font* font, std::string id, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped)
 		m_TextSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);					// Render text surface
	else
		m_TextSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);	// Render text surface with text wrapping

	if (m_TextSurface != NULL) {		
		m_Texture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), m_TextSurface);		// Create texture from surface pixels

		if (m_Texture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {			
			m_Width = m_TextSurface->w;	// Get image dimensions
			m_Height = m_TextSurface->h;
		}

		SDL_FreeSurface(m_TextSurface);	// Get rid of old surface
	}
	else {
		printf("loadFromRenderedText(): Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());	// Error message
	}

	if (id != "") {
		if (m_Texture != 0) {
			m_TextureMap[id] = m_Texture;	// Add to texture map

			return true;
		}
	}

	return m_Texture != NULL;			// Return success
}

/*
	Free the texture from memory
*/
void Texture::free() {
	// Free texture if it exists
	if (m_Texture != NULL) {
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

/*
	Set texture colour
*/
void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(m_Texture, red, green, blue);	// Modulate texture rgb
}

/*
	Set texture blend mode
*/
void Texture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(m_Texture, blending);		// Set blending function
}

/*
	Flash the texture of an object
	Older function before creating texture map
*/
int counter = 0;					// counter for changing alpha for flashing
int alphaUp = 5, alphaDown = 5;		// turn the alpha value up or down
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

/*
	Modify the alpha of a texture
*/
void Texture::modifyAlpha(Uint8 alpha, std::string id) {
	if (id == "")
		SDL_SetTextureAlphaMod(m_Texture, alpha);			// Modulate texture alpha
	else 
		SDL_SetTextureAlphaMod(m_TextureMap[id], alpha);
}

/*
	2017/02/19:
	Function to indicate if a speed boost is active or not
*/
void Texture::speedBoostText(std::string textureText) {
	free();

	//if (!loadFromRenderedText(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 13), true)) {		// Green Text
	if (!renderTextToTexture(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 13), "", true)) {		// Green Text
		printf("speedBoostText(): Unable to render Speed Boost User Interface Text Texture!\n");
	}
}

/*
	2017/02/19:
	Function to indicate how many rockets a player has left
*/
void Texture::numRocketsLeft(std::string textureText) {
	free();

	//if (!loadFromRenderedText(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 36))) {		// Green Text
	if (!renderTextToTexture(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 36))) {		// Green Text
		printf("numRocketsLeft(): Unable to render Num Rockets Left User Interface Text Texture!\n");
	}
}

/* 
	2017-02-15:
	Function to render the players scores, the FPS, and the current game level
*/
void Texture::UIText(std::string textureText, int fontSize) {
	free();

	//if (!loadFromRenderedText(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", fontSize))) {		// Green Text
	if (!renderTextToTexture(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", fontSize))) {		// Green Text
		printf("Unable to render UIText() User Interface Text Texture!\n");
	}
}

/*
	2017-02-15:
	Like the UIText function, only it alters font colour depending on if the timer is running out or not
*/
void Texture::UITextTimer(std::string timerText, unsigned int Timer) {
	free();

	// Time running out change colour to red
	if (Timer >= 0 && Timer <= 5) {
		setFlash(true);

		//if (!loadFromRenderedText(timerText, { 255, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {		// Red Text
		if (!renderTextToTexture(timerText, { 255, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {		// Red Text
			printf("Unable to render UITextTimer() User Interface Timer Text Texture!\n");
		}
	}
	else {
		setFlash(false);

		//if (!loadFromRenderedText(timerText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {		// Green Text
		if (!renderTextToTexture(timerText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {		// Green Text
			printf("Unable to render loadFromRenderedText() User Interface Timer Text Texture!\n");
		}
	}
}

/*
	2017/03/03	THIS FUNCTION IS OK
	2017/02/15:
	Independent messages for player 1 and 2, for picking up objects and upgrading weapons etc
*/

//std::string previous1, previous2, previous3;
void Texture::UITextPlayerMessage(std::string playerMessage, int type) {	
	free();

	if (type == 0) {
		//if (previous1 != playerMessage) {
		//if (!loadFromRenderedText(playerMessage, { 65, 210, 240, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {	// Blue Text For General Message
		if (!renderTextToTexture(playerMessage, { 65, 210, 240, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {	// Blue Text For General Message
				printf("Unable to render General Info Message text texture!\n");
			}
		//}
		//previous1 = playerMessage;
	}
	else if (type == 1) {
		//if (previous2 != playerMessage) {
		//if (!loadFromRenderedText(playerMessage, { 240, 210, 65, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {	// Gold Text For Player 1
		if (!renderTextToTexture(playerMessage, { 240, 210, 65, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {	// Gold Text For Player 1
				printf("Unable to render player 1 Message text texture!\n");
			}
		//}
		//previous2 = playerMessage;
	}
	else if (type == 2) {
		//if (previous3 != playerMessage) {
			//if (!loadFromRenderedText(playerMessage, { 0, 255, 150, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {	// Green Text For Player 2
			if (!renderTextToTexture(playerMessage, { 0, 255, 150, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20))) {	// Green Text For Player 2
				printf("Unable to render player 2 Message text texture!\n");
			}
		//}
		//previous3 = playerMessage;
	}
	//else if (type == MAP_ALERT) {
	else if (type == 3) {
		//if (!loadFromRenderedText(playerMessage, { 0, 20, 200, 240 }, TTF_OpenFont("Fonts/Retro.ttf", 22))) {		// Blue For Map Warning
		if (!renderTextToTexture(playerMessage, { 0, 20, 200, 240 }, TTF_OpenFont("Fonts/Retro.ttf", 22))) {		// Blue For Map Warning
			printf("Unable to render player 2 Message text texture!\n");
		}
	}
}

/*
	Custom render function for weapon indicator in HUD
*/
void Texture::weaponIndicator(std::string textureID, int x) {
	renderMap(textureID, x + 5, 5, 50, 48);
}
/*
	Custom render function for input text
*/
void Texture::loadInputText(std::string input) {
	Texture* inputTextTexture = 0;
	//inputTextTexture->loadFromRenderedTextID(input, "inputTextID", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);		// Lives in top left corner
	inputTextTexture->renderTextToTexture(input, { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), "inputTextID", true);		// Lives in top left corner
}
/*
	Custom render function for rendering text for name
*/
void Texture::loadEnterNameText(std::string nameText) {
	free();
	Texture* enterName = 0;	// The actual hardware texture

	//enterName->loadFromRenderedTextID(nameText, "enterNameID", { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), true);		// Lives in top left corner
	enterName->renderTextToTexture(nameText, { 255, 255, 255, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), "enterNameID", true);		// Lives in top left corner
}

const int NUM_TEXTURES2 = 48;
// 2D Array of textures, with path to file, texture ID, and description for error messages
std::string textures2[NUM_TEXTURES2][3] = {
	// Players
	{ "Art/Player1Ship.png", "player1ID", "Player 1" },								// 2017/03/22 Added Player 1 Texture to map
	{ "Art/Player2Ship.png", "player2ID", "Player 2" },								// 2017/03/22 Added Player 2 Texture to map

	// Game
	{ "Art/Prof.png", "profID", "Professor" },										// Map texture to show the players current position inside the professor
	{ "Art/Player1ShipBlue30.png", "mapShipID", "Blue Mini Map Ship" },				// Map texture to show the players current position inside the professor
	
	// Explosions
	{ "Art/Explosion.png", "explosionID", "Explosion" },							// 2017/03/22 Added Explosion animation
	{ "Art/ExplosionBlood.png", "eplosionBloodID", "Blood Explosion" },				// 2017/03/22 Added Blood Explosion animation
	{ "Art/ExplosionVirusGreen.png", "explosionGreenID", "Green Explosion" },		// 2017/03/22 Added Green Explosion animation
	{ "Art/ExplosionVirusOrange.png", "explosionOrangeID", "Orange Explosion" },	// 2017/03/22 Added Orange Explosion animation
	{ "Art/ExplosionVirusBlue.png", "explosionBlueID", "Blue Explosion" },			// 2017/03/22 Added Blue Explosion animation

	// Blood Cells
	{ "Art/BloodCell.png", "bcID", "Large Blood Cell" },							// 2017/03/17 Added texture for Large Blood Cell to map
	{ "Art/BloodCellSmall.png", "bcsID", "Small Blood Cell" },						// 2017/03/17 Texture for Small Blood Cell to map
	{ "Art/WhiteCell.png", "bcwID", "White Blood Cell" },							// 2017/03/17 Texture for White Blood Cell to map

	// Background images
	{ "Art/bgBegin720a.png", "startBG", "Starting Background" },
	{ "Art/Background720.png", "middleBG", "Middle Background" },
	{ "Art/bgEnd720a.png", "endBG", "End Background" },

	// Init the objects to give information on
	{ "Art/EnemyShip.png", "enemyShipID", "Enemy Ship Info" },
	{ "Art/VirusGreen.png", "greenVirusInfoID", "Green Virus Info" },				// 2017/03/26 Renamed ID, same one used for sprite sheet
	{ "Art/VirusOrange.png", "orangeVirusInfoID", "Orange Virus Info" },			// 2017/03/26 Renamed ID, same one used for sprite sheet
	{ "Art/VirusBlue.png", "blueVirusInfoID", "Blue Virus Info" },					// 2017/03/26 Renamed ID, same one used for sprite sheet

	// Weapons
	{ "Art/SawBlue.png", "sawID", "Saw" },											// 2017/03/18 Added Saw texture to map
	{ "Art/NinjaStarYellow.png", "nsP1ID", "Ninja Star Player 1" },					// 2017/03/18 Added Ninja Star for Player 1 to map
	{ "Art/NinjaStarBlue.png", "nsP2ID", "Ninja Star Player 2" },					// 2017/03/18 Added Ninja Star for Player 2 to map
	{ "Art/VirusFireball.png", "fireballID", "Fire Ball Weapon" },
	{ "Art/EnemyVirusSatellite.png", "satelliteID", "Virus Satellite Projectile" },
	{ "Art/eyeLaserSpriteSheet.png", "eyeLaserID", "Enemy Boss Eye Laser" },		// 2017/03/22 Added Enemy Boss Eye Laser to map
	{ "Art/LaserGreen.png", "greenLaserID", "Green Laser" },
	{ "Art/LaserOrange.png", "orangeLaserID", "Orange Laser" },
	{ "Art/LaserBlue.png", "blueLaserID", "Blue Laser" },
	{ "Art/Shield1.png", "shieldP1ID", "Player 1 Shield" },
	{ "Art/Shield2.png", "shieldP2ID", "Player 2 Shield" },
	{ "Art/Rocket.png", "rocketID", "Rocket Weapon" },								// 2017/03/18 Added Rocket texture to map

	// Power Ups
	{ "Art/PowerUpLife.png", "lifePowerUpID", "New Life Power Up" },
	{ "Art/PowerUpClock.png", "checkpointPowerUpID", "Checkpoint // Timer Power Up" },
	{ "Art/PowerUpRocket.png", "rocketPowerUpID", "Rocket Power Up" },
	{ "Art/PowerUpHealthBox.png", "healthPowerUpID", "Health Power Up" },
	{ "Art/PowerUpLaser.png", "laserPowerUpID", "Laser Power Up" },

	// Laser Grades
	{ "Art/LaserGunV2.png", "laserPowerUpV2ID", "Double Laser HUD" },
	{ "Art/LaserGunV3.png", "laserPowerUpV3ID", "Triple Laser HUD" },

	// Obstacles
	{ "Art/Blockage.png", "blockageID", "Blockage" },

	// Animated Objects
	{ "Art/EnemySpriteSheet.png", "nanoBotID", "Enemy Ship Sprite Sheet" },
	{ "Art/eyeLaserSpriteSheet.png", "eyeLaserID", "Enemy Eye Laser Sprite Sheet" },
	{ "Art/lorcanSpriteSheet.png", "bossID", "Enemy Boss Sprite Sheet" },
	{ "Art/EnemyVirus_SpriteSheet_Green.png", "greenVirusID", "Green Virus Sprite Sheet" },
	{ "Art/EnemyVirus_SpriteSheet_Orange.png", "orangeVirusID", "Orange Virus Sprite Sheet" },
	{ "Art/EnemyVirus_SpriteSheet_Blue.png", "blueVirusID", "Blue Virus Sprite Sheet" },
	{ "Art/EnemyVirus_SpriteSheet_Green_Small.png", "greenVirusSmallID", "Small Green Virus Sprite Sheet" },
	{ "Art/EnemyVirus_SpriteSheet_Orange_Small.png", "orangeVirusSmallID", "Small Orange Virus Sprite Sheet" },
	{ "Art/EnemyVirus_SpriteSheet_Blue_Small.png", "blueVirusSmallID", "Small Blue Virus Sprite Sheet" }
};
/*
	Load the Texture media
*/
bool Texture::loadTextureMedia() {
	bool success = true;

	// Load the textures stored in the textures array
	for (int i = 0; i < NUM_TEXTURES2; i++) {
		if (!load(textures2[i][0], textures2[i][1])) {					// Game Title Logo
			std::cout << "Failed to load " << textures2[i][2] << " texture!" << std::endl;
			success = false;
		}
	}

	return success;
}





/*
//Clear the Texture media

void Texture::clearMedia() {	
	for (int i = 0; i < NUM_TEXTURES2; i++) {
		clearFromTextureMap(textures2[i][1]);	// 2017/03/26 Clear the ID field of texture information array
	}	
	//clearTextureMap();							// 2017/03/26 Clear the entire texture map
}


// 2017/03/26 Removed, unused

void Texture::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
//void Texture::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* rend, SDL_RendererFlip flip) {
SDL_Rect renderQuad = { x, y, mWidth, mHeight };	// Set rendering space and render to screen
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

// Get the colour for the texture

SDL_Color Texture::getFontColour() {
return txtColour;
}
void Texture::setFontColour(SDL_Color f) {
txtColour = f;
}

//SDL_Texture* textXXX = 0;
//bool Texture::loadFromRenderedTextID(SDL_Texture* text, std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer, bool textWrapped) {

//SDL_Texture* Texture::loadTexture(std::string path, SDL_Renderer *rend) {

//bool Texture::loadFromFile(std::string path, SDL_Renderer *rend) {

//void Texture::flashGameObject(int &alpha, bool &flash, int rate, int times) {

// render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
//void Texture::render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {

//bool Texture::load(std::string fileName, std::string id, SDL_Renderer* rend) {

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, bool textWrapped) {


//	Render text to a texture in the map
bool Texture::loadFromRenderedTextID(std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, bool textWrapped) {
free();	//Get rid of preexisting texture

if (!textWrapped)
textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);					// Render text surface
else
textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);	// Render text surface with text wrapping

if (textSurface != NULL) {
mTexture = SDL_CreateTextureFromSurface(Game::Instance()->getRenderer(), textSurface);		// Create texture from surface pixels
if (mTexture == NULL) {
printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());	// Error message
}
else {
mWidth = textSurface->w;	// Get image dimensions
mHeight = textSurface->h;
}

SDL_FreeSurface(textSurface);	// Clear old surface
}
else {
printf("loadFromRenderedText(): Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());	// Error message
}

if (mTexture != 0) {
m_textureMap[id] = mTexture;	// Add to texture map

return true;
}

//std::cout << "NOT WORKING" << std::endl;
return false;
}
*/

