#include <SDL.h>
#include <SDL_ttf.h>
#include "LTexture.h"

LTexture::LTexture() {
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mAlpha = 255;
}

LTexture::~LTexture() {
	free();						// Deallocate
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer *rend) {
	free();	// Get rid of preexisting texture

	SDL_Texture* newTexture = NULL;							// The final texture

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());	// Load image at specified path
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));	// Color key image

		newTexture = SDL_CreateTextureFromSurface(rend, loadedSurface);							// Create texture from surface pixels
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
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer, bool textWrapped) {
	free();	//Get rid of preexisting texture

	if (!textWrapped)
		textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);	//Render text surface
	else
		textSurface = TTF_RenderText_Blended_Wrapped(font, textureText.c_str(), textColor, 600);


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
void LTexture::free() {
	// Free texture if it exists
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(mTexture, red, green, blue);	// Modulate texture rgb
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(mTexture, blending);		// Set blending function
}
int LTexture::getAlpha() {
	return mAlpha;
}
void LTexture::setAlpha(int a) {
	mAlpha = a;
}
void LTexture::modifyAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(mTexture, alpha);			// Modulate texture alpha
}

void LTexture::render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };	// Set rendering space and render to screen

	if (clip != NULL) {									// Set clip rendering dimensions
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(rend, mTexture, clip, &renderQuad, angle, center, flip);	// Render to screen
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}

// 23/01/2017 Added these
int LTexture::getX() {
	return m_X;
}
int LTexture::getY() {
	return m_Y;
}
void LTexture::setX(int x) {
	m_X = x;
}
void LTexture::setY(int y) {
	m_Y = y;
}