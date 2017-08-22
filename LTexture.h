#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>

// Texture wrapper class

//Screen dimension constants
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_HEIGHT_GAME 600

class LTexture {
public:		
	LTexture(int degrees = 0);									// Initializes variables
		
	~LTexture();												// Deallocates memory

	bool loadFromFile(std::string path, SDL_Renderer *rend);	// Loads image at specified path	2017-01-19 Added Renderer

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* rend, bool textWrapped = false);
#endif
	
	void free();												// Deallocates texture
		
	void setColor(Uint8 red, Uint8 green, Uint8 blue);			// Set color modulation
		
	void setBlendMode(SDL_BlendMode blending);					// Set blending
		
	void modifyAlpha(Uint8 alpha);								// Set alpha modulation

	//void flashGameObject(int &alpha, bool &flash, int rate = 10, int times = 0);
	void flashGameObject(int rate = 10, int times = 0);

	int getAlpha();
		
	void setAlpha(int a);

	//void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	// Renders texture at given point
	void render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// 23/01/2017 Added these
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

	// 23/01/2017 Added these
	int m_X;
	int m_Y;
	int m_Alpha;

	// Gets image dimensions
	int getWidth();
	int getHeight();

	// Rotation Angle
	int getDegrees();
	void setDegrees(int d);

	bool getFlash();
	void setFlash(bool flash);

private:	
	SDL_Texture* mTexture;	// The actual hardware texture

	//Image dimensions
	int mWidth;
	int mHeight;
	int mAlpha;
	int mDegrees;
	bool mFlash;
};

#endif