# Audio

## Overview (`Audio.h`, `Audio.cpp`)


```text
┌---------------------------------┐
|               Audio             |
├---------------------------------┤
| -Audio                          | - Constructor, initialise game audio
| -~Audio                         | - Destructor, close game audio
| -currentSong: int               | - Store the current song position in the array
| -listOfMusic: vector            | - List of music tracks stored in an array
| -m_sfxs: map                    | - Map of audio effects, accessed with an ID
| -s_pInstance: static Audio*     | - Audio singleton, 1 instance exists in game
├---------------------------------┤
| +Instance() : Audio*            | - Singleton access to class members & functions
| +loadMediaAudio() : bool        | - Loads music & effects media
| +destroy() : void               | - Use ID to load the effect from the effects map
| +loadFX() : void                | - Play the effect matching the ID passed
| +playFX() : void                | - Select next track in song array & identify song
| +musicForwardsSongName() : void | - Select previous track in song array & identify
| +musicBackSongName() : void     | - Identify current song being played
| +playPauseMusic() : void        | - Play music if stopped/paused or pause if playing
| +stopMusic() : void             | - Stop the current track from playing
| +identifyTrack() : void         | - Clear music and effects chunks audio from memory
└---------------------------------┘
```

The Audio class uses a Singleton pattern via `s_pInstance` to make certain only one audio manager exists throughout the lifecycle of the game.

* **Music Management**: Music tracks are stored in a `listOfMusic` vector. The integer `currentSong` tracks the active song index.
* **Sound Effects**: Sound effects (`Mix_Chunk*`) are stored within an `m_sfxs` map, allowing effects to be retrieved using an identifier string.

## Key Functions

* `Instance()`: Returns the static instance of the audio manager.
* `loadMediaAudio()`: Loads music from the `arrMusic` array into `listOfMusic` and sound effects from `arrSoundEffects` into `m_sfxs` using a loop.
* `loadFX()` / `playFX(std::string id)`: Uses an ID string to play the corresponding effect channel from the map.
* `musicForwardsSongName()` / `musicBackSongName()`: Cycles through the music tracks forwards or backwards and calls `identifyTrack()` to display the track title and artist on screen.
* `playPauseMusic()`: Toggles between playing and pausing the music track using `Mix_PausedMusic()`, `Mix_ResumeMusic()`, and `Mix_PauseMusic()`, outputting a notification message.
* `stopMusic()`: Halts music playback using `Mix_HaltMusic()`.
* `destroy()`: Clears the sound effect map and music vector from memory.
