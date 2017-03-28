/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
	- Name:					Audio.h
	- Description:			Handles game music and sound effects
	- Information:
	- How it works:			There is a list of music objects to contain the songs. Tracks can be skipped using the keyboard and game controller.
							An information message indicates the current track playing.

							An array stores the path, id, and error identifier for each effect, this is then used to load the effects

							Sound effects are played when different objects are spawned such as Play and Enemy weapons, and explosions.
	- Log:

		2017/03/17			Combined music loading with effects loading, as only one function is necessary
							Added array for music information including path, id, and error message to display
							Changed playMusic() to playPauseMusic() and changed type to void from int as identifyTrack() is now in Audio class not Game
							Moved play / pause functionality to playMusic() function in Audio class
							Changed musicForwardSongName() and musicBackSongName() type to void from int, 
							as tracks are identified with identifyTrack() in Audio and not Game class
		2017/03/13			Added sound fx to a map
							Added effect for large blood cells being destroyed
							Added effect for Virus enemies ripping in 2
							Added seperate effects for players collecting power ups
		2017/03/07			Moved identifyTrack() function from Game class
		2017/02/17			Added identifyTrack() function to Game class to dentify the song current playing and display the name on screen
							Started adding original music tracks to the game
		2017/02/09			Separated audio to it's own class
							Fixed music not playing problem
-------------------------------------------------------------------------------------------------------------------------------------------------------*/

#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>					// 2017/01/09 JOE: SOUND - library we use to make audio playing easier
#include <vector>
#include <map>							// The sound effects are contained in a map and can be accessed using a unique id for each

//#define NUMBER_OF_SONGS 4;			// Total number of songs in the playlist
const int NUMBER_OF_SONGS = 4;			// Total number of songs in the playlist

class Audio {
public:
	// Audio Singleton so only one instance of Audio class exists in game, 
	// and easy access to the class and its functions
	static Audio* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Audio();
			return s_pInstance;
		}
		return s_pInstance;
	}		
	
	bool loadMediaAudio();								// Load the music and store in listOfMusic, and sound effects and add to m_sfxs map
	void destroy();										// Clear the audio files from memory when done

	void loadFX(std::string fileName, std::string id);	// 2017/03/13 Load sound fx to map
	void playFX(std::string id);						// 2017/03/13 Play sound fx from map identifying with id

	// Music controls
	void musicForwardSongName();						// 2017/02/17 Returns an int to identify the song name and artist, 2017/03/17 Changed type to void
	void musicBackSongName();							// 2017/02/17 Returns an int to identify the song name and artist, 2017/03/17 Changed type to void
	void playPauseMusic();								// Function to start music playing, 2017/03/17 Change to void, and added pause / play functionality from Game class
	void stopMusic();									// Function to stop music playing

	void identifyTrack(int songName);					// 2017/02/17 Identify the song playing 2017/03/07 Moved from game class

private:
	Audio();											// Constructor is private for use as a Singleton. Initializes the variables
	~Audio();											// Private destructor shuts down and cleans up the mixer API

	int currentSong;									// Play a random song when the game starts, 2017/03/17 Changed to Private

	std::vector<Mix_Music*> listOfMusic;				// List of Music tracks, 2017/03/17 Changed to Private
	std::map<std::string, Mix_Chunk*> m_sfxs;			// Sound effects are stored in a map can be accessed using the unique ID for each effect
	//std::map<std::string, Mix_Music*> m_music;		// Music is stored in array, the tracks are skipped forwards and backwards using an integer to identify the track

	static Audio* s_pInstance;							// Single instance of Audio used as singleton so only one instance exists thoughout the game
};

#endif#pragma once

/*
	//void music();						// Load the music files and add them to the listOfMusic array (2017/03/17 combined with loadMediaAudio() function)

	// Older Public variables used before for loop was added to load sound effects and music

	//The sound effects that will be used (pointers)
	Mix_Chunk *gLaserFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gLaserFX2 = NULL;		// 2017/01/17 Player 2 Laser
	Mix_Chunk *gNinjaFX1 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gNinjaFX2 = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gLaserEFX = NULL;		// 2017/01/09 JOE: SOUND - Mix_Chunk: Data type for short sounds
	Mix_Chunk *gExplosionFX = NULL;		// Explosion sound fx
	Mix_Chunk *gSawFX = NULL;			// Saw sound fx
	Mix_Chunk *gSplashFX = NULL;		// 2017/03/13 Splash sound fx for splitting blood cells
	Mix_Chunk *gRipFX = NULL;			// 2017/03/13 Rip sound fx for virus splitting in 2

	//The music that will be played
	Mix_Music *gMusic1 = NULL;			// 2017/03/04 - Blood Stream
	Mix_Music *gMusic2 = NULL;			// 2017/02/17 - The First Step - Jim O'Regan (Additional drum and bass Joe O'Regan)
	Mix_Music *gMusic3 = NULL;			// 2017/02/22 - Virus - Joe O'Regan
	Mix_Music *gMusic4 = NULL;			// 2017/03/07 - Blood Level - Joe O'Regan (Additional solo Jim O'Regan)


	// Older functions to play effects with easily identifiable function names

	void laserFX_P1();
	void laserFX_P2();
	void ninjaFX_P1();
	void ninjaFX_P2();
	void sawFX();
	void laserFX_Enemy();
	void explosionFX();
	void splashFX();
	void ripFX();

	// Older functions to skip music forwards / backwards

	int musicForward(int song, int numSongs);
	int musicBack(int song, int numSongs);
	void musicForward();
	void musicBack();
*/
