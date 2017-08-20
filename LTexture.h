#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>

// Texture wrapper class

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class LTexture {
public:		
	LTexture();											// Initializes variables
		
	~LTexture();										// Deallocates memory
		
	bool loadFromFile(std::string path);				// Loads image at specified path

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif
	
	void free();										// Deallocates texture
		
	void setColor(Uint8 red, Uint8 green, Uint8 blue);	// Set color modulation
		
	void setBlendMode(SDL_BlendMode blending);			// Set blending
		
	void setAlpha(Uint8 alpha);							// Set alpha modulation
		

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	// Renders texture at given point

	
	// Gets image dimensions
	int getWidth();
	int getHeight();

private:	
	SDL_Texture* mTexture;								// The actual hardware texture

	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif