#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Surface *broker = NULL;

bool loadMedia()
{
    bool success = true;
    broker  = SDL_LoadBMP("media/broker.bmp");
    if(broker == NULL) {
        printf("Unable to find \"broker.bmp\"");
        success = false;
    }
    return success;
}
