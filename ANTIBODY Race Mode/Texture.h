#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>

// Texture wrapper class

//Screen dimension constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_HEIGHT_GAME 480

class Texture {
public:
	Texture();													// Initializes variables

	~Texture();													// Deallocates memory

	bool loadFromFile(std::string path, SDL_Renderer *rend);	// Loads image at specified path	2017-01-19 Added Renderer

#ifdef _SDL_TTF_H												//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* rend, bool textWrapped = false);
#endif

	void free();												// Deallocates texture

	void setColor(Uint8 red, Uint8 green, Uint8 blue);			// Set color modulation

	void setBlendMode(SDL_BlendMode blending);					// Set blending

	void modifyAlpha(Uint8 alpha);								// Set alpha modulation

	int getAlpha();												// Get the Textures current alpha value

	void modifyAlpha(int a);									// Change the Textures alpha value

	//void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	// Renders texture at given point
	void render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


	// Gets image dimensions
	int getWidth();			// Get the texture width
	int getHeight();		// Get the texture height

private:
	SDL_Texture* mTexture;	// The actual hardware texture

	int mWidth;				// Texture width
	int mHeight;			// Texture height
	int mAlpha;				// Texture alpha / transparency value
};

#endif