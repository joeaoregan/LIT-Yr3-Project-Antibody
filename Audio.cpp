#include "Audio.h"
#include <iostream>

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
	gMusic1 = Mix_LoadMUS("Audio/GameSong1.wav");											// Load music
	if (gMusic1 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gMusic2 = Mix_LoadMUS("Audio/GameSong2.mp3");											// Load music
	if (gMusic2 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gMusic3 = Mix_LoadMUS("Audio/GameSong3.mp3");											// Load music
	if (gMusic3 == NULL) {
		printf("Failed to load rage music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Add songs to vector
	listOfMusic.push_back(gMusic1);						// Add tracks to the music array
	listOfMusic.push_back(gMusic2);
	listOfMusic.push_back(gMusic3);

	currentSong = rand() % 3;							// Play a random song on start up

	Mix_PlayMusic(listOfMusic[currentSong], -1);		// Play the currently selected song
}
void Audio::musicForward() {								// Pick next track on the list
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

void Audio::playMusic() {
	Mix_PlayMusic(listOfMusic[currentSong], -1);
}

/*
int Audio::musicForward(int song, int numSongs) {								// Pick next track on the list
	if (song + 1 < numSongs)			// If the current song number (0 number start value) is less than the number of tracks on the list
		song++;									// go to next track on list
	else
		song = 0;								// or else go back to start of list

												//Mix_PlayMusic(listOfMusic[song], -1);
	return song;
}
int Audio::musicBack(int song, int numSongs) {								// Pick previous track on the list
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
}