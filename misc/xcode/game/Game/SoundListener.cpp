#include "SoundListener.hpp"

Mix_Music * background;
Mix_Chunk * firstJump;
Mix_Chunk * secondJump;

SoundListener::SoundListener() {
    // Open the audio mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        cout << Mix_GetError() << endl;
    else {
        cout << "Audio mixer opened" << endl;
    }
    
    background = Mix_LoadMUS("assets/audio/theme-song.wav");
    if(background == NULL) {
        throw invalid_argument("Background music file not loaded.");
    }
    
    firstJump = loadSFX("assets/audio/jump1.mp3");
    secondJump = loadSFX("assets/audio/jump2.mp3");
}

SoundListener::~SoundListener() {
    // Clean up pointers
    Mix_FreeChunk(firstJump);
    Mix_FreeChunk(secondJump);
    Mix_FreeMusic(background);
    firstJump = nullptr;
    secondJump = nullptr;
    background = nullptr;
    
    Mix_Quit();
}

void SoundListener::playBackground(){
    Mix_PlayMusic(background, -1);
}

void SoundListener::pauseBackground() {
    if(Mix_PausedMusic()){
        Mix_ResumeMusic();
    }
    else {
        Mix_PauseMusic();
    }
}

Mix_Chunk * SoundListener::loadSFX(char * fileName){
    Mix_Chunk * result;
    result = Mix_LoadWAV(fileName);
    if(result == NULL) {
        throw invalid_argument("File not loaded.");
    }
    return result;
}

void SoundListener::playSFX(Mix_Chunk * mp3) {
    Mix_PlayChannel(-1, mp3, 0);
}

void SoundListener::playJumpSFX(int command){
    if(command == 1)
        playSFX(firstJump);
    if(command == 0)
        playSFX(secondJump);
}



