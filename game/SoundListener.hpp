#pragma once
#ifndef SoundListener_h
#define SoundListener_h

#include <stdio.h>
#include <iostream>
#include "ISoundListener.hpp"
using namespace std;

class SoundListener : public ISoundListener {
public:
    // Constructor
    SoundListener();
    // Destructor
    ~SoundListener();
    // Plays the background music
    void playBackground();
    // Pauses the music
    void pauseBackground();
    // Loads the sound effect corresponding to the file name
    Mix_Chunk* loadSFX(char * fileName);
    // Plays the sound effect
    void playSFX(Mix_Chunk * mp3);
    // Plays the jump sound effect for the appropriate jump
    void playJumpSFX(int command);
};


#endif /* SoundListener_h */

