#pragma once
#ifndef ISoundListener_hpp
#define ISoundListener_hpp

#include <SDL2/SDL.h>
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2/SDL_thread.h"
#include <string>
using namespace std;

class ISoundListener {
public:
    // Virtual destructor
    virtual ~ISoundListener() {}
    // Plays the background music
    virtual void playBackground() = 0;
    // Pauses the music
    virtual void pauseBackground() = 0;
    // Plays the sound effect corresponding to the file name
    virtual Mix_Chunk * loadSFX(char * fileName) = 0;
    // Plays the sound effect corresponding to the file name
    virtual void playSFX(Mix_Chunk * file) = 0;
    // Plays the jump sound effect for the appropriate jump
    virtual void playJumpSFX(int command) = 0;
    
protected:
    // Static constants corresponding to various key events
    static const int FIRST_JUMP = 1;
    static const int SECOND_JUMP = 0;
};

#endif /* ISoundListener_hpp */


