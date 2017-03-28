/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
	- Name:					Audio.cpp
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

#include "Audio.h"
#include "Game.h"
#include <iostream>

Audio* Audio::s_pInstance;												// Singleton so only one instance of Audio exists in the game, for easy access

const int NUM_SOUND_FX = 11;											// Number of sound effects in array

/* 
	2D Array of sound effects, with path to file, ID, and description for error messages
*/
std::string arrSoundEffects[NUM_SOUND_FX][3] = {
	// Game
	{ "Audio/Laser1.wav", "laser1FX", "Player 1 Laser Effect" },		// Player 1 laser effect
	{ "Audio/Laser2.wav", "laser2FX", "Player 2 Laser Effect" },		// Player 2 laser effect
	{ "Audio/Swoosh1.wav", "ninja1FX", "Player 1 Ninja Star Effect" },	// Player 1 ninja star effect
	{ "Audio/Swoosh2.wav", "ninja2FX", "Player 2 Ninja Star Effect" },	// Player 2 ninja star effect
	{ "Audio/LaserEnemy.wav", "enemyLaserFX", "Enemy Laser Effect" },	// Enemy laser effect
	{ "Audio/explosion.wav", "explosionFX", "Explosion Effect" },		// Explosion effect
	{ "Audio/Saw.wav", "sawFX", "Saw Effect" },							// Saw effect
	{ "Audio/Splash.wav", "splashFX", "Splash Effect" },				// Splash effect for blood cells being destroyed
	{ "Audio/Rip.wav", "ripFX", "Rip Effect" },							// Rip effect for when viruses split
	{ "Audio/Bonus1.wav", "bonusP1FX", "Player 1 Bonus Effect" },		// Player 1 bonus effect for collecting Power Up
	{ "Audio/Bonus2.wav", "bonusP2FX", "Player 2 Bonus Effect" }		// Player 2 bonus effect for collecting Power Up
};

/*
	2D Array storing the path, id, and error message for each music track
*/
std::string arrMusic[NUMBER_OF_SONGS][3] = {
	// Game
	{ "OriginalMusic/1TheFirstStep.mp3", "track1ID", "Music Track 1" },	// Music file 1
	{ "OriginalMusic/2Virus.mp3", "track2ID", "Music Track 2" },		// Music file 2
	{ "OriginalMusic/3BloodStream.wav", "track3ID", "Music Track 3" },	// Music file 3
	{ "OriginalMusic/4BloodLevel.mp3", "track4ID", "Music Track 4" }	// Music file 4
};

/*
	The constructor calls Mix_OpenAudio which is needed before other audio functions can be used
	The audio is initialised in the Game class init() function
*/
Audio::Audio() {
	Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2));						// Initialise the mixer API
}

/*
	The destructor shuts down and cleans up the mixer API
*/
Audio::~Audio() {
	Mix_CloseAudio();													// Shutdown and cleanup the mixer API
}

/* 
	This function loads the effects audio files
	A for loop is used to load each sound effect file
	based on the details stored in the arrSoundEffects array
	that stores the path to the file, song id, and error message to display

	An error message is displayed indicating the sound effect that failed to load
	if one of the effects does not load

	This function also loads the music from files in the OriginalMusic assets folder
	It adds the tracks to the listOfMusic vector
	Picks a random song to play
	and starts the music playing

	If the file fails to load it displays an identifying
	error message based stored in the arrMusic array

	An ID for each track is not necessary as the song is selected at random
	but, is stored in case a certain part of the game requires a certain theme song
*/
bool Audio::loadMediaAudio() {
	bool success = true;

	// Load the effects
	for (int i = 0; i < NUM_SOUND_FX; i++) {
		loadFX(arrSoundEffects[i][0], arrSoundEffects[i][1]); {
			std::cout << "Failed to load  " << arrSoundEffects[i][2] << "! SDL_mixer Error: " <<  Mix_GetError() << std::endl;
			success = false;
		}
	}

	// Load the music
	for (int i = 0; i < NUMBER_OF_SONGS; i++) {
		Mix_Music* pMusic = Mix_LoadMUS(arrMusic[i][0].c_str());								// Load music
		if (pMusic == NULL) {
			std::cout << "Failed to load music file " << arrMusic[i][2] << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
			success = false;
		}
		listOfMusic.push_back(pMusic);
	}

	currentSong = rand() % NUMBER_OF_SONGS;				// Play a random song on start up

	Mix_PlayMusic(listOfMusic[currentSong], -1);		// Play the currently selected song

	return success;
}

/*
	This function is used to load the sound effect
	The effect is then added to the m_sfxs map
	An error message is displayed if the chunk to be loaded is not present
*/
void Audio::loadFX(std::string fileName, std::string id) {
	Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
	if (pChunk == 0) {
		std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
	}

	m_sfxs[id] = pChunk;
}

/*
	This function is used to play sound FX when required in the game
	It uses the effect ID to load the effect from the m_sfxs map
	playFX is called from other classes using the s_pInstance singleton

	An unsuccessful attempt was made to set the audio panning based on the
	x coordinate trigger position of the effect
*/
void Audio::playFX(std::string id) {	
	if (!Mix_SetPanning(1, 255, 10)) {
		printf("Mix_SetPanning: %s\n", Mix_GetError());
		// no panning, is it ok?
	}

	Mix_PlayChannel(1, m_sfxs[id], 0);	
}

/*
	This function skips the current song that is playing forwards
	If the song is the current song is the last song in the array, 
	it plays the song at the start of the listOfMusic array
	It calls the identifyTrack() function to display the track details
	It outputs the current song name to the console
*/
void Audio::musicForwardSongName() {					// Pick next track on the list
	if (currentSong + 1 < listOfMusic.size())			// If the current song number (0 number start value) is less than the number of tracks on the list
		currentSong++;									// go to next track on list
	else
		currentSong = 0;								// or else go back to start of list

	Mix_PlayMusic(listOfMusic[currentSong], -1);
	identifyTrack(currentSong);
	
	/*
	// 2017/03/17 Moved to identifyTrack() function to be used by both musicForwardSongName() and musicBackSongName()
	if (currentSong == 0) std::cout << "current song: THE FIRST STEP by Jim O'Regan (and Joe O'Regan)" << std::endl;
	else if (currentSong == 1) std::cout << "Current Song: VIRUS by Joe O'Regan" << std::endl;
	else if (currentSong == 2) std::cout << "Current Song: BLOOD STREAM by Sean Horgan" << std::endl;
	else if (currentSong == 3) std::cout << "Current Song: BLOOD LEVEL by Joe O'Regan" << std::endl;

	return currentSong;	// 2017/03/17 Changed type from int to void, as song is identified in Audio and not Game class
	*/
}

/*
	This function skips the current song that is playing backwards
	If the song is the current song is the first song in the array, 
	it plays the song at the end of the listOfMusic array
	It calls the identifyTrack() function to display the track details
*/
void Audio::musicBackSongName() {						// Pick previous track on the list
	if (currentSong > 0)
		currentSong--;
	else
		currentSong = listOfMusic.size() - 1;

	Mix_PlayMusic(listOfMusic[currentSong], -1);
	identifyTrack(currentSong);
}

/*
	This function identifies the track name, the artist, and the song title for the games original soundtrack
*/
void Audio::identifyTrack(int songName) {
	if (songName == 0) {
		Game::Instance()->infoMessage("Artist: Jim O'Regan (Additional Drums and Bass Joe O'Regan)", 1);
		Game::Instance()->infoMessage("Song Title: The First Step", 2);
		std::cout << "current song: THE FIRST STEP by Jim O'Regan (and Joe O'Regan)" << std::endl;
	}
	else if (songName == 1) {
		Game::Instance()->infoMessage("Artist: Joe O'Regan", 1);
		Game::Instance()->infoMessage("Song Title: Virus", 2);
		std::cout << "Current Song: VIRUS by Joe O'Regan" << std::endl;
	}
	else if (songName == 2) {
		Game::Instance()->infoMessage("Artist: Sean Horgan", 1);
		Game::Instance()->infoMessage("Song Title: Blood Stream", 2);
		std::cout << "Current Song: BLOOD STREAM by Sean Horgan" << std::endl;
	}
	else if (songName == 3) {
		Game::Instance()->infoMessage("Artist: Joe O'Regan (Additional Guitar Solo Jim O'Regan", 1);
		Game::Instance()->infoMessage("Song Title: Blood Level", 2);
		std::cout << "Current Song: BLOOD LEVEL by Joe O'Regan" << std::endl;
	}
}



/* 
	This function starts the music playing using the randomly selected current song
	It displays a message indicating the music is playing
	It returns the currentSong as an integer to be identified

	If the music is playing and the function is called the music is paused
	If the music is paused it is then played
	2017/03/17 Moved pause functionality from Game class
*/
void Audio::playPauseMusic() {
	if (Mix_PlayingMusic() == 0) {							// If there is no music playing
		Mix_PlayMusic(listOfMusic[currentSong], -1);		// Function to play music
		Game::Instance()->infoMessage("Music Play");		// Display message indicating the music has started playing
		identifyTrack(currentSong);
	}
	else {													// If music is being played
		if (Mix_PausedMusic() == 1) {						// Check if the music is paused
			Mix_ResumeMusic();								// Resume music
			Game::Instance()->infoMessage("Music Play");
		}
		else {												// If the music is playing
			Mix_PauseMusic();								// Pause the music
			Game::Instance()->infoMessage("Music Paused");
		}
	}
}

/*
	This function stops the music playing
	It displays a message indicating the music is stopped
*/
void Audio::stopMusic() {
	Mix_HaltMusic();								// Function to stop music playing
	Game::Instance()->infoMessage("Music Stopped");	// Display message indicating the music has stopped playing
}

/*
	Clear the audio files from memory when done
*/
void Audio::destroy() {
	// Free the sound effects from memory
	//Free the music
	
	/*
	// Free the sound effects from memory
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
	
	m_sfxs.clear;			// Clear the sound effects map	

	//Free the music
	
	Mix_FreeMusic(gMusic1);	// Free music
	gMusic1 = NULL;			// Set to null
	Mix_FreeMusic(gMusic2);	// Free music
	gMusic2 = NULL;
	Mix_FreeMusic(gMusic3);	// Free music
	gMusic3 = NULL;
	Mix_FreeMusic(gMusic4);	// Free music
	gMusic4 = NULL;
	*/
}







/*	// 
	//return currentSong;	// 2017/03/17 Changed type from int to void, as song is identified in Audio and not Game class

	// Attempt to pan stereo audio based on x coordinate position of sound trigger (didn't work)

	Mix_SetPanning(0, 127, 127);
	Mix_SetPanning(1, 127, 1);
	Mix_SetPanning(2, 1, 254);

	Mix_PlayChannel(-1, m_sfxs[id], 0);
	Mix_PlayChannel(2, m_sfxs[id], 0);



// Previous method of loading effects

loadFX("Audio/Laser1.wav", "laser1FX");
loadFX("Audio/Laser1.wav", "laser1FX");
loadFX("Audio/Laser2.wav", "laser2FX");
loadFX("Audio/Swoosh1.wav", "ninja1FX");
loadFX("Audio/Swoosh2.wav", "ninja2FX");
loadFX("Audio/LaserEnemy.wav", "enemyLaserFX");
loadFX("Audio/explosion.wav", "explosionFX");
loadFX("Audio/Saw.wav", "sawFX");
loadFX("Audio/Splash.wav", "splashFX");
loadFX("Audio/Rip.wav", "ripFX");

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
// Load the Splash FX for destroyed blood cells
gSplashFX = Mix_LoadWAV("Audio/Splash.wav");																// Load sound effects
if (gSplashFX == NULL) {
printf("Failed to load Splash sound effect! SDL_mixer Error: %s\n", Mix_GetError());
}
// Load the Rip FX for splitting Virus Enemies
gRipFX = Mix_LoadWAV("Audio/Rip.wav");																// Load sound effects
if (gRipFX == NULL) {
printf("Failed to load Rip sound effect! SDL_mixer Error: %s\n", Mix_GetError());
}



// Older functions for skipping tracks forwards and backwards

void Audio::musicForward() {						// Pick next track on the list
	if (currentSong + 1 < listOfMusic.size())		// If the current song number (0 number start value) is less than the number of tracks on the list
	currentSong++;									// go to next track on list
	else
	currentSong = 0;								// or else go back to start of list

	Mix_PlayMusic(listOfMusic[currentSong], -1);
}

void Audio::musicBack() {							// Pick previous track on the list
	if (currentSong > 0)
		currentSong--;
	else
		currentSong = listOfMusic.size() - 1;

	Mix_PlayMusic(listOfMusic[currentSong], -1);
}

// Older functions to play specific sound effect

void Audio::laserFX_P1() {
	//if (player == 1) Mix_PlayChannel(-1, gLaserFX1, 0);
	Mix_PlayChannel(-1, gLaserFX1, 0);		// Different sound for each player laser
}

void Audio::laserFX_P2() {
	Mix_PlayChannel(-1, gLaserFX2, 0);		// Different sound for each player laser
}

void Audio::ninjaFX_P1() {
	Mix_PlayChannel(-1, gNinjaFX1, 0);		// Play ninja star swoosh effect (Different sound for player 1 and player 2)
}

void Audio::ninjaFX_P2() {
	Mix_PlayChannel(-1, gNinjaFX2, 0);		// Play ninja star swoosh effect
}

void Audio::sawFX() {
	Mix_PlayChannel(-1, gSawFX, 0);			// Play saw starting effect
}

void Audio::laserFX_Enemy() {
	Mix_PlayChannel(-1, gLaserEFX, 0);		// Play enemy laser effect
}

void Audio::explosionFX() {
	Mix_PlayChannel(-1, gExplosionFX, 0);	// Play sound on explosion
}

void Audio::splashFX() {
	Mix_PlayChannel(-1, gSplashFX, 0);		// Play sound on explosion
}
void Audio::ripFX() {
	Mix_PlayChannel(-1, gRipFX, 0);			// Play sound on explosion
}



This function loads the music from files in the OriginalMusic assets folder
It adds the tracks to the listOfMusic vector
Picks a random song to play
and starts the music playing

If the file fails to load it displays an identifying
error message based stored in the arrMusic array

An ID for each track is not necessary as the song is selected at random
but, is stored in case a certain part of the game requires a certain theme song

void Audio::music() {
	//Load music
	for (int i = 0; i < NUMBER_OF_SONGS; i++) {
		Mix_Music* pMusic = Mix_LoadMUS(arrMusic[i][0].c_str());								// Load music
		if (pMusic == NULL) {
			std::cout << "Failed to load music file " << arrMusic[i][2] << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
		}
		listOfMusic.push_back(pMusic);
	}

	currentSong = rand() % NUMBER_OF_SONGS;				// Play a random song on start up

	Mix_PlayMusic(listOfMusic[currentSong], -1);		// Play the currently selected song
														
	// Previous way of loading music files

	gMusic1 = Mix_LoadMUS("OriginalMusic/1TheFirstStep.mp3");									// Load music
	if (gMusic1 == NULL) {
	printf("Failed to load The First Step music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gMusic2 = Mix_LoadMUS("OriginalMusic/2Virus.mp3");											// Load music
	if (gMusic2 == NULL) {
	printf("Failed to load Virus music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gMusic3 = Mix_LoadMUS("OriginalMusic/3BloodStream.wav");									// Load music
	if (gMusic3 == NULL) {
	printf("Failed to load Blood Stream music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gMusic4 = Mix_LoadMUS("OriginalMusic/4BloodLevel.mp3");										// Load music
	if (gMusic4 == NULL) {
	printf("Failed to load Blood Level music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	// Add songs to vector
	listOfMusic.push_back(gMusic1);						// Add tracks to the music array
	listOfMusic.push_back(gMusic2);
	listOfMusic.push_back(gMusic3);
	listOfMusic.push_back(gMusic4);														
}


// 2017/03/17 Old playMusic() function, this returned an integer to identify the audio track in Game class
int Audio::playMusic() {
	Mix_PlayMusic(listOfMusic[currentSong], -1);	// Function to play music
	Game::Instance()->infoMessage("Music Play");	// Display message indicating the music has started playing
	identifyTrack(currentSong);

	return currentSong;								// Returns the current song as an integer, so it can be identified
}
*/