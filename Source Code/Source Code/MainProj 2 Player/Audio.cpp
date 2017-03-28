/*
	2017/02/17 Added identifyTrack() function to dentify the song current playing and display the name on screen
				Started adding original music tracks to the game
	2017/02/09 Separated audio to it's own class
				Fixed music not playing problem
*/
/*
	AUDIO:

	Handles game music and sound effects. 
	
	There is a list of music objects to contain the songs. Tracks can be skipped using the keyboard and game controller. 
	An information message indicates the current track playing.

	Sound effects are played when different objects are spawned such as Play and Enemy weapons, and explosions.
*/
#include "Audio.h"
#include <iostream>

Audio* Audio::s_pInstance;

Audio::Audio() {
	Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2));
}

Audio::~Audio() {
	Mix_CloseAudio();
}

bool Audio::loadMediaAudio() {
	bool success = true;

	// Load the laser FX for Player 1
	gLaserFX1 = Mix_LoadWAV("Audio/Laser1.wav");														// Load sound effects
	if (gLaserFX1 == NULL) {
		printf("Failed to load P1 laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Load the laser FX for Player 2
	gLaserFX2 = Mix_LoadWAV("Audio/Laser2.wav");														// Load sound effects
	if (gLaserFX2 == NULL) {
		printf("Failed to load P2 laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Load the Ninja Star FX for Player 1
	gNinjaFX1 = Mix_LoadWAV("Audio/Swoosh1.wav");														// Load sound effects
	if (gNinjaFX1 == NULL) {
		printf("Failed to load P1 ninja star sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Load the Ninja Star FX for Player 2
	gNinjaFX2 = Mix_LoadWAV("Audio/Swoosh2.wav");														// Load sound effects
	if (gNinjaFX2 == NULL) {
		printf("Failed to load P2 ninja star sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Load the Laser FX for Enemy Ships
	gLaserEFX = Mix_LoadWAV("Audio/LaserEnemy.wav");													// Load sound effects
	if (gLaserEFX == NULL) {
		printf("Failed to load enemy laser beam sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Load the Explosion FX
	gExplosionFX = Mix_LoadWAV("Audio/explosion.wav");													// Load sound effects
	if (gExplosionFX == NULL) {
		printf("Failed to load explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Load the Saw FX for player ships
	gSawFX = Mix_LoadWAV("Audio/Saw.wav");																// Load sound effects
	if (gSawFX == NULL) {
		printf("Failed to load Saw sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	return success;
}

void Audio::music() {
	//Load music
	/*gMusic1 = Mix_LoadMUS("Audio/GameSong1.wav");												// Load music
	if (gMusic1 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
	}*/
	/*gMusic2 = Mix_LoadMUS("Audio/GameSong2.mp3");												// Load music
	if (gMusic2 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
	}*/
	gMusic1 = Mix_LoadMUS("OriginalMusic/BloodStream.wav");												// Load music
	if (gMusic1 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gMusic2 = Mix_LoadMUS("OriginalMusic/2TheFirstStep.mp3");									// Load music
	if (gMusic2 == NULL) {
		printf("Failed to load The First Step music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gMusic3 = Mix_LoadMUS("OriginalMusic/2Virus.mp3");											// Load music
	if (gMusic3 == NULL) {
		printf("Failed to load Virus music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gMusic4 = Mix_LoadMUS("OriginalMusic/Blood Level.mp3");											// Load music
	if (gMusic4 == NULL) {
		printf("Failed to load Virus music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Add songs to vector
	listOfMusic.push_back(gMusic1);
	listOfMusic.push_back(gMusic2);
	listOfMusic.push_back(gMusic3);
	listOfMusic.push_back(gMusic4);

	currentSong = rand() % NUMBER_OF_SONGS;				// Play a random song on start up

	Mix_PlayMusic(listOfMusic[currentSong], -1);		// Play the currently selected song
}

int Audio::musicForwardSongName() {						// Pick next track on the list
	if (currentSong + 1 < listOfMusic.size())			// If the current song number (0 number start value) is less than the number of tracks on the list
		currentSong++;									// go to next track on list
	else
		currentSong = 0;								// or else go back to start of list

	Mix_PlayMusic(listOfMusic[currentSong], -1);

	
	if (currentSong == 0) std::cout << "current song: Blood Stream" << std::endl;
	else if (currentSong == 1) std::cout << "Current Song: The Last Step" << std::endl;
	else if (currentSong == 2) std::cout << "Current Song: Virus" << std::endl;
	else if (currentSong == 3) std::cout << "Current Song: Blood Level" << std::endl;

	return currentSong;
}

int Audio::musicBackSongName() {						// Pick previous track on the list
	if (currentSong > 0)
		currentSong--;
	else
		currentSong = listOfMusic.size() - 1;

	Mix_PlayMusic(listOfMusic[currentSong], -1);

	return currentSong;
}

void Audio::musicForward() {							// Pick next track on the list
	if (currentSong + 1 < listOfMusic.size())			// If the current song number (0 number start value) is less than the number of tracks on the list
		currentSong++;									// go to next track on list
	else
		currentSong = 0;								// or else go back to start of list

	Mix_PlayMusic(listOfMusic[currentSong], -1);
}
void Audio::musicBack() {								// Pick previous track on the list
	if (currentSong > 0)
		currentSong--;
	else
		currentSong = listOfMusic.size() - 1;

	Mix_PlayMusic(listOfMusic[currentSong], -1);
}

int Audio::playMusic() {
	Mix_PlayMusic(listOfMusic[currentSong], -1);
	return currentSong;
}

/*
int Audio::musicForward(int song, int numSongs) {		// Pick next track on the list
	if (song + 1 < numSongs)							// If the current song number (0 number start value) is less than the number of tracks on the list
		song++;											// go to next track on list
	else
		song = 0;										// or else go back to start of list

	//Mix_PlayMusic(listOfMusic[song], -1);
	return song;
}
int Audio::musicBack(int song, int numSongs) {			// Pick previous track on the list
	if (song > 0)
		song--;
	else
		song = numSongs - 1;

	//Mix_PlayMusic(listOfMusic[song], -1);
	return song;
}
*/

void Audio::laserFX_P1() {
	//if (player == 1) Mix_PlayChannel(-1, gLaserFX1, 0);		// Different sound for each player laser
	Mix_PlayChannel(-1, gLaserFX1, 0);		// Different sound for each player laser				
}

void Audio::laserFX_P2() {
	Mix_PlayChannel(-1, gLaserFX2, 0);		// Different sound for each player laser				
}

void Audio::ninjaFX_P1() {
	Mix_PlayChannel(-1, gNinjaFX1, 0);
}

void Audio::ninjaFX_P2() {
	Mix_PlayChannel(-1, gNinjaFX2, 0);
}

void Audio::sawFX() {
	Mix_PlayChannel(-1, gSawFX, 0);
}

void Audio::laserFX_Enemy() {
	Mix_PlayChannel(-1, gLaserEFX, 0);
}

void Audio::explosionFX() {
	Mix_PlayChannel(-1, gExplosionFX, 0);		// Play sound on explosion
}

void Audio::destroy() {
	// Free the laser from memory
	Mix_FreeChunk(gLaserFX1);		// Free a sound effect
	gLaserFX1 = NULL;
	Mix_FreeChunk(gLaserFX2);		// Free a sound effect
	gLaserFX2 = NULL;
	Mix_FreeChunk(gNinjaFX1);		// Free a sound effect
	gNinjaFX1 = NULL;
	Mix_FreeChunk(gNinjaFX2);		// Free a sound effect
	gNinjaFX2 = NULL;
	//Free the sound effects
	Mix_FreeChunk(gLaserEFX);		// Free a sound effect
	gLaserEFX = NULL;
	Mix_FreeChunk(gExplosionFX);	// Free a sound effect
	gExplosionFX = NULL;
	Mix_FreeChunk(gSawFX);			// Free a sound effect
	gSawFX = NULL;

	
	//Free the music
	Mix_FreeMusic(gMusic1);	// Free music
	gMusic1 = NULL;
	Mix_FreeMusic(gMusic2);	// Free music
	gMusic2 = NULL;
	Mix_FreeMusic(gMusic3);	// Free music
	gMusic3 = NULL;
	Mix_FreeMusic(gMusic4);	// Free music
	gMusic4 = NULL;
	//Mix_FreeMusic(gMusic5);	// Free music
	//gMusic5 = NULL;
}