/*	---------------------------------------------------------------------------------------------------------------------
	- Name:					Texture.h
	- Description:			Header file for the Texture class.
	- Information:			Contains all function definitions and variables for the Texture class.
	- Log:
		2017/01/30		Added rotation angle to constructors for Textures that rotate
						Moved flashGameObject() functionality into Texture class
		2017/01/24		Changed screen size from 1280 x 720 from 800 x 600
	----------------------------------------------------------------------------------------------------------------------*/
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include"Game.h"
#include <SDL_image.h>
#include <string>
#include <map>
#include <SDL_ttf.h>

// Texture wrapper class

//Screen dimension constants
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_HEIGHT_GAME 600

class Texture {
public:		
	static Texture* Instance() {						// Single instance of Textures used throughout Game
		if (s_pInstance == 0) {
			s_pInstance = new Texture();
			return s_pInstance;
		}

		return s_pInstance;								// Make sure the texture manager only exists once
	}

	// Need to be private for singleton
	Texture();											// Initializes variables 2017/03/22 No longer need degrees when setting texture
	~Texture();											// Deallocates memory

	bool loadTextureMedia();							// 2017/02/26 Load media for Texture class

	bool load(std::string fileName, std::string id);	// Load an image to the texture map given its path, assigning an ID
	SDL_Texture* loadTexture(std::string path);			// Loads individual image as texture
	bool loadFromFile(std::string path);				// Loads image at specified path	2017-01-19 Added Renderer	// Creates image from font string

	bool renderTextToTexture(std::string textureText, SDL_Color textColor, TTF_Font* font, std::string id = "", bool textWrapped = false);	// Create a texture from text

	// Texture rendering functions
	void renderMap(std::string id = "");				// Render a texture from the map, given an ID
	void renderP(int x, int y);							// render to a point
	void renderMap(std::string id, int x, int y, int width, int height);	// Render texture from map with ID, coordinates, and dimensions
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	// Texture Render function
	void render(std::string id, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	// Map render function
	
	void free();										// Deallocates texture
		
	void setColor(Uint8 red, Uint8 green, Uint8 blue);	// Set color modulation		
	void setBlendMode(SDL_BlendMode blending);			// Set blending
		
	// Flash and Transparency
	void modifyAlpha(Uint8 alpha, std::string id = "");	// Set alpha modulation
	void flashGameObject(int rate = 10, int times = 0);	// Flash texture for game object
	bool getFlash() { return m_Flash; }					// Flash the object or not
	void setFlash(bool flash) { m_Flash = flash; }		// Set the object to flash or not
	int getAlpha() { return m_Alpha; }					// Get alpha value for flashing / transparent textures
	void setAlpha(int a) { m_Alpha = a; }				// Set alpha value for flashing / transparent textures

	// 23/01/2017 Coordinate setter and getter methods
	int getX() { return m_X; }
	int getY() { return m_Y; }
	void setX(int x) { m_X = x; }
	void setY(int y) { m_Y = y; }
	
	// Gets image dimensions
	int getWidth() { return m_Width; }
	int getHeight() { return m_Height; }		

	// Texture map
	std::map<std::string, SDL_Texture*> getTextureMap() { return m_TextureMap; }	// Get the entire map
	void clearTextureMap() { m_TextureMap.clear(); }								// Clear the entire map
	void clearFromTextureMap(std::string id) { m_TextureMap.erase(id); }			// Clear the texture from the map using ID
	SDL_Texture* getTexture(std::string id) { return m_TextureMap[id]; }			// Get a texture from the map using ID
	
	// Custom render functions
	void weaponIndicator(std::string textureID, int x);								// 2017/02/26 Function to render weapon indicators
	void loadInputText(std::string input);											// Custom render function for input text
	void loadEnterNameText(std::string nameText);									// Custom render function for rendering text for name
	void UIText(std::string textureText, int fontSize = 20);						// Render Text for player scores, FPS, and Level
	void UITextTimer(std::string timerText, unsigned int Timer);					// Render Text for Game Timer
	void UITextPlayerMessage(std::string playerMessage, int type = 0);				// Render Player Message
	void numRocketsLeft(std::string textureText);									// 2017/02/19 Indicate the number of rockets each player has left
	void speedBoostText(std::string textureText);									// 2017/02/20 Indicates a speedboost is active

private:

	std::map<std::string, SDL_Texture*> m_TextureMap;	// Map to store textures

	static Texture* s_pInstance;						// Single Instance of Texture class used in Game
		
	SDL_Texture* m_Texture;								// The actual hardware texture

	SDL_Surface* m_TextSurface;							// Surface used to create textures

	int m_Width, m_Height;								// Texture dimensions
	int m_X, m_Y;										// 23/01/2017 Added coordinates for textures

	int m_Alpha;										// Texture alpha value
	bool m_Flash;										// Flash texture for endOfGame, spawnPlayer, collisionCheck		
};

#endif

/*
	int m_TimeToDisplay;								// 31/01/2017 display score value of killed enemy, at enemy coords

	// Render text to texture functions
	//bool loadFromRenderedTextID(std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, bool textWrapped = false);	// Create a texture from text
	//bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, bool textWrapped = false);					// Create a texture from text

	//unsigned int lastTime = 0;

	//void clearMedia();									// 2017/03/01 Unused

	//void flashGameObject(int &alpha, bool &flash, int rate = 10, int times = 0);
	//int Xcoord, Ycoord;		// Texture coordinates 2017/03/26 removed, unused

//void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);	// 2017/03/26 Removed, unused

//void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	// Renders texture at given point
//Texture(int degrees = 0);							// Initializes variables	OLD CONSTRUCTOR, SETS DEGREES FOR ROTATION
	// Rotation Angle
	int getDegrees() { return mDegrees; }			// DEGREES MOVED TO GAME OBJECT
	void setDegrees(int d) { mDegrees = d % 360; }	// returns degrees from 0 to 360
	int mDegrees;									// Degrees of rotation

SDL_Color txtColour;

//bool loadFromRenderedTextIO(std::string id, std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer, bool textWrapped);

//void loadInputText(std::string input);
//void loadEnterNameText(std::string nameText);

bool loadFromRenderedTextID(SDL_Texture* text, std::string textureText, std::string id, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer, bool textWrapped);
bool loadTextureMedia(SDL_Renderer* rend); // 2017/02/26
bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
void weaponIndicator(std::string textureID, int x, SDL_Renderer* rend);	// 2017/02/26 Function to render weapon indicators
SDL_Texture* loadTexture(std::string path, SDL_Renderer *rend);	// Loads individual image as texture
bool loadFromFile(std::string path, SDL_Renderer *rend);		// Loads image at specified path	2017-01-19 Added Renderer
#ifdef _SDL_TTF_H
//Creates image from font string
bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* rend, bool textWrapped = false);
#endif
void renderMap(SDL_Renderer* rend);
void renderMap(std::string id, int x, int y, int width, int height, SDL_Renderer* rend);
//void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);	// Renders texture at given point
void render(int x, int y, SDL_Renderer *rend, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
SDL_Color getFontColour();
void setFontColour(SDL_Color f);
void createdByText();						// 2017/02/20		 2017/03/03 altered
void UIText(std::string textureText, SDL_Renderer* rend);								// Render Text for player scores, FPS, and current Level
void UITextTimer(std::string timerText, SDL_Renderer* rend, unsigned int Timer);		// Render Text for Game Timer
void UITextPlayerMessage(std::string playerMessage, SDL_Renderer* rend, int type = 0);
void numRocketsLeft(std::string textureText, SDL_Renderer* rend);						// 2017/02/19 Indicate the number of rockets each player has left
void speedBoostText(std::string textureText, SDL_Renderer* rend);						// 2017/02/20 Indicates a speedboost is active
void createdByText(SDL_Renderer* rend);													// 2017/02/20
*/