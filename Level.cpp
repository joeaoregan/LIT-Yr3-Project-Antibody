
//2017/03/21 Divide the game into levels

#include <sstream>					// For timer
#include "SDL.h"

#include "_TestData.h"				// 2017/02/09 JOE: Keeps testing functionality in one place
#include "Level.h"					// 2017/03/22 JOE: Level class
#include "Game.h"					// Game header file, with functions and variabls
#include "Texture.h"
#include "HUD.h"					// 2017/02/21 JOE: Class for handling displaying objects on heads up display
#include "Particle.h"
#include "FPS.h"					// 2017/02/01 SEAN/JOE: Class for handling frames for second
#include "StatusBar.h"				// 2017/02/09 JOE: Class for creating status bars, such as health bar
#include "GameObject.h"
#include "ScrollingBackground.h"	// 2017/03/21 JOE: Class for scrolling background
#include "Player.h"
#include "Audio.h"					// 2017/02/09 JOE: Class for handling music and sound effects
#include "EnemyShip.h"				// SEAN/JOE: Enemy ship class
#include "EnemyVirus.h"				// 2017/01/10 SEAN/JOE: Added virus enemy
#include "WeaponPlLaser.h"			// SEAN: Player Laser weapon
#include "WeaponPlNinjaStar.h"		// 2017/01/09 JOE: Player Ninja Star weapon
#include "WeaponPlRocket.h"			// 2017/02/06 JOE: Class for creating rockets
#include "WeaponPlSaw.h"			// 2017/01/17 JOE: Added Saw Weapon
#include "BloodCell.h"				// 2017/01/10 JOE: Added Blood Cell obstacle
#include "PowerUp.h"				// 2017/01/10 SEAN/JOE: Added Power Up
#include "Menu.h"					// 2017/02/14 BRIAN/JOE: Class for handling menus. Includes button.h
#include "Explosion.h"				// 2017/01/25 JOE: Added explosions for Player Laser colliding with Enemy Ships and Virus
#include "SplashScreen.h"			// 2017/02/08 JOE: Class for displaying splash screens
#include "ScoreValueText.h"			// 2017-02-09 JOE: Class for displaying values of scores for destroying objects
#include "CollisionStuff.h"			// 2017/02/09 JOE: Class for handling collisions between objects
#include "Gamepad.h"				// 2017/02/09 JOE: Class for handling gamepad functionality
#include "EnemyBoss.h"				// 2017/02/03 JOE: Class for handling Enemy Boss objects
#include "GameStateMachine.h"		// 2017/02/03 JOE: Class for handling Game State Machine (Finite State Machine)
//#include "StateMainMenu.h"			// 2017/02/03 JOE: Class for handling the main menu state
#include "Blockage.h"
#include "randomMessageGenerator.h"	// 2017/02/04 JOE: Class for randomising messages
#include "SettingsMenu.h"
#include "HighScores.h"
#include "EnterName.h"
#include <math.h>

bool miniMap = true;

std::stringstream framesPerSec;			// In memory text stream - string streams - function like iostreams only instead of reading or writing to the console, they allow you to read and write to a string in memory

int numBlockages = 0;

int ninjaStarP1Counter, ninjaStarP2Counter, laserCounter, rocketCounter;
int ninjaStarP1Missed, ninjaStarP2Missed, ninjaStarP1Streak, ninjaStarP2Streak;
//int scoreTextP1counter, scoreTextP2counter;

/******************************************************************************************************************/

// 2017/03/22 Total amount of spawned objects
int totalExplosions = 0, totalBloodCells = 0, totalLargeBC = 0;
int bloodCellCounterP1, bloodCellcounterP2;

/******************************************************************************************************************/

// Weapons
bool killRocket1 = false;
bool killRocket2 = false;

HUD headsUpDisplay;
Particle particle;
FPS fps1;							// 2017/02/01 Moved FPS functionality to it's own class
StatusBar bar;

// Animation frames
SDL_Rect gEnemyBossSpriteClips[6];				// Sprite frames for Enemy Boss animation
SDL_Rect gEnemyBossEyes[16];					// Sprite frames for Enemy Boss Small Blue Virus generation animation
SDL_Rect gSmallGreenVirusSpriteClips[6];		// Sprite frames for Small Green Virus animation
SDL_Rect gSmallOrangeVirusSpriteClips[6];		// Sprite frames for Small Orange Virus animation
SDL_Rect gSmallBlueVirusSpriteClips[6];			// Sprite frames for Small Blue Virus animation

												//Texture gEnemySpriteSheetTexture;				// Enemy sprite sheet
Texture gEnemyBossSpriteSheetTexture;			// Enemy Boss sprite sheet
Texture gEnemyBossEyesSpriteSheetTexture;		// Enemy Boss Eyes sprite sheet
Texture gEnemyBossStatusBarTextTexture;			// Identify the Enemy Boss on the health bar

Texture gSmallGreenVirusSpriteSheetTexture;		// Small Green Virus sprite sheet
Texture gSmallOrangeVirusSpriteSheetTexture;	// Small Orange Virus sprite sheet
Texture gSmallBlueVirusSpriteSheetTexture;		// Small Blue Virus sprite sheet

// Objects and weapons
Texture gPlayer1Texture;			// Player 1 ship
Texture gPlayer2Texture;			// Player 2 ship

// UI
Texture gTimeTextTexture;			// Countdown time displayed in game screen
Texture gFPSTextTexture;			// Frames Per Second displayed at top of screen

// Messages
Texture gInfoMessageP1TextTexture;	// Player notification messages for picking up objects etc.
Texture gInfoMessageP2TextTexture;	// Player notification messages for picking up objects etc.
Texture gInfoMessageTextTexture;	// Player notification messages for picking up objects etc.
Texture gInfoMessageMapTextTexture;	// Player notification messages for picking up objects etc.

SDL_Color textColour;				// Set the text colour
TTF_Font *gFontRetro20;				// Globally used font 2017-01-25 Changed to Retro font which is more readable

// Game Messages
int pointsValueCounter;								// Time to display score for killing Enemy message
std::string pointsValue;							// Player notification messages, Yellow writing appearing in the middle of the game screen
int infoMessageP1Counter, infoMessageP2Counter;		// Time to display notification messages
int infoMessageCounter, infoMessageMapCounter;
std::string infoMessageP1, infoMessageP2; 			// Player notification messages, Yellow writing appearing in the middle of the game screen
std::string infoMessageGeneral, infoMessageMap;

// Functions
void setViewport(SDL_Rect &rect, int x, int y, int w, int h);	// These classes are giving errors when they are moved to the header file
void setupAnimationClip(SDL_Rect rect[], int width, int height, int frames, int rows = 0);

// Vectors for objects that have collisions
std::vector<GameObject*> listOfGameObjects;		// 2017/01/31 Using to display the scores for each object killed, 2017/02/15 added Power Ups, Explosions

ScrollingBackground* scrollBG = new ScrollingBackground();		// 2017/03/21 Scroll background added to Game Object list
Player* player1 = new Player(PLAYER1);
Player* player2 = new Player(PLAYER2);

bool Level::loadMedia() {
	listOfGameObjects.push_back(player1);					// 2017/03/22 Add Player 1 to Game Objects list
	if (Game::Instance()->twoPlayer) listOfGameObjects.push_back(player2);	// 2017/03/22 Add Player 2 to Game Objects list
	listOfGameObjects.push_back(scrollBG);					// 2017/03/22 Add Scrolling Background to Game Objects list;


	std::cout << player1->getName() << " Health: " << player1->getHealth() << " Lives: " << player1->getNumLives() << std::endl;		// Player 1 health & Lives at start of game

	if (Game::Instance()->twoPlayer) {
		std::cout << "Player 2 Health: " << player2->getHealth() << " Lives: " << player2->getNumLives() << std::endl;					// Player 1 health & Lives at start of game
		//if (testMode) player2->setNumLives(MAX_NUM_LIVES);
	}

	// View ports
	setViewport(gameViewport, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT_GAME);	// Main Game Screen

	// Global Level Media
	bool success = true;														// Loading success flag

	// Open the font
	gFontRetro20 = TTF_OpenFont("Fonts/Retro.ttf", 20);
	if (gFontRetro20 == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		textColour = { 255, 0, 0, 255 };																	// Set text color for three names RED
		TTF_SetFontStyle(gFontRetro20, TTF_STYLE_BOLD);														// Use bold font
	}





	success = headsUpDisplay.loadLevelStuff();									// 2017/02/21 Separated heads up display object initialisation to the class for loading textures for player lives etc
	success = particle.initParticle();

	Texture::Instance()->loadTextureMedia();
	//success = menu1.loadMenuMedia();											// Load buttons etc
	//success = Audio::Instance()->loadMediaAudio();							// 2017/03/17 Combined music loading with effects loading, as only one function is necessary
	success = headsUpDisplay.loadLevelStuff();									// 2017/02/21 Separated heads up display object initialisation to the class for loading textures for player lives etc
	success = particle.initParticle();
	//success = splash.initSplashScreens();										// Initialise the splash screens

																				// Open the font
	gFontRetro20 = TTF_OpenFont("Fonts/Retro.ttf", 20);
	if (gFontRetro20 == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		textColour = { 255, 0, 0, 255 };																	// Set text color for three names RED
		TTF_SetFontStyle(gFontRetro20, TTF_STYLE_BOLD);														// Use bold font
	}

	//gEnemyBossStatusBarTextTexture.loadFromRenderedText("The Gaddinator", { 100, 240, 240, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));
	gEnemyBossStatusBarTextTexture.loadFromRenderedText("Lorctron", { 180, 210, 240, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));

	// Load Textures
	if (!gPlayer1Texture.loadFromFile("Art/Player1Ship.png")) {												// Player 1 Ship Texture
		printf("Failed to load Player 1 texture!\n");
		success = false;
	}
	if (!gPlayer2Texture.loadFromFile("Art/Player2Ship.png")) {												// Player 2 Ship Texture
		printf("Failed to load Player 2 texture!\n");
		success = false;
	}
	if (!gEnemyBossEyesSpriteSheetTexture.loadFromFile("Art/eyeLaserSpriteSheet.png")) {					// Sprite sheet for Enemy Ship
		printf("Failed to load Enemy Boss animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gEnemyBossEyes, 25, 25, 16);
	}

	if (!gEnemyBossSpriteSheetTexture.loadFromFile("Art/lorcanSpriteSheet.png")) {							// Sprite sheet for Enemy Ship
		printf("Failed to load Enemy Boss animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gEnemyBossSpriteClips, 300, 460, 4);											// Set sprite clips
	}

	if (!gSmallGreenVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Green_Small.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Small Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gSmallGreenVirusSpriteClips, 40, 40, 4);										// Set sprite clips
	}
	if (!gSmallOrangeVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Orange_Small.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Small Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gSmallOrangeVirusSpriteClips, 40, 40, 4);									// Set sprite clips
	}
	if (!gSmallBlueVirusSpriteSheetTexture.loadFromFile("Art/EnemyVirus_SpriteSheet_Blue_Small.png")) {	// Sprite sheet for Enemy Blue Virus
		printf("Failed to load Small Blue Virus animation texture!\n");
		success = false;
	}
	else {
		setupAnimationClip(gSmallBlueVirusSpriteClips, 40, 40, 4);									// Set sprite clips
	}

	/*
	// Specific Level Media
	if (Game::Instance()->getCurrentLevel() == LEVEL_1) {
	}
	else if (Game::Instance()->getCurrentLevel() == LEVEL_2) {
	}
	else if (Game::Instance()->getCurrentLevel() == LEVEL_3) {
	}
	*/

	return success;
}

void setupAnimationClip(SDL_Rect rect[], int width, int height, int frames, int rows) {
	for (unsigned int i = 0; i < frames; ++i) {
		rect[i].x = i * width;
		rect[i].y = i * rows;
		rect[i].w = width;
		rect[i].h = height;
	}
}

void Level::clearMedia() {
	gPlayer1Texture.free();
	gPlayer2Texture.free();

	// free animations
	gSmallGreenVirusSpriteSheetTexture.free();
	gSmallOrangeVirusSpriteSheetTexture.free();
	gSmallBlueVirusSpriteSheetTexture.free();

	// String stream textures
	gTimeTextTexture.free();
	gFPSTextTexture.free();

	gInfoMessageP1TextTexture.free();
	gInfoMessageP2TextTexture.free();
	gInfoMessageMapTextTexture.free();
	gInfoMessageTextTexture.free();

	fps1.fpsclose();
	headsUpDisplay.closeLevelStuff();
	particle.closeParticle();

	// Empty Lists
	listOfGameObjects.clear();		// Scores, Power Ups, Explosions

	if (Game::Instance()->getCurrentLevel() == LEVEL_1) {
	}
	else if (Game::Instance()->getCurrentLevel() == LEVEL_2) {
	}
	else if (Game::Instance()->getCurrentLevel() == LEVEL_3) {
	}
}

void Level::update() {
	fps1.fpsthink();			// Update the FPS

	destroyGameObjects();										// 2017-01-09 JOE: Destroy the game objects when finished on the screen
}

void Level::playLevel(int levelNum) {
	//if (!nameEntered)
	//nameEntered = enterName();
	//else
	if (Game::Instance()->displayLevelIntro)
		displayLevelIntroScreens(levelNum);	// Set true or false in _test.cpp

	if (!gameOver) {
		// 2017/03/04 Display a message at the start of each level
		if (countdownTimer == GAME_TIMER) infoMessage(randomLevelMessageGenerator(Game::Instance()->getCurrentLevel()), 3);

		spawnMovingObjects();				// 2017/01/10 JOE: Spawn enemies and obstacles at random coords & distances apart
		moveGameObjects();					// 2017-01-09 JOE: Move the game objects on the screen
		collisionCheck();					// Check collisions between 2 objects
	}

	render();
	//renderGameOver();
}
void Level::render() {
	if (!gameOver) renderGamePlay();					// 2017-01-09 JOE: Render the game objects to the screen
	//else if (gameOver) renderGameOver();
}


int eyeFrame = 0;
void Level::renderGamePlay() {
	// Levels
	displayText();														// 2017/01/17: Display the game text, info messages etc

	if (player1->getAlive()) gPlayer1Texture.flashGameObject(10, 4);	// 2017/01/30 Moved flashGameObject() function into LTexture
	if (player2->getAlive()) gPlayer2Texture.flashGameObject(10, 4);

	// Clear screen
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0x3C, 0x3C, 0x3C, 0xFF);		// Grey colour --> shows up in UI
	SDL_RenderClear(Game::Instance()->getRenderer());

	SDL_RenderSetViewport(Game::Instance()->getRenderer(), &gameViewport);				// Set the viewport to Game Screen

	if (levelOver == false && gameOver == false) {
		//scrollBG->render();												// 2017/03/21 Render the Scrolling Background // 2017/03/22 Added to GameObject List

		SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

		//if (player1->getAlive()) SDL_RenderDrawRect(getRenderer(), &player1->getCollider());					// Player 1 collider rectangle graphic
		//if (twoPlayer && player2->getAlive()) SDL_RenderDrawRect(getRenderer(), &player2->getCollider());		// Player 2 collider rectangle graphic

		for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
			SDL_RenderDrawRect(Game::Instance()->getRenderer(), listOfGameObjects[index]->getCollider());	// Draw object colliders
			frames = listOfGameObjects[index]->getNumFrames();			// 2017/02/09 Fixed the explosion animations, they are now assigned to indiviual objects with the game object frame attribute

			if (listOfGameObjects[index]->getSubType() == ENEMY_BOSS) { //
				listOfGameObjects[index]->render(gEnemyBossSpriteSheetTexture, &gEnemyBossSpriteClips[frames / 10], frames, 4);			// 4 the number of frames
																																		//listOfGameObjects[index]->render();	// Render the Enemy Boss Head animation

																																		// Render Laser Eye Spawning Animation and spawn Eye Lasers
				if (listOfGameObjects[index]->getX() < SCREEN_WIDTH - 400) {

					gEnemyBossEyesSpriteSheetTexture.render(listOfGameObjects[index]->getX() + 57, listOfGameObjects[index]->getY() + 210, &gEnemyBossEyes[frames / 5]);
					gEnemyBossEyesSpriteSheetTexture.render(listOfGameObjects[index]->getX() + 167, listOfGameObjects[index]->getY() + 214, &gEnemyBossEyes[frames / 5]);
					if ((frames) % 128 == 0) {		// If the eye animation reaches the last frame spawn laser from eye coordinates
						spawnEnemyLaser(listOfGameObjects[index]->getX() + 57, listOfGameObjects[index]->getY() + 210, BLUE_VIRUS_BULLET);
						spawnEnemyLaser(listOfGameObjects[index]->getX() + 167, listOfGameObjects[index]->getY() + 214, BLUE_VIRUS_BULLET);
					}
				}

				// Render the Boss Enemy Health Bar
				bar.enemyBossBar(listOfGameObjects[index]->getHealth());	// Health bar for enemy boss
				gEnemyBossStatusBarTextTexture.render((SCREEN_WIDTH - gEnemyBossStatusBarTextTexture.getWidth()) / 2, 6);	// Enemy identifer text for Health bar
			}
			// Render Small Viruses
			else if (listOfGameObjects[index]->getSubType() == VIRUS_SMALL_GREEN) listOfGameObjects[index]->render(gSmallGreenVirusSpriteSheetTexture, &gSmallGreenVirusSpriteClips[frames / 10], frames, 4);			// 6 the number of frames
			else if (listOfGameObjects[index]->getSubType() == VIRUS_SMALL_ORANGE) listOfGameObjects[index]->render(gSmallOrangeVirusSpriteSheetTexture, &gSmallOrangeVirusSpriteClips[frames / 10], frames, 4);		// 6 the number of frames
			else if (listOfGameObjects[index]->getSubType() == VIRUS_SMALL_BLUE) listOfGameObjects[index]->render(gSmallBlueVirusSpriteSheetTexture, &gSmallBlueVirusSpriteClips[frames / 10], frames, 4);			// 6 the number of frames

			else listOfGameObjects[index]->render();
			//else Texture::Instance()->renderMap(listOfGameObjects[index]->getTextureID(), listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getHeight());

			listOfGameObjects[index]->setFrames(frames);	// increment the frames

			listOfGameObjects[index]->m_Texture.modifyAlpha(listOfGameObjects[index]->m_Texture.getAlpha());
		}

		// Render Text
		SDL_RenderSetViewport(Game::Instance()->getRenderer(), &gameViewport);

		checkMessageTimes();								// 2017/03/19 Function to check how loong a message has been on screen, and increment message timers

		gTimeTextTexture.flashGameObject(8);
		gTimeTextTexture.modifyAlpha(gTimeTextTexture.getAlpha());						// Flash the timer
		gTimeTextTexture.render(SCREEN_WIDTH - gTimeTextTexture.getWidth() - 10, 8);	// LAZY

		gFPSTextTexture.render((SCREEN_WIDTH - 150) / 2, 8);

		if (player1->getAlive()) {
			bar.playerHealthBar(player1->getX(), player1->getY(), player1->getWidth(), player1->getHealth());

			if (player1->getRocketBarActive()) {
				player1->rocketScore();				// Set the score for the rocket

				bar.rocketPowerBar(player1->getX(), player1->getY(), player1->getWidth(), player1->getTimer());

				if (player1->getTimer() <= 0) {
					spawnExplosion(player1->getX(), player1->getY(), FIRE_EXPLOSION);
					player1->resetRocket();			// reset the rocket, returns boolean value
				}
			}

			gPlayer1Texture.modifyAlpha(gPlayer1Texture.getAlpha());
			player1->render(gPlayer1Texture);
		}
		if (Game::Instance()->twoPlayer && player2->getAlive()) {
			bar.playerHealthBar(player2->getX(), player2->getY(), player2->getWidth(), player2->getHealth());

			if (player2->getRocketBarActive()) {
				player2->rocketScore();	// return true

				bar.rocketPowerBar(player2->getX(), player2->getY(), player2->getWidth(), player2->getTimer());

				if (player2->getTimer() <= 0) {
					spawnExplosion(player2->getX(), player2->getY(), FIRE_EXPLOSION);
					player2->resetRocket();
				}
			}

			gPlayer2Texture.modifyAlpha(gPlayer2Texture.getAlpha());
			player2->render(gPlayer2Texture);
		}

		for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
			// Orange Virus
			if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {									// 2017/01/25 If the type of virus is an Orange Exploding Virus
																											// Start the timer
				if (listOfGameObjects[index]->getX() > SCREEN_WIDTH - listOfGameObjects[index]->getWidth() - 50)
					listOfGameObjects[index]->setTimer(VIRUS_TIMER);										// Don't decrement the counter until the virus is appearing on screen // x, y, width, height
				else {
					// Start counting down
					if (SDL_GetTicks() >= listOfGameObjects[index]->getTimerTracker() + 500) {				// Every .5 seconds
						listOfGameObjects[index]->setTimerTracker(SDL_GetTicks());							// reset the start time
						listOfGameObjects[index]->setTimer(listOfGameObjects[index]->getTimer() - 0.5);		// Decrement the timer
					}
				}

				// Draw the Orange Virus timer bar
				bar.virusTimer(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getTimer());

				// Explode!!!
				if (listOfGameObjects[index]->getTimer() <= 0) {
					spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), VIRUS_FIREBALL);	// x, y, and type
					listOfGameObjects[index]->setAlive(false);																// When timer runs out kill the virus
				}
			}
			// Blue Virus
			else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {									// 2017/01/25 If the type of virus is an Orange Exploding Virus
																												// Start the timer
				if (listOfGameObjects[index]->getX() > SCREEN_WIDTH - listOfGameObjects[index]->getWidth() - 50) {
					listOfGameObjects[index]->setTimer(VIRUS_TIMER);									// Don't decrement the counter until the virus is appearing on screen // x, y, width, height
				}
				else {
					if (SDL_GetTicks() >= listOfGameObjects[index]->getTimerTracker() + 500) {			// Every .5 seconds
						listOfGameObjects[index]->setTimerTracker(SDL_GetTicks());						// reset the start time
						listOfGameObjects[index]->setTimer(listOfGameObjects[index]->getTimer() - 0.5);	// Decrement the timer
					}
				}

				// Draw the healthbar
				bar.virusTimerBlue(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), listOfGameObjects[index]->getWidth(), listOfGameObjects[index]->getTimer());

				// Spawn the virus satellite object
				if (listOfGameObjects[index]->satelliteObjectOrbiting == false && listOfGameObjects[index]->getX() < SCREEN_WIDTH - 10) {
					spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), BLUE_VIRUS_BULLET, index);// x, y, and type
					listOfGameObjects[index]->satelliteObjectOrbiting = true;
				}

				// Set the Virus Satellite center point
				for (unsigned int index1 = 0; index1 != listOfGameObjects.size(); ++index1) {
					if (listOfGameObjects[index1]->getSubType() == BLUE_VIRUS_BULLET) {

						// Timer For Blue Virus!!!
						if (listOfGameObjects[index]->getTimer() < 0) {
							//listOfGameObjects[index]->setAlive(false);				// When timer runs out kill the virus

							listOfGameObjects[index]->setTimer(VIRUS_TIMER);			// Reset the timer
																						// spawn another object
							spawnEnemyLaser(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), BLUE_VIRUS_BULLET, index);// x, y, and type
							listOfGameObjects[index]->satelliteObjectOrbiting = true;	// Reset satellite orbiting

																						// Fire satellite object when timer runs out
							listOfGameObjects[index]->satelliteObjectOrbiting = false;	// Reset satellite orbiting
							listOfGameObjects[index1]->setProjectileActive(true);		// Set the SATELLITE to firing
						}


						// If it's a blue virus bullet and the virus it's attached to has a timer above 0
						if (index == listOfGameObjects[index1]->whichVirusAssignedTo			// currently assigned virus
							&& listOfGameObjects[index]->getTimer() > 0							// timer > 0
							&& listOfGameObjects[index1]->getProjectileActive() == false) {		// projectile active false
																								// Set the satellite to move around the blue virus
							listOfGameObjects[index1]->orbit(listOfGameObjects[index]->getX() + (listOfGameObjects[index]->getHeight() / 2), listOfGameObjects[index]->getY() + (listOfGameObjects[index]->getWidth() / 2), listOfGameObjects[index]->getTimer());	// Set center point when moving
						}
						else if (index == listOfGameObjects[index1]->whichVirusAssignedTo
							&& listOfGameObjects[index]->getTimer() < 0
							&& listOfGameObjects[index1]->getProjectileActive() == true) {

							listOfGameObjects[index1]->move();								// Projectile movement
						}
					}
				}
			}
		}

		// User Interface / Player Information Panel
		headsUpDisplay.getPlayerInfo(player1->getAlive(), player2->getAlive(),	// 2017/03/20 values needed for heads up display
			player1->getNumLives(), player2->getNumLives(),
			player1->getLaserGrade(), player2->getLaserGrade(),
			player1->getNumRockets(), player2->getNumRockets(),
			player1->getSpeedBoost(), player2->getSpeedBoost(),
			player1->boostTimer(), player2->boostTimer()
		);

		headsUpDisplay.render();												// 2017/03/20 Move HeadsUpDisplay functionality to HUD class
	}
	else if (levelOver == true) {
		SDL_RenderSetViewport(Game::Instance()->getRenderer(), NULL);								// Clear View Port

		//splash.endOfGame(Game::Instance()->getCurrentLevel(), finalScores);

		resetGame(Game::Instance()->getCurrentLevel() + 1);
		if (Game::Instance()->getCurrentLevel() >	MAX_NUM_LEVELS) gameOver = true;
	}

	SDL_RenderPresent(Game::Instance()->getRenderer());					// Update screen
}

void Level::gameProgress() {
	gamerOverMessageDisplayCounter++;
	//std::cout << "Game over counter: " << gamerOverMessageDisplayCounter << std::endl;

	if (gamerOverMessageDisplayCounter >= 250) {
		gamerOverMessageDisplayCounter = 0;

		if (!player1->getAlive() || !player2->getAlive()) {
			resetGame(MENU);								// Reset the current level back to menu
			gameOver = true;
		}
		else {
			Game::Instance()->setCurrentLevel(Game::Instance()->getCurrentLevel() + 1);			// If there is a player alive go to next level

			if (Game::Instance()->getCurrentLevel() > MAX_NUM_LEVELS) {		// If current game level goes over 3
				gameOver = true;
				resetGame(1);
			}
			else
				resetGame(Game::Instance()->getCurrentLevel());				// Increment the level a
		}
	}
}

void Level::displayLevelIntroScreens(int level) {
	// STORY - INSTRUCTIONS - OBJECTIVES - INFORMATION screens, pass in all the textures to give information about for each level
	//displayLevelIntro = splash.levelIntroScreens(Game::Instance()->getCurrentLevel());	// Display level story and info screens

	//if (level <= MAX_NUM_LEVELS) splash.pressButtonToContinue(e);
}

void Level::renderTimer(unsigned int &timer) {
	std::stringstream timeText;
	timeText.str("");

	if (!gameOver) timeText << "Time: " << timer;						// Set the game timer
	else timeText << "Returning To Menu In: " << timer;					// Set the game timer


	currentTime = SDL_GetTicks();										// Get the current game running time
	if (currentTime > lastTime + 1000) {								// Decrement countdown timer
		gTimeTextTexture.UITextTimer(timeText.str().c_str(), timer);	// Render Text - Use a string to render the current Game Time to a Texture
		lastTime = currentTime;											// Store this time
		timer--;														// Decrement the timer
																		//std::cout << "Time: " << countdownTimer << " lastTime: " << lastTime << " currentTime: " << currentTime << std::endl;
	}

	gTimeTextTexture.render(SCREEN_WIDTH - gTimeTextTexture.getWidth() - 10, 8);	// LAZY
}

std::string previous1, previous2, previous3, previous4;

void Level::displayText() {
	if (player1->getAlive()) Game::Instance()->player1Score = player1->getScore();
	if (Game::Instance()->twoPlayer && player2->getAlive()) Game::Instance()->player2Score = player2->getScore();

	if (!Game::Instance()->twoPlayer)
		Game::Instance()->finalScores = "Player 1: " + std::to_string(Game::Instance()->player1Score);					// End of game Player 1 and Player 2 scores
	else if (Game::Instance()->twoPlayer)
		Game::Instance()->finalScores = "Player 1: " + std::to_string(Game::Instance()->player1Score) + " Player 2: " + std::to_string(Game::Instance()->player2Score);	// End of game Player 1 and Player 2 scores

	if (!levelOver && !gameOver) {
		if (checkpointsSpawned == 2 && countdownTimer < 2 && (player1->getAlive() || player2->getAlive())) {
			levelOver = true;		// Level is over
			if (Game::Instance()->getCurrentLevel() == MAX_NUM_LEVELS) gameOver = true;
		}
		else if (countdownTimer > 0 && countdownTimer <= GAME_TIMER) {

			renderTimer(countdownTimer);

			levelOver = false;
		}
		else if (countdownTimer <= 0 || countdownTimer > GAME_TIMER + 5) {
			noTime = true;		// Level is over
			if (Game::Instance()->getCurrentLevel() == MAX_NUM_LEVELS) gameOver = true;
		}

		if (previous1 != infoMessageP1) {
			if (infoMessageP1 != "") gInfoMessageP1TextTexture.UITextPlayerMessage(infoMessageP1, PLAYER_1);	// Render Text - Use a string to render Player 1 notifications
		}
		if (previous2 != infoMessageP2) {
			if (infoMessageP2 != "") gInfoMessageP2TextTexture.UITextPlayerMessage(infoMessageP2, PLAYER_2);	// Render Text - Use a string to render Player 2 notifications
		}
		if (previous3 != infoMessageGeneral) {
			if (infoMessageGeneral != "") gInfoMessageTextTexture.UITextPlayerMessage(infoMessageGeneral);		// Render Text - Use a string to render General notifications
		}
		if (previous4 != infoMessageMap) {
			if (infoMessageMap != "") gInfoMessageMapTextTexture.UITextPlayerMessage(infoMessageMap, 3);		// Render Text - Use a string to render General notifications
		}

		previous1 = infoMessageP1;
		previous2 = infoMessageP2;
		previous3 = infoMessageGeneral;
		previous4 = infoMessageMap;
	}
	else if (levelOver == true) {
		//std::cout << "Level " << getCurrentLevel() << " Complete" << std::endl;
		//gamerOverMessageDisplayCounter = 0;
		gameProgress();
	}// Levels

	if (noTime == true) {
		resetGame(Game::Instance()->getCurrentLevel());
		listOfGameObjects.clear();
	}
}


/*
2017/03/19 Function to check how long a message has been on screen, and increment message timers
*/
void Level::checkMessageTimes() {
	if (infoMessageP1Counter < MESSAGE_TIME) {
		gInfoMessageP1TextTexture.render((SCREEN_WIDTH - gInfoMessageP1TextTexture.getWidth()) / 2, ((SCREEN_HEIGHT - gInfoMessageP1TextTexture.getHeight()) / 2) - 20); // Top message P1
		infoMessageP1Counter++;
	}
	if (infoMessageP2Counter < MESSAGE_TIME) {
		gInfoMessageP2TextTexture.render((SCREEN_WIDTH - gInfoMessageP2TextTexture.getWidth()) / 2, ((SCREEN_HEIGHT - gInfoMessageP2TextTexture.getHeight()) / 2) + 20);// Bottom message P2
		infoMessageP2Counter++;
	}
	if (infoMessageCounter < MESSAGE_TIME) {
		gInfoMessageTextTexture.render((SCREEN_WIDTH - gInfoMessageTextTexture.getWidth()) / 2, ((SCREEN_HEIGHT - gInfoMessageTextTexture.getHeight()) / 2));			// Middle message General
		infoMessageCounter++;
	}
	if (infoMessageMapCounter < MESSAGE_TIME_MAP) {
		gInfoMessageMapTextTexture.render((SCREEN_WIDTH - gInfoMessageMapTextTexture.getWidth()) / 2, SCREEN_HEIGHT_GAME - gInfoMessageMapTextTexture.getHeight() - 5); // Top message P1
		infoMessageMapCounter++;
	}
}

// 2017/02/22 Check player is alive
void Level::displayScoreForObject(int Xcoord, int Ycoord, int score, int player) {
	GameObject* p_PointsValue = new ScoreValueText(Xcoord, Ycoord, score, player);

	if (player == PLAYER_1 && player1->getAlive()) {
		//scoreTextP1counter++;
		if (!p_PointsValue->m_Texture.loadFromRenderedText("+" + std::to_string(score), { 240, 210, 65, 255 }, gFontRetro20)) {	// Gold Text
			printf("Unable to render player text texture!\n");
		}
	}
	else if (player == PLAYER_2 && player2->getAlive()) {
		//scoreTextP2counter++;
		if (!p_PointsValue->m_Texture.loadFromRenderedText("+" + std::to_string(score), { 0, 0, 255, 255 }, gFontRetro20)) {		// Blue Text
			printf("Unable to render player text texture!\n");
		}
	}

	listOfGameObjects.push_back(p_PointsValue);
}

void Level::moveGameObjects() {
	if (player1->getAlive()) player1->move();												// Update ship movement
	if (player2->getAlive()) player2->move();

	//scrollBG.move();																		// Move the Scrolling background

	// Cycle through list of Game Objects and move them, Player scores, and Power Ups so far
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		// Objects that move towards coordinates
		if (listOfGameObjects[index]->getSubType() == PLAYER1_SCORE)		listOfGameObjects[index]->move(player1->getX(), player1->getY());	// Move the score to Player 1 ship
		else if (listOfGameObjects[index]->getSubType() == SAW1)			listOfGameObjects[index]->move(player1->getX(), player1->getY());	// Move Player 1 saw with Player 1 Ship
		else if (listOfGameObjects[index]->getSubType() == PLAYER2_SCORE)	listOfGameObjects[index]->move(player2->getX(), player2->getY());	// Move the score to Player 2 ship
		else if (listOfGameObjects[index]->getSubType() == SAW2)			listOfGameObjects[index]->move(player2->getX(), player2->getY());	// Move Player 2 saw with Player 2 Ship
		else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {	// Move Enemy Virus, tracking the player movement
			if (moveToPlayer1(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY())) listOfGameObjects[index]->move(player1->getX(), player1->getY());
			else listOfGameObjects[index]->move(player2->getX(), player2->getY());
		}
		else if (listOfGameObjects[index]->getSubType() == WHITE_BLOOD_CELL && activeEnemyVirusSmall > 0) {
			std::cout << "white blood cell " << index << "x " << listOfGameObjects[index]->getX() << " y " << listOfGameObjects[index]->getY() << std::endl;

			int nearestSmallVirus = 1280 * 1280 + 600 * 600;	// Furthest distance objects can be apart on screen

																// The White blood cell can attack smaller sized virus objects
			for (unsigned int smallVirusIndex = 0; smallVirusIndex != listOfGameObjects.size(); ++smallVirusIndex) {
				if (listOfGameObjects[smallVirusIndex]->getType() == SMALL_VIRUS) {
					if (abs(listOfGameObjects[smallVirusIndex]->getX() - listOfGameObjects[index]->getX()) * abs(listOfGameObjects[smallVirusIndex]->getX() - listOfGameObjects[index]->getX()) +
						abs(listOfGameObjects[smallVirusIndex]->getY() - listOfGameObjects[index]->getY()) * abs(listOfGameObjects[smallVirusIndex]->getY() - listOfGameObjects[index]->getY()) < nearestSmallVirus)
						nearestSmallVirus = abs(listOfGameObjects[smallVirusIndex]->getX() - listOfGameObjects[index]->getX()) * abs(listOfGameObjects[smallVirusIndex]->getX() - listOfGameObjects[index]->getX()) +
						abs(listOfGameObjects[smallVirusIndex]->getY() - listOfGameObjects[index]->getY()) * abs(listOfGameObjects[smallVirusIndex]->getY() - listOfGameObjects[index]->getY()) < nearestSmallVirus;

					listOfGameObjects[index]->moveStalker(listOfGameObjects[smallVirusIndex]->getX(), listOfGameObjects[smallVirusIndex]->getY());	// move towards nearest small virus
				}
			}
		}
		// Objects with ordinary movement, or movment pattern defined in move function
		else if (listOfGameObjects[index]->getType() != PLAYER) listOfGameObjects[index]->move();
	}
}

bool Level::moveToPlayer1(int x, int y) {
	bool moveToPlayer1 = true;

	if (player2->getAlive() && (abs(player1->getX() - x) * abs(player1->getX() - x)) +	// Distance on X axis between player 1 and virus squared
		(abs(player1->getY() - y) * abs(player1->getY() - y)) >							// Distance on Y axis between player 1 and virus squared
		(abs(player2->getX() - x) * abs(abs(player2->getX() - x)) + 					// Distance on X axis between player 2 and virus squared
		(abs(player2->getY() - y) * abs(abs(player2->getY() - y)))))					// Distance on Y axis between player 2 and virus squared
	{
		moveToPlayer1 = false;
	}

	return moveToPlayer1;
}

// 2017-02-16 Display player messages for player events, added to a function
void Level::infoMessage(std::string message, int type, int timer) {
	if (type == 0) {
		infoMessageCounter = 0;
		infoMessageGeneral = message;
	}
	else if (type == PLAYER_1) {
		infoMessageP1Counter = 0;
		infoMessageP1 = message;
	}
	else if (type == PLAYER_2) {
		infoMessageP2Counter = 0;
		infoMessageP2 = message;
	}
	else if (type == 3) {
		infoMessageMapCounter = 0;
		infoMessageMap = message;
	}
	std::cout << message << std::endl;
}

// Decide how many of each enemy / obstacle on screen at a given time
//void Level::infoMessage(std::string message, int type, int timer) {
void Level::spawnMovingObjects() {
	int blockageCount = 0;
	// Count game objects
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (listOfGameObjects[index]->getSubType() == BLOCKAGE) {
			blockageCount++;
		}
	}
	//std::cout << "number of blockages counted " << blockageCount << std::endl;

	if (player1->getAlive() == false && player1->getNumLives() > 0) spawnPlayer(PLAYER_1);
	if (player2->getAlive() == false && player2->getNumLives() > 0) spawnPlayer(PLAYER_2);

	if (!player1->getAlive() && !player2->getAlive()) gameOver = true;

	if (activeBloodCells < SPAWN_NUM_BLOOD_CELL) {
		activeBloodCells++;									// increment Blood cell counter
		spawnBloodCell(LARGE_BLOOD_CELL);					// Spawn a large blood cell
	}

	if (activeSmallBloodCells < SPAWN_NUM_BLOOD_CELL_S) {
		activeSmallBloodCells++;							// increment Small blood cell counter
		spawnBloodCell(SMALL_BLOOD_CELL);					// Spawn a small blood cell
	}
	if (activeWhiteBloodCells < SPAWN_NUM_BLOOD_CELL_WHITE) {
		activeWhiteBloodCells++;							// increment white blood cell counter
		std::cout << activeWhiteBloodCells << " white" << std::endl;
		spawnBloodCell(WHITE_BLOOD_CELL);					// spawn a white blood cell
	}

	activePowerUps = 0;		// Number of active onscreen Power Ups
	activeEnemyShips = 0;	// Number of active onscreen Enemy Ships
	activeEnemyVirus = 0;	// Number of active onscreen Enemy Virus

							// Check how many of each game object are in the list
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (listOfGameObjects[index]->getType() == POWER_UP) activePowerUps++;
		else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP)	activeEnemyShips++;
		else if (listOfGameObjects[index]->getSubType() == ENEMY_BOSS)	activeEnemyBoss++;
		else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) activeEnemyVirus++;
	}// end for

	if (activePowerUps < SPAWN_NUM_POWER_UPS) { spawnPowerUp(); }


	if (Game::Instance()->getCurrentLevel() == LEVEL_1 && activeEnemyShips < SPAWN_NUM_ENEMY_SHIPS_LVL1 && activeEnemyBoss < 1) { spawnEnemyShip(); }
	else if (Game::Instance()->getCurrentLevel() == LEVEL_2 && activeEnemyShips < SPAWN_NUM_ENEMY_SHIPS_LVL2 && activeEnemyBoss < 1) { spawnEnemyShip(); }
	else if (Game::Instance()->getCurrentLevel() == LEVEL_3 && activeEnemyShips < SPAWN_NUM_ENEMY_SHIPS_LVL3 && activeEnemyBoss < 1) { spawnEnemyShip(); }

	if (Game::Instance()->getCurrentLevel() == LEVEL_1 && activeEnemyVirus < SPAWN_NUM_ENEMY_VIRUS_LVL1 && backgroundLoopCounter != BACKGROUND_SCROLL_TIMES) { spawnEnemyVirus(); }
	else if (Game::Instance()->getCurrentLevel() == LEVEL_2 && activeEnemyVirus < SPAWN_NUM_ENEMY_SHIPS_LVL2) { spawnEnemyVirus(); }
	else if (Game::Instance()->getCurrentLevel() == LEVEL_3 && activeEnemyVirus < SPAWN_NUM_ENEMY_SHIPS_LVL3) { spawnEnemyVirus(); }

	// Start the blockages halfway through the level
	//if (numBlockages < SPAWN_NUM_BLOCKAGES && backgroundLoopCounter > BACKGROUND_SCROLL_TIMES / 2) {
	//if (numBlockages < SPAWN_NUM_BLOCKAGES) {

	/* 2017/03/19 Blockages half-way through level 2, and from the start of level 3 */
	if (numBlockages < SPAWN_NUM_BLOCKAGES && ((Game::Instance()->getCurrentLevel() == 2 && backgroundLoopCounter > BACKGROUND_SCROLL_TIMES / 2) || Game::Instance()->getCurrentLevel() == 3)) {
		//std::cout << "blockage check: " << numBlockages << std::endl;
		spawnBlockage();
	}

	//if (activeEnemyBoss < 1 && backgroundLoopCounter == BACKGROUND_SCROLL_TIMES) spawnEnemyBoss();
	//if (activeEnemyBoss < 1 && getCurrentLevel() == 3 && backgroundLoopCounter == BACKGROUND_SCROLL_TIMES) spawnEnemyBoss();
	//if (backgroundLoopCounter == BACKGROUND_SCROLL_TIMES && activeEnemyBoss < 1) spawnEnemyBoss();	// Spawn the Enemy Boss at the end of the level
	if (activeEnemyBoss < 1) spawnEnemyBoss();	// 2017/03/18 Test: Show the boss at the start of the level
}

// Blockage Spawn Function
void Level::spawnBlockage() {
	GameObject* p_Blockage0 = new Blockage();
	//p_Blockage0->spawn(1290, 40, -BACKGROUND_SCROLL_SPEED, 0);		// Spawn with random X and Y coord, and speed between 1 and 3
	p_Blockage0->spawn(1290, 40, -BACKGROUND_SCROLL_SPEED, 0);			// Spawn with random X and Y coord, and speed between 1 and 3
	listOfGameObjects.push_back(p_Blockage0);

	Blockage* p_Blockage1 = new Blockage();
	p_Blockage1->spawn(1290, 170, -BACKGROUND_SCROLL_SPEED, 0);			// Spawn with random X and Y coord, and speed between 1 and 3
	listOfGameObjects.push_back(p_Blockage1);

	Blockage* p_Blockage2 = new Blockage();
	p_Blockage2->spawn(1290, 300, -BACKGROUND_SCROLL_SPEED, 0);			// Spawn with random X and Y coord, and speed between 1 and 3
	listOfGameObjects.push_back(p_Blockage2);

	Blockage* p_Blockage3 = new Blockage();
	p_Blockage3->spawn(1290, 430, -BACKGROUND_SCROLL_SPEED, 0);			// Spawn with random X and Y coord, and speed between 1 and 3
	listOfGameObjects.push_back(p_Blockage3);

	//std::cout << "Blockage Spawned!\n";

	if (Game::Instance()->twoPlayer) {
		infoMessage(randomBlockageMessage(), 3);						// 2017/03/04 Display a random spawning message for blockages
	}
	numBlockages += 4;
}
void Level::spawnPlayer(int player) {
	int randomYCoord = rand() % 9; // a number 0 to 8

	if (player == PLAYER_1) {
		player1->spawn(50, (randomYCoord * 58) + 50);						// 2017/01/20: Spawn Player 1 at random Y coord
		player1->setAlive(true);
		gPlayer1Texture.setFlash(true);
		gPlayer1Texture.flashGameObject(10, 4);								// 2017/01/30 Moved flashGameObject() function into LTexture
	}
	else if (player == PLAYER_2) {
		player2->spawn(50, (randomYCoord * 58) + 50);
		if (player2->getY() == player1->getY()) spawnPlayer(2);				// 2017/01/20: Spawn Player 2 at random Y coord + different to Player 1
		player2->setAlive(true);
		gPlayer2Texture.setFlash(true);
		gPlayer2Texture.flashGameObject(10, 4);
		//std::cout << "player1.getY() " << player1.getY() << " player2.getY() " << player2.getY() << std::endl;
	}

	if ((!Game::Instance()->twoPlayer && player == PLAYER_1) || (Game::Instance()->twoPlayer)) {
		infoMessage(randomPlayerMessage(player), player);					// 2017/03/04 Random player spawning messagess
	}
}
void Level::spawnEnemyBoss() {
	int x, y, randomSpeed;

	GameObject* p_EnemyBoss = new EnemyBoss();
	spawnRandomAttributes(x, y, randomSpeed, 50, p_EnemyBoss->getHeight(), 1);

	y = 100;

	//p_EnemyBoss->spawn(x, y, -randomSpeed);
	p_EnemyBoss->spawn(x, (SCREEN_HEIGHT_GAME - p_EnemyBoss->getHeight()) / 2, -5);
	listOfGameObjects.push_back(p_EnemyBoss);

	if (Game::Instance()->twoPlayer) {
		infoMessage(randomBossMessage(), 3);								// 2017/03/04 Display a random message when a boss is spawned
	}

	// Enemy boss eye lasers
	//listOfGameObjects.push_back(eyeLaser1);
	//listOfGameObjects.push_back(eyeLaser2);
}
// List of enemy ships to spawn at random times and positions
void Level::spawnEnemyShip() {
	int x, y, randomSpeed;

	GameObject* p_Enemy = new EnemyShip();
	spawnRandomAttributes(x, y, randomSpeed, 50, p_Enemy->getHeight(), 1);
	p_Enemy->spawn(x, y, -randomSpeed);
	listOfGameObjects.push_back(p_Enemy);
}
void Level::spawnEnemyVirus(int subType, int x, int y) {
	int backupX = x, backupY = y, randomSpeed;
	bool useCoords = false;
	if (x != 0 && y != 0) useCoords = true;

	spawnRandomAttributes(x, y, randomSpeed, 150);

	// Spawn the small virus at a random position close to the original virus position
	if (subType == VIRUS_SMALL_GREEN || subType == VIRUS_SMALL_ORANGE || subType == VIRUS_SMALL_BLUE) {
		int randomX = rand() % 60 + backupX - 15;	// Somewhere between - 15 and 45 of original position
		int randomY = rand() % 60 + backupY - 15;
		int randomSpeed = rand() % 4 + 1;

		GameObject* p_SmallVirus = new EnemyVirus(subType);
		p_SmallVirus->spawn(randomX, randomY, -randomSpeed);
		p_SmallVirus->setType(SMALL_VIRUS);
		p_SmallVirus->setColliderHeight(40);
		p_SmallVirus->setColliderWidth(40);
		listOfGameObjects.push_back(p_SmallVirus);
		//Audio::Instance()->ripFX();
		Audio::Instance()->playFX("ripFX");
	}
	else {
		// If no specific virus is to be spawned, pick one at random depending on the level
		if (subType == 0) {
			int randomExplodingVirus = rand() % 4 + 1;									// 1 in 4 chance of Orange Exploding Virus
																						//randomExplodingVirus = 2; // Test blue virus
			if (randomExplodingVirus == 1 && (Game::Instance()->getCurrentLevel() == 2 || Game::Instance()->getCurrentLevel() == 3)) subType = VIRUS_ORANGE;
			else if (randomExplodingVirus == 2 && Game::Instance()->getCurrentLevel() == 3) subType = VIRUS_BLUE;
			else subType = VIRUS_GREEN;
		}

		GameObject* p_Virus = new EnemyVirus(subType, 3.0);							// Orange type = 1
		p_Virus->setTimer(VIRUS_TIMER);
		if (useCoords)
			p_Virus->spawn(backupX, backupY, -randomSpeed - 4, -randomSpeed);
		else
			p_Virus->spawn(x, y, -randomSpeed - 4, -randomSpeed);
		listOfGameObjects.push_back(p_Virus);
		//std::cout << "distance to virus p1: " << abs(((player1.getX() * player1.getX()) + (player1.getY() * player1.getY()))) << " p2: " << abs((player2.getX() * player2.getX()) + (player2.getY() * player2.getY())) << std::endl;
	}
}
void Level::spawnBloodCell(int subType) {
	int x, y, randomSpeed;
	GameObject* p_BloodCell = new BloodCell(subType);

	spawnRandomAttributes(x, y, randomSpeed, 200, p_BloodCell->getHeight());
	p_BloodCell->spawn(x, y, -randomSpeed);											// 2017/01/24 Added Y padding to keep objects within the game screen boundary
	listOfGameObjects.push_back(p_BloodCell);

	//bloodCellCounterP1++;

	std::cout << "Number of Blood Cells: " << totalBloodCells++ << std::endl;
	if (subType == LARGE_BLOOD_CELL) totalLargeBC++;
}
void Level::spawnPowerUp() {
	int x, y, randomSpeed, powerUpType = 0;
	int randomPowerup = rand() % 5 + 1;												// Number between 1 and 4
																					//randomPowerup = 4;

	if (countdownTimer <= 10 && checkpointsSpawned < 2) {
		powerUpType = POWER_UP_CHECKPOINT;											// if the timer is less than or equal 10, spawn the Checkpoint power up
		checkpointsSpawned++;
	}
	else {
		if (randomPowerup == 1) powerUpType = POWER_UP_HEALTH;
		else if (randomPowerup == 2) powerUpType = POWER_UP_LASER;
		else if (randomPowerup == 3) powerUpType = POWER_UP_ROCKET;
		else if (randomPowerup == 4) powerUpType = POWER_UP_LIVES;
	}

	GameObject* p_PowerUp = new PowerUp(powerUpType, 50);						// Type and score
	spawnRandomAttributes(x, y, randomSpeed, 200, p_PowerUp->getHeight());		// Spawn with random X and Y coord, and speed between 1 and 3
	p_PowerUp->spawn(x, y, -5);													// 2017/01/16 USES OVERLOADED FUNCTION -- CHECK
	listOfGameObjects.push_back(p_PowerUp);
}
void Level::spawnRandomAttributes(int &x, int &y, int &randomSpeed, int xMuliplier, int yPadding, int speed) {	// 2017-01-20 Separate out common randomness of game object spawning
	int randomX = rand() % 5 + 1;
	int randomY = rand() % 8 + 1;												// A number between 1 and 8
	randomSpeed = rand() % 4 + speed;

	x = SCREEN_WIDTH + (randomX * xMuliplier);
	y = 40 + (randomY * ((SCREEN_HEIGHT_GAME - yPadding - 80) / 8));			// 40 top and bottom, yPadding, object height
}
// Spawn Weapon at ships location
void Level::spawnExplosion(int x, int y, int subType) {
	GameObject* p_Explosion = new Explosion(x, y, subType);		// Create an explosion at x and y, with given type
	p_Explosion->spawn(x, y - 30);								// Spawn the explosion at the given x & y coords
	listOfGameObjects.push_back(p_Explosion);					// Add explosion to list of game objects

	if (subType == FIRE_EXPLOSION) Audio::Instance()->playFX("explosionFX");	// Play explosion sound effect
	else if (subType == BLOOD_EXPLOSION) Audio::Instance()->playFX("splashFX");	// 2017/03/13 Splash Effect for blood cells
	else Audio::Instance()->playFX("ripFX");									// 2017/03/13 Rip Effect for Virus Enemies ripping in 2

	std::cout << "Number of Explosions: " << totalExplosions++ << std::endl;
}
void Level::spawnLaser(int x, int y, int player, int grade, int velocity) {
	//std::cout << "Laser Grade: " << grade << std::endl;
	GameObject* p_Laser1 = new WeaponPlLaser(player);

	p_Laser1->spawn(x + 65, y + 25, velocity);	// Spawn laser at front of ship, with set veloicty, for player 1, setting sub-type of laser

												// Check the grade of the laser, to decide if it is a single, double, or triple beam
	if (grade == LASER_DOUBLE) {
		p_Laser1->setAngle(LASER2_TOP);

		GameObject* p_Laser2 = new WeaponPlLaser(player, LASER2_BOTTOM, LASER_DOUBLE);

		p_Laser2->spawn(x + 65, y + 30, velocity);

		listOfGameObjects.push_back(p_Laser2);
	}
	if (grade == LASER_TRIPLE) {		// FIRE 2 MORE LASERS AT ANGLES
		GameObject* p_Laser2 = new WeaponPlLaser(player, LASER3_TOP, LASER_TRIPLE);	// Angled laser
		GameObject* p_Laser3 = new WeaponPlLaser(player, LASER3_BOTTOM, LASER_TRIPLE);

		p_Laser2->spawn(x + 65, y + 30, velocity);
		p_Laser3->spawn(x + 65, y + 35, velocity);

		listOfGameObjects.push_back(p_Laser2);
		listOfGameObjects.push_back(p_Laser3);
	}

	listOfGameObjects.push_back(p_Laser1);

	if (!gameOver) {
		//if (player == 1) Audio::Instance()->laserFX_P1();
		//else if (player == 2) Audio::Instance()->laserFX_P2();
		if (player == 1) Audio::Instance()->playFX("laser1FX");
		else if (player == 2) Audio::Instance()->playFX("laser2FX");
	}
}
void Level::spawnEnemyLaser(int xCoord, int yCoord, int subType, int whichVirus) {
	if (subType == ENEMY_SHIP_LASER && xCoord < SCREEN_WIDTH) {							// first type and visible on screen, start shooting
		int distanceBetweenShots = ((rand() % 3 + 1) * 50) + 60;						// 2017/01/20 More random shooting from enemies
																						// if (shipX % 100 == 0) {
		if (xCoord % distanceBetweenShots < 3) {										// 2017-01-20 Not all ships were firing
			GameObject* p_LaserE = new WeaponEnLaser(ENEMY_SHIP_LASER);
			p_LaserE->spawn(xCoord - 20, yCoord + 30, p_LaserE->getVelocity());
			listOfGameObjects.push_back(p_LaserE);

			//Audio::Instance()->laserFX_Enemy();
			Audio::Instance()->playFX("enemyLaserFX");
		}
	}
	else if (subType == VIRUS_FIREBALL) {
		for (unsigned int i = 1; i < 9; i++) {
			//std::cout << "Laser " << i << " created" << std::endl;
			GameObject* p_Laser = new WeaponEnLaser(VIRUS_FIREBALL);	// Create an Enemy Laser of type 1 (Orange Virus)
			p_Laser->spawn(xCoord, yCoord);								// Spawn the laser from the Virus Coordinates

			if (i == 1) p_Laser->setVelX(p_Laser->getVelocity());		// Set the direction for the 8 Orange Virus Lasers
			else if (i == 2) p_Laser->setVelX(-p_Laser->getVelocity());
			else if (i == 3) {
				p_Laser->setVelX(0);
				p_Laser->setVelY(p_Laser->getVelocity());
			}
			else if (i == 4) {
				p_Laser->setVelX(0);
				p_Laser->setVelY(-p_Laser->getVelocity());
			}
			else if (i == 5) {
				p_Laser->setVelX(p_Laser->getVelocity() / sqrt(2));
				p_Laser->setVelY(-p_Laser->getVelocity() / sqrt(2));
			}
			else if (i == 6) {
				p_Laser->setVelX(p_Laser->getVelocity() / sqrt(2));
				p_Laser->setVelY(p_Laser->getVelocity() / sqrt(2));
			}
			else if (i == 7) {
				p_Laser->setVelX(-(p_Laser->getVelocity() / sqrt(2)));
				p_Laser->setVelY(-(p_Laser->getVelocity() / sqrt(2)));
			}
			else if (i == 8) {
				p_Laser->setVelX(-(p_Laser->getVelocity() / sqrt(2)));
				p_Laser->setVelY(p_Laser->getVelocity() / sqrt(2));
			}

			listOfGameObjects.push_back(p_Laser);						// Add the Enemy Lasers to a list to move and render
		}
	}
	else if (subType == BLUE_VIRUS_BULLET) {
		GameObject* p_Laser = new WeaponEnLaser(BLUE_VIRUS_BULLET);
		p_Laser->spawn(xCoord, yCoord, -10);							// Spawn the laser from the Virus Coordinates
		p_Laser->whichVirusAssignedTo = whichVirus;

		listOfGameObjects.push_back(p_Laser);							// Add the Enemy Lasers to a list to move and render
	}
}
void Level::spawnNinjaStar(int x, int y, int player) {					// player to spawn for and their coords
																		//std::cout << "Ninja Star Spawned " << player << "p1 " << PLAYER_1 << " p2 " << PLAYER_2 << std::endl;
	GameObject* p_NinjaStar = new WeaponPlNinjaStar(player);
	p_NinjaStar->spawn(x + 65, y + 25, 10);								// Spawn the weapon at the x & y coords given, with a velocity of 10

	listOfGameObjects.push_back(p_NinjaStar);							// Add to game objects list
	if (!gameOver) {
		if (player == PLAYER_1) {
			ninjaStarP1Counter++;
			//Audio::Instance()->ninjaFX_P1();										// Play a different sound effect depending on the player
			Audio::Instance()->playFX("ninja1FX");										// Play a different sound effect depending on the player
		}
		else if (player == PLAYER_2) {
			ninjaStarP2Counter++;
			//Audio::Instance()->ninjaFX_P2();
			Audio::Instance()->playFX("ninja2FX");
		}
	}
}
void Level::spawnRocket(int x, int y, int player, int type, bool launch) {
	if (launch == false && player == PLAYER_1 && player1->getNumRockets() > 0) player1->setRocketBarActive(true);			// if not ready to fire, player is player 1, and player 1 has rockets
	else if (Game::Instance()->twoPlayer && launch == false && player == PLAYER_2 && player2->getNumRockets() > 0) player2->setRocketBarActive(true);
	else {
		bool createRocket = false;

		if (player == PLAYER_1 && !player1->getProjectileActive() && player1->getNumRockets() > 0) {
			createRocket = player1->initialiseRocket();						// 2017/02/19 initialise the rocket, then create and launch the rocket after returning true from function
		}
		else if (player == PLAYER_2 && !player2->getProjectileActive() && player2->getNumRockets() > 0) {
			createRocket = player2->initialiseRocket();
		}
		if (createRocket) {
			GameObject* p_Rocket = new WeaponPlRocket(player);				// Create a rocket
			p_Rocket->spawn(x, y, 15);	// spawn for the player

										//std::cout << "Rocket Spawned" << std::endl;
			listOfGameObjects.push_back(p_Rocket);							// Add rocket to game object list
		}
	}
}

int numSaws = 0;

void Level::spawnSaw(int x, int y, int subType) {			// player to spawn for and their coords, turn on if inacive, off if active	// 2017-02-08 Updated and working OK
	bool createSaw = false;									// Used to decide which player to create the saw for, so code doesn't need to be repeated

	if (player1->getSawActive()) std::cout << "player 1 saw active" << std::endl;
	else if (!player1->getSawActive()) std::cout << "player 1 saw NOT active" << std::endl;
	if (player2->getSawActive()) std::cout << "player 2 saw active" << std::endl;
	else if (!player2->getSawActive()) std::cout << "player 2 saw NOT active" << std::endl;

	// Check which player to create a saw for
	if (subType == SAW1 && !player1->getSawActive()) {
		createSaw = true;
		player1->setSawActive(true);						// Show saw, set saw active function returns true value
		player1->setShieldActive(false);					// Hide the shield if the saw is active
		numSaws++;
	}
	else if (subType == SAW2 && !player2->getSawActive()) {
		createSaw = true;
		player2->setSawActive(true);
		player2->setShieldActive(false);					// Hide the shield if the saw is active
		numSaws++;
	}

	if (createSaw) {
		GameObject* p_Saw = new WeaponPlSaw(subType);		// Create new saw
		p_Saw->spawn(x + 65, y + 25);						// Spawn the saw at the given x & y coords
		listOfGameObjects.push_back(p_Saw);					// Add the saw to the game object listg
															//if (!gameOver) Audio::Instance()->sawFX();		// Play the sound effect for the saw starting
		if (!gameOver) Audio::Instance()->playFX("sawFX");	// Play the sound effect for the saw starting
	}
	else if (!createSaw) {
		for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {

			if (listOfGameObjects[index]->getSubType() == subType) {		// if saw is the right sub-type
				if (listOfGameObjects[index]->getAlive() == true) {			// if saw is active
					if (listOfGameObjects[index]->getSubType() == SAW1) {
						player1->setSawActive(false);						// If the say is the right sub-type hide saw for Player 1
						player1->setShieldActive(true);
						listOfGameObjects[index]->setAlive(false);
					}

					else if (listOfGameObjects[index]->getSubType() == SAW2) {
						player2->setSawActive(false);						// Hide saw for Player 2
						player2->setShieldActive(true);
						listOfGameObjects[index]->setAlive(false);

					}
					// Erase saw from list
					if (!listOfGameObjects[index]->getAlive()) {
						listOfGameObjects[index]->m_Texture.free();
						listOfGameObjects.erase(listOfGameObjects.begin() + index);
						index--;
					}
				}
			}
		}// end for
	} // end else
	  //std::cout << "Num Saws: " << numSaws << std::endl;
}

// Destroy Game Objects
void Level::destroyGameObjects() {
	// Test game objects are being destroyed and removed from list

	if (Game::Instance()->getCurrentLevel() == LEVEL_1 || Game::Instance()->getCurrentLevel() == LEVEL_2 || Game::Instance()->getCurrentLevel() == LEVEL_3) {
		// Active Enemies
		std::cout << "small virus count " << activeEnemyVirusSmall << std::endl;

		int countSaws = 0, countBloodCells = 0, countEnemies = 0, countEnemyBullets = 0, countPowerUps = 0, countScoreValues = 0;
		int countNumPlayerWeapons = 0, countExplosions = 0;

		int countLargeBloodCells = 0, countSmallBloodCells = 0, countWhiteBloodCells = 0;
		int countNanoBots = 0, countGreenVirus = 0, countOrangeVirus = 0, countBlueVirus = 0;
		int countEnLaser = 0, countFireball = 0, countVBullet = 0;
		int countPUHealth = 0, countPULaser = 0, countPURocket = 0, countPUtimer = 0, countPULife = 0;
		int countP1Laser = 0, countP2Laser = 0, countP1NStar = 0, countP2NStar = 0, countP1Rocket = 0, countP2Rocket = 0;

		// Count number of each object on list
		for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
			if (listOfGameObjects[index]->getSubType() == SAW1 || listOfGameObjects[index]->getSubType() == SAW2) {
				countSaws++;
				//if (listOfGameObjects[index]->getAlive() == false) std::cout << "Dead saw" << std::endl;
			}
			// Blood Cells
			if (listOfGameObjects[index]->getType() == BLOOD_CELL) countBloodCells++;
			if (listOfGameObjects[index]->getSubType() == LARGE_BLOOD_CELL) countLargeBloodCells++;
			else if (listOfGameObjects[index]->getSubType() == SMALL_BLOOD_CELL) countSmallBloodCells++;
			else if (listOfGameObjects[index]->getSubType() == WHITE_BLOOD_CELL) countWhiteBloodCells++;
			// Enemys
			if (listOfGameObjects[index]->getType() == ENEMY_OBJECT) countEnemies++;
			if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN) countGreenVirus++;
			else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) countOrangeVirus++;
			else if (listOfGameObjects[index]->getSubType() == SMALL_VIRUS) countBlueVirus++;
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) countNanoBots++;
			// Enemy Weapons
			if (listOfGameObjects[index]->getType() == ENEMY_WEAPON) countEnemyBullets++;
			if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER) countEnLaser++;
			else if (listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) countFireball++;
			else if (listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET) countVBullet++;
			// Power Ups
			if (listOfGameObjects[index]->getType() == POWER_UP) countPowerUps++;
			if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH) countPUHealth++;
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER) countPULaser++;
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_ROCKET) countPURocket++;
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_CHECKPOINT) countPUtimer++;
			else if (listOfGameObjects[index]->getSubType() == POWER_UP_LIVES) countPULife++;
			// Score Values
			if (listOfGameObjects[index]->getType() == SCORE_TEXT) countScoreValues++;
			// Player Weapons
			if (listOfGameObjects[index]->getType() == PLAYER_WEAPON) countNumPlayerWeapons++;
			if (listOfGameObjects[index]->getSubType() == LASER_P1) countP1Laser++;					// 2017/03/18 Fixed not deleting
			else if (listOfGameObjects[index]->getSubType() == LASER_P2) countP2Laser++;			// 2017/03/18 Fixed not deleting
			else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P1) countP1NStar++;		// 2017/03/18 Fixed not deleting
			else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P2) countP2NStar++;		// 2017/03/18 Fixed not deleting
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P1) countP1Rocket++;
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P2) countP2Rocket++;
			if (listOfGameObjects[index]->getType() == EXPLOSION) countExplosions++;
		}

		std::cout << "\n\n* Blood Cells: " << countBloodCells << " Total: " << totalBloodCells << std::endl;
		std::cout << "Large: " << countLargeBloodCells << " Total Large BC: " << totalLargeBC << " Small: " << countSmallBloodCells << " White: " << countWhiteBloodCells << std::endl;
		std::cout << "* Enemies: " << countEnemies << std::endl;
		std::cout << "Bots: " << countNanoBots << " Green: " << countGreenVirus << " Orange: " << countOrangeVirus << " Blue: " << countBlueVirus << std::endl;
		std::cout << "* Enemy Weapons: " << countEnemyBullets << std::endl;
		std::cout << "En Laser: " << countEnLaser << " Fireball: " << countFireball << " Satellite: " << countVBullet << std::endl;
		std::cout << "* Power Ups: " << countPowerUps << std::endl;
		std::cout << "Health PU: " << countPUHealth << " Laser PU: " << countPULaser << " Rocket PU: " << countPURocket << " Timer PU: " << countPUtimer << " New Life PU: " << countPULife << std::endl;
		std::cout << "* Score Values: " << countScoreValues << std::endl;
		std::cout << "* Player Weapons: " << countNumPlayerWeapons << std::endl;
		std::cout << "P1 Laser: " << countP1Laser << " P2 Laser: " << countP2Laser << " P1 Ninja Star: " << countP1NStar << " P2 Ninja Star: " << countP2NStar << std::endl;
		std::cout << "Saws: " << countSaws << " P1 Rocket: " << countP1Rocket << " P2 Rocket: " << countP2Rocket << std::endl;
		std::cout << "Active Explosions: " << countExplosions << " Total: " << totalExplosions << std::endl;
	}

	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (listOfGameObjects[index]->getX() <= 0 - listOfGameObjects[index]->getWidth()) {
			if (listOfGameObjects[index]->getSubType() == BLOCKAGE) numBlockages--;
			//std::cout << "blockage check 2: " << numBlockages << std::endl;
			listOfGameObjects[index]->setAlive(false);
		}
	}

	// If player is offscreen and past the width of the blockage
	if (player1->getX() <= -player1->getWidth() - 10) {
		spawnPlayer(PLAYER_1);
		managePlayerHealth(PLAYER_1, 25);
	}
	if (player2->getX() <= -player2->getWidth() - 10) {
		spawnPlayer(PLAYER_2);
		managePlayerHealth(PLAYER_2, 25);
	}

	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {															// Erase Game Objects
																																// If the Player the score is for is dead, or the score is active for 2.5 seconds destroy it
		if ((listOfGameObjects[index]->getSubType() == PLAYER1_SCORE)) {
			if (SDL_GetTicks() > listOfGameObjects[index]->getTimerTracker() + 2500 || !player1->getAlive()) listOfGameObjects[index]->setAlive(false); // if the current time is more than the start time + 100, OR player 1 is dead
																																						//if (listOfGameObjects[index]->getAlive() == false) scoreTextP1counter--;											// Decrement the player 1 score text counter
		}
		else if ((listOfGameObjects[index]->getSubType() == PLAYER2_SCORE)) {
			if (SDL_GetTicks() > listOfGameObjects[index]->getTimerTracker() + 2500 || !player2->getAlive()) listOfGameObjects[index]->setAlive(false); // if the current time is more than the start time + 100, OR player 2 is dead
																																						//if (listOfGameObjects[index]->getAlive() == false) scoreTextP2counter--;											// Decrement the player 2 score text counter
		}

		if (!listOfGameObjects[index]->getAlive()) {
			// Decrement the number active on screen
			if (listOfGameObjects[index]->getSubType() == LARGE_BLOOD_CELL) {
				activeBloodCells--;																								// Decrement active blood cells when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), BLOOD_EXPLOSION);			// Expode Blood Cell when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == SMALL_BLOOD_CELL) activeSmallBloodCells--;						// Decrement active small blood cells when one is deleted
			else if (listOfGameObjects[index]->getSubType() == WHITE_BLOOD_CELL) activeWhiteBloodCells--;						// Decrement active white blood cells when one is deleted
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
				activeEnemyShips--;																								// Decrement active enemy ships when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY(), FIRE_EXPLOSION);					// Expode Player Weapon when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
				activeEnemyVirus--;																								// Decrement active enemy Virus when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX() - 25, listOfGameObjects[index]->getY(), GREEN_VIRUS_EXPLOSION);	// Expode Blood Cell when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {
				activeEnemyVirus--;																								// Decrement active enemy Virus when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX() - 25, listOfGameObjects[index]->getY(), ORANGE_VIRUS_EXPLOSION);// Expode Blood Cell when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				activeEnemyVirus--;																								// Decrement active enemy Virus when one is deleted
				spawnExplosion(listOfGameObjects[index]->getX() - 25, listOfGameObjects[index]->getY(), BLUE_VIRUS_EXPLOSION);	// Expode Blood Cell when it is destroyed
			}
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P1) {
				player1->setProjectileActive(false);
				if (player1->getKillRocket()) listOfGameObjects[index]->setAlive(false);
			}
			else if (listOfGameObjects[index]->getSubType() == ROCKET_P2) {
				player2->setProjectileActive(false);
				if (player2->getKillRocket()) listOfGameObjects[index]->setAlive(false);
			}
			else if (listOfGameObjects[index]->getType() == SMALL_VIRUS) activeEnemyVirusSmall--;
			else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P1) {
				ninjaStarP1Missed++;
				ninjaStarP1Counter--;
			}
			else if (listOfGameObjects[index]->getSubType() == NINJA_STAR_P2) {
				ninjaStarP2Missed++;
				ninjaStarP2Counter--;
			}
		}

		// Erase The Object From The List
		if (!listOfGameObjects[index]->getAlive()) {
			//std::cout << "kill " << listOfGameObjects[index]->getName() << std::endl;
			listOfGameObjects[index]->m_Texture.free();
			listOfGameObjects.erase(listOfGameObjects.begin() + index);
			index--;
		}
	}// end for
}


/*
2017/02/06 Added function to handle player scoring, setting the scores for Players 1 and 2
*/
void Level::managePlayerScores(int score, int player, int type) {				// add get name
	if (player == PLAYER_1) player1->setScore(player1->getScore() + score);
	else if (player == PLAYER_2) player2->setScore(player2->getScore() + score);

	if (type == PLAYER_WEAPON) std::cout << "Enemy Ship Killed by Player " << player << std::endl;
	else if (type == SAW1) std::cout << "Enemy Ship Killed by Player 1 Saw!\n";
	else if (Game::Instance()->twoPlayer && type == SAW2) std::cout << "Enemy Ship Killed by Player 2 Saw!\n";
}

void Level::managePlayerHealth(int player, int damage, std::string name) {
	if (player == PLAYER_1) {
		gPlayer1Texture.setFlash(true);								// Flash on collision with Game Object
		player1->setHealth(player1->getHealth() - damage);

		if (player1->getNumLives() <= 0) {							// if the number of lives 0 or less
			player1->setSawActive(false);							// kill the active saw
			player1->setAlive(false);								// kill the player
		}
		else if (player1->getHealth() <= 0) {	// if player health is 0 or less AND player is alive
			player1->setNumLives(player1->getNumLives() - 1);
			if (player1->getNumLives() > 0) {
				spawnPlayer(PLAYER_1);
				player1->setHealth(100);
			}
		}
	}
	else if (Game::Instance()->twoPlayer && player == PLAYER_2) {
		gPlayer2Texture.setFlash(true);								// Flash on collision with Game Object
		player2->setHealth(player2->getHealth() - damage);

		if (player2->getNumLives() <= 0) {
			player2->setSawActive(false);
			player2->setAlive(false);
		}
		//else if (player2->getHealth() <= 0 && player2->getAlive()) {
		else if (player2->getHealth() <= 0) {
			player2->setNumLives(player2->getNumLives() - 1);
			if (player2->getNumLives() > 0) {
				spawnPlayer(PLAYER_2);
				player2->setHealth(100);
			}
		}
		if (SDL_NumJoysticks() > 0) {
			if (player2->getAlive() && SDL_HapticRumblePlay(Game::Instance()->gControllerHaptic, 0.9, 500) != 0) {	// Haptic (Force Feedback) Play rumble at 75% strenght for 500 milliseconds 2017/01/20 Moved to player 2, was rumbling for both players
				printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
			}
		}
	}

	if (damage > 0) {
		//Audio::Instance()->explosionFX();
		Audio::Instance()->playFX("explosionFX");
		if (player == PLAYER_1) std::cout << "Player 1 has collided with " << name << "! Health: " << player1->getHealth() << std::endl;
		if (player == PLAYER_2) std::cout << "Player 2 has collided with " << name << "! Health: " << player2->getHealth() << std::endl;
	}
	else if (damage < 0) std::cout << "Player" << player << " has received a power up of " << -damage << " health";

	//if (SDL_HapticRumblePlay(gControllerHaptic, 0.9, 500) != 0) {	// Haptic (Force Feedback) Play rumble at 75% strenght for 500 milliseconds
	//	printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
	//}
}

/*
	The collisionCheck function, checks for collisions between objects, and triggers appropriate events

	Checks for: collisions between player ships and objects, player weapons and enemies, enemy weapons and player
	player weapons and obstacles, large blood cells, power ups etc.
*/
void Level::collisionCheck() {
	// Check if Player 1 or 2 has collided with another game object
	for (unsigned int index = 0; index != listOfGameObjects.size(); ++index) {
		if (checkCollision(player1->getCollider(), listOfGameObjects[index]->getCollider()) == true) {
			player1->setScore(player1->getScore() + listOfGameObjects[index]->getScore());

			// If the players saw is active
			if (player1->getSawActive()) {
				if (listOfGameObjects[index]->getSubType() == LARGE_BLOOD_CELL) listOfGameObjects[index]->setAlive(false);	// If the players saw is active and it collides with a large blood cell, the blood cell is destroyed
				if (listOfGameObjects[index]->getSubType() == BLOCKAGE) listOfGameObjects[index]->setAlive(false);
			}

			//if (listOfGameObjects[index]->getSubType() == BLOCKAGE) player1->setVelX(player1->getVelX() - player1->getVelX() -BACKGROUND_SCROLL_SPEED);
			if (listOfGameObjects[index]->getSubType() == BLOCKAGE) {
				player1->setX((player1->getX() + listOfGameObjects[index]->getVelX()) - player1->getVelX());
				player1->moveLeft(true);
			}

			// Power Ups
			if (listOfGameObjects[index]->getType() == POWER_UP) {
				if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH) {
					managePlayerHealth(PLAYER_1, -listOfGameObjects[index]->getDamage());
					infoMessage("Player 1 has increased their health!!!", PLAYER_1);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER) {
					player1->setLaserGrade(player1->getLaserGrade() + 1);
					//Laser1 = true;
					infoMessage("Player 1 has upgraded their laser!!!", PLAYER_1);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_ROCKET) {
					player1->setNumRockets(player1->getNumRockets() + 1);
					infoMessage("Player 1 has collected a Rocket!!! Rockets: " + std::to_string(player1->getNumRockets()), PLAYER_1);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_CHECKPOINT) {
					infoMessage("Checkpoint Reached!!!");
					std::cout << "Checkpoint reached!\n";
					countdownTimer += 20;
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LIVES) {
					if (player1->getNumLives() < MAX_NUM_LIVES) {
						player1->setNumLives(player1->getNumLives() + 1);
						infoMessage("Player 1 has increased their number of lives!!!", PLAYER_1);
					}
					else
						infoMessage("Player 1 has already has the max number of lives!!!", PLAYER_1);
				}

				listOfGameObjects[index]->setAlive(false);

				Audio::Instance()->playFX("bonusP1FX");
			}
			// Enemies
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER || listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET || listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) {
				managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getDamage());															// Score used to inicate amount to remove from health --> need to add damage variable
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
				if (player1->getSawActive()) {
					listOfGameObjects[index]->setAlive(false);																				// If saw is active kill that enemy
				}
				else
					if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getDamage() / 5, "Enemy Ship");	// Take off 5 health
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
					spawnEnemyVirus(VIRUS_SMALL_GREEN, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					spawnEnemyVirus(VIRUS_SMALL_GREEN, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {
					spawnEnemyVirus(VIRUS_SMALL_ORANGE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					spawnEnemyVirus(VIRUS_SMALL_ORANGE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					listOfGameObjects[index]->setTimer(0);
				}
				else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
					spawnEnemyVirus(VIRUS_SMALL_BLUE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					spawnEnemyVirus(VIRUS_SMALL_BLUE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getDamage() / 3, "Enemy Virus");	// If player 1 isn't flashing, Take off 5 health
			}

			// Make sure the player isn't colliding with it's own weapon or a blood cell
			if (listOfGameObjects[index]->getType() != PLAYER_WEAPON && listOfGameObjects[index]->getType() != BLOOD_CELL && listOfGameObjects[index]->getSubType() != BLOCKAGE)
				listOfGameObjects[index]->setAlive(false);	// If it's not a collision between a player and a player weapon or a blood cell
		}

		// Check Player 2 collisions
		else if (Game::Instance()->twoPlayer && checkCollision(player2->getCollider(), listOfGameObjects[index]->getCollider()) == true) {
			player2->setScore(player2->getScore() + listOfGameObjects[index]->getScore());
			// If the players saw is active
			if (player2->getSawActive()) {
				if (listOfGameObjects[index]->getSubType() == LARGE_BLOOD_CELL) listOfGameObjects[index]->setAlive(false);	// If the players saw is active and it collides with a large blood cell, the blood cell is destroyed
				if (listOfGameObjects[index]->getSubType() == BLOCKAGE) listOfGameObjects[index]->setAlive(false);
			}

			//if (listOfGameObjects[index]->getSubType() == BLOCKAGE) player1->setVelX(player1->getVelX() - player1->getVelX() -BACKGROUND_SCROLL_SPEED);
			if (listOfGameObjects[index]->getSubType() == BLOCKAGE) {
				//player2->setVelX(-BACKGROUND_SCROLL_SPEED);
				player2->setX((player2->getX() + listOfGameObjects[index]->getVelX()) - player2->getVelX());
				player2->moveLeft(true);
			}

			// Power Ups
			if (listOfGameObjects[index]->getType() == POWER_UP) {
				if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH) {
					managePlayerHealth(PLAYER_2, -listOfGameObjects[index]->getDamage());
					infoMessageP2Counter = 0;
					infoMessage("Player 2 has increased their health!!!", PLAYER_2);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER) {
					player2->setLaserGrade(player2->getLaserGrade() + 1);
					infoMessage("Player 2 has upgraded their laser!!!", PLAYER_2);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_ROCKET) {
					player2->setNumRockets(player2->getNumRockets() + 1);
					infoMessage("Player 2 has collected a Rocket!!! Rockets: " + std::to_string(player2->getNumRockets()), PLAYER_2);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_CHECKPOINT) {
					infoMessage("Checkpoint Reached!!!");
					std::cout << "Checkpoint reached!\n";
					countdownTimer += 20;
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LIVES) {
					if (player2->getNumLives() < MAX_NUM_LIVES) {
						player2->setNumLives(player2->getNumLives() + 1);
						infoMessage("Player 2 has increased their number of lives!!!", PLAYER_2);
					}
					else
						infoMessage("Player 2 has already has the max number of lives!!!", PLAYER_2);
				}

				listOfGameObjects[index]->setAlive(false);

				Audio::Instance()->playFX("bonusP2FX");
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER || listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET || listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) {
				managePlayerHealth(PLAYER_2, listOfGameObjects[index]->getDamage());	// Score used to inicate amount to remove from health --> need to add damage variable
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
				if (player2->getSawActive()) {
					listOfGameObjects[index]->setAlive(false);																				// If saw is active kill that enemy
				}
				else
					if (!gPlayer2Texture.getFlash()) managePlayerHealth(PLAYER_2, listOfGameObjects[index]->getDamage() / 5, "Enemy Ship");	// Take off 5 health
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				if (player2->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
					spawnEnemyVirus(VIRUS_SMALL_GREEN, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					spawnEnemyVirus(VIRUS_SMALL_GREEN, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (player2->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {
					spawnEnemyVirus(VIRUS_SMALL_ORANGE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					spawnEnemyVirus(VIRUS_SMALL_ORANGE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					listOfGameObjects[index]->setTimer(0);
				}
				else if (player2->getSawActive() && listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
					spawnEnemyVirus(VIRUS_SMALL_BLUE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					spawnEnemyVirus(VIRUS_SMALL_BLUE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (!gPlayer2Texture.getFlash()) managePlayerHealth(PLAYER_2, listOfGameObjects[index]->getDamage() / 3, "Enemy Virus");	// If player 2 isn't flashing, Take off 5 health
			}


			//	Certain game objects should not be destroyed when colliding with the player
			//	Blood Cells, Blockage, and Enemy Boss

			if (listOfGameObjects[index]->getType() != PLAYER_WEAPON && listOfGameObjects[index]->getType() != BLOOD_CELL && listOfGameObjects[index]->getSubType() != BLOCKAGE && listOfGameObjects[index]->getSubType() != ENEMY_BOSS)
				listOfGameObjects[index]->setAlive(false);
		}
	}

	// Check Weapons Sub-Type For Collisions With Enemy Sub-Type
	for (unsigned int weaponIndex = 0; weaponIndex != listOfGameObjects.size(); weaponIndex++) {
		for (unsigned int enemyIndex = 0; enemyIndex != listOfGameObjects.size(); enemyIndex++) {
			// If a white blood cell collides with a small virus, the small virus is destroyed
			if (listOfGameObjects[weaponIndex]->getSubType() == WHITE_BLOOD_CELL && listOfGameObjects[enemyIndex]->getType() == SMALL_VIRUS) {
				if (checkCollision(listOfGameObjects[weaponIndex]->getCollider(), listOfGameObjects[enemyIndex]->getCollider()) == true) {
					listOfGameObjects[enemyIndex]->setAlive(false);	// Destroy the small virus
					//infoMessage("DESTROY BLUE VIRUS");
				}
			}

			// 2017/02/19 If there is a collison between ninja stars and large blood cells
			if ((listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P1 || listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P2) && listOfGameObjects[enemyIndex]->getSubType() == LARGE_BLOOD_CELL) {
				if (checkCollision(listOfGameObjects[weaponIndex]->getCollider(), listOfGameObjects[enemyIndex]->getCollider()) == true) {
					listOfGameObjects[enemyIndex]->setAlive(false);
					listOfGameObjects[weaponIndex]->setAlive(false);	// DESTROY
				}
			}

			if (listOfGameObjects[weaponIndex]->getType() == PLAYER_WEAPON && listOfGameObjects[enemyIndex]->getType() == ENEMY_OBJECT) {
				if (checkCollision(listOfGameObjects[weaponIndex]->getCollider(), listOfGameObjects[enemyIndex]->getCollider()) == true) {
					if (listOfGameObjects[enemyIndex]->getSubType() != ENEMY_BOSS) {
						// 2017/02/22 Updated messages to include name
						if (listOfGameObjects[weaponIndex]->getSubType() == ROCKET_P1) {
							infoMessage("Impact!!! Missile has taken out " + listOfGameObjects[enemyIndex]->getName() + "! Score +" + std::to_string(player1->getBonusScore()), PLAYER_1);
							managePlayerScores(player1->getBonusScore(), PLAYER_1, listOfGameObjects[weaponIndex]->getSubType());

							if (listOfGameObjects[enemyIndex]->getSubType() == ENEMY_BOSS) listOfGameObjects[enemyIndex]->setHealth(listOfGameObjects[enemyIndex]->getHealth() - 25);
						}
						else if (Game::Instance()->twoPlayer && listOfGameObjects[weaponIndex]->getSubType() == ROCKET_P2) {
							infoMessage("Impact!!! Missile has taken out" + listOfGameObjects[enemyIndex]->getName() + "! Score +" + std::to_string(player2->getBonusScore()), PLAYER_2);
							managePlayerScores(player2->getBonusScore(), PLAYER_2, listOfGameObjects[weaponIndex]->getSubType());

							if (listOfGameObjects[enemyIndex]->getSubType() == ENEMY_BOSS) listOfGameObjects[enemyIndex]->setHealth(listOfGameObjects[enemyIndex]->getHealth() - 25);
						}

						//	Virus enemies can be cut in half using the Players Saw or Ninja Star weapons
						//	If a virus is cut in half, spawn 2 smaller virus

						else if (listOfGameObjects[weaponIndex]->getSubType() == SAW1 || listOfGameObjects[weaponIndex]->getSubType() == SAW2 || listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P1 || listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P2) {
							if (listOfGameObjects[enemyIndex]->getSubType() == VIRUS_GREEN) {
								spawnEnemyVirus(VIRUS_SMALL_GREEN, listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY());
								spawnEnemyVirus(VIRUS_SMALL_GREEN, listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY());
								activeEnemyVirusSmall += 2;																							// Increment the number of active small enemy virus
							}
							else if (listOfGameObjects[enemyIndex]->getSubType() == VIRUS_ORANGE) {
								spawnEnemyVirus(VIRUS_SMALL_ORANGE, listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY());
								spawnEnemyVirus(VIRUS_SMALL_ORANGE, listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY());
								activeEnemyVirusSmall += 2;																							// Increment the number of active small enemy virus
							}
							else if (listOfGameObjects[enemyIndex]->getSubType() == VIRUS_BLUE) {
								spawnEnemyVirus(VIRUS_SMALL_BLUE, listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY());
								spawnEnemyVirus(VIRUS_SMALL_BLUE, listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY());
								activeEnemyVirusSmall += 2;																							// Increment the number of active small enemy virus
							}
						}

						managePlayerScores(listOfGameObjects[enemyIndex]->getScore(), listOfGameObjects[weaponIndex]->getPlayer(), listOfGameObjects[weaponIndex]->getSubType());		// 2017-02-06 Add to players score

						pointsValueCounter = 0;
						displayScoreForObject(listOfGameObjects[enemyIndex]->getX(), listOfGameObjects[enemyIndex]->getY(), listOfGameObjects[enemyIndex]->getScore(), listOfGameObjects[weaponIndex]->getPlayer());	// Display Score


						if (listOfGameObjects[enemyIndex]->getSubType() != BLOCKAGE || listOfGameObjects[enemyIndex]->getSubType() != ENEMY_BOSS)
							listOfGameObjects[enemyIndex]->setAlive(false);
					}// If it is the enemy boss
					else {

						// Health points deducted for different weapons
						if (listOfGameObjects[weaponIndex]->getSubType() == ROCKET_P1) {
							listOfGameObjects[enemyIndex]->setHealth(listOfGameObjects[enemyIndex]->getHealth() - 20);
						}
						else if (listOfGameObjects[weaponIndex]->getSubType() == ROCKET_P2) {
							listOfGameObjects[enemyIndex]->setHealth(listOfGameObjects[enemyIndex]->getHealth() - 20);
						}
						else if (listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P1) {
							listOfGameObjects[enemyIndex]->setHealth(listOfGameObjects[enemyIndex]->getHealth() - 2);
						}
						else if (listOfGameObjects[weaponIndex]->getSubType() == NINJA_STAR_P2) {
							listOfGameObjects[enemyIndex]->setHealth(listOfGameObjects[enemyIndex]->getHealth() - 2);
						}
						else if (listOfGameObjects[weaponIndex]->getSubType() == LASER_P1) {
							listOfGameObjects[enemyIndex]->setHealth(listOfGameObjects[enemyIndex]->getHealth() - 1);
						}
						else if (listOfGameObjects[weaponIndex]->getSubType() == LASER_P2) {
							listOfGameObjects[enemyIndex]->setHealth(listOfGameObjects[enemyIndex]->getHealth() - 1);
						}

						// If it is not a saw in contact with the enemy spawn an explosion
						if (listOfGameObjects[weaponIndex]->getSubType() != SAW1 && listOfGameObjects[weaponIndex]->getSubType() != SAW2)
							spawnExplosion(listOfGameObjects[weaponIndex]->getX(), listOfGameObjects[weaponIndex]->getY(), FIRE_EXPLOSION);

						// If the Enemy Boss health is less than or equal to 0, kill it
						if (listOfGameObjects[enemyIndex]->getHealth() <= 0) {
							listOfGameObjects[enemyIndex]->setAlive(false);
							levelOver = true;
						}
					}

					listOfGameObjects[weaponIndex]->setAlive(false);	// DESTROY the player weapon
				} // end not enemy boss
			}
		}
	}
}


// Reset a level or the game
void Level::resetGame(int currentLevel) {
	frames = 0;					// Animation Frames
	checkpointsSpawned = 0;		// Reset number of checkpoints spawned

								// Reset the map of the professor
								//setViewport(mapViewport, (SCREEN_WIDTH - 120) / 2, 600, 120, 88);	// Reset the map to small size // 2017/03/20 Moved to HUD
								//Texture::Instance()->modifyAlpha(255, "profID");					// 2017/03/20 Moved to HUD
	headsUpDisplay.resetHUD();											// 2017/03/20 Reset HUD

	std::string finalScores = "";										// Reset the final scores message
	std::string gameWinners = "";										// Reset the game winner message

	Game::Instance()->setCurrentLevel(currentLevel);										// Set the current level

																		//Texture::Instance()->loadFromRenderedTextID("Level " + std::to_string(currentLevel), "levelID", { 0, 255, 0, 255 }, TTF_OpenFont("Fonts/Retro.ttf", 20));
	std::cout << "Current Level Rendering: " << currentLevel << std::endl;

	// Reset the number of objects on screen
	activeBloodCells = 0;
	activeWhiteBloodCells = 0;
	activeSmallBloodCells = 0;
	activePowerUps = 0;
	activeEnemyShips = 0;
	activeEnemyVirusSmall = 0;
	activeEnemyBoss = 0;

	//if (currentLevel == MENU)
	//displayGameIntro = DISPLAY_GAME_INTRO_SCREENS;
	//displayLevelIntro = DISPLAY_LEVEL_INTRO_SCREENS;
	backgroundLoopCounter = 0;
	//	scrollingOffset = 0;						// 2017/03/21 Moved to ScrollingBackground class
	//weaponScrolling = 60;						// 2017/03/20 Moved to HUD class

	// Information Messages
	infoMessageP1Counter = MESSAGE_TIME;		// Time to display player 1 notification messages
	infoMessageP2Counter = MESSAGE_TIME;		// Time to display player 2 notification messages
	infoMessageCounter = MESSAGE_TIME;			// Time to display player 2 notification messages
	infoMessageMapCounter = MESSAGE_TIME_MAP;	// Time to display player 2 notification messages
	pointsValueCounter = MESSAGE_TIME;			// Time to display score for killing Enemy message
	infoMessageP1 = "";							// Reset the player 1 notification message
	infoMessageP2 = "";							// Reset the player 2 notification message
	infoMessageGeneral = "";					// Reset the General notification message
	pointsValue = "";							// Reset the points value for destroyed Enemy message

	gamerOverMessageDisplayCounter = 0;

	// Timer
	lastTime = 0;
	currentTime = SDL_GetTicks();
	countdownTimer = GAME_TIMER;				// Reset the countdown timer
	gPlayer1Texture.setFlash(false);
	gTimeTextTexture.setFlash(false);			// Reset the timer flash
	headsUpDisplay.resetHUD();

	// Reset Players
	if (currentLevel <= 1) {					// If the level isn't progressing
		player1->setScore(0);					// Reset player 1 score
		player1->setNumLives(MAX_NUM_LIVES);	// Set the players lives to the maximum number of lives set in _TestData.h
		//nameEntered = false;					// No name entered yet for player
	}

	player1->setShieldActive(true);
	player1->setSawActive(false);
	player1->setSpeedBoost(false);
	player1->setAlive(false);
	//player1->setHealth(player1->getMaxHealth());
	player1->setVelX(0);
	player1->setVelY(0);
	player1->setTimer(ROCKET_TIMER);
	player1->setNumRockets(3);					// FIX 2017/03/02

	if (Game::Instance()->twoPlayer) {
		if (currentLevel <= 1) {
			player2->setScore(0);				// Reset player 2 score
			player2->setNumLives(MAX_NUM_LIVES);
		}
		gPlayer2Texture.setFlash(false);

		player2->setShieldActive(true);
		player2->setSawActive(false);
		player2->setSpeedBoost(false);

		player2->setAlive(false);
		//player2->setHealth(player2->getMaxHealth());

		player2->setVelX(0);
		player2->setVelY(0);
		player2->setTimer(ROCKET_TIMER);
		player2->setNumRockets(3);				// FIX 2017/03/02
	}

	gameOverTimer = 3;

	// Delete all objects on screen
	if (gameOver || levelOver) {
		listOfGameObjects.clear();		// Scores, Power Ups, Explosions
		gameOverTimer = 5;
		//listOfScoreTextures.clear();
	}

	levelOver = false;
	gameOver = false;
	noTime = false;
}

void setViewport(SDL_Rect &rect, int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

