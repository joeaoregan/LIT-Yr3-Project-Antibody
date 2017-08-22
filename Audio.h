#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>				// 2017/01/09 JOE: SOUND - library we use to make audio playing easier
#include <vector>

class Audio {
public:
	//Audio();							// Initializes the variables
	//~Audio();


	//The music that will be played
	Mix_Music *gMusic1 = NULL;				// Mix_Music: Data type for music
	Mix_Music *gMusic2 = NULL;
	Mix_Music *gMusic3 = NULL;
	unsigned int currentSong;						// Play a random song when the game starts

	std::vector<Mix_Music*> listOfMusic;	// List of Music tracks

	//The sound effects that will be used (pointers)
	Mix_Chunk *gLaserFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gLaserFX2 = NULL;		// 2017/01/17 Player 2 Laser
	Mix_Chunk *gNinjaFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gNinjaFX2 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gLaserEFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gExplosionFX = NULL;		// Explosion sound fx
	Mix_Chunk *gSawFX = NULL;			// Saw sound fx

	void music();

	void laserFX_P1();
	void laserFX_P2();
	void ninjaFX_P1();
	void ninjaFX_P2();
	void sawFX();
	void laserFX_Enemy();
	void explosionFX();

	//int musicForward(int song, int numSongs);
	//int musicBack(int song, int numSongs);
	void musicForward();
	void musicBack();
	void playMusic();

	void destroy();
};

#endif
