#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "sim.h"
entity *broker;
background *bg;
entity *bullet;
Mix_Music *bgm;

bool loadMusic()
{
    bgm      = NULL;
    // Init SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL MIXER COULD NOT PLAY!\n");
        return false;
    }
    bgm = Mix_LoadMUS("media/BGM.wav");
    if(bgm == NULL)
    {
        printf("Failed to load BGM.wav\n");
    }
    return true;
}

bool loadMedia()
{
    bool success = true;
	broker = new entity;
    bg = new background;
	bullet = new entity;
	bullet->setBitmap("media/circle.bmp");
	bullet->setSize(16,16);
    loadMusic();
    return success;
}


