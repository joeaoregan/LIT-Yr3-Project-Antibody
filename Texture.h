#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

// Texture wrapper class

//Screen dimension constants
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_HEIGHT_GAME 600

class Texture {
public:		
	Texture(int degrees = 0);										// Initializes variables
		
	~Texture();														// Deallocates memory

	SDL_Texture* loadTexture(std::string path, SDL_Renderer *rend);	// Loads individual image as texture

	bool loadFromFile(std::string path, SDL_Renderer *rend);		// Loads image at specified path	2017-01-19 Added Renderer
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
	int getAlpha() { return mAlpha; }		
	void setAlpha(int a) { mAlpha = a; }

	//void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	// Renders texture at given point
	void render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// 23/01/2017 Added these
	int getX() { return m_X; }
	int getY() { return m_Y; }
	void setX(int x) { m_X = x; }
	void setY(int y) { m_Y = y; }
	
	// Gets image dimensions
	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

	// Rotation Angle
	int getDegrees() { return mDegrees; }
	void setDegrees(int d) { mDegrees = d % 360; }	// returns degrees from 0 to 360

	bool getFlash() { return mFlash; }
	void setFlash(bool flash) { mFlash = flash; }

	SDL_Color getFontColour();
	void setFontColour(SDL_Color f);

	void UIText(std::string textureText, SDL_Renderer* rend);			// Render Text for player scores, FPS, and current Level
	void UITextTimer(std::string timerText, SDL_Renderer* rend, unsigned int Timer);		// Render Text for Game Timer
	void UITextPlayerMessage(std::string playerMessage, SDL_Renderer* rend, int player);

private:	
	// 31/01/2017 display score value of killed enemy, at enemy coords
	int timeToDisplay;
	int Xcoord;
	int Ycoord;

	SDL_Texture* mTexture;	// The actual hardware texture

	//Image dimensions
	int mWidth;
	int mHeight;
	int mAlpha;
	int mDegrees;
	bool mFlash;

	// 23/01/2017 Added these
	int m_X;
	int m_Y;
	int m_Alpha;	// Textures alpha value

	SDL_Color txtColour;
};

#endif