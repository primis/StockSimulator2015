#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT= 480;

SDL_Window  *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;


bool init()
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO)>0) {
        printf("SDL ERRORL %s\n",SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("Stock Simulator 2015", SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            printf("Window Could not be created! SDL_ERROR: %s\n",SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

