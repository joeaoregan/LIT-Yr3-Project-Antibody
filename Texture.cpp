#include <SDL.h>
//#include <SDL_ttf.h>
#include "Texture.h"

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

SDL_Color Texture::getFontColour() {
	return txtColour;
}
void Texture::setFontColour(SDL_Color f) {
	txtColour = f;
}

SDL_Texture* Texture::loadTexture(std::string path, SDL_Renderer *rend) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(rend, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);	//Get rid of old loaded surface
	}

	return newTexture;
}

bool Texture::loadFromFile(std::string path, SDL_Renderer *rend) {
	free();	// Get rid of preexisting texture

	SDL_Texture* newTexture = NULL;							// The final texture

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());	// Load image at specified path
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));	// Color key image TURNED OFF FOR BLUE VIRUS

		newTexture = SDL_CreateTextureFromSurface(rend, loadedSurface);								// Create texture from surface pixels
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

SDL_Surface* textSurface;

#ifdef _SDL_TTF_H
bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped)
		textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//Render text surface
	else
		textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 1000);

	if (textSurface != NULL) {
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
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
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
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

// render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
void Texture::render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };	// Set rendering space and render to screen

	if (clip != NULL) {									// Set clip rendering dimensions
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(rend, mTexture, clip, &renderQuad, angle, center, flip);	// Render to screen
}

/* 
	2017-02-15:
	Function to render the players scores, the FPS, and the current game level
*/
void Texture::UIText(std::string textureText, SDL_Renderer* rend) {
	if (!loadFromRenderedText(textureText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend)) {		// Green Text
		printf("Unable to render User Interface Text Texture!\n");
	}
}
/*
	2017-02-15:
	Like the UIText function, only it alters font colour depending on if the timer is running out or not
*/
void Texture::UITextTimer(std::string timerText, SDL_Renderer* rend, unsigned int Timer) {
	// Time running out change colour to red
	if (Timer >= 0 && Timer <= 5) {
		setFlash(true);

		if (!loadFromRenderedText(timerText, { 255, 0, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend)) {		// Red Text
			printf("Unable to render User Interface Timer Text Texture!\n");
		}
	}
	else {
		setFlash(false);

		if (!loadFromRenderedText(timerText, { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend)) {		// Green Text
			printf("Unable to render User Interface Timer Text Texture!\n");
		}
	}
}

/*
	2017/02/15:
	Independent messages for player 1 and 2, for picking up objects and upgrading weapons etc
*/
void Texture::UITextPlayerMessage(std::string playerMessage, SDL_Renderer* rend, int player) {
	if (player == 1) {
		if (!loadFromRenderedText(playerMessage, { 240, 210, 65, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend)) {	// Gold Text
			printf("Unable to render player 1 Message text texture!\n");
		}
	}
	else if (player == 2){
		if (!loadFromRenderedText(playerMessage, { 65, 210, 240, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20), rend)) {	// Blue Text
			printf("Unable to render player 2 Message text texture!\n");
		}
	}
}