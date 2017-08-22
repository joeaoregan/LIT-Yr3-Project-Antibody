/*
	2017/02/09 Separated audio to it's own class
				Fixed music not playing problem
*/

#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>				// 2017/01/09 JOE: SOUND - library we use to make audio playing easier
#include <vector>
#include <map>

#define NUMBER_OF_SONGS 5;			// Total number of songs in the playlist

class Audio {
public:
	static Audio* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Audio();
			return s_pInstance;
		}
		return s_pInstance;
	}

	//The music that will be played
	Mix_Music *gMusic1 = NULL;				// Mix_Music: Data type for music
	Mix_Music *gMusic2 = NULL;
	Mix_Music *gMusic3 = NULL;				// 2017/03/04 - Blood Stream
	Mix_Music *gMusic4 = NULL;				// 2017/02/17 - The First Step - Jimmy O'Regan
	Mix_Music *gMusic5 = NULL;				// 2017/02/22 - Virus - Joe O'Regan
	unsigned int currentSong;				// Play a random song when the game starts

	std::vector<Mix_Music*> listOfMusic;	// List of Music tracks

	//The sound effects that will be used (pointers)
	Mix_Chunk *gLaserFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gLaserFX2 = NULL;		// 2017/01/17 Player 2 Laser
	Mix_Chunk *gNinjaFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gNinjaFX2 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gLaserEFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gExplosionFX = NULL;		// Explosion sound fx
	Mix_Chunk *gSawFX = NULL;			// Saw sound fx

	bool loadMediaAudio();

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
	int musicForwardSongName();		// 2017/02/17 Returns an int to identify the song name and artist
	int musicBackSongName();		// 2017/02/17 Returns an int to identify the song name and artist
	int playMusic();

	void destroy();

private:
	Audio();						// Initializes the variables
	~Audio();

	//std::map<std::string, Mix_Chunk*> m_sfxs;
	//std::map<std::string, Mix_Music*> m_music;

	static Audio* s_pInstance;
};

#endif
